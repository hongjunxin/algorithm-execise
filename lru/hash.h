#ifndef _HASH_H_
#define _HASH_H_

#include <stddef.h>

#define ngx_tolower(c)     ((c >= 'A' && c <= 'Z') ? (c | 0x20) : c)
#define ngx_toupper(c)     ((c >= 'a' && c <= 'z') ? (c & ~0x20) : c)

#define ngx_hash(key, c)   ((unsigned) key * 31 + c)

int ngx_hash_key_lc(char *data, size_t len);

#endif
