#include "BaseState.hpp"

BaseState::BaseState(StateId id) : id (id), next_state(StateId::Null)
{
}
