#pragma once

#include <optional>
#include <string_view>

#include "protocol/command.h"

namespace redis_lab
{

class CommandParser
{
public:
    std::optional<Command> Parse(std::string_view input) const;
};

}