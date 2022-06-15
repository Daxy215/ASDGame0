#pragma once


#include "HUD.h"
#include "StandardIO.h"
namespace MSWindow
{
#include <windows.h>
}





struct GameMap
{
	std::string Name;
	std::string Desc;
	std::string Source;
	sf::Texture Preview;
	int Difficulty;


	static std::vector<GameMap> MapData;
	static std::string ChosenMap;

};




void LoadMaps();


class MainMenu
{
	ConfigData config;
	sf::RenderWindow* window;
	VButton* StartButton;
	VButton* LoadButton;
	VButton* DiscordBbutton;
	VButton* ExitButton;


	std::vector<VButton*> ListOfMaps;


public:
	int MenuLoop();
	MainMenu();


	void ChooseMap();

};




