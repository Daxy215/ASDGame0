#include<iostream>
#include "TownCentre.h"
#include "LoaderManager.h"

TownCentre::TownCentre() : Building(getLoaderManager().getBuilding("TowerCentre"), sf::Vector2f(0, 0)) {
	size = 150;
	Health = 100000;
	Components.push_back(new Component("TownCentre"));
}
