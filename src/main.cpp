#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>

enum class Direction {
    UP, DOWN, LEFT, RIGHT
};

int main() {
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(sf::Vector2<unsigned int>(640, 640)), "SFML");
    window.setVerticalSyncEnabled(true);

    sf::Texture atlas;
    atlas.loadFromFile("assets/snake.png");

    sf::Sprite apple(atlas, sf::IntRect({0, 0}, {16, 16}));
    apple.scale({2.0f, 2.0f});

    sf::Sprite head(atlas, sf::IntRect({16, 0}, {16, 16}));
    head.scale({2.0f, 2.0f});

    sf::Sprite board(atlas, sf::IntRect({0, 16}, {10, 10}));
    board.scale({32.0f, 32.0f});
    

    Direction desired_direction = Direction::RIGHT;
    Direction direction = Direction::RIGHT;
    bool changing_direction = false;

    float speed = 1.0f;

    sf::Vector2f position = {9.0f * 32.0f, 9.0f * 32.0f};
    sf::Vector2f apple_position = {13.0f * 32.0f, 9.0f * 32.0f};

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch(event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.scancode == sf::Keyboard::Scan::Escape) window.close();
                    if ((event.key.scancode == sf::Keyboard::Scan::W || event.key.scancode == sf::Keyboard::Scan::Up) && direction != Direction::DOWN && !changing_direction) {
                        changing_direction = true;
                        desired_direction = Direction::UP;
                    }
                    if ((event.key.scancode == sf::Keyboard::Scan::S || event.key.scancode == sf::Keyboard::Scan::Down) && direction != Direction::UP && !changing_direction) {
                        changing_direction = true;
                        desired_direction = Direction::DOWN;
                    }
                    if ((event.key.scancode == sf::Keyboard::Scan::A || event.key.scancode == sf::Keyboard::Scan::Left) && direction != Direction::RIGHT && !changing_direction) {
                        changing_direction = true;
                        desired_direction = Direction::LEFT;
                    }
                    if ((event.key.scancode == sf::Keyboard::Scan::D || event.key.scancode == sf::Keyboard::Scan::Right) && direction != Direction::LEFT && !changing_direction) {
                        changing_direction = true;
                        desired_direction = Direction::RIGHT;
                    }
                    break;
            }
        }

        // Keep the snake aligned with the grid
        if ((int)position.x % 32 == 0 && (int)position.y % 32 == 0) {
            direction = desired_direction;
            changing_direction = false;
        }

        // If the snake is outside of the boundaries, die
        if ((position.x < 0 || position.x > 608) || (position.y < 0 || position.y > 608)) window.close();
        
        switch (direction) {
            case Direction::UP:
                position += {0.0f, -2.0f * speed};
                break;
            case Direction::DOWN:
                position += {0.0f, 2.0f * speed};
                break;
            case Direction::LEFT:
                position += {-2.0f * speed, 0.0f};
                break;
            case Direction::RIGHT:
                position += {2.0f * speed, 0.0f};
                break;
        }

        window.clear(sf::Color(200, 200, 255));

        // Draw the background
        board.setPosition({0, 0});
        window.draw(board);
        board.setPosition({320, 0});
        window.draw(board);
        board.setPosition({320, 320});
        window.draw(board);
        board.setPosition({0, 320});
        window.draw(board);

        apple.setPosition(apple_position);
        window.draw(apple);
        head.setPosition(position);
        window.draw(head);
    
        window.display();

    }
}