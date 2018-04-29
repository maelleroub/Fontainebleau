#include"../bintree.h"
#include"../list.h"
#include<assert.h>
#include<stdlib.h>
#include<stdio.h>

void test(struct binTree *T)
{
  printf("\n----------------\n");
  bt_ugly_print(T);
  bt_breadth_first_print(T);
  printf("size: %zu\nheight: %zu\nwidth: %zu\n", bt_size(T), bt_height(T), bt_width(T));
  printf((bt_is_degenerate(T)) ? "degenerate\n" : "not degenerate\n");
  printf((bt_is_perfect(T)) ? "perfect\n" : "not perfect\n");
  printf((bt_is_bst(T)) ? "bst\n" : "not bst\n");
  struct list *l = bt_to_hierarchy(T);
  list_print_int(l);
  assert(bt_equals(T, hierarchy_to_bt(l)));
  bt_delete(T);
  list_delete(l);
}
  

int main()
{
  struct binTree *A = bt_create(1);
  A->left = bt_create(2);
  A->right = bt_create(3);
  A->left->left = bt_create(4);
  A->left->right = bt_create(5);
  A->right->left = bt_create(6);
  A->right->right = bt_create(7);
  test(A);

  struct binTree *B =  bt_create(4);
  B->right = bt_create(9);
  B->right->left = bt_create(6);
  B->right->left->left = bt_create(5);
  test(B);

  struct binTree *C = bt_create(10);
  C->left = bt_create(4);
  C->right = bt_create(17);
  C->right->right = bt_create(21);
  C->right->right->left = bt_create(19);
  C->left->left = bt_create(3);
  C->left->right = bt_create(8);
  C->left->right->left = bt_create(7);
  C->left->right->right = bt_create(9);
  test(C);

  return 1;
}
