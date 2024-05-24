#include "veb/engine/StateManager.hpp"

namespace veb {

std::stack<std::function<void(double)>> StateManager::stack;

} // namespace veb
