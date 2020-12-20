#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <SFML/Graphics.hpp>
#include <map>

#include "BaseState.hpp"

class Engine {
public:
	~Engine();

	void main_loop();
	void quit() { running = false; }


	static Engine* get_instance();

private:
	Engine();

	void handle_input();
	void update();
	void render() const;

	bool running;
	BaseState* current_state;

	std::map<StateId, BaseState*> state_machine;
};


#endif // !ENGINE_HPP
