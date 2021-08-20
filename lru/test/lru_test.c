#include "lru.h"
#include "ngx_string.h"
#include "hash.h"
#include "md5.h"
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct {
    int valid;
    ngx_str_t client_ip;
} mcdn_auth_info_t;

#define BUCKET_SIZE 5
#define NUM         10 * BUCKET_SIZE

static void print_lru(mcdn_lru_t *lru);

int main(int argc, char **argv)
{
    mcdn_lru_t *lru;
    mcdn_lru_list_elt_t *list_node;
    mcdn_lru_bucket_elt_t *bucket_node;
    mcdn_auth_info_t *infos[NUM], *info;
    char msec[14];
    ngx_str_t tokens[NUM], copy_t;
    struct timeval now, t1, t2;
    int i, key;
    unsigned long t, get_time, set_time;
    void *ret;

    lru = mcdn_lru_init(NUM, BUCKET_SIZE);
    if (lru == NULL) {
        printf("%s failed\n", __FUNCTION__);
    }   

    for (i = 0; i < NUM; ++i) {
        infos[i] = calloc(1, sizeof(mcdn_auth_info_t));
        tokens[i].data = calloc(32, sizeof(char));
        tokens[i].len = 32;
    }

    /* set test */

    for (i = 0; i < NUM; ++i) {
        gettimeofday(&now, NULL);
        t = now.tv_sec * 1000 + now.tv_usec / 1000;
        snprintf(msec, sizeof(msec), "%ld", t);

        md5(tokens[i].data, tokens[i].len, msec, strlen(msec));

        key = ngx_hash_key_lc(tokens[i].data, tokens[i].len);
        if (key < 0) {
            key *= -1;
        }

        infos[i]->valid = 1;
        ret = lru->set(lru, key, &tokens[i], infos[i]);
        if (ret != infos[i]) {
            free(ret);
        }

        if (i == 1) {
            copy_t.data = calloc(tokens[i].len, sizeof(char));
            copy_t.len = tokens[i].len;
            memcpy(copy_t.data, tokens[i].data, tokens[i].len);
        }

        usleep(2000);
    }

    printf("=== printf_lru #1 ===\n");
    print_lru(lru);

    /* get test */

    for (i = 0; i < NUM; ++i) {
        key = ngx_hash_key_lc(tokens[i].data, tokens[i].len);
        if (key < 0) {
            key *= -1;
        }
        if (lru->get(lru, key, &tokens[i]) == NULL) {
            printf("lru->get test failed, line=%d\n", __LINE__);
            exit(-1);
        }

        list_node = ngx_queue_data(ngx_queue_head(&lru->list), mcdn_lru_list_elt_t, queue);
        bucket_node = list_node->bucket_elt;
        
        if (bucket_node->key != key ||
                bucket_node->key_name.len != tokens[i].len ||
                memcmp(bucket_node->key_name.data, tokens[i].data, tokens[i].len) != 0) {
            printf("lru->get test failed, line=%d\n", __LINE__);
            exit(-1);
        }
    }

    printf("=== printf_lru #2 ===\n");
    print_lru(lru);

    /* delete test */

    int delcnt = NUM / 2;

    for (i = 0; i < delcnt; ++i) {
        key = ngx_hash_key_lc(tokens[i].data, tokens[i].len);
        if (key < 0) {
            key *= -1;
        }

        ret = lru->delete(lru, key, &tokens[i]);
        if (ret == NULL) {
            printf("lru->delete test failed, should not return null, line=%d\n", __LINE__);
            exit(-1);
        }

        free(ret);

        if (lru->get(lru, key, &tokens[i]) != NULL) {
            printf("lru->delete test failed, line=%d\n", __LINE__);
            exit(-1);            
        }
    }

    if (lru->nelts + delcnt != NUM) {
        printf("lru->delete test failed, line=%d\n", __LINE__);
        exit(-1);
    }

    printf("=== printf_lru #3 ===\n");
    print_lru(lru);

    /* single set time test */
    info = calloc(1, sizeof(mcdn_auth_info_t));
    info->valid = 0;

    gettimeofday(&t1, NULL);
    ret = lru->set(lru, key, &copy_t, info);
    gettimeofday(&t2, NULL);

    if (ret == NULL) {
        printf("set test failed, line=%d\n", __LINE__);
        exit(-1);
    } else if (ret != info) {
        free(ret);
    }

    set_time = (t2.tv_sec - t1.tv_sec) * 1000000 + (t2.tv_usec - t1.tv_usec);

    printf("=== printf_lru #4 ===\n");
    print_lru(lru);

    /* single get time test */

    key = ngx_hash_key_lc(copy_t.data, copy_t.len);
    if (key < 0) {
        key *= -1;
    }

    gettimeofday(&t1, NULL);
    info = lru->get(lru, key, &copy_t);
    gettimeofday(&t2, NULL);

    get_time = (t2.tv_sec - t1.tv_sec) * 1000000 + (t2.tv_usec - t1.tv_usec);

    copy_t.data[0] = '#';
    key = ngx_hash_key_lc(copy_t.data, copy_t.len);
    if (key < 0) {
        key *= -1;
    }
    info = lru->get(lru, key, &copy_t);
    if (info != NULL) {
        printf("get test failed, line=%d\n", __LINE__);
        exit(-1);
    }

    printf("=== printf_lru #5 ===\n");
    print_lru(lru);

    printf("\n=== lru test pass ===\n");
    printf("lru size: %d, capacity: %d, single set time: %ld usec, single get time: %ld usec\n", 
        lru->nelts, lru->capacity, set_time, get_time);

    while (1) {
        sleep(30);
    }

    return 0;
}

static void print_lru(mcdn_lru_t *lru)
{
    printf("lru capacity=%d bucket_size=%d nelts=%d;\n\n", 
        lru->capacity, lru->bucket_size, lru->nelts);

    int i;
    ngx_queue_t *head, *q;
    mcdn_lru_bucket_elt_t *bn;
    mcdn_lru_list_elt_t *ln;
    mcdn_auth_info_t *info;

    for (i = 0; i < lru->bucket_size; ++i) {
        printf("bucket #%d ===\n", i);

        head = &lru->bucket[i];

        if (ngx_queue_empty(head)) {
            printf("empty\n\n");
            continue;
        }

        q = ngx_queue_head(head);
        while (q != head) {
            bn = ngx_queue_data(q, mcdn_lru_bucket_elt_t, queue);
            ln = bn->list_elt;

            if (ln->bucket_elt != bn) {
                printf("ln->bucket_elt != bn\n");
                exit(-1);
            }

            info = (mcdn_auth_info_t*) bn->value;

            printf("key=%d key_name='%.*s' list_node=%p info->valid=%d\n", 
                bn->key, (int) bn->key_name.len, bn->key_name.data, bn->list_elt, info->valid);

            q = ngx_queue_next(q);
        }
        printf("\n");
    }

    printf("\nlru list ===\n");

    head = &lru->list;
    q = ngx_queue_head(head);
    while (q != head) {
        ln = ngx_queue_data(q, mcdn_lru_list_elt_t, queue);
        printf("%p => ", ln);
        q = ngx_queue_next(q);
    }

    printf("\n\n");
}
