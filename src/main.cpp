#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>

enum class Direction {
    UP, DOWN, LEFT, RIGHT
};

class Snake {
public:
    Snake(sf::Texture& atlas) : die(false), direction(Direction::RIGHT), changed_direction(false) {
        sf::Sprite head(atlas, sf::IntRect({16, 0}, {16, 16}));
        head.scale({2.0f, 2.0f});
        head.setPosition({9.0f * 32.0f, 9.0f * 32.0f});

        sf::Sprite tail(atlas, sf::IntRect({32, 0}, {16, 16}));
        tail.scale({2.0f, 2.0f});
        tail.setPosition({8.0f * 32.0f, 9.0f * 32.0f});
        prev_end_pos = {7.0f * 32.0f, 9.0f * 32.0f};

        snake.push_back(head);
        snake.push_back(tail);
    }

    void add_length(sf::Texture& atlas) {
        sf::Sprite new_segment(atlas, sf::IntRect({32, 0}, {16, 16}));
        new_segment.scale({2.0f, 2.0f});
        new_segment.setPosition(prev_end_pos);

        snake.push_back(new_segment);
    }

    void move() {
        for (int i = snake.size()-1; i >= 0; i--) {
            if (i == snake.size()-1) prev_end_pos = snake[i].getPosition();

            if (i == 0) {
                switch (direction) {
                    case Direction::UP:
                        snake[i].move({0.0f, -32.0f});
                        break;
                    case Direction::DOWN:
                        snake[i].move({0.0f, 32.0f});
                        break;
                    case Direction::LEFT:
                        snake[i].move({-32.0f, 0.0f});
                        break;
                    case Direction::RIGHT:
                        snake[i].move({32.0f, 0.0f});
                        break;
                }

                // Die
                if ((snake[i].getPosition().x < 0 || snake[i].getPosition().x > 608) || (snake[i].getPosition().y < 0 || snake[i].getPosition().y > 608)) {
                    die = true;
                }
            } else {
                snake[i].setPosition(snake[i-1].getPosition());
            }
        }
        changed_direction = false;
    }

    void draw(sf::RenderWindow& window) {
        for (sf::Sprite spr : snake) {
            window.draw(spr);
        }
    }

    Direction direction;
    sf::Vector2f prev_end_pos;
    std::vector<sf::Sprite> snake;

    bool changed_direction;
    bool die;
};

int main() {
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(sf::Vector2<unsigned int>(640, 640)), "Snake: an SFML game by Thomas McConkey");
    window.setVerticalSyncEnabled(true);

    sf::Texture atlas;
    atlas.loadFromFile("assets/atlas.png");

    sf::Sprite apple(atlas, sf::IntRect({0, 0}, {16, 16}));
    apple.scale({2.0f, 2.0f});
    apple.setPosition({13.0f * 32.0f, 9.0f * 32.0f});

    sf::Sprite board(atlas, sf::IntRect({0, 16}, {10, 10}));
    board.scale({32.0f, 32.0f});

    Snake snake = Snake(atlas);

    sf::Clock clock;
    int timer = clock.getElapsedTime().asMilliseconds();
    int delay = 150;

    if (sf::Joystick::isConnected(0)) {
        std::cout << "Gamepad connected" << std::endl;
    } else {
        std::cout << "No gamepad connected, using keyboard input" << std::endl;
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch(event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (!sf::Joystick::isConnected(0)) {
                        if (event.key.scancode == sf::Keyboard::Scan::Escape) window.close();
                        if ((event.key.scancode == sf::Keyboard::Scan::W || event.key.scancode == sf::Keyboard::Scan::Up) && snake.direction != Direction::DOWN && !snake.changed_direction) {
                            snake.direction = Direction::UP;
                            snake.changed_direction = true;
                        }
                        if ((event.key.scancode == sf::Keyboard::Scan::S || event.key.scancode == sf::Keyboard::Scan::Down) && snake.direction != Direction::UP && !snake.changed_direction) {
                            snake.direction = Direction::DOWN;
                            snake.changed_direction = true;
                        }
                        if ((event.key.scancode == sf::Keyboard::Scan::A || event.key.scancode == sf::Keyboard::Scan::Left) && snake.direction != Direction::RIGHT && !snake.changed_direction) {
                            snake.direction = Direction::LEFT;
                            snake.changed_direction = true;
                        }
                        if ((event.key.scancode == sf::Keyboard::Scan::D || event.key.scancode == sf::Keyboard::Scan::Right) && snake.direction != Direction::LEFT && !snake.changed_direction) {
                            snake.direction = Direction::RIGHT;
                            snake.changed_direction = true;
                        }
                    }
                    break;
            }
        }

        if (sf::Joystick::isConnected(0)) {
            if ((sf::Joystick::getAxisPosition(0, sf::Joystick::Y) <= -70.0f) && snake.direction != Direction::DOWN && !snake.changed_direction) {
                snake.direction = Direction::UP;
                snake.changed_direction = true;
            }
            if ((sf::Joystick::getAxisPosition(0, sf::Joystick::Y) >= 70.0f) && snake.direction != Direction::UP && !snake.changed_direction) {
                snake.direction = Direction::DOWN;
                snake.changed_direction = true;
            }
            if ((sf::Joystick::getAxisPosition(0, sf::Joystick::X) <= -70.0f)  && snake.direction != Direction::RIGHT && !snake.changed_direction) {
                snake.direction = Direction::LEFT;
                snake.changed_direction = true;
            }
            if ((sf::Joystick::getAxisPosition(0, sf::Joystick::X) >= 70.0f ) && snake.direction != Direction::LEFT && !snake.changed_direction) {
                snake.direction = Direction::RIGHT;
                snake.changed_direction = true;
            }
        }


        if (clock.getElapsedTime().asMilliseconds() - timer > delay) {
            snake.move();
            timer = clock.getElapsedTime().asMilliseconds();
        }

        if (snake.snake[0].getGlobalBounds().findIntersection(apple.getGlobalBounds())) {
            snake.add_length(atlas);

            back:
                sf::Vector2f new_position = {(float)(rand() % 16) * 32.0f, (float)(rand() % 16) * 32.0f};
                apple.setPosition(new_position);

                for (int i = 1; i < snake.snake.size(); i++) {
                    if (snake.snake[i].getGlobalBounds().findIntersection(apple.getGlobalBounds())) {
                        goto back;
                    }
                }
        }

        for (int i = 1; i < snake.snake.size(); i++) {
            if (snake.snake[0].getGlobalBounds().findIntersection(snake.snake[i].getGlobalBounds()))
                snake.die = true;
        }

        if (snake.die == true) window.close();

        

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

        window.draw(apple);
        snake.draw(window);
    
        window.display();

    }
}