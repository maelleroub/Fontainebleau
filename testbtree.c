#include"btree.h"

int main()
{
  struct vector *rootkeys = vector_create(2);
  vector_insert_int_at(rootkeys, 0, 1); 
  vector_insert_int_at(rootkeys, 1, 3); 
  struct BTree *root = bt_init(2, rootkeys);

  struct vector *keysa = vector_create(2);
  vector_insert_int_at(keysa, 0, 0); 
  vector_insert_int_at(keysa, 1, 0); 
  struct BTree *a = bt_create(2, keysa);

  struct vector *keysb = vector_create(2);
  vector_insert_int_at(keysb, 0, 2); 
  vector_insert_int_at(keysb, 1, 3); 
  struct BTree *b = bt_create(2, keysb);
  
  struct vector *keysc = vector_create(2);
  vector_insert_int_at(keysc, 0, 4); 
  vector_insert_int_at(keysc, 1, 8); 
  struct BTree *c = bt_create(2, keysc);

  struct BTree *r = vector_get(root->children, 0);
  vector_insert_at(r->children, 0, a);
  vector_insert_at(r->children, 1, b);
  vector_insert_at(r->children, 2, c);
  
  bt_breadth_first_print(root);
  return 0;
}
