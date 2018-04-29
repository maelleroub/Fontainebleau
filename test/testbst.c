#include"../bintree.h"
#include"../bst.h"
#include"../list.h"
#include<assert.h>
#include<stdlib.h>
#include<stdio.h>

void bst_test(struct binTree *T)
{
  printf("\n----------------\n");
  bt_ugly_print(T);
  bt_breadth_first_print(T);
  printf("max: %d\n", bst_max(T)->data);
  printf("min: %d\n", bst_min(T)->data);
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
  bt_delete(T);
  bt_delete(U);
  list_delete(l);
}
  

int main()
{
  struct binTree *A = bt_create(4);
  A->left = bt_create(2);
  A->right = bt_create(6);
  A->left->left = bt_create(1);
  A->left->right = bt_create(3);
  A->right->left = bt_create(5);
  A->right->right = bt_create(7);
  bst_test(A);

  struct binTree *B =  bt_create(4);
  B->right = bt_create(9);
  B->right->left = bt_create(6);
  B->right->left->left = bt_create(5);
  bst_test(B);

  struct binTree *C = bt_create(10);
  C->left = bt_create(4);
  C->right = bt_create(17);
  C->right->right = bt_create(21);
  C->right->right->left = bt_create(19);
  C->left->left = bt_create(3);
  C->left->right = bt_create(8);
  C->left->right->left = bt_create(7);
  C->left->right->right = bt_create(9);
  bst_test(C);

  return 1;
}
