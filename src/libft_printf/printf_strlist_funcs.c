/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_strlist_funcs.c                              :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: avaliull <avaliull@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:56:29 by avaliull          #+#    #+#             */
/*   Updated: 2024/11/08 13:47:49 by avaliull       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

// The following functions manage: 
//	- creation of new strings from format string;
//	- adding formatted (created) strings to the list of all strings;
//	- printing and clearing the list on error or success

static void	clr_lst(t_plst **out_lst)
{
	t_plst	*next_node;

	while (*out_lst != NULL)
	{
		next_node = (*out_lst)->next;
		free((*out_lst)->string);
		free(*out_lst);
		*out_lst = next_node;
	}
}

int	final_gigastring_out(t_plst **out_lst, int err_ovrr)
{
	t_plst	*current_node;
	int		total_len;

	total_len = 0;
	current_node = *out_lst;
	while (current_node != NULL)
	{
		if (write(1, current_node->string, current_node->size) == -1)
		{
			err_ovrr = -1;
			break ;
		}
		total_len += current_node->size;
		current_node = current_node->next;
	}
	clr_lst(out_lst);
	if (err_ovrr == -1)
		return (-1);
	return (total_len);
}

static t_plst	*create_out_node(char *str_start, int len)
{
	t_plst	*new_node;

	new_node = (t_plst *) malloc(sizeof(t_plst));
	if (!new_node)
		return (NULL);
	new_node->string = str_start;
	new_node->size = len;
	new_node->next = NULL;
	return (new_node);
}

t_plst	*add_str_to_list(char *str_start, t_plst **out_lst, int len)
{
	t_plst	*next_node;
	t_plst	*last_node;

	if (!str_start)
		return (NULL);
	next_node = create_out_node(str_start, len);
	if (!next_node)
		return (NULL);
	if (!*out_lst)
	{
		*out_lst = next_node;
		return (*out_lst);
	}
	last_node = *out_lst;
	while (last_node->next != NULL)
		last_node = last_node->next;
	last_node->next = next_node;
	return (*out_lst);
}

char	*new_str(char *format, int spec_len, char *start, t_plst **out_lst)
{
	char	*new_str;

	new_str = malloc((format - start + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	new_str [format - start] = '\0';
	ft_memcpy(new_str, start, format - start);
	if (!add_str_to_list(new_str, out_lst, format - start))
		return (NULL);
	return (format + spec_len);
}
