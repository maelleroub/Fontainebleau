#include"bintree.h"
#include"list.h"
#include<assert.h>
#include<stdlib.h>
#include<stdio.h>

void balance_test(struct binTree *T)
{
  printf("\n----------------\n");
  bt_ugly_print(T);
  printf((bt_is_balanced(T)) ? "balanced\n" : "not balanced\n");
}

void avl_test(struct binTree *T)
{
  printf("\n----------------\n");
  bt_ugly_print(T);
  printf((bt_is_avl(T)) ? "avl\n" : "not avl\n");
}

void test(struct binTree *T)
{
  printf("\n----------------\n");
  bt_ugly_print(T);
  bt_breadth_first_print(T);
  printf("size: %zu\nheight: %zu\nwidth: %zu\n", bt_size(T), bt_height(T), bt_width(T));
  printf((bt_is_degenerate(T)) ? "degenerate\n" : "not degenerate\n");
  printf((bt_is_perfect(T)) ? "perfect\n" : "not perfect\n");
  printf((bt_is_bst(T)) ? "bst\n" : "not bst\n");
  printf((bt_is_balanced(T)) ? "balanced\n" : "not balanced\n");
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
  struct binTree *A_sent = bt_init(1);
  struct binTree *A = A_sent->left;
  avl_test(A_sent);
  A->left = bt_create(2);
  avl_test(A_sent);
  A->right = bt_create(3);
  avl_test(A_sent);
  A->left->left = bt_create(4);
  avl_test(A_sent);
  A->left->right = bt_create(5);
  avl_test(A_sent);
  A->right->left = bt_create(6);
  avl_test(A_sent);
  A->right->right = bt_create(7);
  avl_test(A_sent);
  bt_delete(A_sent);
  //test(A_sent);

  struct binTree *B_sent =  bt_init(4);
  struct binTree *B = B_sent->left;
  avl_test(B_sent);
  B->right = bt_create(9);
  avl_test(B_sent);
  B->right->left = bt_create(6);
  avl_test(B_sent);
  B->right->left->left = bt_create(5);
  avl_test(B_sent);
  bt_delete(B_sent);
  //test(B_sent);

  struct binTree *C_sent = bt_init(10);
  struct binTree *C = C_sent->left;
  avl_test(C_sent);
  C->left = bt_create(4);
  avl_test(C_sent);
  C->right = bt_create(17);
  avl_test(C_sent);
  C->right->right = bt_create(21);
  avl_test(C_sent);
  C->right->right->left = bt_create(19);
  avl_test(C_sent);
  C->left->left = bt_create(3);
  avl_test(C_sent);
  C->left->right = bt_create(8);
  avl_test(C_sent);
  C->left->right->left = bt_create(7);
  avl_test(C_sent);
  C->left->right->right = bt_create(9);
  bt_delete(C_sent);
  //test(C_sent);

  return 1;
}
