#ifndef CIRCLE_H
#define CIRCLE_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

class Circle {
 public:
  Circle();

  Circle(std::string name, float posx, float posy, float speedx, float speedy,
         float radius, int r, int g, int b);

  void addCircle();
  void update();
  void draw(sf::RenderWindow& window);

 private:
  std::vector<Circle> shapes;
  std::shared_ptr<sf::Shape> s;

  std::string n, token, fdir;
  float x, y, sx, sy, rad, w, h;
  int size, r, g, b;

  sf::Font font;
  sf::Text text;
  sf::Vector2f speed;
  sf::Texture astroidTexture;
  sf::Texture meteorTexture;
  sf::Texture moonTexture;
  sf::Texture sunTexture;
};

#endif /* ifndef CIRCLE_H */
