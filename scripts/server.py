import socket
import os

print("Server program started")

socket_file = "/tmp/my_unix_socket"

if os.path.exists(socket_file):
    os.remove(socket_file)

server_socket = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
server_socket.bind(socket_file)

num_clients = 1
server_socket.listen(num_clients)

buffer_size = 1024

print("Server started to listening... \n")

while True:
    
    client_socket, client_address = server_socket.accept()
    print("Server: client accepted.")

    query_data = client_socket.recv(buffer_size).decode()
    print("Server: received query: ", query_data)

    if query_data[0] == -1:
        break

    response_data = "Hello world! from server.".encode()
    client_socket.send(response_data)

    client_socket.close()
    print()


print("Server program closed.")
server_socket.close()