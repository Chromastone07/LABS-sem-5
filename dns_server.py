import socket
import sys

DNS_TABLE = {
    "www.google.com": "142.250.190.68",
    "www.yahoo.com": "98.137.11.163",
    "www.dypitpune.edu.in": "192.168.1.100",
    "192.168.1.100": "www.dypitpune.edu.in",
    "142.250.190.68": "www.google.com"
}

HOST = 'localhost'
PORT = 12345
BUFFER_SIZE = 1024

def start_dns_server():
  
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    try:
        server_socket.bind((HOST, PORT))
        print(f"[*] DNS Server started on {HOST}:{PORT}")
        print("[*] Press Ctrl+C to stop the server.")

        while True:
            data, addr = server_socket.recvfrom(BUFFER_SIZE)
            
            query = data.decode().strip()
            print(f"\nReceived query: '{query}' from {addr}")

            response = DNS_TABLE.get(query, "No record found")
            
            server_socket.sendto(response.encode(), addr)
            print(f"Sent response: '{response}'")

    except KeyboardInterrupt:
        print("\n[!] Server stopping...")
    except Exception as e:
        print(f"\n[!] An error occurred: {e}")
    finally:
        server_socket.close()
        print("[*] Socket closed.")

if __name__ == "__main__":
    start_dns_server()