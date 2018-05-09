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
  test_insertion(A, 10);
  test_insertion(A, 12);
  test_insertion(A, 15);
  test_insertion(A, 20);
  test_insertion(A, 26);
  test_insertion(A, 31);
  test_insertion(A, 34);
  test_insertion(A, 38);
  test_insertion(A, 43);
  test_insertion(A, 49);
  test_insertion(A, 51);
  test_insertion(A, 54);
  test_insertion(A, 60);
  test_insertion(A, 62);
  test_insertion(A, 65);
  test_insertion(A, 68);
  test_insertion(A, 74);
  test_insertion(A, 80);
  test_insertion(A, 84);
  test_insertion(A, 37);
  test_deletion(A, 49);
  balance(A);
  avl_delete(A);
}
