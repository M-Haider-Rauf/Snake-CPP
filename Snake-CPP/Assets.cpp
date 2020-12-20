#include "Assets.hpp"
#include "Constants.hpp"

sf::Font Assets::font;

void Assets::load()
{
	font.loadFromFile("res/font.ttf");
}
