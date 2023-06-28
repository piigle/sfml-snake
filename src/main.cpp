#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>

int main() {
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(sf::Vector2<unsigned int>(640, 640)), "SFML");
    window.setVerticalSyncEnabled(true);

    sf::Texture atlas;
    atlas.loadFromFile("assets/snake.png");

    sf::Sprite apple(atlas, sf::IntRect({0, 0}, {16, 16}));
    apple.scale({2.0f, 2.0f});

    sf::Sprite head(atlas, sf::IntRect({16, 0}, {16, 16}));
    head.scale({2.0f, 2.0f});

    sf::Sprite body(atlas, sf::IntRect({32, 0}, {16, 16}));
    body.scale({2.0f, 2.0f});
    
    int i = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) if (event.type == sf::Event::Closed) window.close();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            head.move({0.0f, -1.0f});
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            head.move({-1.0f, 0.0f});
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            head.move({0.0f, 1.0f});
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            head.move({1.0f, 0.0f});
        }

        window.clear(sf::Color(200, 200, 255));

        if (apple.getGlobalBounds().findIntersection(head.getGlobalBounds())) {
            std::cout << "Intersect! " << i++ << std::endl;
        }

        body.setPosition({head.getPosition().x + 32.0f, head.getPosition().y});
        window.draw(apple);
        window.draw(head);
        window.draw(body);
        

        window.display();

    }
}