#include "ipc_socket.hpp"

/**
 * @author: Mehmet Kahraman
 * @date: 08.12.2023
 * @about: Server program and service for calculator app
 */
int main() 
{   
    std::cout << "Server process started." << std::endl;

    Socket server;

    server.open_server_socket();
    server.bind_server_to_socket();
    server.listen_client();

    std::cout << "Server service waiting for client connection..." << std::endl;

    server.query_buffer_size = 3;
    server.resp_buffer_size = 1;

    int calc_result = 0;

    while (true)
    {
        server.wait_and_accept();
        server.get_query();

        if (server.query_vector[0] == 1)
        {
            calc_result = server.query_vector[1] + server.query_vector[2];
        }
        else if (server.query_vector[0] == 2) 
        {
            calc_result = server.query_vector[1] - server.query_vector[2];
        }
        else if (server.query_vector[0] == 3) 
        {
            calc_result = server.query_vector[1] * server.query_vector[2];
        }
        else if (server.query_vector[0] == 4)
        {
            calc_result = server.query_vector[1] / server.query_vector[2];
        }
        else {
            std::cerr << "Server: Invalid operation from client." << std::endl;
            server.close_server_socket();
            return -1;
        }

        server.resp_vector.clear();
        server.resp_vector.push_back(calc_result);
        server.send_response();
        
        std::cout << std::endl;
        close(server.client_fd);
    }

    std::cout << "Service server closing." << std::endl;
    server.close_server_socket();

    return 0;
}