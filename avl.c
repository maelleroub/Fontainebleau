#include"avl.h"
#include"queue.h"

struct AVL* avl_init(int n)
{
  struct AVL *A = malloc(sizeof(struct AVL));
  A->data = NULL;
  A->right = NULL;
  A->balance = 0;
  A->left = avl_create(n);
  return A;
}

struct AVL* avl_create(int n)
{
  struct AVL *A = malloc(sizeof(struct AVL));
  int *data = malloc(sizeof(int));
  *data = n;
  A->data = data;
  A->left = NULL;
  A->right = NULL;
  A->balance = 0;
  return A;
}

int avl_is_empty(struct AVL *A)
{
  return !A || (A->data == NULL && !A->left);
}

size_t avl_size(struct AVL *A)
{
  if(!A)
    return 0;
  if(A->data == NULL)
  {
    if(!A->left)
      return 0;
    A = A->left;
  }
  return 1 + avl_size(A->left) + avl_size(A->right);
}

static int _max(int a, int b)
{
  return (a >= b) ? a : b;
}

size_t avl_height(struct AVL *A)
{
  if(avl_is_empty(A))
    return -1;
  if(A->data == NULL)
    A = A->left;
  return 1 + avl_height((A->balance <= 0) ? A->right : A->left);
}

size_t avl_width(struct AVL *A)
{
  if(avl_is_empty(A))
    return 0;
  A = A->left;
  int maxw = 0;
  int w = 0;
  struct queue *q = malloc(sizeof(struct queue));
  queue_init(q);
  queue_push(q, A);
  queue_push(q, NULL);
  while(!queue_is_empty(q))
  {
    struct AVL *B = queue_pop(q);
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

struct AVL* avl_max(struct AVL *A)
{
  if(avl_is_empty(A))
    return NULL;
  A = A->left;
  while(A->right)
    A = A->right;
  return A;
}

struct AVL* avl_min(struct AVL *A)
{
  if(avl_is_empty(A))
    return NULL;
  A = A->left;
  while(A->left)
    A = A->left;
  return A;
}

struct AVL* avl_search(struct AVL *A, int x)
{
  if(avl_is_empty(A))
    return A;
  if(A->data == NULL)
    return avl_search(A->left, x);
  if(x == *A->data)
    return A;
  if(x < *A->data)
    return avl_search(A->left, x);
  return avl_search(A->right, x);
}

static void _avl_ugly_print(struct AVL *A, int depth)
{
  if(!avl_is_empty(A))
  {
    _avl_ugly_print(A->left, depth + 1);
    for(int i = 0; i < depth; i++)
      printf("  ");
    printf("%d\n", *A->data);
    _avl_ugly_print(A->right, depth + 1);
  }
  else
    printf("\n");
}

void avl_ugly_print(struct AVL *A)
{
  if(avl_is_empty(A))
    return;
  _avl_ugly_print(A->left, 0);
}

void avl_breadth_first_print(struct AVL *A)
{
  if(!avl_is_empty(A))
  {
    A = A->left;
    int nextlevel = 0;
    void *change = malloc(sizeof(void));
    struct queue *q = malloc(sizeof(struct queue));
    queue_init(q);
    queue_push(q, A);
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
        struct AVL *B = v;
        if(avl_is_empty(B))
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

static struct AVL* _rotation_left(struct AVL *A)
{
  struct AVL *R = A->right;
  A->right = R->left;
  R->left = A;
  return R;
}

static struct AVL* _rotation_right(struct AVL *A)
{
  struct AVL *L = A->left;
  A->left = L->right;
  L->right = A;
  return L;
}

static struct AVL* _avl_insert(struct AVL *A, int x, int *change)
{
  if(!A)
  {
    *change = 1;
    return avl_create(x);
  }
  if(x <= *A->data)
  {
    A->left = _avl_insert(A->left, x, change);
    if(*change)
      A->balance = A->balance + 1;
    if(A->balance == 2)
    {
      if(A->left->balance >= 0)
      {
        *change = 0;
        A = _rotation_right(A);
        A->balance = 0;
        A->right->balance = 0;
        return A;
      }
      *change = 0;
      A->left = _rotation_left(A->left);
      A = _rotation_right(A);
      if(A->balance == 1)
      {
        A->left->balance = 0;
        A->right->balance = -1;
      }
      if(A->balance == 0)
      {
        A->left->balance = 0;
        A->right->balance = 0;
      }
      if(A->balance == -1)
      {
        A->left->balance = 1;
        A->right->balance = 0;
      }
      A->balance = 0;
      return A;
    }
    if(!(*change && A->balance == 1))
      *change = 0;
    return A;
  }
  A->right = _avl_insert(A->right, x, change);
  if(*change)
    A->balance = A->balance - 1;
  if(A->balance == -2)
  {
    if(A->right->balance <= 0)
    {
      *change = 0;
      A = _rotation_left(A);
      A->balance = 0;
      A->left->balance = 0;
      return A;
    }
    *change = 0;
    A->right = _rotation_right(A->right);
    A = _rotation_left(A);
    if(A->balance == 1)
    {
      A->left->balance = 0;
      A->right->balance = -1;
    }
    if(A->balance == 0)
    {
      A->left->balance = 0;
      A->right->balance = 0;
    }
    if(A->balance == -1)
    {
      A->left->balance = 1;
      A->right->balance = 0;
    }
    A->balance = 0;
    return A;
  }
  if(!(*change && A->balance == -1))
    *change = 0;
  return A;
}

void avl_insert(struct AVL *A, int x)
{
  int *change = malloc(sizeof(int));
  A->left = _avl_insert(A->left, x, change);
  free(change);
}

void avl_delete(struct AVL *A)
{
  if(A)
  {
    avl_delete(A->left);
    avl_delete(A->right);
    free(A->data);
    free(A);
  }
}
