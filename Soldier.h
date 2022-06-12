#pragma once
#include "Entity.h"
#include "DecayEntity.h"


static struct Effect {
	std::string type;
	float duration;
	float delay;

	Effect(std::string type, float duration, float delay) {
		this->type = type;
		this->duration = duration;
		this->delay = delay;
	}
	
	virtual void apply(Entity* soldier) {

	}

	virtual void onFinish(Entity* soldier) {

	}
};

static struct Fire : public Effect {
	//Damage 2 every 0.2 seconds.
	Fire() : Effect("Fire", 0.5f, 0.25f) {

	}

	void apply(Entity* soldier) {
		//soldier->Health -= 2;
		std::cout << "Damaging.." << std::endl;
		soldier->Health -= 2;
	}
};


class Soldier :
    public Entity {
    float Speed = 100;
public:
    void EntityLogic(double DeltaTime);
    Soldier(std::string inName, sf::Vector2f SpawnLocation, Entity* inTarget);
    Soldier(std::string name, int health, int attack, int size, float attackDelay, int speed);
    Effect* currentEffect;
    void setCurrentEffect(Effect* effect);
    float effectDuration, effectDelay;
    Entity* Target;


    ~Soldier();
};
