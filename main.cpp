#include <cassert>
#include <deque>
#include <iostream>
#include <SFML/Graphics.hpp>

enum class direction {down, left, right, up};

void change_direction(direction new_direction, bool &move_down, bool &move_left, bool &move_right, bool &move_up);
void draw_snake(sf::RenderWindow &window, std::deque<sf::Vector2i> &snake, const int pixel_size);
void move_down (std::deque<sf::Vector2i> &snake);
void move_left (std::deque<sf::Vector2i> &snake);
void move_right(std::deque<sf::Vector2i> &snake);
void move_up   (std::deque<sf::Vector2i> &snake);
void Rainbow(const double x, double& r, double& g, double& b) noexcept;

int main()
{
  const int window_size = 600;
  sf::RenderWindow window(sf::VideoMode(window_size, window_size), "Sneek", sf::Style::Titlebar | sf::Style::Close);

  std::deque<sf::Vector2i> snake_player1 =
  {
    sf::Vector2i(8, 10),
    sf::Vector2i(8, 9),
    sf::Vector2i(8, 8),
    sf::Vector2i(8, 7),
    sf::Vector2i(8, 6)
  };

  std::deque<sf::Vector2i> snake_player2 =
  {
    sf::Vector2i(6, 10),
    sf::Vector2i(6, 9),
    sf::Vector2i(6, 8),
    sf::Vector2i(6, 7),
    sf::Vector2i(6, 6)
  };

  bool move_down_player1 = true;
  bool move_left_player1 = false;
  bool move_right_player1 = false;
  bool move_up_player1 = false;

  bool move_down_player2 = true;
  bool move_left_player2 = false;
  bool move_right_player2 = false;
  bool move_up_player2 = false;

  sf::Vector2i fruit(7,12);

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
            direction new_direction_player1 = direction::down;
            change_direction(new_direction_player1, move_down_player1, move_left_player1, move_right_player1, move_up_player1);
          }
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
          {
            direction new_direction_player1 = direction::left;
            change_direction(new_direction_player1, move_down_player1, move_left_player1, move_right_player1, move_up_player1);
          }
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
          {
            direction new_direction_player1 = direction::right;
            change_direction(new_direction_player1, move_down_player1, move_left_player1, move_right_player1, move_up_player1);
          }
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
          {
            direction new_direction_player1 = direction::up;
            change_direction(new_direction_player1, move_down_player1, move_left_player1, move_right_player1, move_up_player1);
          }
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
          {
            direction new_direction_player2 = direction::down;
            change_direction(new_direction_player2, move_down_player2, move_left_player2, move_right_player2, move_up_player2);
          }
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
          {
            direction new_direction_player2 = direction::left;
            change_direction(new_direction_player2, move_down_player2, move_left_player2, move_right_player2, move_up_player2);
          }
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
          {
            direction new_direction_player2 = direction::right;
            change_direction(new_direction_player2, move_down_player2, move_left_player2, move_right_player2, move_up_player2);
          }
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
          {
            direction new_direction_player2 = direction::up;
            change_direction(new_direction_player2, move_down_player2, move_left_player2, move_right_player2, move_up_player2);
          }
        default:
          break;
      }
    }

    if(snake_player1.front() == fruit)
    {
      snake_player1.push_front(fruit);
      const int fruit_x = rand() % 15;
      const int fruit_y = rand() % 15;
      fruit = sf::Vector2i(fruit_x, fruit_y);
    }
    else if(snake_player2.front() == fruit)
    {
      snake_player2.push_front(fruit);
      const int fruit_x = rand() % 15;
      const int fruit_y = rand() % 15;
      fruit = sf::Vector2i(fruit_x, fruit_y);
    }

    const int pixel_size = 40;
    sf::RectangleShape fruit_shape;
    fruit_shape.setPosition(fruit.x * pixel_size, fruit.y * pixel_size);
    fruit_shape.setSize(sf::Vector2f(pixel_size, pixel_size));

    double update_time = 100; //milliseconds
    if(clock.getElapsedTime().asMilliseconds() >= update_time)
    {
      if(move_down_player1  == true) { move_down (snake_player1); }
      if(move_left_player1  == true) { move_left (snake_player1); }
      if(move_right_player1 == true) { move_right(snake_player1); }
      if(move_up_player1    == true) { move_up   (snake_player1); }
      if(move_down_player2  == true) { move_down (snake_player2); }
      if(move_left_player2  == true) { move_left (snake_player2); }
      if(move_right_player2 == true) { move_right(snake_player2); }
      if(move_up_player2    == true) { move_up   (snake_player2); }

      clock.restart();
    }

    window.clear();
    draw_snake(window, snake_player1, pixel_size);
    draw_snake(window, snake_player2, pixel_size);
    window.draw(fruit_shape);
    window.display();
  }
}


void change_direction(direction new_direction, bool &move_down, bool &move_left, bool &move_right, bool &move_up )
{
  if(new_direction == direction::down)
  {
    move_down = true;
    move_left = false;
    move_right = false;
    move_up = false;
  }
  else if(new_direction == direction::left)
  {
    move_down = false;
    move_left = true;
    move_right = false;
    move_up = false;
  }
  else if(new_direction == direction::right)
  {
    move_down = false;
    move_left = false;
    move_right = true;
    move_up = false;
  }
  else if(new_direction == direction::up)
  {
    move_down = false;
    move_left = false;
    move_right = false;
    move_up = true;
  }
}
void draw_snake(sf::RenderWindow &window, std::deque<sf::Vector2i> &snake, const int pixel_size)
{
  for(int i = 0; i != static_cast<int>(snake.size()); ++i)
  {
    const auto coordinat = snake[i];
    const double f{static_cast<double>(i) / static_cast<int>(snake.size())};
    double r, g, b;
    Rainbow(f, r, g, b);

    sf::RectangleShape s;
    s.setFillColor(sf::Color(b * 255, g * 255, r * 255));
    s.setPosition(coordinat.x * pixel_size, coordinat.y * pixel_size);
    s.setSize(sf::Vector2f(pixel_size, pixel_size));
    window.draw(s);
  }
}
void move_down(std::deque<sf::Vector2i> &snake)
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
void move_left(std::deque<sf::Vector2i> &snake)
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
void move_right(std::deque<sf::Vector2i> &snake)
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
void move_up(std::deque<sf::Vector2i> &snake)
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
