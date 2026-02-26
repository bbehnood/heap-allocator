#ifndef INTERNAL_H
#define INTERNAL_H

#include <stddef.h>

typedef struct block
{
    size_t size;
    int free;
    struct block *next;
} block_t;

#define META_SIZE sizeof(block_t)

#endif // !INTERNAL_H
