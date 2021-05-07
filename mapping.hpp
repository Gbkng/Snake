///////////////////////////////////////
// Project : GuySnake
// Author : Guillaume Brooking
// Date : May 2021
// Email : guillaume.brooking@gmail.com
///////////////////////////////////////

#ifndef GUYBRO_MAPPING_HPP_
#define GUYBRO_MAPPING_HPP_

#include <iostream>
#include "SFML/Graphics.hpp"
#include "utils.hpp"

// // forward decl
// int generateRandomIndex(int);
template <int Nx, int Ny, int dX, int dY>
class FillMap
{
  using FoodShape = sf::RectangleShape;

public:
  static constexpr int N = Nx * Ny;
  FillMap(sf::RenderWindow &window) : window_(window), food_({dX, dY})
  {
    for (auto &blockType : map_)
    {
      blockType = FillType::Empty;
    }
    food_.setFillColor(foodColor_);
    filledBlockNumber_ = 0;
    placeFood();
  }

  enum FillType
  {
    Empty,
    Body,
    Food
  };

  /**
   * Here is how this method works :
   * - there is N_max = (N - filledBlockNumber_) blocks that are avaiable.
   * - a random rank randIndex is generated in [0, N_max]
   * - then, the rankIndex-th FREE block is filled with food
   * 
   * This means that all filled block must be skipped. 
   * This is what the inner while loop aims for.
   **/
  void placeFood()
  {
    // std::cout << "From FillMap::placeFood :" << std::endl;
    const int randIndex = generateRandomInteger(N - filledBlockNumber_ - 1);
    // std::cout << "randIndex : " << randIndex << std::endl;
    int rankCandidate = 0;
    for (int k = 0; k < randIndex; k++)
    {
      ++rankCandidate;
      while (map_.at(rankCandidate) == FillType::Body || map_.at(rankCandidate) == FillType::Food) // skip body or food
      {
        ++rankCandidate;
      }
    } // rankCandidate now equal finalRank, ie. where to add food
    // std::cout << "rankCandidate : " << rankCandidate << std::endl;
    // std::cout << "filledBlockNumber_ : " << filledBlockNumber_ << std::endl;
    map_.at(rankCandidate) = FillType::Food;
    // filledBlockNumber_++;

    // calculate where to add it
    food_.setPosition(rankCandidate % Nx * dX, rankCandidate / Nx * dY);
  }

  // void emptyFood(const sf::Vector2f coord)
  // {
  //   auto [X, Y] = positionToMapCoord_(coord);
  //   auto &blockType = map_.at(Y * Nx + X);
  //   if (blockType == FillType::Food)
  //   {
  //     map_.at(Y * Nx + X) = FillType::Empty;
  //     filledBlockNumber_--;
  //   }
  //   else
  //   {
  //     std::cout << "Trying to emptyFood a non-food block" << std::endl;
  //   }
  // }

  // fill with snake
  void fill(const sf::Vector2f coord)
  {
    auto [X, Y] = positionToMapCoord_(coord);
    map_.at(Y * Nx + X) = FillType::Body;
    ++filledBlockNumber_;
  }

  void empty(const sf::Vector2f coord)
  {
    auto [X, Y] = positionToMapCoord_(coord);
    map_.at(Y * Nx + X) = FillType::Empty;
    --filledBlockNumber_;
  }

  bool isFood(const sf::Vector2f coord) const
  {
    auto [X, Y] = positionToMapCoord_(coord);
    if (map_.at(Y * Nx + X) == FillType::Food)
    {
      return true;
    }
    return false;
  }
  bool isFilled(const sf::Vector2f coord) const
  {
    auto [X, Y] = positionToMapCoord_(coord);
    if (map_.at(Y * Nx + X) == FillType::Body)
    {
      return true;
    }
    return false;
  }

  // DEBUG
  void printMap()
  {
    for (int k = 0; k < map_.size(); k++)
    {
      if ((k) % Nx == 0)
        std::cout << std::endl;
      std::cout << map_.at(k) << " ";
    }
    std::cout << std::endl;
  }

  void draw()
  {
    drawFood_();
  }

private:
  sf::RenderWindow &window_;
  std::array<FillType, N> map_;
  FoodShape food_;
  sf::Color foodColor_ = sf::Color::White;
  int filledBlockNumber_;

  std::pair<int, int> positionToMapCoord_(const sf::Vector2f position) const
  {
    const int X = (static_cast<int>(position.x)) / dX; // X : block horizontal coordinate
    const int Y = (static_cast<int>(position.y)) / dY; // Y : block vertical coordinate
    // std::cout << "x position : " << static_cast<int>(position.x) << " ; y position : " << static_cast<int>(position.y) <<  std::endl;
    // std::cout << "X : " << X << " ; Y : " << Y << std::endl;

    return std::make_pair(X, Y);
  }
  void drawFood_()
  {
    window_.draw(food_);
  }
};
#endif