#include<iostream>
#include "Building.h"
#include "Soldier.h"

static struct Effect {
	std::string type;
	int duration;

	Effect(std::string type, int duration) {
		this->type = type;
		this->duration = duration;
	}

	void apply(Soldier* soldier) {

	}
};

static struct Fire : public Effect {
	Fire() : Effect("Fire", 2) {

	}

	void apply(Soldier * soldier) {
		soldier->Health -= 2;
		std::cout << "Damaging.." << std::endl;
	}
};

class LoaderManager {
public:
	/*
	* No clue how to use arrays in c++...
	* change it to an array - It's much faster.
	*/
	std::vector<Building*> buildings;
	std::vector<Soldier*> soldiers;
	std::vector<Effect*> effects {
		new Fire()
	};
	
	void loadBuildings();
	void loadSoliders();
	Building* getBuilding(std::string name);
	Soldier* getSoldier(std::string name);
	Effect* getEffects(std::string type);
};

LoaderManager& getLoaderManager();