#include"bintree.h"
#include"bst.h"
#include"list.h"
#include<assert.h>
#include<stdlib.h>
#include<stdio.h>

void insert_root_test(struct binTree *T, int x)
{
  printf("\n----------------\nInsertion of %d as root:", x);
  bst_insert_root(T, x);
  bt_ugly_print(T);
  assert(bt_is_bst(T));
}

void insert_leaf_test(struct binTree *T, int x)
{
  printf("\n----------------\nInsertion of %d as leaf:", x);
  bst_insert_leaf(T, x);
  bt_ugly_print(T);
  assert(bt_is_bst(T));
}

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
  bt_ugly_print(A);
  insert_root_test(A, 3);
  insert_leaf_test(A, 25);
  insert_root_test(A, 12);
  insert_leaf_test(A, 2);
  insert_root_test(A, 9);
  insert_leaf_test(A, 10);
  insert_root_test(A, 0);
  insert_leaf_test(A, 1);
  insert_root_test(A, 7);
  bst_test(A);
  deletion_test(A, 7);
  deletion_test(A, 5);
  insert_root_test(A, 5);
  insert_leaf_test(A, 6);
  deletion_test(A, 5);
  bt_delete(A);
  printf("\n----------------\n");

  return 1;
}
