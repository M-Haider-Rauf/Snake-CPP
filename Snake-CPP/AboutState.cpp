#include "AboutState.hpp"
#include "Window.hpp"
#include "Assets.hpp"

AboutState::AboutState() 
	: BaseState(StateId::AboutState)
	, str_about(
R"(
Assalam-o-Alaikum!

This is the about page!
This is a snake game I made in C++.

-- Muhammad Haider Rauf

    (Press any key to go back)
)")
	, about_text(str_about, Assets::font)
{
	about_text.setFillColor(sf::Color::White);
	about_text.setPosition({50, 150});
}

void AboutState::handle_events(sf::Event& e)
{
	if (e.type == sf::Event::KeyPressed) {
		this->next_state = StateId::MenuState;
	}
}

void AboutState::update()
{
}

void AboutState::render() const
{
	g_window->draw(about_text);
}

void AboutState::on_enter()
{
}