#include "protocol/command_parser.h"

namespace redis_lab
{

std::optional<Command> CommandParser::Parse(std::string_view input) const
{
    if (input.empty())
    {
        return std::nullopt;
    }

    std::vector<std::string_view> tokens;
    
    //split message into tokens
    size_t start = 0;

    for (size_t end = 0; end <= input.size(); end++)
    {
        if (end == input.size() || input[end] == ' ')
        {
            if (end > start)
            {
                tokens.push_back(input.substr(start, end - start));
            }

            start = end + 1;
        }
    }

    if (tokens.empty())
    {
        return std::nullopt;
    }
    
    //create & fill command details
    Command command;

    const auto& command_name = tokens[0];

    if (command_name == "GET")
    {
        command.type = CommandType::GET;
    }
    else if (command_name == "SET")
    {
        command.type = CommandType::SET;
    }
    else if (command_name == "DEL")
    {
        command.type = CommandType::DEL;
    }
    else if (command_name == "EXISTS")
    {
        command.type = CommandType::EXISTS;
    }
    else if (command_name == "PING")
    {
        command.type = CommandType::PING;
    }
    else
    {
        return std::nullopt;//UNKNOWN
    }

    const size_t arg_count = tokens.size() - 1;

    switch (command.type)
    {
        case CommandType::PING:
            if (arg_count != 0)
                return std::nullopt;
            break;

        case CommandType::GET:
        case CommandType::DEL:
        case CommandType::EXISTS:
            if (arg_count != 1)
                return std::nullopt;
            break;

        case CommandType::SET:
            if (arg_count != 2)
                return std::nullopt;
            break;

        default:
            return std::nullopt;
    }

    for (size_t i = 1; i < tokens.size(); ++i)
    {
        command.args.emplace_back(tokens[i]);
    }

    return command;
}

} // namespace