#include "protocol/command_parser.h"

namespace redis_lab
{

std::optional<Command> CommandParser::Parse(std::string_view input) const
{
    return std::nullopt;
}

}