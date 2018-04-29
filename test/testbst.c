#include"../bst.h"
#include"../list.h"
#include<assert.h>
#include<stdlib.h>
#include<stdio.h>

void bst_test(struct BST *T)
{
  printf("\n----------------\n");
  bst_ugly_print(T);
  bst_breadth_first_print(T);
  printf("max: %d\n", bst_max(T)->data);
  printf("min: %d\n", bst_min(T)->data);
  printf("size: %zu\nheight: %zu\nwidth: %zu\n", bst_size(T), bst_height(T), bst_width(T));
  printf((bst_is_degenerate(T)) ? "degenerate\n" : "not degenerate\n");
  printf((bst_is_perfect(T)) ? "perfect\n" : "not perfect\n");
  struct BST *F1 = bst_search(T, 1);
  if(F1)
    printf("1 is present in the tree\n");
  else
    printf("1 is not present in the tree\n");
  struct BST *F9 = bst_search(T, 9);
  if(F9)
    printf("9 is present in the tree\n");
  else
    printf("9 is not present in the tree\n");
  struct list *l = bst_to_hierarchy(T);
  list_print_int(l);
  struct BST *U = hierarchy_to_bst(l);
  assert(bst_equals(T, U));
  bst_delete(T);
  bst_delete(U);
  list_delete(l);
}
  

int main()
{
  struct BST *A = bst_create(4);
  A->left = bst_create(2);
  A->right = bst_create(6);
  A->left->left = bst_create(1);
  A->left->right = bst_create(3);
  A->right->left = bst_create(5);
  A->right->right = bst_create(7);
  bst_test(A);

  struct BST *B =  bst_create(4);
  B->right = bst_create(9);
  B->right->left = bst_create(6);
  B->right->left->left = bst_create(5);
  bst_test(B);

  struct BST *C = bst_create(10);
  C->left = bst_create(4);
  C->right = bst_create(17);
  C->right->right = bst_create(21);
  C->right->right->left = bst_create(19);
  C->left->left = bst_create(3);
  C->left->right = bst_create(8);
  C->left->right->left = bst_create(7);
  C->left->right->right = bst_create(9);
  bst_test(C);

  return 1;
}
