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

    RC::SV url(default_url);
    RC::SV domain = URL::extract_domain_name(url);

    printf("%.*s\n", (int)domain.len, domain.data);

    const char *domain_cstr = domain.as_cstr();
    const char *res = client.get(domain_cstr);
    delete[] domain_cstr;

    return 0;
}
