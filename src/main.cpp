#include <SFML/Window.hpp>
#include <SFML/Window/VideoMode.hpp>

#include <iostream>

int main() {
    std::cout << "yay" << std::endl;
    sf::Window window = sf::Window(sf::VideoMode(sf::Vector2<unsigned int>(800, 600)), "SFML Window");
    window.setVerticalSyncEnabled(true);

    while (window.isOpen()) {
        sf::Event event;




        while (window.pollEvent(event)) if (event.type == sf::Event::Closed) window.close();
    }

    std::cout << "yay" << std::endl;
}