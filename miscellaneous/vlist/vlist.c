#include "vlist.h"

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  void *val;
  struct node *l1, *l2;
} node_t;

// Obowiązuje niezmiennik: head i tail łączą się z listą poprzez l2
// natomiast l1 wskazuje w obu przypadkach na NULL
struct vlist {
  node_t *head, *tail;
  size_t size;
};

typedef struct vlist vlist_t;

// Podpina nw do el, tam gdzie wcześniej byl old
static void link(node_t *el, node_t *old, node_t *nw) {
  if (el) {
    if (el->l1 == old)
      el->l1 = nw;
    else
      el->l2 = nw;
  }
}

static void swap(node_t *a, node_t *b) {
  node_t *tmp = a;
  a = b;
  b = tmp;
}

static node_t *create_node(void *val) {
  node_t *res = malloc(sizeof(node_t));
  if (!res) {
    errno = ENOMEM;
    return NULL;
  }

  res->val = val;
  return res;
}

// Zwraca wskaźnik na sąsiada el niebędącego prev
static node_t *next(node_t *el, node_t *prev) {
  if (el->l1 != prev) return el->l1;
  return el->l2;
}

// Zwraca wskaźnik na n-ty element listy l; czas liniowy
static node_t *_get_elem(vlist_t l, size_t n) {
  if (n >= l.size) {
    errno = EINVAL;
    return NULL;
  }

  node_t *res = l.head->l2, *prev = l.head, *help;

  for (size_t i = 0; i < n; ++i) {
    help = res;
    res = next(res, prev);
    prev = help;
  }

  return res;
}

vlist_t create_vlist() {
  vlist_t res = {(node_t *)malloc(sizeof(node_t)),
                 (node_t *)malloc(sizeof(node_t)), 0UL};

  if (!res.head || !res.tail) {
    errno = ENOMEM;
    return (vlist_t){NULL, NULL, 0};
  }

  res.head->l1 = NULL;
  res.head->l2 = res.tail;
  res.tail->l1 = NULL;
  res.tail->l2 = res.head;

  return res;
}

bool is_empty(const vlist_t l) { 
  return l.head->l2 == l.tail;
}

void *front(const vlist_t l) { 
  return l.head->l2->val;
}

size_t size(vlist_t l) {
  return l.size;
}

void *get_elem(vlist_t l, size_t n) {
  return _get_elem(l, n)->val;
}

void *remove_elem(vlist_t l, size_t n) {
  if (n >= l.size) {
    errno = EINVAL;
    return NULL;
  }

  node_t *el = _get_elem(l, n);
  void *res = el->val;

  link(el->l1, el, el->l2);
  link(el->l2, el, el->l1);
  free(el);

  return res;
}

void *pop_front(vlist_t l) {
  if (!is_empty(l)) return remove_elem(l, 0);
  else {
    errno = EINVAL;
    return NULL;
  }
}

void push_back(vlist_t l, void *val) {
  node_t *el = create_node(val);
  if (!el) {
    errno = ENOMEM;
    return;
  }

  el->l1 = l.tail;
  el->l2 = l.tail->l2;
  link(l.tail->l2, l.tail, el);
  l.tail->l2 = el;
  ++l.size;
}

void reverse(vlist_t l) {
  swap(l.head, l.tail);
}

// Przepina listę na koniec innej listy, "przepięta" lista jest potem
// zdatna do użycia i niezależna od listy, do której została "przepięta"
void append(vlist_t list1, vlist_t list2) {
  node_t *b = list1.tail;
  node_t *f = list2.head;

  link(b->l2, b, f->l2);
  link(f->l2, f, b->l2);

  b->l2 = f;
  f->l2 = b;
  list1.tail = list2.tail;
  list2.head = f;
  list2.tail = b;

  list2.size += list1.size;
  list1.size = 0;
}

// Usuwa listę i dealokuje pamięć po head oraz tail
void delete_list(vlist_t l) {
  while (!is_empty(l))
    pop_front(l);
  free(l.head);
  free(l.tail);
}
