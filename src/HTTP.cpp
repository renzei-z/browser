#include <HTTP.h>
#include <URL.h>
#include <RC/SV.h>
#include <RC/String.h>

#if defined(__linux__)
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#else
#error "Unsupported operating system."
#endif

RC::String HTTPClient::get(const char *url) {
    RC::SV url_sv(url);
    const char *domain_name = URL::extract_domain_name(url_sv).as_cstr();

    const char *host = resolve_host(domain_name);
    if (!host) {
        printf("Could not resolve the host for URL: %s.\n", url);
        return nullptr;
    }
    printf("Host found: %s\n", host);

    int sockfd = socket_create(host);

    if (sockfd < 0) {
        printf("Could not open a socket to %s: %s.\n", host, strerror(errno));
        return nullptr;
    }
    
    RC::String request = "GET " + RC::String(url) + " HTTP/1.1\r\n"
                        + "Host: " + RC::String(domain_name) + "\r\n"
                        + "Connection: close\r\n\r\n";

    send(sockfd, request.as_cstr(), request.len(), 0);

    printf("----------\nSent request: %s\n----------\n", request.as_cstr());

    RC::String response;
    char buffer[4096];
    while (true) {
        ssize_t bytes_received = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received <= 0) {
            break; // Connection closed
        }
        buffer[bytes_received] = '\0'; // Null-terminate the buffer
        response.append(buffer);
    }

    close(sockfd); 
    delete[] domain_name;

    printf("----------\nReceived response: %s\n----------\n", response.as_cstr());
    return response;
}

const char *HTTPClient::resolve_host(const char *url) {
    struct addrinfo hints, *res, *p;
    static char ip_string[INET6_ADDRSTRLEN];

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    int status = getaddrinfo(url, NULL, &hints, &res);
    if (status != 0) {
        printf("Could not resolve hostname for URL: %s. (getaddrinfo) - status %d.\n", url, status);
        return nullptr;
    }

    for (p = res; p != nullptr; p = p->ai_next) {
        void *addr;
        const char *ipver;

        if (p->ai_family == AF_INET) { // IPV4
            struct sockaddr_in* ipv4 = (struct sockaddr_in*)p->ai_addr;
            addr = &(ipv4->sin_addr);
            ipver = "IPv4";
        } else { // IPV6
            struct sockaddr_in6* ipv6 = (struct sockaddr_in6*)p->ai_addr;
            addr = &(ipv6->sin6_addr);
            ipver = "IPv6";
        }
        inet_ntop(p->ai_family, addr, ip_string, sizeof(ip_string));
        freeaddrinfo(res);
        return ip_string;
    }

    freeaddrinfo(res);
    return nullptr;
}

void HTTPClient::handle_error(const char *error_msg) {

}

int HTTPClient::socket_create(const char *host) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        printf("Could not create socket for %s.\n", host);
        return -1;
    }

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(HTTP_PORT);
    inet_pton(AF_INET, host, &server_addr.sin_addr);

    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        printf("Could not connect to address %s through socket: %s", host, strerror(errno));
        close(sockfd);
        return -1;
    }

    return sockfd;
}

// HTTPResponse
bool HTTPResponse::parse_response(RC::String str) {
    valid = false;

    RC::SV str_sv(str.as_cstr(), str.len()); 
    RC::Vector<RC::SV> lines = str_sv.split_multiple('\n');
    if (lines.is_empty()) return false;

    RC::SV status_line = lines[0].trim();
    RC::Vector<RC::SV> status_parts = status_line.split_multiple(' ');

    if (status_parts.len() < 3) return false; // Invalid status line
    
    http_version = status_parts[0];
    status_code = status_parts[1].to_int();
    if (status_code < 0) return false;
    // FIXME: Status phrase only parses first word; e.g. "Bad Request" -> "Bad"
    status_phrase = status_parts[2];

    for (size_t i = 1; i < lines.len(); i++) {
        RC::SV line = lines[i].trim();
        if (line.len == 0) break;

        headers.push_back(line);
    }
    
    return true;
}
