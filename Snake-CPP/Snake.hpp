#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <vector>
#include <SFML/System.hpp>

class Food;

enum struct Direction {
	None, Up, Right, Down, Left
};

class Snake {
public:
	Snake(int x = 0.0, int y = 0.0);
	void render() const;

	void update();
	void grow();
	void cut(unsigned cell = 0);
	unsigned collide_with_body() const;
	bool collide_with_food(const Food&);
	Direction get_head_dir() const;
	size_t len() const { return body.size(); }

	Direction move_dir;

private:
	std::vector<sf::Vector2i> body;
};


#endif // !SNAKE_HPP
