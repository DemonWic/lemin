#include "lem_in.h"

int     add_lem(t_data *data, t_way *way, t_lemlist *lems)
{
	t_lemlist   *new;
	t_lemlist   *tmp;
	
	new = (t_lemlist*)malloc(sizeof(t_lemlist));
	new->lem = (t_lem*)malloc(sizeof(t_lem));
	new->lem->n = data->cur_n++;
	new->lem->way = way;
	new->lem->pos = NULL;
	new->next = NULL;
	data->col--;
	if (!lems)
	{
		lems = new;
		return (1);
	}
	tmp = lems;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (1);
}

t_lemlist   *new_lems(t_data *data, t_wlist *ways, t_lemlist *lems)
{
	t_wlist *cur;
	int     pred;
	
	cur = ways;
	pred = 0;
	while (cur)
	{
		if (data->col > cur->way->len * pred)
			add_lem(data, cur->way, lems);
		else
			break ;
		pred++;
		cur = cur->next;
	}
	return (lems);
}

char    *get_next_pos(char *cur, t_clist *way)
{
	t_clist *tmp;
	
	tmp = way;
	if (!cur)
		return (tmp->val);
	while (ft_strcmp(tmp->val, cur) != 0)
		tmp = tmp->next;
	if (!tmp->next)
		return (NULL);
	return (tmp->next->val);
}

int     end_lem(t_lemlist *lems, t_data *data, t_lemlist *cur)
{
	t_lemlist   *tmp;
	t_lemlist   *prev;
	
	prev = NULL;
	tmp = lems;
	ft_putchar('L');
	ft_putstr(ft_itoa(cur->lem->n));
	ft_putchar('-');
	ft_putstr(data->end->room->name);
	ft_putchar(' ');
	while (tmp)
	{
		if (tmp->lem->n == cur->lem->n)
		{
			if (prev)
				prev->next = tmp->next;
			else
				lems = tmp->next;
			return (1);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (0);
}

int     make_step(t_lemlist *lems, t_data *data)
{
	t_lemlist   *cur;
	
	cur = lems;
	while (cur)
	{
		cur->lem->pos = get_next_pos(cur->lem->pos, cur->lem->way->way);
		if (cur->lem->pos == NULL)
			end_lem(lems, data, cur);
		ft_putchar('L');
		ft_putstr(ft_itoa(cur->lem->n));
		ft_putchar('-');
		ft_putstr(cur->lem->pos);
		ft_putchar(' ');
		cur = cur->next;
	}
	return (1);
}

int     go_lem(t_data *data)
{
	t_wlist     *ways;
	t_lemlist   *lems;
	
	ways = get_ways(data);
	lems = NULL;
	lems = new_lems(data, ways, lems);
	while (lems)
	{
		make_step(lems, data);
		lems = new_lems(data, ways, lems);
	}
	return (1);
}

