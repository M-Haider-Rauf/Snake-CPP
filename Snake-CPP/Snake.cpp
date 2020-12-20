#include "Snake.hpp"
#include "Constants.hpp"
#include "Window.hpp"
#include "Food.hpp"

#include <SFML/Graphics.hpp>

Snake::Snake(int x, int y) : body{ {x, y} }, move_dir(Direction::None)
{
}

void Snake::render() const
{
	for (size_t i = 0; i < body.size(); ++i) {
		sf::RectangleShape rect(sf::Vector2f(CELL_SIZE, CELL_SIZE));

		int x = body[i].x * (CELL_SIZE);
		int y = body[i].y * (CELL_SIZE);

		rect.setPosition(sf::Vector2f(x, y));

		if (i == 0) rect.setFillColor(sf::Color::Red);
		else rect.setFillColor(sf::Color::Blue);

		g_window->draw(rect);
	}
}


void Snake::update()
{
	if (move_dir != Direction::None) {
		for (size_t i = body.size() - 1; i > 0; --i) {
			body[i] = body[i - 1];
		}
	}

	auto& head = body[0];

	switch (move_dir) {
	case Direction::None:
		break;

	case Direction::Up:
		head.y -= 1;
		break;

	case Direction::Right:
		head.x += 1;
		break;

	case Direction::Down:
		head.y += 1;
		break;

	case Direction::Left:
		head.x -= 1;
		break;

	default:
		break;
	}

	if (head.x < 0) head.x = GRID_COLS - 1;
	else if (head.x >= GRID_COLS) head.x = 0;

	if (head.y < 0) head.y = GRID_ROWS - 1;
	else if (head.y >= GRID_ROWS) head.y = 0;

}

void Snake::grow()
{
	const size_t len = body.size();

	const auto tail = body.back();
	const auto head = body[0];

	if (len > 1) {
		const auto tail_bone = body[len - 2];

		if (tail.y == tail_bone.y) {
			if (tail_bone.x > tail.x) body.push_back({ tail.x - 1, tail.y});
			else  body.push_back({ tail.x + 1, tail.y});
		}

		else  {
			if (tail_bone.y > tail.y) body.push_back({ tail.x, tail.y - 1});
			else  body.push_back({ tail.x, tail.y + 1});
		}
	}

	else {
		switch (move_dir) {
		case Direction::Left:
			body.push_back({ tail.x + 1, tail.y });
			break;

		case Direction::Right:
			body.push_back({ tail.x - 1, tail.y });
			break;

		case Direction::Up:
			body.push_back({ tail.x, tail.y + 1});
			break;

		case Direction::Down:
			body.push_back({ tail.x, tail.y - 1});
			break;

		default:
			body.push_back({ tail.x, tail.y - 1 });
			break;
		}
	}
}

void Snake::cut(unsigned cell)
{
	body.erase(body.begin() + cell, body.end());
}

unsigned Snake::collide_with_body() const
{
	for (size_t i = 3; i < body.size(); ++i) {
		if (body[0] == body[i]) return i;
	}

	return 0;
}

bool Snake::collide_with_food(const Food& food)
{
	return body[0].x == food.x && body[0].y == food.y;
}

Direction Snake::get_head_dir() const
{
	const size_t len = body.size();
	if (len == 1) return move_dir;

	const auto head = body[0];
	const auto neck = body[1];


	if (head.y == neck.y) {
		if (head.x > neck.x) return Direction::Right;
		return Direction::Left;
	}
	
	if (head.y > neck.y) return Direction::Down;
	return Direction::Up;
}
