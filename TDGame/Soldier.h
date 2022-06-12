#pragma once
#include "Entity.h"
#include "DecayEntity.h"
#include "LoaderManager.h"

class Soldier :
    public Entity
{
    
    float Speed = 100;
public:
    void EntityLogic(double DeltaTime);
    Soldier(std::string inName, sf::Vector2f SpawnLocation, Entity* inTarget);
    Soldier(std::string name, int health, int attack, int size, float attackDelay, int speed);
    void setCurrentEffect(Effect* effect);
    Effect* currentEffect;
    int effectDuration;
    Entity* Target;

    ~Soldier();  
};

