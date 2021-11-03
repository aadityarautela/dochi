#pragma once
#include <cmath>
#include <iostream>
#include <string>

struct Node {
private:
  Node *prev;
  Node *next;
  Node *child;
  Node *parent;
  int id;
  int value;
  int degree;
  bool marked;

public:
  friend class FibonacciHeap;
  Node *getPrev() { return prev; }
  Node *getNext() { return next; }
  Node *getChild() { return child; }
  Node *getParent() { return parent; }
  int getValue() { return value; }
  int getId() { return id; }
  bool isMarked() { return marked; }
  bool hasChildren() { return child; }
  bool hasParent() { return parent; }
};

class FibonacciHeap {
protected:
  Node *heap;

public:
  FibonacciHeap();
  virtual ~FibonacciHeap();
  Node *insert(int id, int value);
  void merge(FibonacciHeap &other);
  bool isEmpty();
  std::pair<int,int> getMinimum();
  std::pair<int,int> removeMinimum();
  void decreaseKey(Node *n, int value);
  Node *find(int value);
  void display() const;

private:
  Node *_empty();
  Node *_singleton(int id, int value);
  Node *_merge(Node *a, Node *b);
  void _deleteAll(Node *n);
  void _addChild(Node *parent, Node *child);
  void _unMarkAndUnParentAll(Node *n);
  Node *_removeMinimum(Node *n);
  Node *_cut(Node *heap, Node *n);
  Node *_decreaseKey(Node *heap, Node *n, int value);
  Node *_find(Node *heap, int value);
  void _display_tree(Node *n, std::string pre) const;
};