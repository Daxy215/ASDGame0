#include <iostream>
#include "Soldier.h"

void Soldier::EntityLogic(double Deltatime)
{
	Entity::EntityLogic(Deltatime);

	//If the soldier has an effect
	if (currentEffect != nullptr) {
		if (currentEffect->duration < effectDuration) {
			effectDuration += Deltatime;

			currentEffect->apply(this);
		}
	}

	//unit vector calculations can be put somewhere else
	//is in the entity class now
	if (DistanceTo(Target)<Target->size+size)
	{
		//attack
		if (CountdownToNextAttack<0)
		{
			AttackEntity(Target);
			CountdownToNextAttack = AttackDelay;
		}
		else
		{
			CountdownToNextAttack -= Deltatime;
		}
	}
	else
	{
		//move	
		Loc=(Loc + FindLookAtVector(Target) *(float)Deltatime*Speed);
	}
}

Soldier::Soldier(std::string inName, sf::Vector2f SpawnLocation, Entity* inTarget) : Entity(inName) {
	Target = inTarget;
	Loc = SpawnLocation;

	Soldier* soldier = getLoaderManager().getSoldier(inName);

	if(soldier == nullptr) {
		std::cout << "[ERROR] Couldn't find a soldier with the name of: " << inName << " - Check the json file" << std::endl;

		return;
	}

	Health = soldier->Health;
	Attack = soldier->Attack;
	size = soldier->size;
	AttackDelay = soldier->AttackDelay;
	Speed = soldier->Speed;

	Components.push_back(new Component(inName));
}

Soldier::Soldier(std::string name, int health, int attack, int size, float attackDelay, int speed) : Entity(name) {
	Health = health;
	Attack = attack;
	this->size = size;
	AttackDelay = attackDelay;
	Speed = speed;
}

void Soldier::setCurrentEffect(Effect* effect) {
	this->currentEffect = effect;
	this->effectDuration = 0;
}

Soldier::~Soldier()
{
	Entity::StaticEntities.push_back(new DecayEntity(Name+"Corpse",2,Loc));

}
