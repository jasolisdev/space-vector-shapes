#include "../include/circle.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

Circle::Circle() {}

Circle::Circle(std::string name, float posx, float posy, float speedx,
               float speedy, float radius, int red, int green, int blue)
    : n(""),
      x(posx),
      y(posy),
      sx(speedx),
      sy(speedy),
      rad(radius),
      r(red),
      g(green),
      b(blue) {}

void Circle::addCircle() {
  std::cout << "Loading config.txt\n";
  std::ifstream fin("config.txt");
  if (fin.fail()) {
    std::cerr << "Config file not found\n";
  } else if (fin.is_open()) {
    std::cout << "config.txt loaded\n";
    while (fin.good()) {
      fin >> token;
      if (token == "Astroid") {
        fin >> n >> x >> y >> rad >> sx >> sy >> r >> g >> b;
        Circle shape;
        shape.s = std::make_shared<sf::CircleShape>(rad);
        if (!astroidTexture.loadFromFile("assets/asteroid.png")) {
          std::cerr << "failed to load";
        }
        shape.s->setTexture(&astroidTexture);
        shape.s->setPosition(x, y);
        // shape.s->setFillColor(sf::Color(r, g, b));
        shape.speed = sf::Vector2f(sx, sy);
        shapes.push_back(shape);
      } else if (token == "Meteor") {
        fin >> n >> x >> y >> rad >> sx >> sy >> r >> g >> b;
        Circle shape;
        shape.s = std::make_shared<sf::CircleShape>(rad);
        if (!meteorTexture.loadFromFile("assets/Meteor2.png")) {
          std::cerr << "failed to load";
        }
        shape.s->setTexture(&meteorTexture);
        shape.s->setPosition(x, y);
        // shape.s->setFillColor(sf::Color(r, g, b));
        shape.speed = sf::Vector2f(sx, sy);
        shapes.push_back(shape);
      } else if (token == "Moon") {
        fin >> n >> x >> y >> rad >> sx >> sy >> r >> g >> b;
        Circle shape;
        shape.s = std::make_shared<sf::CircleShape>(rad);
        if (!moonTexture.loadFromFile("assets/moon.png")) {
          std::cerr << "failed to load";
        }
        shape.s->setTexture(&moonTexture);
        shape.s->setPosition(x, y);
        shape.s->setFillColor(sf::Color(r, g, b));
        shape.speed = sf::Vector2f(sx, sy);
        shapes.push_back(shape);
      } else if (token == "Sun") {
        fin >> n >> x >> y >> rad >> sx >> sy >> r >> g >> b;
        Circle shape;
        shape.s = std::make_shared<sf::CircleShape>(rad);
        if (!sunTexture.loadFromFile("assets/sun.png")) {
          std::cerr << "failed to load";
        }
        shape.s->setTexture(&sunTexture);
        shape.s->setPosition(x, y);
        // shape.s->setFillColor(sf::Color(r, g, b));
        speed = sf::Vector2f(sx, sy);
        shape.speed = sf::Vector2f(sx, sy);
        shapes.push_back(shape);
      }
    }
  }
}

void Circle::update() {
  for (auto& i : shapes) {
    i.s->setPosition(i.s->getPosition().x - i.speed.x,
                     i.s->getPosition().y - i.speed.y);

    i.s->rotate(0.01f);

    if ((i.s->getPosition().x < 0) ||
        (i.s->getLocalBounds().width + i.s->getPosition().x) > 1280 ||
        (i.s->getPosition().y < 0) ||
        (i.s->getLocalBounds().height + i.s->getPosition().y) > 720) {
      i.speed *= -1.05f;
    }
  }
}

void Circle::draw(sf::RenderWindow& window) {
  for (auto& i : shapes) {
    window.draw(*i.s);
  }
}
