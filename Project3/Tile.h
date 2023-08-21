#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "TextureManager.h"

using namespace std;
class Tile
{
	int xPos;
	int yPos;
	int numClose;
	bool flag;
	bool mine;
	bool pressed;
	bool reveal;


	


public:
	sf::Sprite revealed;
	sf::Texture textReveal;
	sf::Sprite hidden;
	sf::Texture textHide;
	sf::Sprite numberMine;
	sf::Texture textNumMine;
	sf::Sprite flagTexture;
	sf::Texture textflagText;

	Tile();
	Tile(int x, int y);

	int getX();
	int getY();
	void setPosition(int x, int y);
	void setPressed(bool tof);
	bool getPressed();
	void setNum(int num);
	int getNum();
	void setFlag(bool tof);
	bool getFlag();
	void setMine(bool tof);
	bool getMine();
	void setReveal(bool tof);
	bool getReveal();
	void flipReveal();

	sf::Sprite getSprite();
	sf::Sprite revealAllSprite();

	bool flipTile();
	bool flipFlag();

};