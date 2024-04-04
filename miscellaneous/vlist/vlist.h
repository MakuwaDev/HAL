#ifndef VLIST_H
#define VLIST_H

#include <sys/types.h>
#include <stdbool.h>

typedef struct vlist vlist_t;

vlist_t create_vlist();
bool is_empty(const vlist_t l);
void* front(const vlist_t l);
size_t size(vlist_t l);
void* get_elem(vlist_t l, size_t n);
void* remove_elem(vlist_t l, size_t n);
void* pop_front(vlist_t l);
void push_back(vlist_t l, void *val);
void reverse(vlist_t l);
void append(vlist_t list1, vlist_t list2);
void delete_list(vlist_t l);

#endif
