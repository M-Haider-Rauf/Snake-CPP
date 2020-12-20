#ifndef END_STATE_HPP
#define END_STATE_HPP

#include "BaseState.hpp"
#include <SFML/Graphics.hpp>

class EndState : public BaseState {
public:
	EndState();

	void handle_events(sf::Event&) override;
	void update() override;
	void render() const override;

	void on_enter() override;

private:
	sf::Text lost_text;
	sf::Text score_text;
};


#endif // !END_STATE_HPP
