#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
using std::unordered_map;
using std::string;

class TextureManager
{
	//only one texture map
	static void LoadTexture(string fileName);
	static unordered_map<string, sf::Texture> textures;

public:
	static sf::Texture& GetTexture(string textureName);
	static void Clear();
};

