#include "TextureManager.h"

// redeclaring the varaible so the cpp knows it exist used for static variables
unordered_map<string, sf::Texture> TextureManager::textures;

void TextureManager::LoadTexture(string fileName)
{
	string path = "images/";
	path += fileName + ".png";

	textures[fileName].loadFromFile(path);
}

sf::Texture& TextureManager::GetTexture(string textureName)
{
	// if not found then create one
	if (textures.find(textureName) == textures.end()) {
		LoadTexture(textureName);
	}

	return textures[textureName];
}

void TextureManager::Clear()
{
	textures.clear(); //get rid of all stored objects
}
