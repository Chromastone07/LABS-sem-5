
import socket

client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_address = ('localhost', 12345)

while True:
    query = input("\nEnter Hostname or IP (or 'exit' to quit): ")
    if query.lower() == 'exit':
        break
    
    client.sendto(query.encode(), server_address)
    
    data, _ = client.recvfrom(1024)
    print("Resolved Address:", data.decode())

client.close()
print("Client closed.")