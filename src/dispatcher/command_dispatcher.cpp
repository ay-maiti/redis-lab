#include "dispatcher/command_dispatcher.h"

#include <iostream>

namespace redis_lab
{

CommandDispatcher::CommandDispatcher(StorageEngine& storage)
    : storage_(storage)
{
}

void CommandDispatcher::Execute(const Command& command)
{
    switch (command.type)
    {
        case CommandType::SET:
        {
            auto status = storage_.Set(command.args[0], command.args[1]);

            std::cout << "SET status: "
                      << static_cast<int>(status)
                      << '\n';

            break;
        }

        case CommandType::GET:
        {
            auto value = storage_.Get(command.args[0]);

            if (value)
            {
                std::cout << "GET value: " << *value << '\n';
            }
            else
            {
                std::cout << "GET: key not found\n";
            }

            break;
        }

        case CommandType::DEL:
        {
            auto status = storage_.Delete(command.args[0]);

            std::cout << "DEL status: "
                      << static_cast<int>(status)
                      << '\n';

            break;
        }

        case CommandType::EXISTS:
        {
            bool exists = storage_.Exists(command.args[0]);

            std::cout << "EXISTS: "
                      << exists
                      << '\n';

            break;
        }

        case CommandType::PING:
        {
            std::cout << "PONG\n";
            break;
        }

        default:
            break;
    }
}

} // namespace redis_lab