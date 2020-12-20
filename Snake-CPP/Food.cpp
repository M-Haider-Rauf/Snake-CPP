#include "Food.hpp"
#include "Constants.hpp"
#include "Window.hpp"
#include "SFML/Graphics.hpp"
#include <random>


void Food::reset()
{
	static std::uniform_int_distribution<> xDist (0, GRID_COLS - 1);
	static std::uniform_int_distribution<> yDist(0, GRID_ROWS - 1);
	static std::default_random_engine eng(std::random_device().operator()());

	x = xDist(eng);
	y = yDist(eng);
}

void Food::render() const
{
	sf::CircleShape circ(CELL_SIZE / 2.0 - 4u);
	circ.setFillColor(sf::Color::Red);
	circ.setPosition(sf::Vector2f( x * CELL_SIZE + 4u, y * CELL_SIZE + 4u));

	g_window->draw(circ);
}
