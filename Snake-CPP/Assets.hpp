#ifndef VECTOR_HPP
#define VECTOR_HPP


#include <vector>
#include <SFML/Graphics.hpp>

class Assets {
public:
	Assets() = delete;
	~Assets() = delete;
	Assets(const Assets&) = delete;
	Assets& operator=(const Assets&) = delete;

	static void load();

	static sf::Font font;
};


#endif // !VECTOR_HPP