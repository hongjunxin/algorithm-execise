#include <hash.h>

unsigned int ngx_hash_key_lc(char *data, size_t len)
{
    unsigned int  i, key;

    key = 0;

    for (i = 0; i < len; i++) {
        key = ngx_hash(key, ngx_tolower(data[i]));
    }

    return key;
}