/*
 * Copyright (C) hongjunxin
 */

#include <stdio.h>
#include <string.h>
#include "lru.h"

static void* mcdn_lru_set(mcdn_lru_t *lru, int key, ngx_str_t *key_name, void *value);
static void* mcdn_lru_get(mcdn_lru_t *lru, int key, ngx_str_t *key_name);
static void* mcdn_lru_delete(mcdn_lru_t *lru, int key, ngx_str_t *key_name);

mcdn_lru_t* mcdn_lru_init(int capacity, int bucket_size)
{
    mcdn_lru_t *lru;
    int i;

    lru = (mcdn_lru_t*) calloc(1, sizeof(mcdn_lru_t));
    if (lru == NULL) {
        return NULL;
    }

    if (capacity < 1 || bucket_size < 1 || capacity < bucket_size) {
        return NULL;
    }

    lru->capacity = capacity;
    lru->bucket_size = bucket_size;
    lru->nelts = 0;

    lru->bucket = (ngx_queue_t*) calloc(bucket_size, sizeof(ngx_queue_t));
    if (lru->bucket == NULL) {
        free(lru);
        return NULL;
    }

    for (i = 0; i < bucket_size; ++i) {
        ngx_queue_init(&lru->bucket[i]);
    }

    ngx_queue_init(&lru->list);

    lru->set = mcdn_lru_set;
    lru->get = mcdn_lru_get;
    lru->delete = mcdn_lru_delete;

    return lru;
}

/* return the old value pointer if it remove from lru, or new value pointer on seccess
   or NULL on error */
static void* mcdn_lru_set(mcdn_lru_t *lru, int key, ngx_str_t *key_name, void *value)
{
    ngx_queue_t *head, *q;
    mcdn_lru_bucket_elt_t *bucket_node;
    mcdn_lru_list_elt_t *list_node;
    void *ret = NULL;

    head = &lru->bucket[key % lru->bucket_size];

    if (lru->nelts == lru->capacity) {
        q = ngx_queue_last(&lru->list);
        list_node = ngx_queue_data(q, mcdn_lru_list_elt_t, queue);
        bucket_node = list_node->bucket_elt;

        ngx_queue_remove(&list_node->queue);
        ngx_queue_remove(&bucket_node->queue);

        ret = bucket_node->value;
        lru->nelts--;
    } else {
        bucket_node = calloc(1, sizeof(mcdn_lru_bucket_elt_t));
        list_node = calloc(1, sizeof(mcdn_lru_list_elt_t));

        if (bucket_node == NULL || list_node == NULL) {
            goto error;
        }
        
        bucket_node->key_name.data = calloc(key_name->len, sizeof(char));
        bucket_node->key_name.len = key_name->len;
        if (bucket_node->key_name.data == NULL) {
            goto error;
        }
    }

    memcpy(bucket_node->key_name.data, key_name->data, key_name->len);
    bucket_node->key = key;
    bucket_node->value = value;
    bucket_node->list_elt = list_node;
    list_node->bucket_elt = bucket_node;

    ngx_queue_insert_head(head, &bucket_node->queue);
    ngx_queue_insert_head(&lru->list, &list_node->queue);

    lru->nelts++;

    return ret == NULL ? value : ret;

error:
    if (bucket_node) {
        free(bucket_node);
    }

    if (list_node) {
        free(list_node);
    }

    return NULL;
}

static void* mcdn_lru_get(mcdn_lru_t *lru, int key, ngx_str_t *key_name)
{
    ngx_queue_t *head, *q;
    mcdn_lru_bucket_elt_t *bucket_node;
    mcdn_lru_list_elt_t *list_node;

    head = &lru->bucket[key % lru->bucket_size];
	if (ngx_queue_empty(head)) {
		return NULL;
	}

	q = ngx_queue_head(head);

	while (q != head) {
		bucket_node = ngx_queue_data(q, mcdn_lru_bucket_elt_t, queue);

		if (bucket_node->key == key &&
                bucket_node->key_name.len == key_name->len &&
				memcmp(bucket_node->key_name.data, key_name->data, key_name->len) == 0) {

            list_node = bucket_node->list_elt;

            if (ngx_queue_head(&lru->list) != &list_node->queue) {
                ngx_queue_remove(&list_node->queue);
                ngx_queue_insert_head(&lru->list, &list_node->queue);
            }

			return bucket_node->value;
		}

		q = ngx_queue_next(q);
	}
    
    return NULL;
}

static void* mcdn_lru_delete(mcdn_lru_t *lru, int key, ngx_str_t *key_name)
{
    void *ret;
    ngx_queue_t *head, *q;
    mcdn_lru_bucket_elt_t *bucket_node;
    mcdn_lru_list_elt_t *list_node;

    ret = NULL;

    head = &lru->bucket[key % lru->bucket_size];
	if (ngx_queue_empty(head)) {
		return NULL;
	}

	q = ngx_queue_head(head);

	while (q != head) {
		bucket_node = ngx_queue_data(q, mcdn_lru_bucket_elt_t, queue);

		if (bucket_node->key == key &&
                bucket_node->key_name.len == key_name->len &&
				memcmp(bucket_node->key_name.data, key_name->data, key_name->len) == 0) {

            ret = bucket_node->value;            
            list_node = bucket_node->list_elt;

            ngx_queue_remove(&list_node->queue);
            ngx_queue_remove(&bucket_node->queue);

            free(bucket_node->key_name.data);
            free(bucket_node);
            free(list_node);

            lru->nelts--;

            break;
		}

		q = ngx_queue_next(q);
	}
    
    return ret;
}
