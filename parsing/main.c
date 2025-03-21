/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 11:15:46 by sidrissi          #+#    #+#             */
/*   Updated: 2025/03/17 03:41:09 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* */
int check_quotes(char *line, int i, int count_quote)
{
	char quote;

	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			quote = line[i];
			count_quote++;
			i++;
			while (line[i] && line[i] != quote)
				i++;
			if (line[i] == quote)
				count_quote++;
			else
				break;
			i++;
		}
		else
			i++;
	}
	if (count_quote % 2)
		return (1);
	return (0);
}

/* */
int lexing(char *line)
{
	int i;
	int count_quote;
	t_token *tokens;
	t_data *data;

	i = 0;
	count_quote = 0;
	if (check_quotes(line, i, count_quote))
		return (ft_putstr_fd("missing quotation\n", 2), 1);

	tokens = tokenization(line, i);
	if (tokens == NULL)
		return (0);

	ft_rename(tokens);
	ft_expand(tokens);
	ft_herdoc(tokens);

	data = parsing(&tokens);

	// PRINT
	// t_data *tmp = data;
	// while (tmp)
	// {

	// 	printf("Command: %s\n", tmp->cmd ? tmp->cmd : "(no command)");

	// 	// Print arguments
	// 	printf("Arguments:");
	// 	if (tmp->args)
	// 	{
	// 		for (int i = 0; tmp->args[i]; i++)
	// 			printf(" %s", tmp->args[i]);
	// 	}
	// 	printf("\n");
	// 	if (tmp->file)
	// 	{
	// 		while (tmp->file)
	// 		{
	// 			printf("[fname: %s | ftype: %d]\n", tmp->file->name, tmp->file->type);
	// 			tmp->file = tmp->file->next;
	// 		}
	// 	}

	// 	printf("\n");
	// 	tmp = tmp->next;
	// }

	// Free the entire t_data list and its contents
	t_data *current_data = data;
	while (current_data)
	{
		t_data *next_data = current_data->next;

		// Free command string
		free(current_data->cmd);
		current_data->cmd = NULL;

		// Free arguments array
		if (current_data->args)
		{
			for (int i = 0; current_data->args[i]; i++)
			{
				free(current_data->args[i]);
				current_data->args[i] = NULL;
			}
			free(current_data->args);
			current_data->args = NULL;
		}

		// Free redirections linked list
		t_redir *current_redir = current_data->file;
		while (current_redir)
		{
			t_redir *next_redir = current_redir->next;
			free(current_redir->name);
			free(current_redir);
			current_redir = next_redir;
		}
		current_data->file = NULL;

		// Free the current t_data node
		free(current_data);
		current_data = next_data;
	}

	free_tokens(tokens);
	return (0);
}

/*
int lexing(char *line)
{
	int i;
	int count_quote;
	t_token *tokens;

	i = 0;
	count_quote = 0;
	if (check_quotes(line, i, count_quote))
		return (ft_putstr_fd("missing quotation\n", 2), 1);

	tokens = tokenization(line, i);
	if (tokens == NULL)
		return (0);

	t_token *temp = tokens;

	while (temp)
	{
		if (temp->value)
		{
			i = 0;
			while (temp->value[i])
			{
				printf("[value : %s -:- type : %d]\n", temp->value[i], temp->type);
				i++;
			}
		}
		temp = temp->next;
	}
	free_tokens(tokens);
	return (0);
}

*/

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;

	char *line;
	while (1)
	{
		line = readline("Minishell: ");
		if (line == NULL)
		{
			// free(line);
			break;
		}
		lexing(line);
		if (line[0] != '\0')
			add_history(line);
		free(line);
	}
	return (0);
}

/*
should call ft_herdoc after parsing to open the file herdoc and change the name from limter to name of file herdoc
*/