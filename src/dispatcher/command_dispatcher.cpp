#include "dispatcher/command_dispatcher.h"

#include <iostream>

namespace redis_lab
{

CommandDispatcher::CommandDispatcher(StorageEngine& storage)
    : storage_(storage)
{
}

CommandResult CommandDispatcher::Execute(const Command& command)
{
    switch (command.type)
    {
        case CommandType::SET:
        {
            auto status = storage_.Set(command.args[0], command.args[1]);

            if (status == Status::INVALID_KEY)
            {
                return {CommandStatus::INVALID_KEY, std::nullopt};
            }

            return {CommandStatus::OK, std::nullopt};
        }

        case CommandType::GET:
        {
            auto value = storage_.Get(command.args[0]);

            if (!value)
            {
                return {CommandStatus::KEY_NOT_FOUND, std::nullopt};
            }

            return {CommandStatus::OK, *value};
        }

        case CommandType::DEL:
        {
            auto status = storage_.Delete(command.args[0]);

            if (status == Status::KEY_NOT_FOUND)
            {
                return {CommandStatus::KEY_NOT_FOUND, std::nullopt};
            }

            if (status == Status::INVALID_KEY)
            {
                return {CommandStatus::INVALID_KEY, std::nullopt};
            }

            return {CommandStatus::OK, std::nullopt};
        }

        case CommandType::EXISTS:
        {
            return {
                CommandStatus::OK,
                storage_.Exists(command.args[0]) ? "1" : "0"
            };
        }

        case CommandType::PING:
        {
            return {
                CommandStatus::OK,
                "PONG"
            };
        }

        default:
        {
            return {CommandStatus::INVALID_COMMAND, std::nullopt};
        }
    }
}

} // namespace redis_lab