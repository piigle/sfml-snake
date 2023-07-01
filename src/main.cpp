#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>
#include <cmath>

#include "snake.hpp"

int main() {
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(sf::Vector2<unsigned int>(640, 640)), "Snake");
    window.setVerticalSyncEnabled(true);

    sf::Texture atlas;
    atlas.loadFromFile("assets/atlas.png");

    sf::Sprite apple(atlas, sf::IntRect({0, 0}, {16, 16}));
    apple.scale({2.0f, 2.0f});
    apple.setPosition({13.0f * 32.0f, 9.0f * 32.0f});

    sf::Sprite S(atlas, sf::IntRect({48, 0}, {16, 16}));
    S.setOrigin({8.0f, 8.0f});
    S.setScale({4.0f, 4.0f});
    S.setPosition({6.0f * 32.0f,  4.0f * 32.0f});
    sf::Sprite N(atlas, sf::IntRect({64, 0}, {16, 16}));
    N.setOrigin({8.0f, 8.0f});
    N.setScale({4.0f, 4.0f});
    N.setPosition({8.0f * 32.0f,  4.0f * 32.0f});
    sf::Sprite A(atlas, sf::IntRect({80, 0}, {16, 16}));
    A.setOrigin({8.0f, 8.0f});
    A.setScale({4.0f, 4.0f});
    A.setPosition({10.0f * 32.0f,  4.0f * 32.0f});
    sf::Sprite K(atlas, sf::IntRect({96, 0}, {16, 16}));
    K.setOrigin({8.0f, 8.0f});
    K.setScale({4.0f, 4.0f});
    K.setPosition({12.0f * 32.0f,  4.0f * 32.0f});
    sf::Sprite E(atlas, sf::IntRect({112, 0}, {16, 16}));
    E.setOrigin({8.0f, 8.0f});
    E.setScale({4.0f, 4.0f});
    E.setPosition({14.0f * 32.0f,  4.0f * 32.0f});

    sf::Sprite play_button(atlas, sf::IntRect({16, 16}, {32, 16}));
    play_button.setOrigin({16.0f, 8.0f});
    play_button.setPosition({10.0f * 32.0f, 8.0f * 32.0f});
    play_button.scale({4.0f, 4.0f});
    
    sf::Sprite exit_button(atlas, sf::IntRect({0, 32}, {32, 16}));
    exit_button.setOrigin({16.0f, 8.0f});
    exit_button.setPosition({10.0f * 32.0f, 12.0f * 32.0f});
    exit_button.scale({4.0f, 4.0f});

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

    bool main_menu = true;
    bool play_button_selected = true; // For Controller

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch(event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (!sf::Joystick::isConnected(0) && !main_menu) {
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

        // Draw the background
        window.clear(sf::Color(200, 200, 255));
        board.setPosition({0, 0});
        window.draw(board);
        board.setPosition({320, 0});
        window.draw(board);
        board.setPosition({320, 320});
        window.draw(board);
        board.setPosition({0, 320});
        window.draw(board);

        if (main_menu) { 
            if (sf::Joystick::isConnected(0)) { // Controller
                if ((sf::Joystick::getAxisPosition(0, sf::Joystick::Y) <= -70.0f) && !play_button_selected) {
                    play_button_selected = true;
                }
                if ((sf::Joystick::getAxisPosition(0, sf::Joystick::Y) >= 70.0f) && play_button_selected) {
                    play_button_selected = false;
                }

                if (play_button_selected) {
                    play_button.setScale({4.4f, 4.4f});
                    exit_button.setScale({4.0f, 4.0f});
                    if (sf::Joystick::isButtonPressed(0, 0)) main_menu = false;
                } else {
                    play_button.setScale({4.0f, 4.0f});
                    exit_button.setScale({4.4f, 4.4f});
                    if (sf::Joystick::isButtonPressed(0, 0)) window.close();
                }
            } else { // Mouse
                sf::Vector2i pos = sf::Mouse::getPosition(window);
                if (play_button.getGlobalBounds().contains({static_cast<int>(pos.x), static_cast<int>(pos.y)})) {
                    play_button.setScale({4.4f, 4.4f});
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        main_menu = false;
                    }
                } else {play_button.setScale({4.0f, 4.0f});}

                if (exit_button.getGlobalBounds().contains({static_cast<int>(pos.x), static_cast<int>(pos.y)})) {
                    exit_button.setScale({4.4f, 4.4f});
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        window.close();
                    }
                } else {exit_button.setScale({4.0f, 4.0f});}
            }

            S.setPosition({6.0f * 32.0f, 8.0f * (float)std::sin(0.005f * clock.getElapsedTime().asMilliseconds()) + 4.0f * 32.0f});
            N.setPosition({8.0f * 32.0f, 8.0f * (float)std::sin(0.005f * clock.getElapsedTime().asMilliseconds() + 2.0f) + 4.0f * 32.0f});
            A.setPosition({10.0f * 32.0f, 8.0f * (float)std::sin(0.005f * clock.getElapsedTime().asMilliseconds() + 4.0f) + 4.0f * 32.0f});
            K.setPosition({12.0f * 32.0f, 8.0f * (float)std::sin(0.005f * clock.getElapsedTime().asMilliseconds() + 6.0f) + 4.0f * 32.0f});
            E.setPosition({14.0f * 32.0f, 8.0f * (float)std::sin(0.005f * clock.getElapsedTime().asMilliseconds() + 8.0f) + 4.0f * 32.0f});
            

            // Title Screen
            window.draw(S);
            window.draw(N);
            window.draw(A);
            window.draw(K);
            window.draw(E);

            // Buttons
            window.draw(play_button);
            window.draw(exit_button);
        } else {
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

            if (snake.die == true) {

                apple.setPosition({13.0f * 32.0f, 9.0f * 32.0f});
                snake = Snake(atlas);

                main_menu = true;
            }

            window.draw(apple);
            snake.draw(window);
        }
    
        window.display();

    }
}