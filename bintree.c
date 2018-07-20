#include"bintree.h"

struct binTree* bint_init(int n)
{
  struct binTree *T = malloc(sizeof(struct binTree));
  T->data = NULL;
  T->right = NULL;
  T->left = bint_create(n);
  return T;
}

struct binTree* bint_create(int n)
{
  struct binTree *T = malloc(sizeof(struct binTree));
  int *data = malloc(sizeof(int));
  *data = n;
  T->data = data;
  T->left = NULL;
  T->right = NULL;
  return T;
}

int bint_is_empty(struct binTree *T)
{
  return !T || (T->data == NULL && !T->left);
}

int bint_size(struct binTree *T)
{
  if(!T)
    return 0;
  if(T->data == NULL)
  {
    if(!T->left)
      return 0;
    T = T->left;
  }
  return 1 + bint_size(T->left) + bint_size(T->right);
}

static int _max(int a, int b)
{
  return (a >= b) ? a : b;
}

int bint_height(struct binTree *T)
{
  if(bint_is_empty(T))
    return -1;
  if(T->data == NULL)
    T = T->left;
  return 1 + _max(bint_height(T->left), bint_height(T->right));
}

int bint_is_degenerate(struct binTree *T)
{
  if(bint_is_empty(T))
    return 1;
  if(T->left && T->right)
    return 0;
  return bint_is_degenerate(T->left) && bint_is_degenerate(T->right);
}

static size_t _left_path_len(struct binTree *T)
{
  size_t x;
  for(x = 0; T; x++)
    T = T->left;
  return x;
}

static int _bint_is_perfect(struct binTree *T, size_t h, size_t lvl)
{
  if(bint_is_empty(T->left) ^ bint_is_empty(T->right))
    return 0;
  if(T->left)
    return _bint_is_perfect(T->left, h, lvl + 1) && _bint_is_perfect(T->right, h, lvl + 1);
  return h == lvl;
}

int bint_is_perfect(struct binTree *T)
{
  if(bint_is_empty(T))
    return 1;
  T = T->left;
  size_t h = _left_path_len(T);
  return _bint_is_perfect(T, h, 1);
}

int bint_width(struct binTree *T)
{
  if(bint_is_empty(T))
    return 0;
  T = T->left;
  int maxw = 0;
  int w = 0;
  struct queue *q = malloc(sizeof(struct queue));
  queue_init(q);
  queue_push(q, T);
  queue_push(q, NULL);
  while(!queue_is_empty(q))
  {
    struct binTree *B = queue_pop(q);
    if(!B)
    {
      maxw = _max(w, maxw);
      w = 0;
      if(!queue_is_empty(q))
        queue_push(q, NULL);
    }
    else
    {
      w++;
      if(B->left)
        queue_push(q, B->left);
      if(B->right)
        queue_push(q, B->right);
    }
  }
  queue_delete(q);
  return (size_t) maxw;
}

static int _bint_is_bst(struct binTree *T, int *low, int *high)
{
  if(!T)
    return 1;
  if(low == NULL)
  {
    if(high != NULL && *T->data >= *high)
      return 0;
    return _bint_is_bst(T->left, low, T->data) && _bint_is_bst(T->right, T->data, high);
  }
  if(high == NULL)
  {
    if(*T->data < *low)
      return 0;
    return _bint_is_bst(T->left, low, T->data) && _bint_is_bst(T->right, T->data, high);
  }
  if(*T->data < *low || *T->data >= *high)
    return 0;
  return _bint_is_bst(T->left, low, T->data) && _bint_is_bst(T->right, T->data, high);
}

int bint_is_bst(struct binTree *T)
{
  if(bint_is_empty(T))
    return 1;
  return _bint_is_bst(T->left, NULL, NULL);
}

static int _bint_is_balanced(struct binTree *T, int *h)
{
  if(!T)
  {
    *h = -1;
    return 1;
  }
  int bl = _bint_is_balanced(T->left, h);
  int hl = *h;
  int br = _bint_is_balanced(T->right, h);
  int hr = *h;
  if(!(bl && br))
    return 0;
  if(hl - hr > 1 || hr - hl > 1)
    return 0;
  *h = 1 + _max(hl, hr);
  return 1;
}

int bint_is_balanced(struct binTree *T)
{
  int *h = malloc(sizeof(int));
  int b = _bint_is_balanced(T->left, h);
  free(h);
  return b;
}

static int _bint_is_avl(struct binTree *T, int *low, int *high, int *h)
{
  if(!T)
  {
    *h = -1;
    return 1;
  }
  if(low == NULL)
  {
    if(high != NULL && *T->data >= *high)
      return 0;
  }
  else
  {
    if(high == NULL)
    {
      if(*T->data < *low)
        return 0;
    }
    else
    {
      if(*T->data < *low || *T->data >= *high)
        return 0;
    }
  }
  int bl = _bint_is_avl(T->left, low, T->data, h);
  int hl = *h;
  int br = _bint_is_avl(T->right, T->data, high, h);
  int hr = *h;
  if(!(bl && br))
    return 0;
  if(hl - hr > 1 || hr - hl > 1)
    return 0;
  *h = 1 + _max(hl, hr);
  return 1;
}

int bint_is_avl(struct binTree *T)
{
  if(bint_is_empty(T))
    return 1;
  int *h = malloc(sizeof(int));
  int b = _bint_is_avl(T->left, NULL, NULL, h);
  free(h);
  return b;
}

struct list* bint_to_hierarchy(struct binTree *T)
{
  struct list *l = malloc(sizeof(struct list));
  l->next = NULL;
  if (!bint_is_empty(T))
  {
    T = T->left;
    int nextlevel = 0;
    void *change = malloc(sizeof(1));
    struct queue *q = malloc(sizeof(struct queue));
    queue_init(q);
    queue_push(q, T);
    queue_push(q, change);
    while(1)
    {
      void* v = queue_pop(q);
      if(v == change)
      {
        if(!nextlevel)
          break;
        nextlevel = 0;
        queue_push(q, change);
      }
      else
      {
        struct binTree *B = v;
        struct list *l1 = malloc(sizeof(struct list));
        l1->next = NULL;
        if(bint_is_empty(B))
        {
          l1->data = NULL;
          queue_push(q, NULL);
          queue_push(q, NULL);
        }
        else
        {
          l1->data = B->data;
          queue_push(q, B->left);
          queue_push(q, B->right);
          nextlevel = nextlevel || B->left || B->right;
        }
        list_push_back(l, l1);
      }
    }
    free(change);
    queue_delete(q);
  }
  return l;
}

struct binTree* hierarchy_to_bint(struct list *l)
{
  struct list *list = list_copy(l);
  if(list_is_empty(list))
    return NULL;
  struct list *x = list_pop_front(list);
  struct binTree *root = bint_init(*((int *) x->data));
  free(x);
  struct queue *q = malloc(sizeof(struct queue));
  queue_init(q);
  queue_push(q, root->left);
  while(!list_is_empty(list))
  {
    struct binTree *cur = queue_pop(q);
    struct list *l = list_pop_front(list);
    if(l && cur)
    {
      if(!l->data)
      {
        cur->left = NULL;
        queue_push(q, NULL);
      }
      else
      {
        struct binTree *bintleft = bint_create(*((int *) l->data));
        cur->left = bintleft;
        queue_push(q, bintleft);
      }
    }
    struct list *r = list_pop_front(list);
    if(r && cur)
    {
      if(!r->data)
      {
        cur->right = NULL;
        queue_push(q, NULL);
      }
      else
      {
        struct binTree *bintright = bint_create(*((int *) r->data));
        cur->right = bintright;
        queue_push(q, bintright);
      }
    }
    free(l);
    free(r);
    if(!cur)
    {
      queue_push(q, NULL);
      queue_push(q, NULL);
    }
  }
  queue_delete(q);
  list_delete(list);
  return root;
}

int bint_equals(struct binTree *A, struct binTree *B)
{
  if(bint_is_empty(A) ^ bint_is_empty(B))
    return 0;
  if(bint_is_empty(A) && bint_is_empty(B))
    return 1;
  if(A->data == NULL)
    return bint_equals(A->left, B->left);
  if(*A->data != *B->data)
    return 0;
  return bint_equals(A->left, B->left) && bint_equals(A->right, B->right);
}

static void _bint_ugly_print(struct binTree *T, int depth)
{
  if(!bint_is_empty(T))
  {
    _bint_ugly_print(T->left, depth + 1);
    for(int i = 0; i < depth; i++)
      printf("  ");
    printf("%d\n", *T->data);
    _bint_ugly_print(T->right, depth + 1);
  }
  else
    printf("\n");
}

void bint_ugly_print(struct binTree *T)
{
  if(bint_is_empty(T))
    return;
  _bint_ugly_print(T->left, 0);
}

void bint_breadth_first_print(struct binTree *T)
{
  if(!bint_is_empty(T))
  {
    T = T->left;
    int nextlevel = 0;
    void *change = malloc(sizeof(void));
    struct queue *q = malloc(sizeof(struct queue));
    queue_init(q);
    queue_push(q, T);
    queue_push(q, change);
    while(1)
    {
      void* v = queue_pop(q);
      if(v == change)
      {
        printf("\n");
        if(!nextlevel)
          break;
        nextlevel = 0;
        queue_push(q, change);
      }
      else
      {
        struct binTree *B = v;
        if(bint_is_empty(B))
        {
          printf("X  ");
          queue_push(q, NULL);
          queue_push(q, NULL);
        }
        else
        {
          printf("%d  ", *B->data);
          queue_push(q, B->left);
          queue_push(q, B->right);
          nextlevel = nextlevel || B->left || B->right;
        }
      }
    }
    free(change);
    queue_delete(q);
  }
}

void bint_delete(struct binTree *T)
{
  if(T)
  {
    bint_delete(T->left);
    bint_delete(T->right);
    free(T->data);
    free(T);
  }
}

static struct AVL* _bint_to_avl(struct binTree *T, int *h)
{
  if(!T)
  {
    *h = -1;
    return NULL;
  }
  struct AVL *A = avl_create(*T->data);
  A->left = _bint_to_avl(T->left, h);
  int hl = *h;
  A->right = _bint_to_avl(T->right, h);
  int hr = *h;
  A->balance = hl - hr;
  *h = 1 + _max(hl, hr);
  return A;
}

struct AVL* bint_to_avl(struct binTree *T)
{
  if(bint_is_empty(T))
  {
    struct AVL *A = malloc(sizeof(struct AVL));
    A->data = NULL;
    A->left = NULL;
    A->right = NULL;
    A->balance = 0;
    return A;
  }
  struct AVL *A = avl_init(*T->left->data);
  int *h = malloc(sizeof(int));
  A->left->left = _bint_to_avl(T->left->left, h);
  int hl = *h;
  A->left->right = _bint_to_avl(T->left->right, h);
  int hr = *h;
  A->left->balance = hl - hr;
  free(h);
  return A;
}
