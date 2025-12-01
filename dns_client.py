import socket

server_address = ('localhost', 12345)
client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

while True:
    message = input("Enter domain or IP to resolve (or 'exit'): ")
    if message.lower() == 'exit':
        break
        
    client_socket.sendto(message.encode(), server_address)
    data, _ = client_socket.recvfrom(1024)
    print(f"Server Response: {data.decode()}")

client_socket.close()