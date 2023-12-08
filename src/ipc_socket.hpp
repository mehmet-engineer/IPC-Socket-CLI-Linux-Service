#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <signal.h>
#include <chrono>
#include <thread>
#include <vector>
#include <cstring>

/**
 * @author: Mehmet Kahraman
 * @date: 08.12.2023
 * @about: Inter process communication with UNIX domain sockets
 */

class Socket {

    private:

        // socket definitions
        const char* socket_path;
        int domain;
        int type;
        int protocol;

        // server definitions
        int socket_server;
        sockaddr_un addr;
        int backlog;

        // query response definitions
        int operation;
        int number1;
        int number2;
        int result;

        // client definitions
        int socket_client;

 
    public:

        // query response definitions
        int client_fd;
        int query_buffer_size;
        std::vector<int> query_vector;
        int resp_buffer_size;
        std::vector<int> resp_vector;
        ssize_t query_bytesRead;

        // Constructor
        Socket();

        // socket member functions
        void open_server_socket();
        void open_client_socket();
        void close_server_socket();
        void close_client_socket();

        // server member functions
        void bind_server_to_socket();
        void listen_client();
        void wait_and_accept();
        void get_query();
        void send_response();

        // client member functions
        void connect_to_server();
        void send_query();
        void get_response();

};