#include <HTTP.h>

#if defined(__linux__)
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#else
#error "Unsupported operating system."
#endif

const char *HTTPClient::get(const char *url) {
    const char *host = resolve_host(url);
    if (!host) {
        printf("Could not resolve the host for URL: %s.\n", url);
        return nullptr;
    }
    printf("Host found: %s\n", host);

    return nullptr;
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
    
}
