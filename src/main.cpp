#include <iostream>
#include "..//include//server//blocking_server.h"

int main()
{   
    BlockingServer server(8080);
    server.Start();

    return 0;
}