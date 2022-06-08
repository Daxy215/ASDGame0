#include<iostream>
#include "Building.h"
#include "Soldier.h"

class LoaderManager {
public:
	/*
	* No clue how to use arrays in c++...
	* change it to an array - It's much faster.
	*/
	std::vector<Building*> buildings;
	std::vector<Soldier*> soldiers;
	
	void loadBuildings();
	void loadSoliders();
	Building* getBuilding(std::string name);
	Soldier* getSoldier(std::string name);
};

LoaderManager& getLoaderManager();