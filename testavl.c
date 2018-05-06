#include<stdio.h>
#include<stdlib.h>
#include"bintree.h"
#include"avl.h"

int main()
{
  struct binTree *A_sent = bt_init(1);
  struct binTree *A = A_sent->left;
  A->left = bt_create(2);
  A->right = bt_create(3);
  A->left->left = bt_create(4);
  A->left->right = bt_create(5);
  A->right->left = bt_create(6);
  A->right->right = bt_create(7);
  bt_ugly_print(A_sent);
  struct AVL *B = bt_to_avl(A_sent);
  printf("----------\n");
  avl_ugly_print(B);
  return 1;
}
