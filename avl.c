#include"avl.h"

struct AVL* avl_init(int n)
{
  struct AVL *A = malloc(sizeof(struct AVL));
  A->data = NULL;
  A->right = NULL;
  A->balance = 0;
  A->left = avl_create(n);
  return A;
}

struct AVL* avl_create(int n)
{
  struct AVL *A = malloc(sizeof(struct AVL));
  int *data = malloc(sizeof(int));
  *data = n;
  A->data = data;
  A->left = NULL;
  A->right = NULL;
  A->balance = 0;
  return A;
}

int avl_is_empty(struct AVL *A)
{
  return !A || (A->data == NULL && !A->left);
}

static void _avl_ugly_print(struct AVL *A, int depth)
{
  if(!avl_is_empty(A))
  {
    _avl_ugly_print(A->left, depth + 1);
    for(int i = 0; i < depth; i++)
      printf("  ");
    printf("%d\n", *A->data);
    _avl_ugly_print(A->right, depth + 1);
  }
  else
    printf("\n");
}

void avl_ugly_print(struct AVL *A)
{
  if(avl_is_empty(A))
    return;
  _avl_ugly_print(A->left, 0);
}
