#include"../bintree.h"
#include"../bst.h"
#include"../list.h"
#include<assert.h>
#include<stdlib.h>
#include<stdio.h>

void deletion_test(struct binTree *T, int x)
{
  printf("\n----------------\nDeletion of %d:", x);
  bst_delete_elm(T, x);
  bt_ugly_print(T);
}

void bst_test(struct binTree *T)
{
  printf("\n----------------\n");
  bt_ugly_print(T);
  bt_breadth_first_print(T);
  printf("max: %d\n", *bst_max(T)->data);
  printf("min: %d\n", *bst_min(T)->data);
  printf("size: %zu\nheight: %zu\nwidth: %zu\n", bt_size(T), bt_height(T), bt_width(T));
  printf((bt_is_degenerate(T)) ? "degenerate\n" : "not degenerate\n");
  printf((bt_is_perfect(T)) ? "perfect\n" : "not perfect\n");
  struct binTree *F1 = bst_search(T, 1);
  if(F1)
    printf("1 is present in the tree\n");
  else
  {
    printf("1 is not present in the tree\n\n");
    bst_insert_leaf(T, 1);
    bt_ugly_print(T);
    assert(bst_search(T, 1));
    printf("\n1 present after insertion\n");
  }
  struct binTree *F9 = bst_search(T, 9);
  if(F9)
    printf("9 is present in the tree\n");
  else
  {
    printf("9 is not present in the tree\n");
    bst_insert_leaf(T, 9);
    bt_ugly_print(T);
    assert(bst_search(T, 9));
    printf("\n9 present after insertion\n");
  }
  struct list *l = bt_to_hierarchy(T);
  list_print_int(l);
  struct binTree *U = hierarchy_to_bt(l);
  assert(bt_equals(T, U));
  bt_delete(U);
  list_delete(l);
}
  

int main()
{
  struct binTree *A = bt_init(4);
  struct binTree *subA = A->left;
  subA->left = bt_create(2);
  subA->right = bt_create(6);
  subA->left->left = bt_create(1);
  subA->left->right = bt_create(3);
  subA->right->left = bt_create(5);
  subA->right->right = bt_create(7);
  //bst_test(A);
  bt_ugly_print(A);
  deletion_test(A, 4);
  deletion_test(A, 0);
  deletion_test(A, 2);
  deletion_test(A, 6);
  bt_delete(A);
  printf("\n----------------\n");

  struct binTree *B =  bt_init(4);
  struct binTree *subB = B->left;
  subB->right = bt_create(9);
  subB->right->left = bt_create(6);
  subB->right->left->left = bt_create(5);
  //bst_test(B);
  bt_ugly_print(B);
  deletion_test(B, 9);
  deletion_test(B, 5);
  deletion_test(B, 4);
  deletion_test(B, 6);
  deletion_test(B, 24);
  bt_delete(B);
  printf("\n----------------\n");

  struct binTree *C = bt_init(10);
  struct binTree *subC = C->left;
  subC->left = bt_create(4);
  subC->right = bt_create(17);
  subC->right->right = bt_create(21);
  subC->right->right->left = bt_create(19);
  subC->left->left = bt_create(3);
  subC->left->right = bt_create(8);
  subC->left->right->left = bt_create(7);
  subC->left->right->right = bt_create(9);
  //bst_test(C);
  bt_ugly_print(C);
  deletion_test(C, 9);
  deletion_test(C, 8);
  deletion_test(C, 10);
  deletion_test(C, 4);
  deletion_test(C, 21);
  bt_delete(C);
  printf("\n----------------\n");

  return 1;
}
