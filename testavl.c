#include<stdio.h>
#include<stdlib.h>
#include"bintree.h"
#include"avl.h"

static void _balance(struct AVL *A, int depth)
{
  if(!avl_is_empty(A))
  {
    _balance(A->left, depth + 1);
    for(int i = 0; i < depth; i++)
      printf("  ");
    printf("%d\n", A->balance);
    _balance(A->right, depth + 1);
  }
  else
    printf("\n");
}

void balance(struct AVL *A)
{
  if(avl_is_empty(A))
    return;
  _balance(A->left, 0);
}

void test_deletion(struct AVL *A, int x)
{
  printf("\n----------------\n");
  printf("Deletion of %d:\n", x);
  avl_delete_elm(A, x);
  avl_ugly_print(A);
}

void test_insertion(struct AVL *A, int x)
{
  printf("\n----------------\n");
  printf("Insertion of %d:\n", x);
  avl_insert(A, x);
  avl_ugly_print(A);
}

void avl_test(struct AVL *A)
{
  printf("\n----------------\n");
  avl_ugly_print(A);
  avl_breadth_first_print(A);
  printf("max: %d\n", *avl_max(A)->data);
  printf("min: %d\n", *avl_min(A)->data);
  printf("size: %zu\nheight: %zu\nwidth: %zu\n", avl_size(A), avl_height(A), avl_width(A));
  struct AVL *F1 = avl_search(A, 1);
  if(F1)
    printf("1 is present in the tree\n");
  else
    printf("1 is not present in the tree\n\n");
  struct AVL *F9 = avl_search(A, 9);
  if(F9)
    printf("9 is present in the tree\n");
  else
    printf("9 is not present in the tree\n");
}

int main()
{
  struct AVL *A = avl_init(4);
  avl_ugly_print(A);
  test_insertion(A, 11);
  test_deletion(A, 11);
  test_insertion(A, 13);
  test_insertion(A, 2);
  test_insertion(A, 5);
  test_insertion(A, 1);
  test_insertion(A, 8);
  test_deletion(A, 5);
  test_deletion(A, 13);
  test_insertion(A, 20);
  test_insertion(A, 10);
  test_insertion(A, 9);
  test_insertion(A, 40);
  test_deletion(A, 9);
  test_deletion(A, 4);
  test_deletion(A, 2);
  balance(A);
  avl_delete(A);
}
