#pragma once

namespace veb {

class State {
public:
    State() = default;
    virtual ~State() = default;

    virtual void Run(double delta) = 0;
};

} // namespace veb
