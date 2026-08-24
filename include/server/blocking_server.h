#ifndef BLOCKING_SERVER_H
#define BLOCKING_SERVER_H

#include <cstdint>
#include "protocol/command_parser.h"
#include "storage/storage_engine.h"
#include "protocol/command_parser.h"
#include "dispatcher/command_dispatcher.h"
class BlockingServer
{
public:
    explicit BlockingServer(uint16_t port);
    ~BlockingServer() = default;

    BlockingServer(const BlockingServer&) = delete;
    BlockingServer& operator=(const BlockingServer&) = delete;

    BlockingServer(BlockingServer&&) = default;
    BlockingServer& operator=(BlockingServer&&) = default;

    void Start();

private:
    void HandleClient(int clientSocket);

    int server_fd_;
    uint16_t port_;
    StorageEngine storage_;
    redis_lab::CommandParser command_parser_;
    redis_lab::CommandDispatcher command_dispatcher_;
};

#endif