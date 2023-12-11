#include "ipc_socket.hpp"

/**
 * @author: Mehmet Kahraman
 * @date: 11.12.2023
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

    int operation;
    int number1;
    int number2;

    std::vector<int> query_vector;
    std::vector<int> response_vector;

    if (strcmp(argv[1], "add") == 0)
    {
        operation = 1;
    }
    else if (strcmp(argv[1], "subtract") == 0)
    {
        operation = 2;
    }
    else if (strcmp(argv[1], "multiply") == 0)
    {
        operation = 3;
    }
    else if (strcmp(argv[1], "divide") == 0)
    {
        operation = 4;
    }
    else {
        std::cerr << "Client: Invalid operation." << std::endl;
        client.close_client_socket();
        std::exit(-1);
    }

    try {
        number1 = std::stoi(argv[2]);
        number2 = std::stoi(argv[3]);
    }
    catch (const std::exception& e) {
        std::cerr << "Error while parsing arguments: " << e.what() << std::endl;
        client.close_client_socket();
        std::exit(-1);
    }

    std::cout << "Client: Sending query: " << operation << " " << number1 << " " << number2 << std::endl;
    
    query_vector = {operation, number1, number2};
    client.send_query(query_vector);

    response_vector = client.get_response();
    std::cout << "Client: Received response: " << response_vector[0] << std::endl;

    client.close_client_socket();

    return 0;
}