#ifndef BST_H_
#define BST_H_

#include<stdlib.h>
#include<stdio.h>
#include"list.h"

struct binTree* bst_max(struct binTree *T);

struct binTree* bst_min(struct binTree *T);

struct binTree* bst_search(struct binTree *T, int x);

void bst_insert_leaf(struct binTree *T, int x);

void bst_delete_elm(struct binTree *T, int x);

void bst_insert_root(struct binTree *T, int x);

#endif
