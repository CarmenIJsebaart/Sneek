#include <cassert>
#include <deque>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>

enum class direction {down, left, right, up};

void catch_fruit(std::deque<sf::Vector2i> &snake_that_eats, sf::Vector2i &fruit);
void change_direction(direction new_direction, bool &move_down, bool &move_left, bool &move_right, bool &move_up);
void check_if_snake_is_eaten_by_itself(std::deque<sf::Vector2i> &snake);
void check_if_snake_is_eaten_by_other_snake(std::deque<sf::Vector2i> &eating_snake, std::deque<sf::Vector2i> &to_be_eaten_snake);
void do_movement(std::deque<sf::Vector2i> &snake, bool move_down_snake, bool move_left_snake, bool move_right_snake, bool move_up_snake);
void draw_snake(sf::RenderWindow &window, std::deque<sf::Vector2i> &snake, const int pixel_size);
void move_down (std::deque<sf::Vector2i> &snake);
void move_left (std::deque<sf::Vector2i> &snake);
void move_right(std::deque<sf::Vector2i> &snake);
void move_up   (std::deque<sf::Vector2i> &snake);
void rainbow(const double x, double& r, double& g, double& b) noexcept;

int main()
{
  const int window_size = 600;
  sf::RenderWindow window(sf::VideoMode(window_size, window_size), "Sneek", sf::Style::Titlebar | sf::Style::Close);
  // player1 = right snake
  std::deque<sf::Vector2i> snake_player1 =
  {
    sf::Vector2i(12, 10),
    sf::Vector2i(12, 9),
    sf::Vector2i(12, 8),
    sf::Vector2i(12, 7),
    sf::Vector2i(12, 6)
  };

  //player2 = left snake
  std::deque<sf::Vector2i> snake_player2 =
  {
    sf::Vector2i(8, 10),
    sf::Vector2i(8, 9),
    sf::Vector2i(8, 8),
    sf::Vector2i(8, 7),
    sf::Vector2i(8, 6)
  };

  bool move_down_player1 = true;
  bool move_left_player1 = false;
  bool move_right_player1 = false;
  bool move_up_player1 = false;

  bool move_down_player2 = true;
  bool move_left_player2 = false;
  bool move_right_player2 = false;
  bool move_up_player2 = false;

  sf::Vector2i fruit(10,12);

  sf::Font font;
  font.loadFromFile("arial.ttf");

  int player1_score = 0;
  std::ostringstream oss1;
  oss1 << player1_score;
  sf::Text score_player1;
  score_player1.setString(oss1.str());
  score_player1.setFont(font);
  score_player1.setCharacterSize(65);
  score_player1.setPosition(sf::Vector2f(400, 0));

  int player2_score = 0;
  std::ostringstream oss2;
  oss2 << player2_score;
  sf::Text score_player2;
  score_player2.setString(oss2.str());
  score_player2.setFont(font);
  score_player2.setCharacterSize(65);
  score_player2.setPosition(sf::Vector2f(10, 0));

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
            const direction new_direction_player1 = direction::down;
            change_direction(new_direction_player1, move_down_player1, move_left_player1, move_right_player1, move_up_player1);
          }
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
          {
            const direction new_direction_player1 = direction::left;
            change_direction(new_direction_player1, move_down_player1, move_left_player1, move_right_player1, move_up_player1);
          }
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
          {
            const direction new_direction_player1 = direction::right;
            change_direction(new_direction_player1, move_down_player1, move_left_player1, move_right_player1, move_up_player1);
          }
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
          {
            const direction new_direction_player1 = direction::up;
            change_direction(new_direction_player1, move_down_player1, move_left_player1, move_right_player1, move_up_player1);
          }
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
          {
            const direction new_direction_player2 = direction::down;
            change_direction(new_direction_player2, move_down_player2, move_left_player2, move_right_player2, move_up_player2);
          }
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
          {
            const direction new_direction_player2 = direction::left;
            change_direction(new_direction_player2, move_down_player2, move_left_player2, move_right_player2, move_up_player2);
          }
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
          {
            const direction new_direction_player2 = direction::right;
            change_direction(new_direction_player2, move_down_player2, move_left_player2, move_right_player2, move_up_player2);
          }
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
          {
            const direction new_direction_player2 = direction::up;
            change_direction(new_direction_player2, move_down_player2, move_left_player2, move_right_player2, move_up_player2);
          }
          break;
        default:
          break;
      }
    }

    if(snake_player1.front() == fruit)
    {
      catch_fruit(snake_player1, fruit);
      player1_score += 10;
      oss1.str("");
      oss1 << player1_score;
      score_player1.setString(oss1.str());
      std::cout << player1_score << std::endl;
    }
    else if(snake_player2.front() == fruit)
    {
      catch_fruit(snake_player2, fruit);
      player2_score += 10;
      oss2.str("");
      oss2 << player2_score;
      score_player2.setString(oss2.str());
      std::cout << player2_score << std::endl;
    }

    const int pixel_size = 30;
    sf::RectangleShape fruit_shape;
    fruit_shape.setPosition(fruit.x * pixel_size, fruit.y * pixel_size);
    fruit_shape.setSize(sf::Vector2f(pixel_size, pixel_size));

    const double update_time = 115; //milliseconds
    if(clock.getElapsedTime().asMilliseconds() >= update_time)
    {
      do_movement(snake_player1, move_down_player1, move_left_player1, move_right_player1, move_up_player1);
      do_movement(snake_player2, move_down_player2, move_left_player2, move_right_player2, move_up_player2);
      check_if_snake_is_eaten_by_other_snake(snake_player1, snake_player2);
      check_if_snake_is_eaten_by_other_snake(snake_player2, snake_player1);
      check_if_snake_is_eaten_by_itself(snake_player1);
      check_if_snake_is_eaten_by_itself(snake_player2);
      clock.restart();
    }

    window.clear();
    draw_snake(window, snake_player1, pixel_size);
    draw_snake(window, snake_player2, pixel_size);
    window.draw(fruit_shape);
    window.draw(score_player1);
    window.draw(score_player2);
    window.display();
  }
}

void catch_fruit(std::deque<sf::Vector2i> &snake_that_eats, sf::Vector2i &fruit)
{
  snake_that_eats.push_front(fruit);
  const int fruit_x = rand() % 15;
  const int fruit_y = rand() % 15;
  fruit = sf::Vector2i(fruit_x, fruit_y);
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
void check_if_snake_is_eaten_by_itself(std::deque<sf::Vector2i> &snake)
{
  for(int i = 1; i < static_cast<int>(snake.size()); ++i)
  {
    const auto begin_coordinat_snake = snake[0];
    assert(i >= 1);
    assert(i < static_cast<int>(snake.size()));
    const auto any_coordinat_snake = snake[i];
    if(begin_coordinat_snake == any_coordinat_snake)
    {
      int snake_size_before_popback = snake.size();
      int snake_popback_amount = snake_size_before_popback - i;
      assert(!snake.empty());
      for(int j = 0; j != snake_popback_amount; ++j)
      {
        if(snake.size() > 3)
        {
          snake.pop_back();
        }
      }
      assert(!snake.empty());
    }
  }
}
void check_if_snake_is_eaten_by_other_snake(std::deque<sf::Vector2i> &eating_snake, std::deque<sf::Vector2i> &to_be_eaten_snake)
{
  for(int i = 0; i < static_cast<int>(to_be_eaten_snake.size()); ++i)
  {
    const auto begin_coordinat_eating_snake = eating_snake[0];
    assert(i >= 0);
    assert(i < static_cast<int>(to_be_eaten_snake.size()));
    const auto any_coordinat_to_be_eaten_snake = to_be_eaten_snake[i];
    if(begin_coordinat_eating_snake == any_coordinat_to_be_eaten_snake)
    {
      int to_be_eaten_snake_size_before_popback = to_be_eaten_snake.size();
      int to_be_eaten_snake_popback_amount = to_be_eaten_snake_size_before_popback - i;
      assert(!to_be_eaten_snake.empty());
      for(int j = 0; j != to_be_eaten_snake_popback_amount; ++j)
      {
        if(to_be_eaten_snake.size() > 3)
        {
          to_be_eaten_snake.pop_back();
        }
      }
      assert(!to_be_eaten_snake.empty());
    }
  }
}
void do_movement(std::deque<sf::Vector2i> &snake, bool move_down_snake, bool move_left_snake, bool move_right_snake, bool move_up_snake)
{
  if (snake.empty())
  {
    std::stringstream msg;
    msg << __func__ << ": snake cannot be empty";
    throw std::invalid_argument(msg.str());
  }
  if     (move_down_snake  == true) { move_down (snake); }
  else if(move_left_snake  == true) { move_left (snake); }
  else if(move_right_snake == true) { move_right(snake); }
  else if(move_up_snake    == true) { move_up   (snake); }
}
void draw_snake(sf::RenderWindow &window, std::deque<sf::Vector2i> &snake, const int pixel_size)
{
  if (snake.empty())
  {
    std::stringstream msg;
    msg << __func__ << ": snake cannot be empty";
    throw std::invalid_argument(msg.str());
  }
  for(int i = 0; i != static_cast<int>(snake.size()); ++i)
  {
    const auto coordinat = snake[i];
    const double f{static_cast<double>(i + 1) / static_cast<int>(snake.size() + 1)};
    double r, g, b;
    rainbow(f, r, g, b);

    sf::RectangleShape s;
    s.setFillColor(sf::Color(b * 255, g * 255, r * 255));
    s.setPosition(coordinat.x * pixel_size, coordinat.y * pixel_size);
    s.setSize(sf::Vector2f(pixel_size, pixel_size));
    window.draw(s);
  }
}
void move_down(std::deque<sf::Vector2i> &snake)
{
  if (snake.empty())
  {
    std::stringstream msg;
    msg << __func__ << ": snake cannot be empty";
    throw std::invalid_argument(msg.str());
  }

  if(snake.front().y == 19)
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
  if (snake.empty())
  {
    std::stringstream msg;
    msg << __func__ << ": snake cannot be empty";
    throw std::invalid_argument(msg.str());
  }
  if(snake.front().x == 0)
  {
    const sf::Vector2i new_head(19, snake.front().y);
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
  if (snake.empty())
  {
    std::stringstream msg;
    msg << __func__ << ": snake cannot be empty";
    throw std::invalid_argument(msg.str());
  }
  if(snake.front().x == 19)
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
  if (snake.empty())
  {
    std::stringstream msg;
    msg << __func__ << ": snake cannot be empty";
    throw std::invalid_argument(msg.str());
  }
  if(snake.front().y == 0)
  {
    const sf::Vector2i new_head(snake.front().x, 19);
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
void rainbow(const double x, double& r, double& g, double& b) noexcept
{
  const double pi{3.14159};

  if (x <= 0.0 || x >= 1.0)
  {
    assert(!"Should not get here");
    r = g = b = 0.0; return;
  }

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
  assert(!(r < 0.01 && g < 0.01 && b < 0.01));
}
