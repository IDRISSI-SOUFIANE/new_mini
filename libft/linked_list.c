/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 23:11:15 by sidrissi          #+#    #+#             */
/*   Updated: 2025/03/17 03:31:18 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token *ft_lstlast(t_token *lst)
{
	t_token *tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void ft_lstadd_back(t_token **lst, t_token *new)
{
	if (!lst || !new)
		return;
	if (*lst)
		ft_lstlast(*lst)->next = new;
	else
		*lst = new;
}

t_token *ft_lstnew(char *content, t_keyword type)
{
	t_token *new_node;

	new_node = (t_token *)malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->value = content;
	new_node->type = type;
	new_node->next = NULL;
	return (new_node);
}

/*
#include "../include/minishell.h"

void free_redir(t_redir *redir)
{
	t_redir *temp;

	while (redir)
	{
		temp = redir->next;
		free(redir->name);
		free(redir);
		redir = temp;
	}
}

void free_data(t_data *data)
{
	t_data *temp;

	while (data)
	{
		temp = data->next;
		free(data->cmd);
		if (data->args)
		{
			for (int i = 0; data->args[i]; i++)
				free(data->args[i]);
			free(data->args);
		}
		free_redir(data->file);
		free(data);
		data = temp;
	}
}
*/