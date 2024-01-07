#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "Coin.h"
#include "Potion.h"

class GameUI {
public:
    GameUI(sf::RenderWindow* window, int playerhealth, int scores);
    void setHealth(int health);
    int getScores();
    void setScores(int score);
    void addScores(int scores);
    void update(float deltaTime, sf::Vector2f playerPosition);
    void draw();
    void displayGameTime(sf::Clock clock);
    void displaySpeedPotionEffect();
    void activatePotion(float duration);

private:
    sf::RenderWindow* window;
    sf::Font font;
    sf::Text timeText;
    sf::Text scoresText;
    std::vector<sf::Texture> healthTextures;
    std::vector<sf::Sprite> healthSprites;
    Coin* coin;
    sf::Vector2f uiOffset;
    sf::Text potionTimerText;
    sf::Clock potionClock;
    bool isPotionActive = false;
    int playerHealth;
    int scores;

    void updateHealthSprite();
    void setHealthSprites();
    void setText();
    void setScoresDisplay(sf::Vector2f uiPosition);
    void updateScores();
};

