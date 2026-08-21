#pragma once

#include <optional>
#include <string>

namespace redis_lab
{

enum class CommandStatus
{
    OK,
    KEY_NOT_FOUND,
    INVALID_KEY,
    INVALID_COMMAND
};

struct CommandResult
{
    CommandStatus status;
    std::optional<std::string> value;
};

} // namespace redis_lab