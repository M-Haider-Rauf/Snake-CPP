#include "MenuState.hpp"
#include "Assets.hpp"
#include "Constants.hpp"
#include "Window.hpp"
#include "Engine.hpp"
#include <SFML/Graphics.hpp>

MenuState::MenuState()
	: BaseState(StateId::MenuState)
	, title_text(new sf::Text("SNAKE", Assets::font))
	, texts { 
		new sf::Text("Play", Assets::font), 
		new sf::Text("About", Assets::font),
		new sf::Text ("QuiT", Assets::font)
	}
	, curr_option(0)
{
	title_text->setFillColor(sf::Color::Blue);
	title_text->setCharacterSize(80u);
	auto bound = title_text->getGlobalBounds();
	sf::Vector2f title_pos = {
		((float)WIN_WIDTH - bound.width) * 0.5f,
		100.0f
	};

	title_text->setPosition(title_pos);

	for (size_t i = 0; i < texts.size(); ++i) {
		texts[i]->setCharacterSize(40u);
		float x = 320.0f;
		float y = (230.0f) + 120.0f * i;
		texts[i]->setPosition({x, y});
		texts[i]->setFillColor(sf::Color::Red);
	}
}

MenuState::~MenuState()
{
	
	delete title_text;
	for (sf::Text* text : texts) {
		delete text;
	}
}

void MenuState::handle_events(sf::Event& event_q)
{
	if (event_q.type == sf::Event::KeyPressed) {
		switch (event_q.key.code) {
		case  sf::Keyboard::Down:
			++curr_option;
			if (curr_option >= texts.size()) {
				curr_option = 0;
			}
			break;

		case sf::Keyboard::Up:
			if (curr_option == 0) {
				curr_option = texts.size() - 1;
			} 
			else {
				--curr_option;
			}
			break;

		case sf::Keyboard::Enter:

			switch (curr_option) {
			case 0:
				this->next_state = StateId::PlayState;
				break;

			case 1:
				this->next_state = StateId::AboutState;
				break;

			case 2:
				Engine::get_instance()->quit();
				break;

			default:
				break;
			}

			break;

		default:
			break;
		}
	}
}

void MenuState::update()
{
}

void MenuState::render() const
{
	g_window->draw(*title_text);
	for (size_t i = 0; i < texts.size(); ++i) {
		if (i == curr_option) {
			texts[i]->setFillColor(sf::Color::Green);
		}
		else {
			texts[i]->setFillColor(sf::Color::Red);
		}
		g_window->draw(*texts[i]);
	}
}

void MenuState::on_enter()
{
	curr_option = 0;
}
