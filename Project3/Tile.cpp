#include "Tile.h"

Tile::Tile()
{
}

Tile::Tile(int x, int y)
{
	xPos = x;
	yPos = y;

	revealed.setPosition(xPos,yPos);
	hidden.setPosition(xPos, yPos);
	numberMine.setPosition(xPos, yPos);
	flagTexture.setPosition(xPos, yPos);

	revealed.setTexture(TextureManager::GetTexture("tile_revealed"));
	hidden.setTexture(TextureManager::GetTexture("tile_hidden"));
	flagTexture.setTexture(TextureManager::GetTexture("flag"));

	//flagTexture.setColor(sf::Color(255, 255, 255, 0));

	flag = false;
	mine = false;
	pressed = false;
	reveal = false;
	numClose = 0;
}

int Tile::getX()
{
	return xPos;
}

int Tile::getY()
{
	return yPos;
}

void Tile::setPosition(int x, int y)
{
	xPos = x;
	yPos = y;
}

void Tile::setPressed(bool tof)
{
	pressed = tof;
}

bool Tile::getPressed()
{
	return pressed;
}

void Tile::setNum(int num)
{
	numClose = num;
}

int Tile::getNum()
{
	return numClose;
}

void Tile::setFlag(bool tof)
{
	flag = tof;
}

bool Tile::getFlag()
{
	return flag;
}

void Tile::setMine(bool tof)
{
	mine = tof;
}

bool Tile::getMine()
{
	return mine;
}

bool Tile::getReveal()
{
	return reveal;
}

void Tile::flipReveal()
{
	reveal = !reveal;
}

sf::Sprite Tile::getSprite()
{
	if (flag) {
		return flagTexture;
	}
		else if (!pressed) {
			return hidden;
		}
		else if (mine && pressed) {
			numberMine.setTexture(TextureManager::GetTexture("mine"));
			return numberMine;
		}
		else if (numClose == 1 && pressed) {
			numberMine.setTexture(TextureManager::GetTexture("number_1"));
			return numberMine;
		}
		else if (numClose == 2 && pressed) {
			numberMine.setTexture(TextureManager::GetTexture("number_2"));
			return numberMine;
		}
		else if (numClose == 3 && pressed) {
			numberMine.setTexture(TextureManager::GetTexture("number_3"));
			return numberMine;
		}
		else if (numClose == 4 && pressed) {
			numberMine.setTexture(TextureManager::GetTexture("number_4"));
			return numberMine;
		}
		else if (numClose == 5 && pressed) {
			numberMine.setTexture(TextureManager::GetTexture("number_5"));
			return numberMine;
		}
		else if (numClose == 6 && pressed) {
			numberMine.setTexture(TextureManager::GetTexture("number_6"));
			return numberMine;
		}
		else if (numClose == 7 && pressed) {
			numberMine.setTexture(TextureManager::GetTexture("number_7"));
			return numberMine;
		}
		else if (numClose == 8 && pressed) {
			numberMine.setTexture(TextureManager::GetTexture("number_8"));
			return numberMine;
		}
		else
			return revealed;
	
}

void Tile::setReveal(bool tof)
{
	reveal = tof;
}

bool Tile::flipTile()
{
	return pressed = !pressed;
}

bool Tile::flipFlag()
{
	return flag = !flag;
}

sf::Sprite Tile::revealAllSprite() {
	if (reveal) {
		if (mine) {
			numberMine.setTexture(TextureManager::GetTexture("mine"));
			return numberMine;
		}
		else
			return getSprite();
	}
	else
		return getSprite();
}


