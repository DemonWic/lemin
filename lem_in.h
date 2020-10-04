#ifndef LEM_IN_H
#define LEM_IN_H

# include "libft/libft.h"
# include "lists.h"
# include <stdio.h>
# include <limits.h>

typedef struct  s_room
{
	int         x;
	int         y;
	int         marker;
	char        *name;
}               t_room;

typedef struct  s_link
{
	char        *s1;
	char        *s2;
}               t_link;

typedef struct  s_node
{
	t_room      *room;
	char        **rel;
}               t_node;

typedef struct  s_ukaz
{
	char        *prev;
	char        *cur;
}               t_ukaz;

typedef struct  s_way
{
	t_clist     *way;
	int         len;
}               t_way;

typedef struct  s_fdata
{
	t_clist *open;
	t_clist *closed;
	t_ukaz  uks[1000];
	int     u_len;
}               t_fdata;

typedef struct  s_lem
{
	t_way       *way;
	char        *pos;
	int         n;
}               t_lem;

typedef struct  s_data
{
	t_node      *start;
	t_node      *end;
	t_rlist     *rooms;
	t_llist     *links;
	t_nlist     *nodes;
	t_wlist     *ways;
	int         col;
	int         cur_n;
}               t_data;

int			    get_next_line(const int fd, char **line);
int		        read_data(t_data *data);
int             make_graf(t_data *data);
t_wlist         *get_ways(t_data *data);
int             find_ways(t_data *data);
int             go_lem(t_data *data);

#endif
