/*#include "../include/minishell.h"

static void append_char(t_expand *ex, char c)
{
	char *new_res;
	char tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	new_res = ft_strjoin(ex->res, tmp);
	free(ex->res);
	ex->res = new_res;
}

static void handle_even_dollars(t_expand *ex)
{
	int num;
	char *dollars;
	char *new_res;

	num = ex->dollar_count / 2;
	dollars = malloc(num + 1);
	if (!dollars)
		return;
	ft_memset(dollars, '$', num);
	dollars[num] = '\0';
	new_res = ft_strjoin(ex->res, dollars);
	free(ex->res);
	free(dollars);
	ex->res = new_res;
}

static void extract_var(t_expand *ex, char *str)
{
	int start;

	ex->var_len = 0;
	start = ex->i;
	while (ft_isalnum(str[ex->i]) || str[ex->i] == '_') // || ?
	{
		ex->i++;
		ex->var_len++;
	}
	ex->var_name = ft_substr(str, start, ex->var_len);
}

static void handle_odd_dollars(t_expand *ex, char *str)
{
	char *val;
	char *new_res;

	if (ft_isalnum(str[ex->i]) || str[ex->i] == '_') // || ?
	{
		extract_var(ex, str);
		val = getenv(ex->var_name); // if I remove the export should check if THERE is NO EXPORT TO PREVENT THE SEGV
		if (!val)
			val = "";
		new_res = ft_strjoin(ex->res, val);
		free(ex->res);
		free(ex->var_name);
		ex->res = new_res;
	}
}

static void process_dollar(t_expand *ex, char *str)
{
	ex->dollar_count = 0;
	while (str[ex->i] == '$')
	{
		ex->dollar_count++;
		ex->i++;
	}
	if (ex->dollar_count % 2)
		handle_odd_dollars(ex, str);
	else
		handle_even_dollars(ex);
}

static void handle_single_quote(t_expand *ex, char *str)
{
	ex->i++;
	while (str[ex->i] && str[ex->i] != '\'')
	{
		append_char(ex, str[ex->i]);
		ex->i++;
	}
	if (str[ex->i] == '\'')
		ex->i++;
}

static void handle_double_quote(t_expand *ex, char *str)
{
	ex->i++;
	while (str[ex->i] && str[ex->i] != '"')
	{
		if (str[ex->i] == '$')
		{
			process_dollar(ex, str);
		}
		else
		{
			append_char(ex, str[ex->i]);
			ex->i++;
		}
	}
	if (str[ex->i] == '"')
		ex->i++;
}

static char *expand_string(char *str, int *flag) // expand_string(char *str, int *flag)
{
	t_expand ex;

	ft_memset(&ex, 0, sizeof(ex));
	ex.res = ft_strdup("");
	if (!ex.res)
		return (NULL);
	while (str[ex.i])
	{
		if (str[ex.i] == '\'')
			handle_single_quote(&ex, str);
		else if (str[ex.i] == '"')
		{
			handle_double_quote(&ex, str); // flag = 2
			*flag = 2;					   // return (ft_split(ex.res, ' ')); //
		}
		else if (str[ex.i] == '$')
			process_dollar(&ex, str); // check?
		else
		{
			append_char(&ex, str[ex.i]); // check?
			ex.i++;
		}
	}
	return (ex.res);
}

void ft_expand(t_token *tokens)
{
	// t_token *temp;
	char *expanded;
	int flag;

	flag = 0;

	// temp = tokens;
	while (tokens)
	{
		if (tokens->type != F_HERDOC)
		{
			expanded = expand_string(tokens->value[0], &flag); //  expand_string(tokens->value, &falg);
			free(tokens->value);
			tokens->value[0] = expanded;
		}
		tokens = tokens->next;
	}
	// tokens = temp;
	// remove_null(tokens);
}
*/

#include "../include/minishell.h"

static void append_char(t_expand *ex, char c)
{
	char *new_res;
	char tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	new_res = ft_strjoin(ex->res, tmp);
	free(ex->res);
	ex->res = new_res;
}

static void handle_even_dollars(t_expand *ex)
{
	int num;
	char *dollars;
	char *new_res;

	num = ex->dollar_count / 2;
	dollars = malloc(num + 1);
	if (!dollars)
		return;
	ft_memset(dollars, '$', num);
	dollars[num] = '\0';
	new_res = ft_strjoin(ex->res, dollars);
	free(ex->res);
	free(dollars);
	ex->res = new_res;
}

static void extract_var(t_expand *ex, char *str)
{
	int start;

	ex->var_len = 0;
	start = ex->i;
	while (ft_isalnum(str[ex->i]) || str[ex->i] == '_') // || ?
	{
		ex->i++;
		ex->var_len++;
	}
	ex->var_name = ft_substr(str, start, ex->var_len);
}

static void handle_odd_dollars(t_expand *ex, char *str)
{
	char *val;
	char *new_res;

	if (ft_isalnum(str[ex->i]) || str[ex->i] == '_') // || ?
	{
		extract_var(ex, str);
		val = getenv(ex->var_name); // if I remove the export should check if THERE is NO EXPORT TO PREVENT THE SEGV
		if (!val)
			val = "";
		new_res = ft_strjoin(ex->res, val);
		free(ex->res);
		free(ex->var_name);
		ex->res = new_res;
	}
}

static void process_dollar(t_expand *ex, char *str)
{
	ex->dollar_count = 0;
	while (str[ex->i] == '$')
	{
		ex->dollar_count++;
		ex->i++;
	}
	if (ex->dollar_count % 2)
		handle_odd_dollars(ex, str);
	else
		handle_even_dollars(ex);
}

static void handle_single_quote(t_expand *ex, char *str)
{
	ex->i++;
	while (str[ex->i] && str[ex->i] != '\'')
	{
		append_char(ex, str[ex->i]);
		ex->i++;
	}
	if (str[ex->i] == '\'')
		ex->i++;
}

static void handle_double_quote(t_expand *ex, char *str)
{
	ex->i++;
	while (str[ex->i] && str[ex->i] != '"')
	{
		if (str[ex->i] == '$')
		{
			process_dollar(ex, str);
		}
		else
		{
			append_char(ex, str[ex->i]);
			ex->i++;
		}
	}
	if (str[ex->i] == '"')
		ex->i++;
}

static char **split(t_expand *ex, int *flag)
{
	char **result;

	if (*flag == 2)
	{
		result = ft_split(ex->res, ' ');
		free(ex->res);
	}
	else
	{
		result = malloc(2 * sizeof(char *));
		if (!result)
		{
			free(ex->res);
			return (NULL);
		}
		result[0] = ex->res;
		result[1] = NULL;
	}
	return (result);
}

static char **expand_string(char *str, int *flag)
{
	t_expand ex;

	ft_memset(&ex, 0, sizeof(ex));
	ex.res = ft_strdup("");
	if (!ex.res)
		return NULL;
	while (str[ex.i])
	{
		if (str[ex.i] == '\'')
			handle_single_quote(&ex, str);
		else if (str[ex.i] == '"')
		{
			handle_double_quote(&ex, str);
			*flag = 0;
		}
		else if (str[ex.i] == '$')
			process_dollar(&ex, str);
		else
		{
			append_char(&ex, str[ex.i]);
			ex.i++;
		}
	}
	return (split(&ex, flag));
}

/*
void ft_expand(t_token *tokens)
{
	int flag;
	char **expanded;

	while (tokens)
	{
		if (tokens->type != F_HERDOC && tokens->value && tokens->value[0])
		{
			flag = 2;
			expanded = expand_string(tokens->value[0], &flag);

			// Free old values
			if (tokens->value)
			{
				free(tokens->value[0]); // Free the original string
				free(tokens->value);	// Free the array container
			}
			tokens->value = expanded;
		}
		tokens = tokens->next;
	}
}
*/

void ft_expand(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type != F_HERDOC && tokens->value && tokens->value[0])
		{
			int flag = 0;
			char **expanded = expand_string(tokens->value[0], &flag);

			// Free old values
			if (tokens->value)
			{
				for (int i = 0; tokens->value[i]; i++)
					free(tokens->value[i]); // Free each string
				free(tokens->value);		// Free the array
			}

			// Assign new expanded values
			tokens->value = expanded;
		}
		tokens = tokens->next;
	}
}

// void    remove_null(t_token *tokens)
// {
// 	t_token *temp;
// 	t_token *prev;
// 	t_token *next;

// 	temp = tokens;
// 	while (temp)
// 	{
// 		if (!temp->value)
// 		{
// 			next = temp->next;
// 			free(temp->value);
// 			free(temp);
// 		}
// 		prev = temp;
// 		temp = temp->next;
// 	}
// }

/*
should ask ossama or talha about the test of echo
when we have a empty string
*/

/*suprime the token
: $gkjgkj $lkflflk
*/