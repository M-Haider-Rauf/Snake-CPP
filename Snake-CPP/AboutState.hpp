#ifndef ABOUT_STATE_HPP
#define ABOUT_STATE_HPP

#include "BaseState.hpp"

#include <SFML/Graphics.hpp>

class AboutState : public BaseState {
public:
	AboutState();

	void handle_events(sf::Event& e) override;
	void update() override;
	void render() const override;

	void on_enter() override;
	

private:
	const std::string str_about;
	sf::Text about_text;
};
#endif