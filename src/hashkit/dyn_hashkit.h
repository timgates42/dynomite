/*
 * Dynomite - A thin, distributed replication layer for multi non-distributed storages.
 * Copyright (C) 2014 Netflix, Inc.
 */ 

/*
 * twemproxy - A fast and lightweight proxy for memcached protocol.
 * Copyright (C) 2011 Twitter, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _NC_HASHKIT_H_
#define _NC_HASHKIT_H_

#include <dyn_core.h>
#include <dyn_server.h>

#define HASH_CODEC(ACTION)                      \
    ACTION( HASH_ONE_AT_A_TIME, one_at_a_time ) \
    ACTION( HASH_MD5,           md5           ) \
    ACTION( HASH_CRC16,         crc16         ) \
    ACTION( HASH_CRC32,         crc32         ) \
    ACTION( HASH_CRC32A,        crc32a        ) \
    ACTION( HASH_FNV1_64,       fnv1_64       ) \
    ACTION( HASH_FNV1A_64,      fnv1a_64      ) \
    ACTION( HASH_FNV1_32,       fnv1_32       ) \
    ACTION( HASH_FNV1A_32,      fnv1a_32      ) \
    ACTION( HASH_HSIEH,         hsieh         ) \
    ACTION( HASH_MURMUR,        murmur        ) \
    ACTION( HASH_JENKINS,       jenkins       ) \
    ACTION( HASH_MURMUR3,       murmur3       ) \

#define DIST_CODEC(ACTION)                      \
    ACTION( DIST_KETAMA,        ketama        ) \
    ACTION( DIST_MODULA,        modula        ) \
    ACTION( DIST_RANDOM,        random        ) \
    ACTION( DIST_VNODE,         vnode         ) \
    ACTION( DIST_SINGLE,        single        ) \

#define DEFINE_ACTION(_hash, _name) _hash,
typedef enum hash_type {
    HASH_CODEC( DEFINE_ACTION )
    HASH_SENTINEL
} hash_type_t;
#undef DEFINE_ACTION

#define DEFINE_ACTION(_dist, _name) _dist,
typedef enum dist_type {
    DIST_CODEC( DEFINE_ACTION )
    DIST_SENTINEL
} dist_type_t;
#undef DEFINE_ACTION

rstatus_t hash_one_at_a_time(const char *key, size_t key_length, struct dyn_token *token);
void md5_signature(const unsigned char *key, unsigned int length, unsigned char *result);
rstatus_t hash_md5(const char *key, size_t key_length, struct dyn_token *token);
rstatus_t hash_crc16(const char *key, size_t key_length, struct dyn_token *token);
rstatus_t hash_crc32(const char *key, size_t key_length, struct dyn_token *token);
rstatus_t hash_crc32a(const char *key, size_t key_length, struct dyn_token *token);
rstatus_t hash_fnv1_64(const char *key, size_t key_length, struct dyn_token *token);
rstatus_t hash_fnv1a_64(const char *key, size_t key_length, struct dyn_token *token);
rstatus_t hash_fnv1_32(const char *key, size_t key_length, struct dyn_token *token);
rstatus_t hash_fnv1a_32(const char *key, size_t key_length, struct dyn_token *token);
rstatus_t hash_hsieh(const char *key, size_t key_length, struct dyn_token *token);
rstatus_t hash_jenkins(const char *key, size_t length, struct dyn_token *token);

rstatus_t hash_murmur(const char *key, size_t length, struct dyn_token *token);
rstatus_t hash_murmur3(const char *key, size_t length, struct dyn_token *token);

rstatus_t datacenter_verify_continuum(void *elem, void *data);
rstatus_t vnode_update(struct server_pool *pool);
uint32_t vnode_dispatch(struct continuum *continuum, uint32_t ncontinuum, struct dyn_token *token);


rstatus_t ketama_update(struct server_pool *pool);
uint32_t ketama_dispatch(struct continuum *continuum, uint32_t ncontinuum, uint32_t hash);
rstatus_t modula_update(struct server_pool *pool);
uint32_t modula_dispatch(struct continuum *continuum, uint32_t ncontinuum, uint32_t hash);
rstatus_t random_update(struct server_pool *pool);
uint32_t random_dispatch(struct continuum *continuum, uint32_t ncontinuum, uint32_t hash);

#endif