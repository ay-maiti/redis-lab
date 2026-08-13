#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <vector>

#include "protocol/command_type.h"

namespace redis_lab
{

struct Command
{
    CommandType type{CommandType::UNKNOWN};
    std::vector<std::string> args;
};

}

#endif