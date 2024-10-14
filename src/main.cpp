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

    printf("%s\n", res.as_cstr());

    return 0;
}
