#include "internal.h"
#include <sys/mman.h>

static block_t *heap_head = NULL;

block_t *request_space(size_t size)
{
    size_t total_size = size + META_SIZE;

    block_t *block = mmap(NULL, total_size, PROT_READ | PROT_WRITE,
                          MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    if (block == MAP_FAILED) return NULL;

    block->size = size;
    block->free = 0;
    block->next = NULL;

    return block;
}

block_t *find_free_block(size_t size)
{
    block_t *current = heap_head;

    while (current)
    {
        if (current->free && current->size >= size) return current;
        current = current->next;
    }

    return NULL;
}
