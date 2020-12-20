#ifndef MENU_STATE_HPP
#define MENU_STATE_HPP

#include "BaseState.hpp"
#include <vector>

namespace sf {
	class Event;
	class Text;
}

class MenuState : public BaseState {
public:

	MenuState();
	~MenuState();

	void handle_events(sf::Event&) override;
	void update() override;
	void render() const override;
	
	void on_enter() override;

private:
	size_t curr_option;
	sf::Text* title_text;
	std::vector<sf::Text*> texts;
};


#endif