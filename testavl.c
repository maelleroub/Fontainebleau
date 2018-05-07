#include<stdio.h>
#include<stdlib.h>
#include"bintree.h"
#include"avl.h"

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
  struct binTree *A_sent = bt_init(13);
  struct binTree *A = A_sent->left;
  A->left = bt_create(5);
  A->right = bt_create(25);
  A->left->left = bt_create(1);
  A->left->right = bt_create(7);
  A->right->left = bt_create(17);
  A->right->right = bt_create(43);
  A->left->right->left = bt_create(6);
  bt_ugly_print(A_sent);
  struct AVL *B = bt_to_avl(A_sent);
  avl_test(B);
  bt_delete(A_sent);
  avl_delete(B);
  return 1;
}
