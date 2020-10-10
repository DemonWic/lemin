#include "lem_in.h"

int     add_lem(t_data *data, int i, t_lem *lems[data->ant_count], int cur_lems)
{
	t_lem   *new;
	
	new = (t_lem*)malloc(sizeof(t_lem));
	new->way = data->ways[i];
	new->n = cur_lems + 1;
	new->pos = data->ways[i]->way[0];
	new->finished = 0;
	lems[cur_lems] = new;
	data->col--;
	data->cur_n++;
	return (++cur_lems);
}

int     count_min_lems(t_data *data, int a)
{
	int     i;
	int     res;
	
	res = 0;
	i = 0;
	while (i <= a)
	{
		res += data->ways[i]->len - data->ways[0]->len + 1;
		i++;
	}
	return (res);
}
int     new_lems(t_data *data, t_lem *lems[data->ant_count], int cur_lems)
{
	int     i;
	
	i = 0;
	while (i <= data->w_count)
	{
		if (data->col >= count_min_lems(data, i))
		{
			cur_lems = add_lem(data, i, lems, cur_lems);
			ft_putchar('L');
			ft_putstr(ft_itoa(cur_lems));
			ft_putchar('-');
			ft_putstr(lems[cur_lems - 1]->way->way[0]);
			ft_putchar(' ');
		}
		else
			break ;
		i++;
	}
	return (cur_lems);
}

char    *get_next_pos(char *cur, t_way *way)
{
	int     i;
	
	i = 0;
	while (i < way->len)
	{
		if (ft_strcmp(cur, way->way[i]) == 0)
		{
			free(cur);
			return (ft_strdup(way->way[i + 1]));
		}
	}
	free(cur);
	return (NULL);
}

int     end_lem(t_data *data, t_lem *lems[data->ant_count], int i)
{
	ft_putchar('L');
	ft_putstr(ft_itoa(lems[i]->n));
	ft_putchar('-');
	ft_putstr(data->end->name);
	ft_putchar(' ');
	lems[i]->finished = 1;
	data->cur_n--;
	return (1);
}

int     make_step(t_data *data, t_lem *lems[data->ant_count], int cur_lems)
{
	int     i;
	
	i = 0;
	while (i < cur_lems)
	{
		if (lems[i]->finished == 1)
			continue ;
		lems[i]->pos = get_next_pos(lems[i]->pos, lems[i]->way);
		if (lems[i]->pos == NULL)
		{
			end_lem(data, lems, i);
			continue ;
		}
		ft_putchar('L');
		ft_putstr(ft_itoa(lems[i]->n));
		ft_putchar('-');
		ft_putstr(lems[i]->pos);
		ft_putchar(' ');
		i++;
	}
	return (1);
}

int     go_lem(t_data *data)
{
	int     cur_lems;
	t_lem   *lems[data->ant_count];
	
	cur_lems = 0;
	data->col = data->ant_count;
	data->cur_n = 0;
	cur_lems = new_lems(data, lems, cur_lems);
	while (data->cur_n > 0)
	{
		cur_lems = make_step(data, lems, cur_lems);
		cur_lems = new_lems(data, lems, cur_lems);
	}
	return (1);
}

