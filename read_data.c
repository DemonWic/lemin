#include "lem_in.h"

static char	*read_line(void)
{
	char	*line;
	
	line = NULL;
	get_next_line(0, &line);
	return (line);
}

int         count(char **a)
{
	int i;

	i = 0;
	while (a[i] != NULL)
		i++;
	return (i);
}

static int   add_room(t_rlist *rooms, char *line, int marker)
{
	t_room  *new;
	char    **words;
	int     i;
	t_rlist *tmp;
	t_rlist *new_elem;
	
	words = ft_strsplit(line, ' ');
	i = 0;
	if (count(words) != 3)
		return (0);
	while (words[1][i] != 0)
		if (!ft_isdigit(words[1][i++]))
			return (0);
	i = 0;
	while (words[2][i] != 0)
		if (!ft_isdigit(words[2][i++]))
			return (0);
	new = (t_room*)malloc(sizeof(t_room));
	new->name = words[0];
	new->marker = marker;
	new->x = ft_atoi(words[1]);
	new->y = ft_atoi(words[2]);
	new_elem = (t_rlist*)malloc(sizeof(t_rlist));
	new_elem->room = new;
	new_elem->next = NULL;
	if (!rooms)
	{
		rooms = new_elem;
		return (1);
	}
	tmp = rooms;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_elem;
	return (1);
}

static int   add_link(t_llist *links, char *line)
{
	t_link  *new;
	char    **words;
	t_llist *tmp;
	t_llist *new_elem;
	
	words = ft_strsplit(line, '-');
	if (count(words) != 2)
		return (0);
	new = (t_link*)malloc(sizeof(t_link));
	new->s1 = words[0];
	new->s2 = words[1];
	new_elem = (t_llist*)malloc(sizeof(t_llist));
	new_elem->link = new;
	new_elem->next = NULL;
	if (!links)
	{
		links = new_elem;
		return (1);
	}
	tmp = links;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_elem;
	return (1);
}

int		    read_data(t_data *data)
{
	int		status;
	char	*line;
	int     marker;
	
	status = 1;
	data = (t_data*)malloc(sizeof(t_data));
	data->links = NULL;
	data->rooms = NULL;
	data->start = NULL;
	data->end = NULL;
	data->nodes = NULL;
	data->ways = NULL;
	data->cur_n = 1;
	marker = 0;
	while (status)
	{
		line = read_line();
		if (!line)
			return (0);
		if (status == 1)
		{
			data->col = ft_atoi(line);
			status++;
			continue ;
		}
		if (status == 2)
		{
			if (line[0] == '#')
			{
				if (ft_strcmp(line, "##start") == 0)
					marker = 1;
				if (ft_strcmp(line, "##end") == 0)
					marker = 2;
				continue ;
			}
			if (!add_room(data->rooms, line, marker))
				status++;
			marker = 0;
		}
		if (status == 3)
		{
			if (line[0] == '#')
				continue ;
			if (!add_link(data->links, line))
				return (-1);
		}
		free(line);
	}
	return (status);
}

