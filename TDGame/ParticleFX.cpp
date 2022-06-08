#include "ParticleFX.h"
#include <iostream>
#include <fstream>
#include <json/json.h>






void ParticleFX::Render(sf::RenderWindow* window, sf::Vector2f RenderLoc, double DeltaTime)
{

	int idx = 0;
	for (Shape* i : Shapes)
	{
		window->draw(*i->s);
		i->s->setPosition(i->s->getPosition()+(i->Velocity*(float)DeltaTime));
		i->RemainingTime -= DeltaTime;
		i->s->setScale(i->s->getScale()+i->s->getScale()*(float)DeltaTime*Template.DeltaSize);
		i->Velocity = (i->Velocity + i->Velocity * (float)DeltaTime*Template.DeltaVelocity);
		
		if (i->RemainingTime<=0)
		{
			
			delete i->s;
			delete i;
			Shapes.erase(Shapes.begin()+idx);
		}
		else
		{
			
			idx++;
		}
		
	}
	
	if (SpawnShapeTimeRemain<=0)
	{
		
		SpawnShapeTimeRemain = SpawnShapeTime + Utils::RandomFloatInRange(SpawnShapeTimeVariance);
	
		sf::Vector2f tVel;
		if (RandomVelocity)
		{
			tVel = sf::Vector2f(Utils::RandomFloatInRange(Velocity.x),Utils::RandomFloatInRange(Velocity.y));
		}
		else
		{
			tVel = Velocity;
		}
		Shapes.push_back(new Shape(Template.LifeTime, tVel));
		Shapes.back()->s = new sf::Sprite();
		Shapes.back()->s->setScale(sf::Vector2f(Template.Size,Template.Size));
		Shapes.back()->s->setColor(Template.Colour);
		Shapes.back()->s->setPosition(Loc+ sf::Vector2f(Utils::RandomFloatInRange(Template.LocVariance), Utils::RandomFloatInRange(Template.LocVariance)));
		Shapes.back()->s->setTexture(*Anim::Animations.at(Template.ShapeType)->GetDefaultFrame());
		Shapes.back()->s->setOrigin(sf::Vector2f(Shapes.back()->s->getLocalBounds().width/2,Shapes.back()->s->getLocalBounds().height/2));
		if (Template.RandomRotation)
		{
			Shapes.back()->s->setRotation(rand()%360);
		}
		
	}
	else
	{
		SpawnShapeTimeRemain -= DeltaTime;
	}

	Lifetime -= DeltaTime;
	PendingDelete = Lifetime < 0;



}

ParticleFX::ParticleFX(std::string name)
{


	Json::Value cfg_root = "";
	std::ifstream cfgfile("Data/Particles/"+name+".json");

	cfgfile >> cfg_root;



		Lifetime = cfg_root["lifetime"].asFloat();
		SpawnShapeTime = cfg_root["spawntime"].asFloat();
		SpawnShapeTimeVariance = cfg_root["spawnvariance"].asFloat();
		RandomVelocity = cfg_root["randomvelocity"].asBool();
		Velocity.x = cfg_root["xvelocity"].asFloat();
		Velocity.y = cfg_root["yvelocity"].asFloat();
		Template.ShapeType = cfg_root["texture"].asString();
		Template.LocVariance = cfg_root["locationvariance"].asFloat();
		Template.LifeTime = cfg_root["plifetime"].asFloat();
		Template.LifeTimeVariance = cfg_root["plifetimevariance"].asFloat();
		Template.Size = cfg_root["size"].asFloat();
		Template.DeltaSize = cfg_root["deltasize"].asFloat();
		Template.Colour.r = cfg_root["rcolour"].asFloat();
		Template.Colour.g = cfg_root["gcolour"].asFloat();
		Template.Colour.b = cfg_root["bcolour"].asFloat();
		Template.RandomRotation = cfg_root["randomrotation"].asBool();
		Template.DeltaVelocity = cfg_root["deltavelocity"].asFloat();
	





	SpawnShapeTimeRemain = 0;



	cfgfile.close();
}
