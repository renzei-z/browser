#pragma once

#include <RC/Vector.h>
#include <RC/String.h>
#include <RC/SV.h>

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
};

class HTTPResponse {
public:
    HTTPResponse() : http_version(RC::SV(""))
        , status_code(0)
        , status_phrase(RC::SV(""))
        , headers(RC::Vector<RC::SV>())
        , body(RC::SV("")) {}
    ~HTTPResponse() {};

    bool parse_response(RC::String str);

    bool valid = false;
    RC::SV http_version;
    int status_code;
    RC::SV status_phrase;
    RC::Vector<RC::SV> headers;
    RC::SV body;
};
