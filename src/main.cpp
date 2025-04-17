#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include <vector>
#include "enemy.h"
#include "level.h"

//textures
//sf::Texture textureAvain("textures/avain.png");
sf::Texture texturePelaaja("textures/pelaaja.png");
sf::Texture texturePalikka("textures/palikka.png");
sf::Texture textureEnemy("textures/hirvio.png");

//sprites
//sf::Sprite spriteAvain(textureAvain);

sf::Sprite spritePelaaja(texturePelaaja);

std::vector<sf::Sprite*> spritePalikkat;
std::vector<Enemy*> enemies;
std::vector<sf::Sprite*> spriteEnemies;

//int level[] = {
//1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
//1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,
//1,0,1,1,0,1,1,1,0,1,1,0,1,0,1,0,1,0,0,1,
//1,0,1,0,0,0,0,1,0,0,1,0,1,0,1,0,1,1,0,1,
//1,0,1,0,1,1,0,1,0,1,1,0,0,0,0,0,0,0,0,1,
//1,0,0,0,1,1,0,1,0,0,1,0,1,1,0,1,1,1,0,1,
//1,0,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,
//1,0,1,1,1,1,1,1,0,0,1,1,1,1,1,0,1,0,1,1,
//1,0,0,0,0,0,0,1,1,0,1,0,0,0,1,1,1,0,1,1,
//1,0,1,0,1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,1,
//1,0,1,0,0,0,0,1,1,0,0,0,1,0,1,1,1,1,1,1,
//1,0,1,0,1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,1,
//1,0,1,0,1,1,1,1,1,0,1,0,1,0,1,1,1,1,0,1,
//1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,
//1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
//
//};

//settings
float playerSpeed = 1;

//gamestate
float playerXPosition;
float playerYPosition;

void SpawnEnemy() {
    Enemy* enemy = new Enemy();
    enemies.push_back(enemy);
    enemy->xPosition = 18*32;
    enemy->yPosition = 1*32;

    sf::Sprite* sprite = new sf::Sprite(textureEnemy);
    spriteEnemies.push_back(sprite);

    enemy->spawned = true;
}

bool IsBlocked(int x, int y) {
    
    int i = x + y * 20;
    if (level[i] == 1) {
        return true;
    }
    else {
        return false;
    }
}

void MovePlayer() {

    float verticalInput = 0.0;
    float horizontalInput = 0.0;

    if (GetAsyncKeyState('W') & 0x8000) {
        verticalInput -= 1.0 * playerSpeed;
    }

    if (GetAsyncKeyState('S') & 0x8000)
    {
        verticalInput += 1.0 * playerSpeed;
    }

    if (GetAsyncKeyState('D') & 0x8000) {
        horizontalInput += 1.0 * playerSpeed;
    }

    if (GetAsyncKeyState('A') & 0x8000)
    {
        horizontalInput -= 1.0 * playerSpeed;
    }

    float newPlayerX = (playerXPosition + horizontalInput)/32;
    float newPlayerY = (playerYPosition + verticalInput)/32;

    if (!IsBlocked(static_cast<int>(round(newPlayerX)), static_cast<int>(round(newPlayerY)))) {
        playerXPosition = playerXPosition + horizontalInput;
        playerYPosition = playerYPosition + verticalInput;

    }
    
    
}

void InitializeLevel() {

    int i = 0;
    for (size_t y = 0; y < 15; y++)
    {
        for (size_t x = 0; x < 20; x++)
        {
            if (level[i] == 1) {
                sf::Sprite* sprite = new sf::Sprite(texturePalikka);
                spritePalikkat.push_back(sprite);
                sf::Vector2f blockPosition(x * 32, y * 32);
                sprite->setPosition(blockPosition);
            }

            i++;
        }
    }

    std::cout << "Level initialization done! " << sizeof(spritePalikkat) << "\n";
}

int main()
{

    auto window = sf::RenderWindow(sf::VideoMode({800u, 600u}), "CMake SFML Project");
    sf::Window* pWindow = &window;
    window.setFramerateLimit(144);
    
    InitializeLevel();

    SpawnEnemy();

    playerXPosition = 1*32;
    playerYPosition = 1*32;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear();

        MovePlayer();

        for (size_t i = 0; i < enemies.size(); i++)
        {
            enemies[i]->Update();
        }

        //draw level
        for (size_t i = 0; i < spritePalikkat.size(); i++)
        {
            window.draw(*spritePalikkat[i]);
        }

        //draw player
        sf::Vector2f playerPosition(playerXPosition, playerYPosition);
        spritePelaaja.setPosition(playerPosition);
        window.draw(spritePelaaja);

        //draw enemies
        for (size_t i = 0; i < spriteEnemies.size(); i++)
        {
            sf::Vector2f position(enemies[i]->xPosition, enemies[i]->yPosition);
            spriteEnemies[i]->setPosition(position);
            window.draw(*spriteEnemies[i]);
        }

        window.display();
    }
}
