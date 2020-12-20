#ifndef FOOD_HPP
#define FOOD_HPP

class Snake;

struct Food {
	Food() {}
	
	void reset();

	void render() const;

	int x = 0, y = 0;
};


#endif // !FOOD_HPP
