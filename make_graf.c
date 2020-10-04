#include "lem_in.h"

t_node  *make_node(t_room *room, t_data *data)
{
	t_node  *ret;
	
	ret = (t_node*)malloc(sizeof(t_node));
	ret->room = room;
	ret->rel = NULL;
	if (room->marker == 1)
	{
		if (!data->start)
			data->start = ret;
		else
			return (NULL);
	}
	if (room->marker == 2)
	{
		if (!data->end)
			data->end = ret;
		else
			return (NULL);
	}
	return (ret);
}

int     make_links(t_node *node, t_llist *links)
{
	int     i;
	t_llist *cur;
	
	i = 0;
	cur = links;
	node->rel = (char**)malloc(sizeof(char*) * 100);
	while (cur)
	{
		if (ft_strcmp(cur->link->s1,node->room->name) == 0)
			node->rel[i++] = cur->link->s2;
		if (ft_strcmp(cur->link->s2,node->room->name) == 0)
			node->rel[i++] = cur->link->s1;
		cur = cur->next;
	}
	node->rel[i] = NULL;
	return (1);
}

int     make_graf(t_data *data)
{
	t_nlist *nodes;
	t_nlist *start;
	
	nodes = (t_nlist*)malloc(sizeof(t_nlist));
	if (!(nodes->node = make_node(data->rooms->room, data)))
		return (0);
	nodes->next = NULL;
	start = nodes;
	data->rooms = data->rooms->next;
	while (data->rooms)
	{
		nodes->next = (t_nlist*)malloc(sizeof(t_nlist));
		if (!(nodes->next->node = make_node(data->rooms->room, data)))
			return (0);
		nodes = nodes->next;
		if (!make_links(nodes->node, data->links))
			return (0);
		data->rooms = data->rooms->next;
		nodes->next = NULL;
	}
	data->nodes = start;
	return (1);
}

