///////////////////////////////////////
// Project : GuySnake
// Author : Guillaume Brooking
// Date : May 2021
// Email : guillaume.brooking@gmail.com
///////////////////////////////////////

#include "SFML/Graphics.hpp"
#include <iostream>
#include <memory>

// #include "utils.hpp"
#include "snake.hpp"
#include "mapping.hpp"

int main()
{
  // width of screen expressed in term of number of snake block
  constexpr int Nx = 20;
  constexpr int Ny = 20;

  // dimension of a snake block (ie. space occupied by one snake's element)
  constexpr int dX = 20;
  constexpr int dY = 20;

  // window dimension and generation
  constexpr int width = Nx * dX;
  constexpr int height = Ny * dY;
  // window generation
  sf::RenderWindow window(sf::VideoMode(width, height), "GuySnake");

  // game clock
  sf::Clock clock;
  constexpr int clockTick = 50; // 200ms between each step of the snake

  sf::Font font;
  if (!font.loadFromFile("../DejaVuSerif.ttf"))
  {
    std::cout << "Failed to load font" << std::endl;
  }

  using Snake = Snake<Nx, Ny, dX, dY>;
  // snake init
  Snake snake(window, font, {0.f, 0.f});

  // VSync, not to burn the CPU only for a snake game ...
  window.setVerticalSyncEnabled(true);
  window.setFramerateLimit(30);

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      snake.update(event);
      switch (event.type)
      {
      case sf::Event::Closed:
        window.close();
        break;
      case sf::Event::KeyPressed:
        switch (event.key.code)
        {
        case sf::Keyboard::Escape:
          window.close();
          break;
        default:
          break;
        }
        break;
      default:
        break;
      }
    }

    sf::Time elapsed = clock.getElapsedTime();
    if (elapsed.asMilliseconds() > clockTick)
    {
      if (!snake.move()) // illegal move
      {
        snake.gameOver();
        break;
      }
      clock.restart();
    }

    window.clear();
    snake.draw();
    window.display();
  }

  return 0;
}