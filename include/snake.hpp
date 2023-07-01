#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <vector>

enum class Direction {
    UP, DOWN, LEFT, RIGHT
};

class Snake {
public:
    Snake(sf::Texture& atlas);

    void add_length(sf::Texture& atlas);
    void move();
    void draw(sf::RenderTarget& window);

    Direction direction;
    sf::Vector2f prev_end_pos;
    std::vector<sf::Sprite> snake;

    bool changed_direction;
    bool die;
};