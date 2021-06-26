/*
 * Copyright (C) hongjunxin
 */

#ifndef _LRU_H_
#define _LRU_H_

#include <stdlib.h>
#include "ngx_queue.h"
#include "ngx_string.h"

typedef struct mcdn_lru_s  mcdn_lru_t;
typedef struct mcdn_lru_bucket_elt_s  mcdn_lru_bucket_elt_t;
typedef struct mcdn_lru_list_elt_s  mcdn_lru_list_elt_t;

struct mcdn_lru_s {
    ngx_queue_t *bucket;   /* lru hash table */
    ngx_queue_t list;      /* lru list, length must <= capacity */
    int bucket_size;
    int capacity;
    int nelts;

    void* (*set)(mcdn_lru_t *self, int key, ngx_str_t *key_name, void *value);
    void* (*get)(mcdn_lru_t *self, int key, ngx_str_t *key_name);
};

struct mcdn_lru_bucket_elt_s {
    ngx_queue_t queue;
    mcdn_lru_list_elt_t *list_elt;
    ngx_str_t key_name;
    int key;
    void *value;
};

struct mcdn_lru_list_elt_s {
    ngx_queue_t queue;
    mcdn_lru_bucket_elt_t *bucket_elt;
};

mcdn_lru_t* mcdn_lru_init(int capacity, int bucket_size);

#endif
