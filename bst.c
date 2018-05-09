#include"bst.h"

struct binTree* bst_max(struct binTree *T)
{
  if(bt_is_empty(T))
    return NULL;
  T = T->left;
  while(T->right)
    T = T->right;
  return T;
}

struct binTree* bst_min(struct binTree *T)
{
  if(bt_is_empty(T))
    return NULL;
  T = T->left;
  while(T->left)
    T = T->left;
  return T;
}

struct binTree* bst_search(struct binTree *T, int x)
{
  if(bt_is_empty(T))
    return T;
  if(T->data == NULL)
    return bst_search(T->left, x);
  if(x == *T->data)
    return T;
  if(x < *T->data)
    return bst_search(T->left, x);
  return bst_search(T->right, x);
}

static struct binTree* _bst_insert_leaf(struct binTree* T, int x)
{
  if(!T)
    return bt_create(x);
  if(x <= *T->data)
    T->left = _bst_insert_leaf(T->left, x);
  else
    T->right = _bst_insert_leaf(T->right, x);
  return T;
}

void bst_insert_leaf(struct binTree *T, int x)
{
  T->left = _bst_insert_leaf(T->left, x);
}

static struct binTree* _bst_delete_max(struct binTree *T, int *x)
{
  if(bt_is_empty(T))
    return NULL;
  if(bt_is_empty(T->right))
  {
    struct binTree *N = T->left;
    *x = *(T->data);
    free(T->data);
    free(T);
    return N;
  }
  T->right = _bst_delete_max(T->right, x);
  return T;
}

static struct binTree* _bst_delete_min(struct binTree *T, int *x)
{
  if(bt_is_empty(T))
    return NULL;
  if(bt_is_empty(T->left))
  {
    struct binTree *N = T->right;
    *x = *(T->data);
    free(T->data);
    free(T);
    return N;
  }
  T->left = _bst_delete_min(T->left, x);
  return T;
}

static struct binTree* _bst_delete_elm(struct binTree *T, int x)
{
  if(!T)
    return T;
  if(x < *T->data)
  {
    T->left = _bst_delete_elm(T->left, x);
    return T;
  }
  if(x > *T->data)
  {
    T->right = _bst_delete_elm(T->right, x);
    return T;
  }
  //Node to delete
  if(bt_is_empty(T->left))
  {
    if(bt_is_empty(T->right))
    {
      free(T->data);
      free(T);
      return NULL;
    }
    int *d = malloc(sizeof(int));
    T->right = _bst_delete_min(T->right, d);
    *T->data = *d;
    free(d);
    return T;
  }
  int *d = malloc(sizeof(int));
  T->left = _bst_delete_max(T->left, d);
  *T->data = *d;
  free(d);
  return T;
}

void bst_delete_elm(struct binTree *T, int x)
{
  T->left = _bst_delete_elm(T->left, x);
}

static struct binTree* _rotation_left(struct binTree *T)
{
  struct binTree *R = T->right;
  T->right = R->left;
  R->left = T;
  return R;
}

static struct binTree* _rotation_right(struct binTree *T)
{
  struct binTree *L = T->left;
  T->left = L->right;
  L->right = T;
  return L;
}

static struct binTree* _bst_insert_root(struct binTree *T, int x, int *l)
{
  if(!T)
  {
    *l = 0;
    return bt_create(x);
  }
  if(x <= *T->data)
  {
    T->left = _bst_insert_root(T->left, x, l);
    if(*l == 1)
      T->left = _rotation_right(T->left);
    if(*l == -1)
      T->left = _rotation_left(T->left);
    *l = 1;
  }
  else
  {
    T->right = _bst_insert_root(T->right, x, l);
    if(*l == 1)
      T->right = _rotation_right(T->right);
    if(*l == -1)
      T->right = _rotation_left(T->right);
    *l = -1;
  }
  return T;
}


void bst_insert_root(struct binTree *T, int x)
{
  if(T->left == NULL)
    T->left = bt_create(x);
  else
  {
    int *l = malloc(sizeof(int));
    T->left = _bst_insert_root(T->left, x, l);
    if(*l == 1)
      T->left = _rotation_right(T->left);
    if(*l == -1)
      T->left = _rotation_left(T->left);
    free(l);
  }
}
