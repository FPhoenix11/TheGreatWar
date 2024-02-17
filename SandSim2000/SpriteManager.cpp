#include "SpriteManager.h"
#include <iostream>


SpriteManager::SpriteManager(const char* filePath)
{
	spriteList.push_back(std::make_pair("RedBaron", SpriteSheet(filePath, 3, 3)));
}

sf::Sprite* SpriteManager::GetSprite(std::string spriteSheetID, int spriteIndex)
{
	SpriteSheet currentSprite;
	
	auto it = std::find_if(spriteList.begin(), spriteList.end(), spriteSheetID) 
}

