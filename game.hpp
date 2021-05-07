///////////////////////////////////////
// Project : GuySnake
// Author : Guillaume Brooking
// Date : May 2021
// Email : guillaume.brooking@gmail.com
///////////////////////////////////////

#ifndef GUYBRO_GAME_HPP_
#define GUYBRO_GAME_HPP_

#include <iostream>

// ------- BLOCK GAME -----

class BlockGame
{
public:
  BlockGame(sf::RenderWindow &window, sf::Font &font, int clockTick = 200) : window_(window),
                                                             clockTick_(clockTick), // 200ms
                                                             font_(font),
                                                             score_(0)
  {
    scoreDisplay_.setFont(font_);

    scoreDisplay_.setCharacterSize(40); // in pixels, not points!
    scoreDisplay_.setFillColor(sf::Color(255, 255, 255, 200));
    scoreDisplay_.setStyle(sf::Text::Bold);
    scoreDisplay_.setPosition(10, 10);
  }
  inline const sf::RenderWindow &getWindow() const { return window_; }

  void setClockTick();
  void over();
  void gameOver()
  {
    std::cout << "GAME OVER !" << std::endl;
    window_.clear(sf::Color(255, 0, 0, 255));
  }
  void drawScore_()
  {
    scoreDisplay_.setString(std::to_string(score_));
    window_.draw(scoreDisplay_);
  }

protected:
  sf::RenderWindow &window_;
  const sf::Font &font_;
  int score_;
  int clockTick_; // 200ms between each game tick
  sf::Text scoreDisplay_;
};

#endif