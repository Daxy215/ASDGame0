#pragma once
#include "Entity.h"
#include "DecayEntity.h"


static struct Effect {
	std::string type;
	int duration;

	Effect(std::string type, int duration) {
		this->type = type;
		this->duration = duration;
	}
	
	void apply(Entity* soldier) {

	}
	
};

static struct Fire : public Effect {
	Fire() : Effect("Fire", 2) {

	}


	

	void apply(Entity* soldier) {
		//soldier->Health -= 2;
		//std::cout << "Damaging.." << std::endl;
		soldier->Health -= 2;
		std::cout << "Damaging.." << std::endl;
	}
	
};


class Soldier :
    public Entity
{

    float Speed = 100;
public:
    void EntityLogic(double DeltaTime);
    Soldier(std::string inName, sf::Vector2f SpawnLocation, Entity* inTarget);
    Soldier(std::string name, int health, int attack, int size, float attackDelay, int speed);
    Effect* currentEffect;
    void setCurrentEffect(Effect* effect);
    int effectDuration;
    Entity* Target;


    ~Soldier();  




};
