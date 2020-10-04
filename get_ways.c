#include "lem_in.h"

int     check_way(t_way *way, t_wlist *other)
{
	t_wlist *tmp;
	t_clist *tmp2;
	t_clist *tmp3;
	
	tmp = other;
	tmp3 = way->way;
	while (tmp3)
	{
		while (tmp)
		{
			tmp2 = tmp->way->way;
			while (tmp2)
			{
				if (ft_strcmp(tmp2->val, tmp3->val) == 0)
					return (0);
				tmp2 = tmp2->next;
			}
			tmp = tmp->next;
		}
		tmp3 = tmp3->next;
	}
	return (1);
}

t_wlist *find_min_way(t_data *data, t_wlist *other)
{
	int     min;
	t_wlist *ret;
	t_wlist *tmp;
	
	min = INT32_MAX;
	ret = NULL;
	tmp = data->ways;
	while (tmp)
	{
		if (tmp->way->len < min && check_way(tmp->way, other))
		{
			min = tmp->way->len;
			ret = tmp;
		}
		tmp = tmp->next;
	}
	return (ret);
}

t_wlist *get_ways(t_data *data)
{
	t_wlist *ret;
	t_wlist *new;
	t_wlist *cur;
	t_wlist *tmp;
	
	ret = NULL;
	while ((cur = find_min_way(data, ret)))
	{
		new = (t_wlist*)malloc(sizeof(t_wlist));
		new->way = cur->way;
		new->next = NULL;
		if (!ret)
		{
			ret = new;
			continue ;
		}
		tmp = ret;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (ret);
}

