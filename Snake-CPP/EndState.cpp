#include "EndState.hpp"
#include "Window.hpp"
#include "Assets.hpp"
#include "PlayState.hpp"

EndState::EndState() 
	: BaseState(StateId::EndState)
	, lost_text("", Assets::font)
{
	lost_text.setFillColor(sf::Color::Red);
	lost_text.setCharacterSize(40u);
	lost_text.setPosition(sf::Vector2f(120, 270));
}

void EndState::handle_events(sf::Event& event_q)
{
	if (event_q.type == sf::Event::KeyPressed) {
		switch (event_q.key.code) {
		case sf::Keyboard::R:
			next_state = StateId::PlayState;
			break;
		}
	}
}

void EndState::update()
{
}

void EndState::render() const
{
	g_window->draw(lost_text);
}

void EndState::on_enter()
{
	std::string text = std::string("Game Over!\n") +
		"Your score is " + std::to_string(PlayState::get_score()) +
		"\nPress R to restart...";
	lost_text.setString(text);
}
