#include "GameStateManager.h"

#define CELLSIZE 100

GameStateManager::GameStateManager(unsigned int numCells) {
    initializeBattlefieldVector(numCells);
}

void GameStateManager::initialiseQuadTree(unsigned int battlefieldSize)
{
    state.quadTree = new QuadTree(sf::IntRect(0, 0, battlefieldSize, battlefieldSize), 0);
    generateQuadTree((QuadTree*)state.quadTree);
    /*Sam the quad tree should be a member property of 
    the GameState and the GameStateManager should be 
    where it's initialised. */
}

void GameStateManager::generateQuadTree(QuadTree* root) {
    //TEMP: Lambda function to create a new random BattlefieldCell at (x, y)
    auto TEMP_RandomCell = [](int x, int y) {
        TerrainTile newTerr;
        newTerr.depth = rand() % 3;
        newTerr.facing = 0;
        newTerr.terrain = "default";

        BattlefieldCell newCell;
        newCell.x = x;
        newCell.y = y;
        newCell.terrain = newTerr;

        return newCell;
        };

    float size = root->quadRect.getSize().x / 2;
    if (size > CELLSIZE) {

        //Make internal nodes at half the size
        std::array<QuadTree*, 4> children;

        for (int i = 0; i < 4; i++) {

            children[i] = new QuadTree(
                sf::IntRect(
                    root->quadRect.getPosition().x + size * (i % 2),
                    root->quadRect.getPosition().y + size * ((int)(i > 1)),
                    size, size
                ), 
                root->depth + 1
            );

            generateQuadTree((QuadTree*)children[i]);
        }

        root->setChildren(children);
    } else {

        //This is the final level - make leaf nodes of size 100 and create a battlefield cell for each and give the leaf its iterator
        std::array<QuadTree*, 4> children;

        for (int i = 0; i < 4; i++) {
            int x = root->quadRect.getPosition().x + size * (i % 2);       //+size when i = 1 or 3
            int y = root->quadRect.getPosition().y + size * ((int)(i > 1)); //+size when i = 2 or 3  

            state.BattlefieldVector.push_back(TEMP_RandomCell(x / 100, y / 100 ));

            std::vector<BattlefieldCell>::iterator iter = std::prev(state.BattlefieldVector.end());

            children[i] = new QuadTreeLeaf(
                sf::IntRect(x, y, size, size), 
                root->depth + 1,
                iter
            );
        }

        root->setChildren(children);
    }
}

void GameStateManager::initializeBattlefieldVector(unsigned int numCells) 
{
    state.BattlefieldVector.resize(numCells);
    state.BattlefieldVector.clear();
    initialiseQuadTree(std::sqrt(numCells) * 100);
}

