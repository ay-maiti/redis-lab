#pragma once

#include "protocol/command.h"
#include "storage/storage_engine.h"
#include "command_result.h"

namespace redis_lab
{

class CommandDispatcher
{
public:
    explicit CommandDispatcher(StorageEngine& storage);

    CommandResult Execute(const Command& command);

private:
    StorageEngine& storage_;
};

} // namespace redis_lab