/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteemo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 18:26:11 by student           #+#    #+#             */
/*   Updated: 2020/08/11 18:26:14 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		main(int argc, char **argv)
{
	t_data  *data;
	
	data = NULL;
	read_data(data);
	make_graf(data);
	find_ways(data);
	go_lem(data);
	return (0);
}
