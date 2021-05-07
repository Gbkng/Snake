///////////////////////////////////////
// Project : GuySnake
// Author : Guillaume Brooking
// Date : May 2021
// Email : guillaume.brooking@gmail.com
///////////////////////////////////////

#include <random>
#include <cassert>
#include "utils.hpp"

sf::Color generateRandomColor()
{
  static std::default_random_engine generator;
  static std::uniform_int_distribution<int> distribution(0, 255); // color : RGB 0 - 255

  const sf::Uint8 randR = static_cast<sf::Uint8>(distribution(generator));
  const sf::Uint8 randG = static_cast<sf::Uint8>(distribution(generator));
  const sf::Uint8 randB = static_cast<sf::Uint8>(distribution(generator));

  return sf::Color(randR, randG, randB);
}

int generateRandomInteger(int N)
{
  int randInt = rand() % (N + 1);
  return randInt;
}