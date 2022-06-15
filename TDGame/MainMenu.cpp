#include "MainMenu.h"
#include <json/json.h>



std::vector<GameMap> GameMap::MapData;
std::string GameMap::ChosenMap;

int MainMenu::MenuLoop()
{
	sf::Event event;


	while (window->isOpen())
	{
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (StartButton->CallIfHovered())
				{
					window->close();
					ChooseMap();
					return 0;
				}
				if (LoadButton->CallIfHovered())
				{
					window->close();
					return 1;
				}
				if (ExitButton->CallIfHovered())
				{
					window->close();
					return -1;
				}
			}
		}

		window->clear();
		StartButton->Render(window);
		LoadButton->Render(window);
		ExitButton->Render(window);

		


		window->display();
	}

	return 0;
}

MainMenu::MainMenu()
{
	config = getConfiguration();
	//MSWindow::ShellExecute(0, 0, L"http://www.google.com", 0, 0, SW_SHOW);

	window = new sf::RenderWindow(sf::VideoMode(config.ScreenX, config.ScreenY), "TD Game", sf::Style::Fullscreen);
	StartButton = new VButton(sf::Vector2i(config.ScreenX/2-250,300),sf::Vector2i(config.ScreenX/2+250,500),"MainMenu/Start.png");
	LoadButton = new VButton(sf::Vector2i(config.ScreenX / 2 - 250, 600), sf::Vector2i(config.ScreenX / 2 + 250, 800), "MainMenu/Load.png");
	ExitButton = new VButton(sf::Vector2i(config.ScreenX / 2 - 250, 900), sf::Vector2i(config.ScreenX / 2 + 250, 1000), "MainMenu/Exit.png");
}

void LoadMaps()
{
	Json::Value cfg_root = "";
	std::ifstream cfgfile("Data/Maps/Maps.json");

	
	cfgfile >> cfg_root;


	for (Json::Value::const_iterator itr = cfg_root.begin(); itr != cfg_root.end(); itr++) 
	{
		
		GameMap::MapData.push_back(*new GameMap());
		GameMap::MapData.back().Name = itr.name();
		GameMap::MapData.back().Desc = cfg_root[GameMap::MapData.back().Name]["Description"].asString();
		GameMap::MapData.back().Difficulty = cfg_root[GameMap::MapData.back().Name]["Difficulty"].asInt();
		GameMap::MapData.back().Source = cfg_root[GameMap::MapData.back().Name]["Source"].asString();
		std::string PreviewSource = cfg_root[GameMap::MapData.back().Name]["Preview"].asString();
		GameMap::MapData.back().Preview.loadFromFile("Data/Maps/Previews/"+ PreviewSource);
	}



}



void MainMenu::ChooseMap()
{
	config = getConfiguration();

	window = new sf::RenderWindow(sf::VideoMode(config.ScreenX, config.ScreenY), "TD Game", sf::Style::Fullscreen);


	LoadMaps();
	std::vector<VButton*> MapButtons;

	int yLoc = 0;
	for(GameMap i: GameMap::MapData)
	{
		MapButtons.push_back(new VButton(sf::Vector2i(25,yLoc), sf::Vector2i(175,yLoc+50), "GenericButton.png", i.Name));
		yLoc += 55;
	}

	sf::Text Desc;
	Desc.setFont(*Button::GenericFont);
	Desc.setCharacterSize(18);
	Desc.setPosition(sf::Vector2f(200,125));

	int ChosenMapIdx = 0;


	sf::Sprite PreviewSprite;
	PreviewSprite.setPosition(400,400);


	VButton StartButtonMap(sf::Vector2i(config.ScreenX*0.9,config.ScreenY*0.9), sf::Vector2i(config.ScreenX * 0.95, config.ScreenY * 0.95),"GenericButton.png","Start");


	sf::Event event;

	while (window->isOpen())
	{
		window->clear();

		PreviewSprite.setTexture(GameMap::MapData.at(ChosenMapIdx).Preview);
		Desc.setString(GameMap::MapData.at(ChosenMapIdx).Desc);
		GameMap::ChosenMap = GameMap::MapData.at(ChosenMapIdx).Source;


		for(VButton* i: MapButtons)
		{
			i->Render(window);
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{

			int IdxTemp = 0;
			for (VButton* i: MapButtons)
			{
				if (i->CallIfHovered())
				{
					ChosenMapIdx = IdxTemp;
					break;
				}
				IdxTemp++;
			}
			if (StartButtonMap.CallIfHovered())
			{
				window->close();
				
				return;
			}

		}





		window->draw(Desc);
		window->draw(PreviewSprite);
		StartButtonMap.Render(window);

		window->display();
	}
}