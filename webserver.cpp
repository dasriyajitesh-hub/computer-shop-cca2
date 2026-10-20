#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <string>

static const std::string page = R"HTML(<!doctype html>
<html lang="en"><head><meta charset="utf-8"><meta name="viewport" content="width=device-width,initial-scale=1">
<title>Computer Shop</title><style>body{font-family:Arial,sans-serif;max-width:850px;margin:40px auto;padding:0 18px;color:#222}h1{color:#174ea6}.items{display:grid;grid-template-columns:repeat(auto-fit,minmax(180px,1fr));gap:12px}.item{border:1px solid #ddd;border-radius:10px;padding:14px;background:#f8faff}.tag{color:#137333;font-weight:bold}</style></head>
<body><h1>Computer Shop</h1><p>Welcome to the Computer Parts Store.</p><p class="tag">Application status: Running on C++</p><div class="items">
<div class="item"><b>CPU</b><p>Rs 50,000</p></div><div class="item"><b>GPU</b><p>Rs 35,000</p></div><div class="item"><b>RAM</b><p>Rs 8,000</p></div><div class="item"><b>SSD</b><p>Rs 15,000</p></div><div class="item"><b>Motherboard</b><p>Rs 16,000</p></div><div class="item"><b>Monitor</b><p>Rs 45,000</p></div><div class="item"><b>Laptop</b><p>Rs 55,000</p></div></div><p>Deployed through Jenkins CI/CD, Docker, Amazon ECR and Kubernetes.</p></body></html>)HTML";

int main() {
    int server = socket(AF_INET, SOCK_STREAM, 0);
    if (server < 0) { std::cerr << "Could not create socket\n"; return 1; }
    int opt = 1; setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    sockaddr_in address{}; address.sin_family = AF_INET; address.sin_addr.s_addr = INADDR_ANY; address.sin_port = htons(5000);
    if (bind(server, reinterpret_cast<sockaddr*>(&address), sizeof(address)) < 0 || listen(server, 20) < 0) { std::cerr << "Could not bind/listen on port 5000\n"; close(server); return 1; }
    std::cout << "Computer Shop C++ server listening on port 5000\n";
    while (true) {
        int client = accept(server, nullptr, nullptr); if (client < 0) continue;
        char buffer[2048]{}; ssize_t n = read(client, buffer, sizeof(buffer)-1);
        std::string request(buffer, n > 0 ? static_cast<size_t>(n) : 0);
        std::string body = request.rfind("GET /health", 0) == 0 ? "OK" : page;
        std::string type = request.rfind("GET /health", 0) == 0 ? "text/plain" : "text/html; charset=utf-8";
        std::string response = "HTTP/1.1 200 OK\r\nContent-Type: " + type + "\r\nContent-Length: " + std::to_string(body.size()) + "\r\nConnection: close\r\n\r\n" + body;
        (void)write(client, response.data(), response.size()); close(client);
    }
    close(server); return 0;
}
