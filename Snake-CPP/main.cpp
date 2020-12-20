#include "Engine.hpp"

int main()
{
	Engine* engine = Engine::get_instance();
	engine->main_loop();
}