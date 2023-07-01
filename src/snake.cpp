#include "snake.hpp"

Snake::Snake(sf::Texture& atlas) : die(false), direction(Direction::RIGHT), changed_direction(false) {
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

void Snake::add_length(sf::Texture& atlas) {
    sf::Sprite new_segment(atlas, sf::IntRect({32, 0}, {16, 16}));
    new_segment.scale({2.0f, 2.0f});
    new_segment.setPosition(prev_end_pos);

    snake.push_back(new_segment);
}

void Snake::move() {
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

void Snake::draw(sf::RenderTarget& window) {
    for (sf::Sprite spr : snake) {
        window.draw(spr);
    }
}