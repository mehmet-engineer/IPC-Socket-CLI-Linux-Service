#include "ipc_socket.hpp"

/**
 * @author: Mehmet Kahraman
 * @date: 11.12.2023
 * @about: Inter process communication with UNIX domain sockets
 */

static void signal_handler(int signum)
{
    std::cout << " !! Received signal: " << signum << std::endl;
    std::exit(-1);
}

// Constructor
Socket::Socket() 
{
    // create domain socket
    socket_path = "/tmp/my_unix_socket";
    domain = AF_UNIX;
    type = SOCK_STREAM;
    protocol = 0;

    // create signals to signal handler function
    signal(SIGINT, signal_handler);
    signal(SIGKILL, signal_handler);
    signal(SIGTERM, signal_handler);

    // server address for binding to socket
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path) - 1);

    // server parameters
    int backlog = 5;

} 

void Socket::open_server_socket() 
{
    socket_server = socket(domain, type, protocol);

    if (socket_server == -1) {
        std::cerr << "Server socket could not be created." << std::endl;
        close_server_socket();
        std::exit(-1);
    }

    unlink(socket_path);
}

void Socket::open_client_socket() 
{
    socket_client = socket(domain, type, protocol);

    if (socket_client == -1) {
        std::cerr << "Client socket could not be created." << std::endl;
        close_client_socket();
        std::exit(-1);
    }
}

void Socket::close_server_socket() 
{
    close(socket_server);
}

void Socket::close_client_socket() 
{
    close(socket_client);
}

void Socket::bind_server_to_socket()
{
    if (bind(socket_server, (sockaddr*)&addr, sizeof(addr)) == -1) {
        std::cerr << "Socket could not be bound to socket." << std::endl;
        close_server_socket();
        std::exit(-1);
    }

    std::cout << "Server socket opened with " << addr.sun_family << " domain." << std::endl;
    std::cout << "Server socket opened with " << addr.sun_path << " path." << std::endl;
}

void Socket::listen_client()
{
    std::cout << "Server started to listening." << std::endl;

    int listen_result = listen(socket_server, backlog);

    if (listen_result == -1) {
        std::cerr << "Server Listen failed." << std::endl;
        close_server_socket();
        std::exit(-1);
    }
}

void Socket::wait_and_accept()
{
    client_fd = accept(socket_server, NULL, NULL);

    if (client_fd == -1) {
        std::cerr << "Server: Client connection could not be accepted." << std::endl;
        close_server_socket();
        std::exit(-1);
    }

    std::cout << "Server accepted client connection." << std::endl;
}

std::vector<int> Socket::get_query()
{      
    char buffer[query_buffer_size];
    query_bytesRead = read(client_fd, buffer, sizeof(buffer));

    if (query_bytesRead == -1) {
        std::cerr << "Server: Error reading from socket. bytesRead failed." << std::endl;
        close_server_socket();
        std::exit(-1);
    }

    std::vector<int> query_vec(query_buffer_size);
    for (int i=0; i<query_buffer_size; i++) {
        query_vec[i] = buffer[i];
        std::cout << "Server: Received query[" << i << "]: " << static_cast<int>(buffer[i]) << std::endl;
    }

    return query_vec;
}

void Socket::send_response(std::vector<int> &resp_vector)
{   
    char resp_buffer[resp_vector.size()];
    for (int i=0; i<resp_vector.size(); i++) {
        resp_buffer[i] = resp_vector[i];
    }
    auto write_result = write(client_fd, resp_buffer, sizeof(resp_buffer));

    if (write_result == -1) {
        std::cerr << "Server: Could not write response to client." << std::endl;
        close_server_socket();
        std::exit(-1);
    }

    for (int i=0; i<resp_vector.size(); i++) {
        std::cout << "Server: Sent response[" << i << "]: " << static_cast<int>(resp_buffer[i]) << std::endl;
    }
}

void Socket::connect_to_server()
{
    if (connect(socket_client, (struct sockaddr*) &addr, sizeof(struct sockaddr_un)) == -1) 
    {   
        std::cerr << "Client could not connect to server socket." << std::endl;
        std::exit(-1);
    }

    std::cout << "Client connected to server. \n" << std::endl;
}

void Socket::send_query(std::vector<int> &query_vector)
{   
    char query_buffer[query_vector.size()];
    for (int i=0; i<query_vector.size(); i++) {
        query_buffer[i] = query_vector[i];
    }
    auto write_result = write(socket_client, query_buffer, sizeof(query_buffer));

    if (write_result == -1) {
        std::cerr << "Client: Could not write queryto socket." << std::endl;
        close_client_socket();
        std::exit(-1);
    }
}

std::vector<int> Socket::get_response()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    char result_buffer[resp_buffer_size];

    resp_bytesRead = read(socket_client, &result_buffer, sizeof(result_buffer));

    if (resp_bytesRead == -1) {
        std::cerr << "Client: Could not read response from server." << std::endl;
        close_client_socket();
        std::exit(-1);
    }

    std::vector<int> result_vec(resp_buffer_size);
    for (int i=0; i<resp_buffer_size; i++) {
        result_vec[i] = result_buffer[i];
    }

    return result_vec;
}