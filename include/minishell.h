/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 21:22:56 by sidrissi          #+#    #+#             */
/*   Updated: 2025/03/17 03:35:30 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

// # include <libc.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>

#define ERROR "minishell: syntax error near unexpected token\n"
#define name_length 9

typedef enum s_keyword
{
	READ_IN,
	WRITE_OUT,
	APPEND,
	HERDOC,
	PIPE,
	PIPES,
	WORD,
	START,
	FREAD_IN,
	FWRITE_OUT,
	F_HERDOC,
	F_APPEND,
	CMD,
} t_keyword;

typedef struct s_quote_data
{
	char *line;
	int *i;
	char *buffer;
	int *buffer_index;
} t_quote_data;

typedef struct s_token
{
	char **value;
	t_keyword type;
	struct s_token *next;
} t_token;

typedef struct s_expand
{
	char *res;
	int i;
	int dollar_count;
	int var_len;
	char *var_name;
} t_expand;
/*              *********************************************        */

typedef struct s_redir
{
	char *name;
	t_keyword type;
	struct s_redir *next;
} t_redir;

typedef struct s_data
{
	char *cmd; // ALSO DOUBLE POINTER WHEN EXPAND $VAR="ONE TWO ..."
	char **args;
	t_redir *file;
	struct s_data *next;
} t_data;

// Function prototypes
t_data *parsing(t_token **tokens);
char *ft_strjoin_free(char *s1, char *s2);

/*********************Parsing**********************/

/*main.c*/
int check_quotes(char *line, int i, int count_quote);
int lexing(char *line);

/*---------------tokenization---------------*/
int sp(char c);
void handle_quotes(t_quote_data *data);
void handle_special_chars(char *line, int *i, t_token **head);
void handle_words(char *line, int *i, char *buffer, int *buffer_index);
t_token *tokenization(char *line, int i);

/*---------------garbage---------------*/
// Linked list:
void free_tokens(t_token *tokens);
t_token *deldum(t_token **head);

/*---------------error---------------*/
int error1(t_token *tokens);

/*---------------expand---------------*/
void ft_expand(t_token *tokens);

/*---------------ft_rename------------*/
void ft_rename(t_token *tokens);

/*-------------ft_herdoc--------------*/

void ft_herdoc(t_token *tokens);

/*===============libft===============*/
char *ft_substr(char *s, int start, int len);
void ft_putstr_fd(char *s, int fd);
int ft_strlen(char *s);
char *ft_strdup(char *s);
int ft_isprint(int c);
int ft_cmp(char *word);
char *ft_strjoin(char *s1, char *s2);
// Linked list:
t_token *ft_lstlast(t_token *lst);
t_token *ft_lstnew(char *content, t_keyword type);
void ft_lstadd_back(t_token **lst, t_token *new);

int ft_isalnum(int c);
int ft_isalpha(int c);
int ft_isdigit(int c);
void *ft_memset(void *b, int c, size_t len);
int ft_strcmp(char *s1, char *s2);

/***************ft_split************* */

void *ft_free(char **strs, int count);
char **ft_split(char *s, char c);

/* just remove them cause we don't use them*/
// int		ft_strncmp(char *s1, char *s2, int n);/*not use it check before remove it */
// char	*ft_strndup(char *s, size_t n);/*not use it check before remove it */
// char	*ft_allocate(char **res, int len);/*not use it check before remove it */
// char	*ft_strcat(char *dest, char *src);/*not use it check before remove it */
// char	*ft_strncpy(char *dest, char *src, int n);/*not use it check before remove it */

#endif