#include <SFML/Graphics.hpp>
#include "../include/circle.h"
#include <iostream>
#include <vector>

int main(int argc, char *argv[])
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Space Vector Shapes");
    window.setVerticalSyncEnabled(true);

    sf::Texture space;
    space.loadFromFile("assets/SpaceBackground.png");

    sf::Sprite spaceSprite;
    spaceSprite.setTexture(space);


    Circle c1;
    c1.addCircle();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(spaceSprite);
        c1.update();
        c1.draw(window);
        window.display();

    }

    return 0;
}
