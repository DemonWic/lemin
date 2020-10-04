#include "lem_in.h"

int     add_to_clist(t_clist *list, char *cur)
{
	t_clist *new;
	t_clist *tmp;
	
	new = (t_clist*)malloc(sizeof(t_clist));
	new->val = cur;
	new->next = NULL;
	if (!list)
	{
		list = new;
		return (1);
	}
	tmp = list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (1);
}

t_node  *get_node_by_name(t_data *data, char *name)
{
	t_nlist *tmp;
	
	tmp = data->nodes;
	while (tmp)
	{
		if (ft_strcmp(tmp->node->room->name, name) == 0)
			return (tmp->node);
		tmp = tmp->next;
	}
	return (NULL);
}

t_clist *open_node(t_clist *open, t_clist *closed, t_node *cur)
{
	t_clist *tmp;
	
	tmp = closed;
	while (tmp)
	{
		if (ft_strcmp(cur->room->name, tmp->val) == 0)
			return (open);
		tmp = tmp->next;
	}
	add_to_clist(open, cur->room->name);
	return (open);
}

t_clist *close_node(t_clist *closed, t_clist *open, t_node *cur)
{
	t_clist *tmp;
	t_clist *prev;
	t_clist *next;
	
	add_to_clist(closed, cur->room->name);
	tmp = open;
	prev = NULL;
	while (tmp)
	{
		next = tmp->next;
		if (ft_strcmp(tmp->val, cur->room->name) == 0)
		{
			if (prev)
				prev->next = next;
			else
				open = next;
			free(tmp->val);
			free(tmp);
			return (closed);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (closed);
}

int     add_ukaz(t_fdata *f_data, t_node *prev, char *cur)
{
	f_data->uks[f_data->u_len].cur = cur;
	f_data->uks[f_data->u_len].prev = prev->room->name;
	f_data->u_len++;
	return (1);
}

t_ulist *add_ul(t_ulist *ul, t_ukaz *uk)
{
	t_ulist *new;
	
	new = (t_ulist*)malloc(sizeof(t_ulist));
	new->val = uk;
	new->next = NULL;
	if (!ul)
		return (new);
	new->next = ul;
	return (new);
}

t_ukaz  *find_uk(t_node *cur, t_fdata *f_data)
{
	int     i;
	
	i = 0;
	while (i < f_data->u_len + 1)
	{
		if (ft_strcmp(cur->room->name, f_data->uks[i].cur) == 0)
			return (&f_data->uks[i]);
		i++;
	}
	return (NULL);
}

int     add_way(t_data *data, t_node *cur, t_fdata *f_data)
{
	t_way   *new;
	t_wlist *new_way;
	t_ulist *ul;
	
	ul = NULL;
	new = (t_way*)malloc(sizeof(t_way));
	new->len = 0;
	while (ft_strcmp(cur->room->name, data->start->room->name) == 0)
	{
		ul = add_ul(ul, find_uk(cur, f_data));
		cur = get_node_by_name(data, ul->val->prev);
		new->len++;
	}
	new->way = (t_clist*)malloc(sizeof(t_clist));
	while (ul)
	{
		add_to_clist(new->way, ul->val->cur);
		ul = ul->next;
	}
	new_way = (t_wlist*)malloc((sizeof(t_wlist)));
	new_way->way = new;
	new_way->next = data->ways;
	data->ways = new_way;
	return (1);
}

int     find_ways(t_data *data)
{
	t_fdata *f_data;
	t_node  *cur;
	int     i;
	
	f_data = (t_fdata*)malloc(sizeof(t_fdata));
	f_data->open = NULL;
	f_data->closed = NULL;
	f_data->u_len = 0;
	f_data->open = open_node(f_data->open, f_data->closed, data->start);
	while (f_data->open)
	{
		cur = get_node_by_name(data, f_data->open->val);
		f_data->closed = close_node(f_data->closed, f_data->open, cur);
		i = 0;
		while (cur->rel[i] != NULL)
		{
			if (ft_strcmp(cur->rel[i], data->end->room->name) == 0)
			{
				add_way(data, cur, f_data);
				i++;
				continue ;
			}
			open_node(f_data->open, f_data->closed, get_node_by_name(data, cur->rel[i]));
			add_ukaz(f_data, cur, cur->rel[i]);
			i++;
		}
	}
}

