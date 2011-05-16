#ifndef STORAGE_H
#define STORAGE_H

typedef struct rec {
  struct rec *link;
} rec_rec, *rec_ptr;

typedef struct mgr{
    rec_rec free;
    int  rec_size;
    int count;
    void (*free_hook)();
} mgr_rec, *mgr_ptr;

#define ALLOCSIZE (2<<15)

void init_storage();
char *stg_malloc();
void stg_free();
mgr_ptr new_mgr();
rec_ptr new_rec(),dup_rec();
void free_rec();

#endif STORAGE_H
