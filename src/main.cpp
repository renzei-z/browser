#include <HTTP.h>
#include <URL.h>

#include <stdio.h>

#define UNUSED(x) ((void)x)

int main(int argc, char **argv) {
    const char *default_url = "https://example.com/folder1";
    if (argc > 1) {
        default_url = argv[1];
    }

    HTTPClient client;

    RC::String res = client.get(default_url);
    HTTPResponse response;
    bool valid = response.parse_response(res);

    printf("%s %d %s\n", response.http_version.as_cstr(), response.status_code, response.status_phrase.as_cstr());

    for (size_t i = 0; i < response.headers.len(); i++) {
        printf("Header: %s\n", response.headers[i].as_cstr());
    }

    return 0;
}
