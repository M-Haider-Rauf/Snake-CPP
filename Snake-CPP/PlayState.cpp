#include "PlayState.hpp"
#include "Engine.hpp"
#include "Window.hpp"

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Assets.hpp"
#include "Constants.hpp"
#include <iostream>
#include <map>

int PlayState::score = 0;

PlayState::PlayState() 
	: BaseState(StateId::PlayState)
	, snake()
	, clock()
	, food()
	, texts()
{

	texts["score"] = sf::Text("Score: 0", Assets::font);
	texts["score"].setFillColor(sf::Color::Green);
	texts["score"].setCharacterSize(30);
	texts["score"].setPosition(sf::Vector2f(50, GRID_HEIGHT + 10));

	texts["lives"] = sf::Text("Lives: 5", Assets::font);
	texts["lives"].setFillColor(sf::Color::Green);
	texts["lives"].setCharacterSize(30);
	texts["lives"].setPosition(sf::Vector2f(GRID_WIDTH - 200, GRID_HEIGHT + 10));

	texts["pause"] = sf::Text("", Assets::font);
	texts["pause"].setFillColor(sf::Color::Red);
	texts["pause"].setCharacterSize(30);
	texts["pause"].setPosition(sf::Vector2f(GRID_WIDTH - 450, GRID_HEIGHT + 10));

	this->on_enter();
}

PlayState::~PlayState()
{
}

void PlayState::handle_events(sf::Event& event_q)
{
	if (event_q.type == sf::Event::KeyPressed) {

		Direction curr_dir = snake.get_head_dir();

		switch (event_q.key.code) {
		case sf::Keyboard::Escape: 
			Engine::get_instance()->quit();
			break;
			
		case sf::Keyboard::P:
			paused = !paused;
			break;

		case sf::Keyboard::A:
			if (curr_dir != Direction::Right && !paused) snake.move_dir = Direction::Left;
			break;

		case sf::Keyboard::D:
			if (curr_dir != Direction::Left && !paused) snake.move_dir = Direction::Right;
			break;

		case sf::Keyboard::W:
			if (curr_dir != Direction::Down && !paused) snake.move_dir = Direction::Up;
			break;

		case sf::Keyboard::S:
			if (curr_dir != Direction::Up && !paused) snake.move_dir = Direction::Down;
			break;
			
		default:
			break;
		}
	}
}


void PlayState::update()
{
	if (paused) texts["pause"].setString("PAUSED!");
	else texts["pause"].setString("");

	if (paused || clock.getElapsedTime().asSeconds() < 1.0f / update_ps) {
		return;
	}

	snake.update();

	int col = snake.collide_with_body();

	if (col) {
		int p = snake.len() - col;

		snake.cut(col);
		score -=  5 * p;
		--lives;
	}

	if (lives == 0) {
		next_state = StateId::EndState;
	}

	if (snake.collide_with_food(food)) {
		snake.grow();
		food.reset();
		score += 10;
	}

	texts["score"].setString("Score: " + std::to_string(score));
	texts["lives"].setString("Lives: " + std::to_string(lives));

	clock.restart();
}

void PlayState::render() const
{
	this->draw_field();
	food.render();
	snake.render();

	for (const auto& text : texts) g_window->draw(text.second);
}

void PlayState::on_enter()
{
	this->snake = Snake(GRID_COLS / 2, GRID_COLS / 2);
	for (int i = 1; i <= 3; ++i) snake.grow();

	score = 0;
	lives = 5;
	food.reset();
	clock.restart();
}

void PlayState::draw_field() const
{
	bool flag = true;
	for (size_t y = 0; y < GRID_ROWS; ++y) {
		//flag = !flag;

		for (size_t x = 0; x < GRID_COLS; ++x) {
			sf::RectangleShape rect(sf::Vector2f(CELL_SIZE, CELL_SIZE));
			rect.setPosition(sf::Vector2f(x * CELL_SIZE, y * CELL_SIZE));

			if (flag) rect.setFillColor(sf::Color(34, 139, 34)); // aka lawn green
			else rect.setFillColor(sf::Color(0, 100, 0)); //A darker shade of green

			g_window->draw(rect);

			flag = !flag;
		}
	}
}
