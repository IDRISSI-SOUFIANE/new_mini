/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 22:43:23 by sidrissi          #+#    #+#             */
/*   Updated: 2025/03/17 03:30:10 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_data *ft_lstnew_p(void)
{
	t_data *new_node = malloc(sizeof(t_data));
	if (!new_node)
		return (NULL);
	new_node->cmd = NULL;
	new_node->args = NULL;
	new_node->file = NULL;
	new_node->next = NULL;
	return (new_node);
}

void add_redirection(t_data *current, t_token *token)
{
	t_redir *new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return;
	new_redir->name = ft_strdup(token->value[0]);
	new_redir->type = token->type;
	new_redir->next = NULL;

	if (!current->file)
		current->file = new_redir;
	else
	{
		t_redir *last = current->file;
		while (last->next)
			last = last->next;
		last->next = new_redir;
	}
}

void add_argument(t_data *current, char *arg)
{
	int count;
	int i;
	char **new_args;

	count = 0;
	i = 0;
	if (current->args)
		while (current->args[count])
			count++;
	new_args = malloc((count + 2) * sizeof(char *));
	if (!new_args)
		return;
	while (i < count)
	{
		new_args[i] = current->args[i];
		i++;
	}
	new_args[count] = ft_strdup(arg);
	new_args[count + 1] = NULL;
	free(current->args);
	current->args = new_args;
}

t_data *parsing(t_token **tokens)
{
	t_token *temp;
	t_data *lst;
	t_data *current;

	temp = *tokens;
	lst = ft_lstnew_p();
	current = lst;
	while (temp)
	{
		if (temp->type == PIPE)
		{
			current->next = ft_lstnew_p();
			current = current->next;
		}
		else if (temp->type == CMD)
			current->cmd = ft_strdup(temp->value[0]); // current->cmd = temp->value
		else if (temp->type == WORD)
			add_argument(current, temp->value[0]); // current->args = temp->value
		else if (temp->type >= FREAD_IN && temp->type <= F_APPEND)
			add_redirection(current, temp);
		temp = temp->next;
	}
	return (lst);
}
