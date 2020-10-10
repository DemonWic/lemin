#ifndef LEM_IN_H
#define LEM_IN_H

# include "libft/libft.h"
# include "lists.h"
# include <stdio.h>
# include <limits.h>

# define MAP_SIZE 4000

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

typedef struct      s_node
{
	char            *name;
	int             x;
	int             y;
	char            *rel;
	int             marker;
	struct s_node   *next;
}                   t_node;

typedef struct  s_ukaz
{
	char        *prev;
	char        *cur;
}               t_ukaz;

typedef struct  s_way
{
	char        *way[MAP_SIZE];
	int         len;
}               t_way;

typedef struct  s_fdata
{
	char    *open[MAP_SIZE];
	char    *closed[MAP_SIZE];
	t_ukaz  uks[MAP_SIZE];
	int     u_len;
	int     o_len;
	int     c_len;
}               t_fdata;

typedef struct  s_lem
{
	t_way       *way;
	char        *pos;
	int         n;
	int         finished;
}               t_lem;

typedef struct  s_data
{
	t_node      *start;
	t_node      *end;
	t_node      *nodes;
	t_way       *ways[MAP_SIZE];
	int         w_count;
	int         col;
	int         ant_count;
	int         cur_n;
}               t_data;

int			    get_next_line(const int fd, char **line);
int		        read_data(t_data *data);
int             make_graf(t_data *data);
t_wlist         *get_ways(t_data *data);
int             find_ways(t_data *data);
int             go_lem(t_data *data);

#endif
