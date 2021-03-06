#ifndef ASSOC_H
#define ASSOC_H

typedef struct assoc{
  struct assoc *link;
  node_ptr x;
  node_ptr y;
} assoc_rec,*assoc_ptr;

hash_ptr new_assoc();
node_ptr find_assoc();
void insert_assoc();
void init_assoc();

#endif
