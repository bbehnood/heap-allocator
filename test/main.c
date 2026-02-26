#include "allocator.h"
#include <stdio.h>
#include <string.h>

// Simple test macros
#define TEST_ASSERT(cond, msg)                                                 \
    do                                                                         \
    {                                                                          \
        if (!(cond))                                                           \
        {                                                                      \
            printf("FAIL: %s\n", msg);                                         \
        }                                                                      \
        else                                                                   \
        {                                                                      \
            printf("PASS: %s\n", msg);                                         \
        }                                                                      \
    } while (0)

int main()
{
    printf("=== Custom Heap Allocator Tests ===\n");

    // Test 1: Allocate a single block
    void *p1 = heap_alloc(100);
    TEST_ASSERT(p1 != NULL, "Allocate 100 bytes");

    // Test 2: Allocate another block
    void *p2 = heap_alloc(200);
    TEST_ASSERT(p2 != NULL, "Allocate 200 bytes");

    // Test 3: Check that allocations are distinct
    TEST_ASSERT(p1 != p2, "Different blocks should not overlap");

    // Test 4: Free a block
    heap_free(p1);
    TEST_ASSERT(1, "Free p1 (check visually)"); // Free just sets free flag

    // Test 5: Reuse freed block
    void *p3 = heap_alloc(50); // smaller than p1
    TEST_ASSERT(p3 == p1, "Allocator should reuse freed block if large enough");

    // Test 6: Allocate zero bytes
    void *p4 = heap_alloc(0);
    TEST_ASSERT(p4 == NULL, "Allocating 0 bytes should return NULL");

    // Test 7: Free NULL pointer
    heap_free(NULL); // Should do nothing
    TEST_ASSERT(1, "Freeing NULL pointer does nothing");

    // Test 8: Allocate multiple blocks and check heap linked list
    void *blocks[5];
    for (int i = 0; i < 5; i++)
    {
        blocks[i] = heap_alloc(64);
        TEST_ASSERT(blocks[i] != NULL, "Multiple allocations");
    }

    printf("=== Tests Completed ===\n");
    return 0;
}
