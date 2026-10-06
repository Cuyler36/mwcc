#ifndef MSL_ALLOC_G_H
#define MSL_ALLOC_G_H

struct ListElem {
    struct ListElem *next;
    struct ListElem *prev;
};
typedef struct ListElem ListElem;
extern struct ListElem *DAT_0057d2a0;
extern struct ListElem *__cdecl unlink_list_elem(struct ListElem *entry);
extern void fn_00404220(ListElem *element);
extern unsigned int *allocate_sub_block(unsigned int request);

#endif
