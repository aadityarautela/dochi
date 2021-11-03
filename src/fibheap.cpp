#include "../includes/fibheap.h"

FibonacciHeap::FibonacciHeap() { heap = _empty(); }

FibonacciHeap::~FibonacciHeap() {
  if (heap) {
    _deleteAll(heap);
  }
}

Node *FibonacciHeap::insert(int id, int value) {
  Node *ret = _singleton(id, value);
  heap = _merge(heap, ret);
  return ret;
}

void FibonacciHeap::merge(FibonacciHeap &other) {
  heap = _merge(heap, other.heap);
  other.heap = _empty();
}

bool FibonacciHeap::isEmpty() { return heap == NULL; }

std::pair<int, int> FibonacciHeap::getMinimum() {
  return {heap->id, heap->value};
}

std::pair<int, int> FibonacciHeap::removeMinimum() {
  Node *old = heap;
  heap = _removeMinimum(heap);
  std::pair<int, int> ret = {old->id, old->value};
  delete old;
  return ret;
}

void FibonacciHeap::decreaseKey(Node *n, int value) {
  heap = _decreaseKey(heap, n, value);
}

Node *FibonacciHeap::find(int value) { return _find(heap, value); }

void FibonacciHeap::display() const {
  Node *p = heap;
  if (p == NULL) {
    std::cout << "The Heap is Empty" << std::endl;
    return;
  }
  std::cout << "The root Nodes of Heap are: " << std::endl;
  _display_tree(heap, "");
  std::cout << std::endl;
}

Node *FibonacciHeap::_empty() { return NULL; }

Node *FibonacciHeap::_singleton(int id, int value) {
  Node *n = new Node;
  n->id = id;
  n->value = value;
  n->prev = n->next = n;
  n->degree = 0;
  n->marked = false;
  n->child = NULL;
  n->parent = NULL;
  return n;
}

Node *FibonacciHeap::_merge(Node *a, Node *b) {
  if (a == NULL)
    return b;
  if (b == NULL)
    return a;
  if (a->value > b->value) {
    Node *temp = a;
    a = b;
    b = temp;
  }
  Node *an = a->next;
  Node *bp = b->prev;
  a->next = b;
  b->prev = a;
  an->prev = bp;
  bp->next = an;
  return a;
}

void FibonacciHeap::_deleteAll(Node *n) {
  if (n != NULL) {
    Node *c = n;
    do {
      Node *d = c;
      c = c->next;
      _deleteAll(d->child);
      delete d;
    } while (c != n);
  }
}

void FibonacciHeap::_addChild(Node *parent, Node *child) {
  child->prev = child->next = child;
  child->parent = parent;
  parent->degree++;
  parent->child = _merge(parent->child, child);
}

void FibonacciHeap::_unMarkAndUnParentAll(Node *n) {
  if (n == NULL)
    return;
  Node *c = n;
  do {
    c->marked = false;
    c->parent = NULL;
    c = c->next;
  } while (c != n);
}

Node *FibonacciHeap::_removeMinimum(Node *n) {
  _unMarkAndUnParentAll(n->child);
  if (n->next == n) {
    n = n->child;
  } else {
    n->next->prev = n->prev;
    n->prev->next = n->next;
    n = _merge(n->next, n->child);
  }
  if (n == NULL)
    return n;
  Node *trees[64] = {NULL};

  while (true) {
    if (trees[n->degree] != NULL) {
      Node *t = trees[n->degree];
      if (t == n)
        break;
      trees[n->degree] = NULL;
      t->prev->next = t->next;
      t->next->prev = t->prev;
      if (n->value < t->value) {
        _addChild(n, t);
      } else {
        if (n->next == n) {
          t->next = t->prev = t;
        } else {
          n->prev->next = t;
          n->next->prev = t;
          t->next = n->next;
          t->prev = n->prev;
        }
        _addChild(t, n);
        n = t;
      }
      continue;
    } else {
      trees[n->degree] = n;
    }
    n = n->next;
  }
  Node *min = n;
  do {
    if (n->value < min->value)
      min = n;
    n = n->next;
  } while (min != n);
  return min;
}

Node *FibonacciHeap::_cut(Node *heap, Node *n) {
  if (n->next == n) {
    n->parent->child = NULL;
  } else {
    n->next->prev = n->prev;
    n->prev->next = n->next;
    n->parent->child = n->next;
  }
  n->next = n->prev = n;
  n->marked = false;
  n->parent->degree--;
  return _merge(heap, n);
}

Node *FibonacciHeap::_decreaseKey(Node *heap, Node *n, int value) {
  if (n->value < value)
    return heap;
  n->value = value;
  Node *parent = n->parent;
  if (parent != nullptr && n->value < parent->value) {
    heap = _cut(heap, n);
    n->parent = NULL;
    while (parent != NULL && parent->marked) {
      heap = _cut(heap, parent);
      n = parent;
      parent = n->parent;
      n->parent = NULL;
    }
    if (parent != NULL && parent->parent != NULL)
      parent->marked = true;
    if (n->value < heap->value)
      heap = n;
  }
  return heap;
}

Node *FibonacciHeap::_find(Node *heap, int value) {
  Node *n = heap;
  if (n == NULL)
    return NULL;
  do {
    if (n->value == value)
      return n;
    Node *ret = _find(n->child, value);
    if (ret)
      return ret;
    n = n->next;
  } while (n != heap);
  return NULL;
}

void FibonacciHeap::_display_tree(Node *n, std::string pre) const {
  std::string pc = "│  ";
  Node *x = n;
  do {
    if (x->next != n) {
      std::cout << pre << "├─";
    } else {
      std::cout << pre << "└─";
      pc = "   ";
    }
    if (x->child == nullptr) {
      std::cout << "─" << x->value << std::endl;
    } else {
      std::cout << "┐" << x->value << std::endl;
      _display_tree(x->child, pre + pc);
    }
    x = x->next;
  } while (x != n);
}