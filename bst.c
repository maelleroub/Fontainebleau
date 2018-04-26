#include<stdlib.h>
#include<stdio.h>

int _max(int a, int b)
{
  return (a >= b) ? a : b;
}

struct bst
{
  int data;
  struct bst *left;
  struct bst *right;
};

int is_empty(struct bst *T)
{
  return T == NULL;
}

int size(struct bst *T)
{
  return (is_empty(T)) ? 0 : 1 + size(T->left) + size(T->right);
}

int height(struct bst *T)
{
  return (is_empty(T)) ? -1 : 1 + _max(height(T->left), height(T->right));
}

int equals(struct bst *A, struct bst *B)
{
  if(is_empty(A) ^ is_empty(B))
    return 0;
  if(is_empty(A) && is_empty(B))
    return 1;
  if(A->data != B->data)
    return 0;
  return equals(A->left, B->left) && equals(A->right, B->right);
}

struct bst* search(struct bst *T, int x)
{
  if(is_empty(T) || T->data == x)
    return T;
  return search((x < T->data) ? T->left : T->right, x);
}

struct bst* insertion(struct bst *T, int x)
{
  if(is_empty(T))
  {
    struct bst *B = malloc(sizeof(struct bst*));
    B->data = x;
    return B;
  }
  if(x <= T->data)
    T->left = insertion(T->left, x);
  else
    T->right = insertion(T->right, x);
  return T;
}

void _ugly_print(struct bst *T, int depth)
{
  if(!is_empty(T))
  {
    _ugly_print(T->left, depth + 1);
    for(int i = 0; i < depth; i++)
      printf("  ");
    printf("%d\n", T->data);
    _ugly_print(T->right, depth + 1);
  }
  else
    printf("\n");
}

void ugly_print(struct bst *T)
{
  _ugly_print(T, 0);
}
