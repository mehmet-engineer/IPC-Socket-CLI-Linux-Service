#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <signal.h>
#include <chrono>
#include <thread>

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

        int client_fd;
        int query_buffer_size;
        char query_buffer;
        ssize_t query_bytesRead;

        // query process definitions
        int operation;
        int number1;
        int number2;
        int result;
        int resp_buffer_size;
        char resp_buffer;

        // server definitions
        int socket_client;


 
    public:

        // Constructor
        Socket();

        void open_socket();
        void close_socket();

        void create_signal_handler(int signum);

        // server member functions
        void bind_server_to_socket();
        void listen_client();
        void wait_for_accept();
        void get_query();
        void process_query();
        void send_response();

        // client member functions
        void connect_to_server();
        void send_query();
        void get_response();

        // Destructor
        ~Socket();

};