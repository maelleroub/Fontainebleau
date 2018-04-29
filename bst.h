#include<stdlib.h>
#include<stdio.h>
#include"list.h"

struct binTree* bst_max(struct binTree *T);

struct binTree* bst_min(struct binTree *T);

struct binTree* bst_search(struct binTree *T, int x);

struct binTree* bst_insert_leaf(struct binTree *T, int x);
