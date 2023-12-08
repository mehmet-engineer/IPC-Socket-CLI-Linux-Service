#include "ipc_socket.hpp"

/**
 * @author: Mehmet Kahraman
 * @date: 08.12.2023
 * @about: CLI Client program for calculator app
 */

int main(int argc, char* argv[]) 
{

    Socket client;

    client.open_client_socket();
    client.connect_to_server();

    if (argc != 4) {
        std::cerr << "Client: Invalid number of arguments." << std::endl;
        client.close_client_socket();
        std::exit(-1);
    }

    if (strcmp(argv[1], "add") == 0)
    {

    }
    else if (strcmp(argv[1], "subtract") == 0)
    {
        
    }
    else if (strcmp(argv[1], "multiply") == 0)
    {
        
    }
    else if (strcmp(argv[1], "divide") == 0)
    {
        
    }
    else {
        std::cerr << "Client: Invalid operation." << std::endl;
        client.close_client_socket();
        std::exit(-1);
    }

    // send query

    // get response

    client.close_client_socket();

    return 0;
}