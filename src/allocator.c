#include "allocator.h"
#include "internal.h"
#include <stdint.h>
#include <sys/mman.h>

static block_t *heap_head = NULL;

static block_t *request_space(size_t size)
{
    if (size > SIZE_MAX - META_SIZE) return NULL;
    size_t total_size = size + META_SIZE;

    block_t *block = mmap(NULL, total_size, PROT_READ | PROT_WRITE,
                          MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    if (block == MAP_FAILED) return NULL;

    block->size = size;
    block->free = 0;
    block->next = NULL;

    return block;
}

static block_t *find_free_block(size_t size)
{
    block_t *current = heap_head;

    while (current)
    {
        if (current->free && current->size >= size) return current;
        current = current->next;
    }

    return NULL;
}

void *heap_alloc(size_t size)
{
    if (size == 0) return NULL;

    block_t *block;

    if (!heap_head)
    {
        block = request_space(size);
        if (!block) return NULL;
        heap_head = block;
    }
    else
    {
        block = find_free_block(size);

        if (!block)
        {
            block = request_space(size);
            if (!block) return NULL;

            block_t *last = heap_head;

            while (last->next) last = last->next;

            last->next = block;
        }
        else
        {
            block->free = 0;
        }
    }

    return block + 1;
}

void heap_free(void *ptr)
{
    if (!ptr) return;

    block_t *block = (block_t *)ptr - 1;
    block->free = 1;
}
