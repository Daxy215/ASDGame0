#include <json/json.h>
#include <fstream>
#include "LoaderManager.h"
#include "GameData.h"

void LoaderManager::loadBuildings() {
	//Loading the data file.
	Json::Value cfg_root = "";
	std::ifstream cfgfile("Data/Buildings/buildings.json");

	//Reading it as json.
	cfgfile >> cfg_root;

	//const int buildingsSize = cfg_root.size();

	//std::cout << "[DEBUG] JSON: " << cfg_root << std::endl;
	//std::cout << "[DEBUG] BUILDINGS SIZE " << buildingsSize << std::endl;

	//Iterate throughout the buildings.
	for (Json::Value::const_iterator itr = cfg_root.begin(); itr != cfg_root.end(); itr++) {
		std::string buildingName = itr.name();

		//Setting values
		std::string componentName = cfg_root[buildingName]["ComponentName"].asString();
		std::string buildingType = cfg_root[buildingName]["BuildingType"].asString();
		std::string effectType = cfg_root[buildingName]["EffectType"].asString();
		int damage = cfg_root[buildingName]["Damage"].asInt();
		float speed = cfg_root[buildingName]["Speed"].asFloat();
		float timeExists = cfg_root[buildingName]["TimeExists"].asFloat();
		float timeGap = cfg_root[buildingName]["TimeGap"].asFloat();
		float attackDelay = cfg_root[buildingName]["AttackDelay"].asFloat();
		int health = cfg_root[buildingName]["Health"].asInt();
		int size = cfg_root[buildingName]["Size"].asInt();
		int range = cfg_root[buildingName]["Range"].asInt();
		int cost = cfg_root[buildingName]["Cost"].asInt();

		Building* b = new Building(buildingName, componentName, buildingType, effectType, damage, speed,
			timeExists, timeGap, attackDelay, health, size, range, cost);

		//Loading audios Compnent values
		for (Json::Value::const_iterator itr = cfg_root[buildingName]["Audios"].begin(); itr != cfg_root[buildingName]["Audios"].end(); itr++) {
			std::string audioValue = itr.name();

			b->AudioComponents.emplace(audioValue, new SoundComponent(cfg_root[buildingName]["Audios"][audioValue]["SoundComponent"].asString()));
		}

		for (Json::Value::const_iterator itr = cfg_root[buildingName]["Upgrades"].begin(); itr != cfg_root[buildingName]["Upgrades"].end(); itr++) {
			std::string upgradeName = itr.name();

			std::string componentName = cfg_root[buildingName]["Upgrades"][upgradeName]["ComponentName"].asString();
			std::string buildingType = cfg_root[buildingName]["Upgrades"][upgradeName]["BuildingType"].asString();
			std::string effectType = cfg_root[buildingName]["Upgrades"][upgradeName]["EffectType"].asString();
			int damage = cfg_root[buildingName]["Upgrades"][upgradeName]["Damage"].asInt();
			float speed = cfg_root[buildingName]["Upgrades"][upgradeName]["Speed"].asFloat();
			float timeExists = cfg_root[buildingName]["Upgrades"][upgradeName]["TimeExists"].asFloat();
			float timeGap = cfg_root[buildingName]["Upgrades"][upgradeName]["TimeGap"].asFloat();
			float attackDelay = cfg_root[buildingName]["Upgrades"][upgradeName]["AttackDelay"].asFloat();
			int health = cfg_root[buildingName]["Upgrades"][upgradeName]["Health"].asInt();
			int size = cfg_root[buildingName]["Upgrades"][upgradeName]["Size"].asInt();
			int range = cfg_root[buildingName]["Upgrades"][upgradeName]["Range"].asInt();
			int cost = cfg_root[buildingName]["Upgrades"][upgradeName]["Cost"].asInt();

			b->upgrades.push_back(new Building(buildingName, componentName, buildingType, effectType, damage, speed,
				timeExists, timeGap, attackDelay, health, size, range, cost));
		}

		//Adding a new building to the list
		buildings.push_back(b);
	}
}

void LoaderManager::loadSoliders() {
	//Loading the data file.
	Json::Value cfg_root = "";
	std::ifstream cfgfile("Data/SoldiersData.json");
	//Reading it as json.
	cfgfile >> cfg_root;

	for (Json::Value::const_iterator itr = cfg_root.begin(); itr != cfg_root.end(); itr++) {
		std::string soldierName = itr.name();

		int health = cfg_root[soldierName]["Health"].asInt();
		int attack = cfg_root[soldierName]["Attack"].asInt();
		int size = cfg_root[soldierName]["Size"].asInt();
		float attackDelay = cfg_root[soldierName]["AttackDelay"].asFloat();
		int speed = cfg_root[soldierName]["Speed"].asInt();

		soldiers.push_back(new Soldier(soldierName, health, attack, size, attackDelay, speed));
	}
}

void LoaderManager::loadWaves() {
	//Loading the data file.
	Json::Value cfg_root = "";
	std::ifstream cfgfile("Data/Waves/defualt.json");
	//Reading it as json.
	cfgfile >> cfg_root;

	for (Json::Value::const_iterator itr = cfg_root.begin(); itr != cfg_root.end(); itr++) {
		std::string waveName = itr.name();

		Wave* wave = new Wave(waveName);

		//Loop through all of the enemies in the waves
		for (Json::Value::const_iterator it = cfg_root[waveName]["Soldiers"].begin(); it != cfg_root[waveName]["Soldiers"].end(); it++) {
			std::string soldierName = it.name();

			Soldier* soldier = getSoldier(soldierName);

			if (soldier == nullptr) {
				std::cout << "[DEBUG] Couldn't find an enemy with the name of " << soldier << " inside wave with a name of " << waveName << std::endl;

				continue;
			}

			int amount = cfg_root[waveName]["Soldiers"][soldierName].asInt();

			for(int i = 0; i < amount; i++)
				wave->soldiers.push_back(soldier);
		}

		for (Json::Value::const_iterator its = cfg_root[waveName]["Conditions"].begin(); its != cfg_root[waveName]["Conditions"].end(); its++) {
			std::string condition = its.name();
			int amount = cfg_root[waveName]["Conditions"][condition].asInt();

			wave->conditions.push_back(new Condition(condition, amount));
		}

		waves.push_back(wave);
	}
}

Building* LoaderManager::getBuilding(std::string name) {
	for (int i = 0; i < buildings.size(); i++) {
		if (buildings[i]->Name == name) {
			return buildings[i];
		}
	}

	return nullptr;
}

Soldier* LoaderManager::getSoldier(std::string name) {
	for (int i = 0; i < soldiers.size(); i++) {
		if (soldiers[i]->Name == name) {
			return soldiers[i];
		}
	}

	return nullptr;
}

LoaderManager& getLoaderManager() {
	static LoaderManager manager;
	return manager;
}

Effect* LoaderManager::getEffects(std::string type) {
	for (int i = 0; i < effects.size(); i++)
		if (effects[i]->type == type)
			return effects[i];

	return nullptr;
}

std::vector<Wave*> LoaderManager::getWaves() {
	std::vector<Wave*> returnWaves;

	for (int i = 0; i < waves.size(); i++) {
		bool conditionsMet = true;

		for (int j = 0; j < waves[i]->conditions.size(); j++) {
			std::string condition = waves[i]->conditions[j]->name;
			int amount = waves[i]->conditions[j]->condition;

			//Check for condition
			if (condition == "Buildings") {
				if (GameData::Buildings.size() < amount) conditionsMet = false;
			}
			else if (condition == "Mines") {
				if (GameData::Mines.size() < amount) conditionsMet = false;
			} //else if (condition == "Gold") {
				//if (GameInstance::Gold < amount) conditionsMet = false;
			//} 
			else {
				conditionsMet = false;

				std::cout << "[DEBUG] Error couldn't find a condition with the name of " << condition << " inside a wave with the name of " << waves[i]->name << std::endl;
			}
		}

		//If all conditions we met, add it to the list.
		if (conditionsMet)
			returnWaves.push_back(waves[i]);
	}

	return returnWaves;
}
