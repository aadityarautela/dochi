#pragma once

struct Node {
  int n;
  int degree;
  Node *parent;
  Node *child;
  Node *left;
  Node *right;
  char mark;

  char C;
};

