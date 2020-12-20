#include "Engine.hpp"
#include "Window.hpp"
#include "Constants.hpp"

#include <SFML/Graphics.hpp>
#include "PlayState.hpp"
#include "EndState.hpp"
#include "MenuState.hpp"
#include "AboutState.hpp"
#include "Assets.hpp"

Engine::Engine() : running(true), current_state(nullptr), state_machine()
{
	g_window = new sf::RenderWindow(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), 
									"Snake", sf::Style::Close);
	g_window->setVerticalSyncEnabled(true);
	auto win_pos = g_window->getPosition();
	win_pos.y = 0;
	g_window->setPosition(win_pos);

	Assets::load();

	state_machine.insert({ StateId::PlayState , new PlayState });
	state_machine.insert({ StateId::EndState, new EndState });
	state_machine.insert({ StateId::MenuState, new MenuState });
	state_machine.insert({ StateId::AboutState, new AboutState });
	current_state = state_machine[StateId::MenuState];
}

Engine::~Engine()
{

	for (auto it = state_machine.begin(); it != state_machine.end(); ++it) {
		delete it->second;
	}

	//g_window->close();
	delete g_window;
	g_window = nullptr;
}


void Engine::handle_input()
{
	sf::Event event_q;
	while (g_window->pollEvent(event_q)) {
		if (event_q.type == sf::Event::Closed) {
			this->quit();
		}
		current_state->handle_events(event_q);
	}
}

void Engine::update()
{
	current_state->update();
	StateId next_state = current_state->get_next_state();

	if (next_state != StateId::Null) {
		current_state = state_machine[next_state];
		current_state->no_next_state();
		current_state->on_enter();
	}
}

void Engine::render() const
{
	g_window->clear();

	current_state->render();

	g_window->display();
}

void Engine::main_loop()
{
	while (running) {
		this->handle_input();
		this->update();
		this->render();
	}
}

Engine* Engine::get_instance()
{
	static Engine engine;
	return &engine;
}
