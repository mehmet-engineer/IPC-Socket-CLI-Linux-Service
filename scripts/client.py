import socket

socket_file = "/tmp/my_unix_socket"
buffer_size = 1024

client_socket = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)

try:

    client_socket.connect(socket_file)
    print("Client: connected to server.")

    query_data = "Hello world! from client.".encode()
    client_socket.send(query_data)

    response_data = client_socket.recv(buffer_size).decode()
    print("Client: received response:", response_data)

except:
    print("Client: connection failed.")

finally:
    client_socket.close()