#ifndef PLAY_STATE_HPP
#define PLAY_STATE_HPP

#include "BaseState.hpp"
#include "Snake.hpp"
#include "Food.hpp"
#include <map>
#include "SFML/Graphics.hpp"

class PlayState : public BaseState {
public:
	PlayState();
	~PlayState();

	void handle_events(sf::Event&) override;
	void update() override;
	void render() const override;

	void on_enter() override;

	static int get_score()
	{
		return PlayState::score;
	}


private:
	sf::Clock clock;
	void draw_field() const;

	Snake snake;
	Food food;
	std::map<std::string, sf::Text> texts;
	unsigned lives = 5;
	bool paused = false;

	static int score;
	float update_ps = 13.0f;
};


#endif // !PLAY_STATE_HPP
