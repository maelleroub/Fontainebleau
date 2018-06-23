#include"bintree.h"
#include"list.h"
#include<assert.h>
#include<stdlib.h>
#include<stdio.h>

void balance_test(struct binTree *T)
{
  printf("\n----------------\n");
  bint_ugly_print(T);
  printf((bint_is_balanced(T)) ? "balanced\n" : "not balanced\n");
}

void avl_test(struct binTree *T)
{
  printf("\n----------------\n");
  bint_ugly_print(T);
  printf((bint_is_avl(T)) ? "avl\n" : "not avl\n");
}

void balance_print(struct binTree *T)
{
  printf("\n----------------\nBalances:\n");
  struct AVL *A = bint_to_avl(T);
  avl_balance_print(A);
  avl_delete(A);
}

void test(struct binTree *T)
{
  printf("\n----------------\n");
  bint_ugly_print(T);
  bint_breadth_first_print(T);
  printf("size: %d\nheight: %d\nwidth: %d\n", bint_size(T), bint_height(T), bint_width(T));
  printf((bint_is_degenerate(T)) ? "degenerate\n" : "not degenerate\n");
  printf((bint_is_perfect(T)) ? "perfect\n" : "not perfect\n");
  printf((bint_is_bst(T)) ? "bst\n" : "not bst\n");
  printf((bint_is_balanced(T)) ? "balanced\n" : "not balanced\n");
  struct list *l = bint_to_hierarchy(T);
  list_print_int(l);
  struct binTree *U = hierarchy_to_bint(l);
  assert(bint_equals(T, U));
  bint_delete(U);
  list_delete(l);
}
  

int main()
{
  struct binTree *A_sent = bint_init(1);
  struct binTree *A = A_sent->left;
  avl_test(A_sent);
  A->left = bint_create(2);
  avl_test(A_sent);
  A->right = bint_create(3);
  avl_test(A_sent);
  A->left->left = bint_create(4);
  avl_test(A_sent);
  A->left->right = bint_create(5);
  avl_test(A_sent);
  A->right->left = bint_create(6);
  avl_test(A_sent);
  A->right->right = bint_create(7);
  avl_test(A_sent);
  test(A_sent);
  balance_print(A_sent);
  bint_delete(A_sent);

  struct binTree *B_sent =  bint_init(4);
  struct binTree *B = B_sent->left;
  avl_test(B_sent);
  B->right = bint_create(9);
  avl_test(B_sent);
  B->right->left = bint_create(6);
  avl_test(B_sent);
  B->right->left->left = bint_create(5);
  avl_test(B_sent);
  test(B_sent);
  balance_print(B_sent);
  bint_delete(B_sent);

  struct binTree *C_sent = bint_init(10);
  struct binTree *C = C_sent->left;
  avl_test(C_sent);
  C->left = bint_create(4);
  avl_test(C_sent);
  C->right = bint_create(17);
  avl_test(C_sent);
  C->right->right = bint_create(21);
  avl_test(C_sent);
  C->right->right->left = bint_create(19);
  avl_test(C_sent);
  C->left->left = bint_create(3);
  avl_test(C_sent);
  C->left->right = bint_create(8);
  avl_test(C_sent);
  C->left->right->left = bint_create(7);
  avl_test(C_sent);
  C->left->right->right = bint_create(9);
  test(C_sent);
  balance_print(C_sent);
  bint_delete(C_sent);

  return 1;
}
