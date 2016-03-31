#include <cassert>
#include <deque>
#include <iostream>
#include <SFML/Graphics.hpp>

void Rainbow(const double x, double& r, double& g, double& b) noexcept
{
  const double pi{3.14159};

  if (x <= 0.0 || x >= 1.0) { r = g = b = 0.0; return; }

  const double f_r = std::max(0.0,
    (x < 0.5
    ? std::cos(x * 1.5 * pi)
    : -std::sin(x * 1.5 * pi)
    ) );
  const double f_g = std::max(0.0,  std::sin( x * 1.5 * pi ));
  const double f_b = std::max(0.0, -std::cos( x * 1.5 * pi ));
  const double max = std::max(f_r,  std::max(f_g, f_b      ));
  assert(max!=0.0);

  r = f_r / max;
  g = f_g / max;
  b = f_b / max;
}

int main()
{
  const int window_size = 600;
  sf::RenderWindow window(sf::VideoMode(window_size, window_size), "Sneek", sf::Style::Titlebar | sf::Style::Close);

  sf::Vector2i fruit(10,14);

  bool move_down = true;
  bool move_left = false;
  bool move_right = false;
  bool move_up = false;

  std::deque<sf::Vector2i> snake =
  {
    sf::Vector2i(10,10),
    sf::Vector2i(10,9),
    sf::Vector2i(10,8),
    sf::Vector2i(10,7),
    sf::Vector2i(10,6)
  };

  sf::Clock clock;

  while(window.isOpen())
  {
    sf::Event event;

    while(window.pollEvent(event))
    {      
      switch(event.type)
      {
        case sf::Event::Closed:
          window.close();
          break;
        case sf::Event::KeyPressed:
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
          {
            move_down = true;
            move_left = false;
            move_right = false;
            move_up = false;
          }
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
          {
            move_down = false;
            move_left = true;
            move_right = false;
            move_up = false;
          }
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
          {
            move_down = false;
            move_left = false;
            move_right = true;
            move_up = false;
          }
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
          {
            move_down = false;
            move_left = false;
            move_right = false;
            move_up = true;
          }
        default:
          break;
      }
    }

    if (snake.front() == fruit)
    {
      snake.push_front(fruit);
      const int fruit_x = rand() % 15;
      const int fruit_y = rand() % 15;
      fruit = sf::Vector2i(fruit_x, fruit_y);
    }

    sf::RectangleShape fruit_shape;
    fruit_shape.setPosition(fruit.x * 40.0, fruit.y * 40.0);
    fruit_shape.setSize(sf::Vector2f(40,40));

    double update_time = 100; //milliseconds

    if(clock.getElapsedTime().asMilliseconds() >= update_time)
    {
      if(move_down == true)
      {
        if(snake.front().y == 14)
        {
          const sf::Vector2i new_head(snake.front().x, 0);
          snake.push_front(new_head);
          snake.pop_back();
        }
        else
        {
          const sf::Vector2i new_head(snake.front().x, snake.front().y + 1);
          snake.push_front(new_head);
          snake.pop_back();
        }
      }
      if(move_left == true)
      {
        if(snake.front().x == 0)
        {
          const sf::Vector2i new_head(14, snake.front().y);
          snake.push_front(new_head);
          snake.pop_back();
        }
        else
        {
          const sf::Vector2i new_head(snake.front().x - 1, snake.front().y);
          snake.push_front(new_head);
          snake.pop_back();
        }
      }
      if(move_right == true)
      {
        if(snake.front().x == 14)
        {
          const sf::Vector2i new_head(0, snake.front().y);
          snake.push_front(new_head);
          snake.pop_back();
        }
        else
        {
          const sf::Vector2i new_head(snake.front().x + 1, snake.front().y);
          snake.push_front(new_head);
          snake.pop_back();
        }
      }
      if(move_up == true)
      {
        if(snake.front().y == 0)
        {
          const sf::Vector2i new_head(snake.front().x, 14);
          snake.push_front(new_head);
          snake.pop_back();
        }
        else
        {
          const sf::Vector2i new_head(snake.front().x, snake.front().y - 1);
          snake.push_front(new_head);
          snake.pop_back();
        }
      }

      clock.restart();
    }

    window.clear();

    for(int i = 0; i != static_cast<int>(snake.size()); ++i)
    {
      const auto coordinat = snake[i];
      const double f{static_cast<double>(i) / static_cast<int>(snake.size())};
      double r, g, b;
      Rainbow(f, r, g, b);

      sf::RectangleShape s;
      s.setFillColor(sf::Color(r * 255,g * 255, b * 255));
      s.setPosition(coordinat.x * 40.0, coordinat.y * 40.0);
      s.setSize(sf::Vector2f(40,40));
      window.draw(s);
    }

    window.draw(fruit_shape);
    window.display();
  }
}
