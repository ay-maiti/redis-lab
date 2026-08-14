#pragma once

#include "protocol/command.h"

namespace redis_lab
{

class CommandDispatcher
{
public:
    void Execute(const Command& command);
};

} // namespace redis_lab