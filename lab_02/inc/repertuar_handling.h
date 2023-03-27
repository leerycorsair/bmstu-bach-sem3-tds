#ifndef __REPERTUAR_HANDLING_H__
#define __REPERTUAR_HANDLING_H__

#include "err_codes.h"
#include "show_t.h"
#include <inttypes.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REP_RECS 100

int fread_repertuar(FILE *f, show_t rep[MAX_REP_RECS], size_t *rep_size, key_t key_rep[MAX_REP_RECS]);
int repertuar_add_rec(show_t rep[MAX_REP_RECS], size_t *rep_size, key_t key_rep[MAX_REP_RECS]);
int repertuar_del_rec(show_t rep[MAX_REP_RECS], size_t *rep_size, key_t key_rep[MAX_REP_RECS]);
void print_rep_with_key(show_t rep[MAX_REP_RECS], size_t rep_size, key_t key_rep[MAX_REP_RECS]);
void print_rep_no_key(show_t rep[MAX_REP_RECS], size_t rep_size);
void print_rep_key(key_t key_rep[MAX_REP_RECS], size_t rep_size);
void sort_rep(show_t rep[MAX_REP_RECS], size_t rep_size, key_t key_rep[MAX_REP_RECS]);
void sort_key(key_t key_rep[MAX_REP_RECS], size_t rep_size);
void cmp_sorts(show_t rep[MAX_REP_RECS], size_t rep_size, key_t key_rep[MAX_REP_RECS]);
int shows_for_kids(show_t rep[MAX_REP_RECS], size_t rep_size);
int read_show(FILE *f, show_t *buf);
void form_key(show_t rep[MAX_REP_RECS], size_t rep_size, key_t key_rep[MAX_REP_RECS]);
int fread_line(FILE *file, char *s, int str_len);
int cmp_shows(const void *p, const void *q);
int cmp_keys(const void *p, const void *q);
void print_show(show_t show);
int read_line(char str[MAX_STR_SIZE + 1]);
int save_curr_table(show_t rep[MAX_REP_RECS], size_t rep_size);

#endif