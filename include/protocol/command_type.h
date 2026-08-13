#ifndef COMMAND_TYPE_H
#define COMMAND_TYPE_H

namespace redis_lab
{

enum class CommandType
{
    GET,
    SET,
    DEL,
    EXISTS,
    PING,
    UNKNOWN
};

} 

#endif