


import socket

dns_table = {
    "www.google.com": "142.250.190.68",
    "www.yahoo.com": "98.137.11.163",
    "www.dypitpune.edu.in": "192.168.1.100",
    "192.168.1.100": "www.dypitpune.edu.in",
    "142.250.190.68": "www.google.com"
}

server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server.bind(('localhost', 12345))

print("DNS Server started... waiting for queries")

while True:
    data, addr = server.recvfrom(1024)
    query = data.decode()
    print(f"Received query: {query}")
    
    response = dns_table.get(query, "No record found")
    server.sendto(response.encode(), addr)
    
    print(f"Sent response: {response}\n")