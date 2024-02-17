#pragma once
#include <vector>
#include "SFML/Graphics.hpp"
#include "SpriteSheet.h"
#include <list>

class SpriteManager
{
public:
    SpriteManager(const char* filePath);
    std::list<std::pair<std::string, SpriteSheet>> spriteList;

    sf::Sprite* GetSprite(std::string spriteSheetID, int spriteIndex);
};