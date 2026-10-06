#include <stddef.h>
#include "msl/alloc_g.h"
#define Block_construct alloc_g_Block_construct
#define Block_link alloc_g_Block_link
#define Block_subBlock alloc_g_Block_subBlock
#define Block_unlink alloc_g_Block_unlink
#define FixBlock_construct alloc_g_FixBlock_construct
#define SubBlock_construct alloc_g_SubBlock_construct
#define SubBlock_merge_next alloc_g_SubBlock_merge_next
#define SubBlock_merge_prev alloc_g_SubBlock_merge_prev
#define SubBlock_split alloc_g_SubBlock_split
#define allocate_from_var_pools alloc_g_allocate_from_var_pools
#define deallocate_from_var_pools alloc_g_deallocate_from_var_pools
#define link alloc_g_link
#define link_new_block alloc_g_link_new_block
#define unlink alloc_g_unlink
#include "ansi_prefix.Win32.h"
#include "alloc.c"
#define wchar_t msl_wchar_t
#undef wchar_t

struct ListElem *DAT_0057d2a0;

struct ListElem * __cdecl unlink_list_elem(struct ListElem *entry)
{
  struct ListElem *next = entry->prev;
  if (next == entry)
    next = 0;
  if (DAT_0057d2a0 == entry)
    DAT_0057d2a0 = next;
  if (next) {
    next->next = entry->next;
    next->next->prev = next;
  }
  entry->prev = 0;
  entry->next = 0;
  return next;
}

void fn_00404220(ListElem *element) {
    if (DAT_0057d2a0 != NULL) {
        element->next = DAT_0057d2a0->next;
        element->next->prev = element;
        element->prev = DAT_0057d2a0;
        DAT_0057d2a0->next = element;
        DAT_0057d2a0 = element;
    } else {
        DAT_0057d2a0 = element;
        element->next = element;
        element->prev = element;
    }
}

unsigned int *allocate_sub_block(unsigned int request) {
    struct ListElem *arena;
    unsigned int *block;
    void *record;
    unsigned int *words;

    request = (request + 0xf) & ~7u;
    if (request < 0x50) {
        request = 0x50;
    }

    arena = DAT_0057d2a0 ? DAT_0057d2a0 : (struct ListElem *)alloc_g_link_new_block(request);
    if (arena == 0) {
        return 0;
    }

    do {
        record = arena;
        words = record;
        if (request <= words[2]) {
            block = (unsigned int *)alloc_g_Block_subBlock((struct Block *)arena, request);
            if (block != 0) {
                DAT_0057d2a0 = arena;
                break;
            }
        }
        arena = arena->prev;
        if (arena == DAT_0057d2a0) {
            arena = (struct ListElem *)alloc_g_link_new_block(request);
            if (arena == 0) {
                return 0;
            }
            block = (unsigned int *)alloc_g_Block_subBlock((struct Block *)arena, request);
            break;
        }
    } while (1);

    return block + 2;
}

