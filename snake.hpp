///////////////////////////////////////
// Project : GuySnake
// Author : Guillaume Brooking
// Date : May 2021
// Email : guillaume.brooking@gmail.com
///////////////////////////////////////

#ifndef GUYBRO_SNAKE_HPP_
#define GUYBRO_SNAKE_HPP_

#include "SFML/Graphics.hpp"
#include "game.hpp"
#include "mapping.hpp"

// ------- SNAKE -----

template <int nBlockX,
          int nBlockY,
          int blockX,
          int blockY>
class Snake : public BlockGame
{
  using SnakeShape = sf::RectangleShape;
  static constexpr float dX = static_cast<float>(blockX); // rectangle width
  static constexpr float dY = static_cast<float>(blockY); // rectangle height
  static constexpr int Nx = nBlockX;                      // rectangle width
  static constexpr int Ny = nBlockY;                      // rectangle height
public:
  Snake(sf::RenderWindow &window,
  sf::Font &font,
        const sf::Vector2f initPosition) : BlockGame(window, font),
                                           elementDim_({dX, dY}),
                                           color_(sf::Color::Red),
                                           direction_(Direction::None),
                                           previousDirection_(Direction::None),
                                           fillMap_(window)
  {
    SnakeShape firstElement(elementDim_);
    firstElement.setFillColor(color_);
    firstElement.setPosition(initPosition);
    body_.push_back(firstElement);

    lastTailPosition_ = initPosition; // dummy init
    fillMap_.fill(initPosition);
  }
  enum Direction
  {
    Up,
    Down,
    Left,
    Right,
    None
  };

  inline const sf::Color getColor() const { return color_; }
  inline void setColor(const sf::Color color)
  {
    color_ = color;
    updateColor_();
  }
  inline void setDirection(const Direction direction)
  {
    if (body_.size() == 1)
    {
      previousDirection_ = direction;
    }
    previousDirection_ = direction_;
    direction_ = direction;
  }
  inline Direction getDirection() const { return direction_; }
  void grow()
  {
    // create a new element
    SnakeShape newElement(elementDim_);
    newElement.setFillColor(color_);
    // calculate where to add it

    newElement.setPosition(lastTailPosition_);
    fillMap_.fill(lastTailPosition_);

    body_.push_back(newElement);
  }

  void update(sf::Event &event)
  {
    if (event.type == sf::Event::KeyPressed)
    {
      switch (event.key.code)
      {
      case sf::Keyboard::Left:
        setDirection(Snake::Direction::Left);
        break;
      case sf::Keyboard::Right:
        setDirection(Snake::Direction::Right);
        break;
      case sf::Keyboard::Up:
        setDirection(Snake::Direction::Up);
        break;
      case sf::Keyboard::Down:
        setDirection(Snake::Direction::Down);
        break;
      case sf::Keyboard::Space:
        setColor(generateRandomColor());
        break;
      default:
        break;
      }
    }
  }

  // return false if illegal move
  bool move()
  {
    auto newHeadPosition = computeNewHeadPosition_();

    // fillMap_.printMap();

    // check that provided direction is not to the opposite of the current one (i.e. down for up, right for left, up for down etc.)
    // only if size > 1
    if (body_.size() > 1)
    {
      if (body_.at(1).getPosition() == newHeadPosition)
      {
        direction_ = previousDirection_;
        newHeadPosition = computeNewHeadPosition_();
      }
    }
    if (fillMap_.isFilled(newHeadPosition))
    {
      if (direction_ != Direction::None)
      {
        std::cout << "You've bitten yourself, you fool!" << std::endl;
        return false;
      }
    }
    else if (fillMap_.isFood(newHeadPosition))
    {
      std::cout << "Yummy! ";
      // fillMap_.emptyFood(newHeadPosition);
      fillMap_.placeFood();
      increaseScore_();
      std::cout << "Score : " << score_ << std::endl;
      this->grow();
      setColor(generateRandomColor());
    }

    lastTailPosition_ = body_.back().getPosition(); // save the tail position in case of snake growth
    fillMap_.empty(lastTailPosition_);

    // move all element except head
    for (int k = body_.size() - 1; k > 0; k--) // reversed order to avoid aliasing
    {
      const auto nextElementPosition = body_.at(k - 1).getPosition();
      body_.at(k).setPosition(nextElementPosition);
    }

    // move head. Correspond to case k = 0
    body_.front().setPosition(newHeadPosition);
    fillMap_.fill(newHeadPosition);

    return true;
  }

  inline void draw()
  {
    for (const auto &element : body_)
    {
      window_.draw(element);
    }
    fillMap_.draw();
    drawScore_();
  }

private:
  const sf::Vector2f elementDim_;
  sf::Color color_;
  Direction direction_;
  Direction previousDirection_;
  std::vector<SnakeShape> body_;
  sf::Vector2f lastTailPosition_;

  FillMap<nBlockX, nBlockY, blockX, blockY> fillMap_;

  void increaseScore_()
  {
    score_ += 1 + body_.size() / 10;
  }

  inline void updateColor_()
  {
    for (auto &element : body_)
    {
      element.setFillColor(color_);
    }
  }

  sf::Vector2f computeNewHeadPosition_()
  {
    const auto width = window_.getSize().x;
    const auto height = window_.getSize().y;

    const auto head = body_.front();
    const auto headX = head.getPosition().x;
    const auto headY = head.getPosition().y;

    auto newHeadPosition = head.getPosition(); // before offset add
    switch (direction_)
    {
    case Direction::Right:
      if (headX + dX < width)
      {
        newHeadPosition += {dX, 0.f};
      }
      else
      {
        newHeadPosition = {0.f, headY};
      }
      break;
    case Direction::Left:
      if (headX - dX >= 0.)
      {
        newHeadPosition += {-dX, 0.f};
      }
      else
      {
        newHeadPosition = {width - dX, headY};
      }
      break;
    case Direction::Up:
      if (headY - dY >= 0.)
      {
        newHeadPosition += {0.f, -dY};
      }
      else
      {
        newHeadPosition = {headX, height - dY};
      }

      break;
    case Direction::Down:
      if (headY + dY < height)
      {
        newHeadPosition += {0.f, dY};
      }
      else
      {
        newHeadPosition = {headX, 0.f};
      }
      break;
    default:
      break;
    }
    return newHeadPosition;
  }
};

#endif