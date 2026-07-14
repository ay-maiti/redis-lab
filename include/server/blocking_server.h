#ifndef BLOCKING_SERVER_H
#define BLOCKING_SERVER_H

#include <cstdint>

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
};

#endif