#pragma once
#include <vector>
#include "SFML/Graphics.hpp"
#include "SpriteSheet.h"
#include <list>

class SpriteManager
{
public:
    SpriteManager(const char* filePath);
    SpriteManager() {};
    std::list<std::pair<std::string, SpriteSheet>> spriteSheetList;

    sf::Sprite* GetSprite(std::string spriteSheetID, int spriteIndex);

    SpriteSheet& GetSpriteSheet(std::string spriteSheetID);
};