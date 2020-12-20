#ifndef BASE_STATE_HPP
#define BASE_STATE_HPP

namespace sf {
	class Event;
}

enum struct StateId {
	Null = 0, PlayState, MenuState, EndState, AboutState
};

class BaseState {
public:
	BaseState(StateId);
	StateId get_next_state() const { return next_state; }
	void no_next_state() { this->next_state = StateId::Null; }

	virtual void handle_events(sf::Event& event) = 0;
	virtual void update() = 0;
	virtual void render() const = 0;
	
	virtual void on_enter() = 0;

	const StateId id;

protected:
	StateId next_state;
};

#endif // !BASE_STATE_HPP
