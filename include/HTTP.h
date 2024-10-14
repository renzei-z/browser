#pragma once

#include <RC/Vector.h>
#include <RC/String.h>

#define HTTP_PORT 80
#define HTTPS_PORT 443

class HTTPClient {
public:
    HTTPClient() {};
    ~HTTPClient() {};

    RC::String get(const char *url);
private:
    const char *resolve_host(const char *url);
    void handle_error(const char *error_msg);
    int socket_create(const char *host);

//    RC::Vector<const char*> headers;
};
