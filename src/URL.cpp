#include <URL.h>

namespace URL {

RC::SV extract_domain_name(RC::SV& url) {
    // Skip scheme
    const char *scheme_separator = "://";
    size_t scheme_pos = url.find_substr(scheme_separator);

    size_t domain_start = 0;
    if (scheme_pos != url.len) {
        domain_start = scheme_pos + strlen(scheme_separator);
    }

    // Find next / (end of domain)
    size_t domain_end = url.find_char('/', domain_start);

    // If '/' isn't found, domain_end = url.len, which is what we want :D
    size_t domain_len = domain_end - domain_start;
    return url.substr(domain_start, domain_len);
}

}
