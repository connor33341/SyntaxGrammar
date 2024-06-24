import socket
import re

def load_syntax_map(file_path):
    syntax_map = []
    with open(file_path, 'r') as file:
        for line in file:
            if line.strip():
                token_name, pattern = line.split(maxsplit=1)
                syntax_map.append((token_name, re.compile(pattern.strip())))
    return syntax_map

def tokenize_input(input_text, syntax_map):
    tokens = []
    while input_text:
        match = None
        for token_name, pattern in syntax_map:
            match = pattern.match(input_text)
            if match:
                tokens.append((token_name, match.group()))
                input_text = input_text[match.end():]
                break
        if not match:
            tokens.append(('UNKNOWN', input_text[0]))
            input_text = input_text[1:]
    return tokens

def start_server(host='0.0.0.0', port=12345, syntax_map_file='syntax.smap'):
    syntax_map = load_syntax_map(syntax_map_file)
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server_socket:
        server_socket.bind((host, port))
        server_socket.listen(5)
        print(f"Server started and listening on {host}:{port}")

        while True:
            client_socket, client_address = server_socket.accept()
            with client_socket:
                print(f"Connection from {client_address}")
                while True:
                    data = client_socket.recv(1024).decode()
                    if not data:
                        break
                    print(f"Received data: {data}")
                    tokens = tokenize_input(data, syntax_map)
                    response = "\n".join([f"{token[0]}: {token[1]}" for token in tokens])
                    client_socket.sendall(response.encode())

if __name__ == "__main__":
    start_server()
