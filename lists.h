#ifndef LISTS_H
# define LISTS_H

# include "lem_in.h"

typedef struct  s_nlist
{
	struct s_node   *node;
	struct s_nlist  *next;
}               t_nlist;

typedef struct  s_rlist
{
	struct s_room   *room;
	struct s_rlist  *next;
}               t_rlist;

typedef struct  s_llist
{
	struct s_link   *link;
	struct s_llist  *next;
}               t_llist;

typedef struct  s_clist
{
	char            *val;
	struct s_clist  *next;
}               t_clist;

typedef struct  s_ulist
{
	struct s_ukaz   *val;
	struct s_ulist  *next;
}               t_ulist;

typedef struct  s_wlist
{
	struct s_way    *way;
	struct s_wlist  *next;
}               t_wlist;

typedef struct  s_lemlist
{
	struct s_lem        *lem;
	struct s_lemlist    *next;
}               t_lemlist;

#endif
