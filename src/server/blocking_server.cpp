#include <iostream>
#include <unistd.h>
#include <cerrno>
#include <cstdint> //uint16_t
#include <cstdio> //perror and printf
#include <cstdlib> //exit
#include <cstring> //memset
#include <arpa/inet.h> //socket functions
#include "server/blocking_server.h"

constexpr int kBacklog = 5;

BlockingServer::BlockingServer(uint16_t port)
    : server_fd_(-1),
      port_(port),
      storage_(),
      command_parser_(),
      command_dispatcher_(storage_)
{
}

void BlockingServer::HandleClient(int clientSocket){
    char buffer[1024] = {0};
    const char *resp = "OK";
    while(true){
        memset(buffer, 0, sizeof(buffer));
        int val_read = read(clientSocket, buffer, 1024);
        if(val_read <=0){
            std::cout<<"client disconnected or error occured.\n";
            break;
        }
        std::cout<<"Received: "<<buffer<<std::endl;
        std::string_view request(buffer, val_read);
        auto command = command_parser_.Parse(request);
        if (!command)
        {
            std::cout << "Invalid command\n";
            continue;
        }
        redis_lab::CommandResult result = command_dispatcher_.Execute(*command);
        std::cout << "Command type: "
                << static_cast<int>(command->type) << '\n';

        for (const auto& arg : command->args)
        {
            std::cout << "Arg: " << arg << '\n';
        }
        std::string response;

        switch (result.status)
        {
            case redis_lab::CommandStatus::OK:
                response = result.value.value_or("OK");
                break;

            case redis_lab::CommandStatus::KEY_NOT_FOUND:
                response = "KEY_NOT_FOUND";
                break;

            case redis_lab::CommandStatus::INVALID_KEY:
                response = "INVALID_KEY";
                break;

            case redis_lab::CommandStatus::INVALID_COMMAND:
                response = "INVALID_COMMAND";
                break;
        }
        response += "\n";
        send(clientSocket, response.data(), response.size(), 0);
        std::cout<<"Response sent to client.\n";
    }
    close(clientSocket);
    std::cout<<"Connection" <<clientSocket<< "closed by server thread.\n";
}

void BlockingServer::Start(){
    int new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    //1. create TCP socket
    server_fd_ = socket(AF_INET, SOCK_STREAM, 0);
    if(server_fd_ < 0){
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    //2. configure the server address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port_);

    //3. bind the socket to IP and port
    if(bind(server_fd_, (struct sockaddr*)&address, sizeof(address))<0){
        perror("bind failed");
        close(server_fd_);
        exit(EXIT_FAILURE);
    }

    //4. listen
    if(listen(server_fd_, kBacklog)<0){
        perror("listen failed");
        close(server_fd_);
        exit(EXIT_FAILURE);
    }

    std::cout<<"server listening on port "<<port_<<"...\n";

    //loop to accept and handle client connections
    while(true){
        std::cout<<"waiting for new conection..."<<std::endl;
        new_socket = accept(server_fd_, (struct sockaddr*)&address, (socklen_t*) &addrlen);
        if(new_socket<0){
            std::cerr<<"accept failed"<<strerror(errno)<<std::endl;
            continue;   //go back to waiting for new connection
        }
        std::cout<<"connection "<<new_socket<<" accepted from client"<<std::endl;
        HandleClient(new_socket);
    }

    close(server_fd_);
}