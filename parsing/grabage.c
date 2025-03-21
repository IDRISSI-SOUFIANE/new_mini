/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grabage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 23:58:28 by sidrissi          #+#    #+#             */
/*   Updated: 2025/02/27 14:14:48 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// void free_tokens(t_token *tokens)
// {
// 	t_token *tmp;

// 	while (tokens)
// 	{
// 		tmp = tokens;
// 		tokens = tokens->next;

// 		// Ensure value is freed properly
// 		if (tmp->value)
// 		{
// 			for (int i = 0; tmp->value[i]; i++)
// 				free(tmp->value[i]); // Free each string
// 			free(tmp->value);		 // Free the array itself
// 		}

// 		free(tmp); // Free the struct
// 	}
// }

// t_token *deldum(t_token **head)
// {
// 	t_token *temp;

// 	if (!head)
// 		return (NULL);
// 	temp = *head;
// 	*head = (*head)->next;
// 	free(temp->value);
// 	free(temp);
// 	temp = NULL;
// 	return (*head);
// }

void free_tokens(t_token *tokens)
{
	t_token *tmp;
	int i;

	i = 0;
	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;

		if (tmp->value)
		{
			while (tmp->value[i])
			{
				free(tmp->value[i]);
				i++;
			}
			free(tmp->value);
		}

		free(tmp); // Free the struct
	}
}

t_token *deldum(t_token **head)
{
	t_token *temp;
	int i;

	i = 0;
	if (!head || !*head)
		return (NULL);
	temp = *head;
	*head = (*head)->next;

	if (temp->value)
	{
		while (temp->value[i])
		{
			free(temp->value[i]);
			i++;
		}
		free(temp->value);
	}
	free(temp);
	return (*head);
}
