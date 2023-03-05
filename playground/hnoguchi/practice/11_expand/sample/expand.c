/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 17:04:13 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/02/26 16:35:17 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static void	remove_quote(char **new_word, char **rest, char *current_word)
{
	char	quote;

	quote = *current_word;
	current_word++;
	while (*current_word != quote)
	{
		if (*current_word == '\0')
		{
			fatal_error("Unclosed quote");
		}
		add_character(new_word, *current_word);
		current_word++;
	}
	*rest = current_word;
}

static void	remove_double_quote(char **new_word, int last_status, char **rest, char *current_word)
{
	char	quote;

	quote = *current_word;
	current_word++;
	while (*current_word != quote)
	{
		if (*current_word == '\0')
		{
			fatal_error("Unclosed quote");
		}
		else if (is_variable(current_word))
		{
			append_variable_str(new_word, &current_word, current_word);
			// continue ;
		}
		else if (is_special_parameter(current_word))
		{
			append_special_param(new_word, last_status, &current_word, current_word);
			// continue ;
		}
		else
		{
			add_character(new_word, *current_word);
			current_word++;
		}
	}
	*rest = current_word;
}

static void	try_remove_quote(t_token *token)
{
	char	*new_word;
	char	*current_word;

	new_word = NULL;
	current_word = NULL;
	while (token != NULL)
	{
		dprintf(STDOUT_FILENO, "=============================\n");
		dprintf(STDOUT_FILENO, "[BEFORE] : [%s]\n", token->word);
		if (token->kind != TK_WORD)
		{
			token = token->next;
			continue ;
		}
		current_word = token->word;
		while (*current_word != '\0')
		{
			if (*current_word == SINGLE_QUOTE_CHAR)
			{
				remove_quote(&new_word, &current_word, current_word);
			}
			else if (*current_word == DOUBLE_QUOTE_CHAR)
			{
				remove_double_quote(&new_word, token->last_status, &current_word, current_word);
			}
			else if (is_variable(current_word))
			{
				append_variable_str(&new_word, &current_word, current_word);
				continue ;
			}
			else if (is_special_parameter(current_word))
			{
				append_special_param(&new_word, token->last_status, &current_word, current_word);
				continue ;
			}
			else
			{
				add_character(&new_word, *current_word);
			}
			current_word++;
		}
		free(token->word);
		current_word = NULL;
		token->word = new_word;
		new_word = NULL;
		dprintf(STDOUT_FILENO, "[AFTER]  : [%s]\n", token->word);
		dprintf(STDOUT_FILENO, "=============================\n\n");
		token = token->next;
	}
}

void	create_token_list(t_token **token, t_token_kind kind, char **test_set, int status)
{
	if (*test_set == NULL)
	{
		return ;
	}
	*token = malloc(sizeof(t_token));
	if (token == NULL)
	{
		fatal_error("malloc");
	}
	(*token)->kind = kind;
	(*token)->word = strdup(*test_set);
	if ((*token)->word == NULL)
	{
		fatal_error("malloc");
	}
	(*token)->last_status = status;
	(*token)->next = NULL;
	test_set++;
	status += 37;
	create_token_list(&(*token)->next, TK_WORD, test_set, status);
}

void	print_token(t_token **token)
{
	if (*token == NULL)
	{
		return ;
	}
	dprintf(STDOUT_FILENO, "token->word : [%s]\n", (*token)->word);
	print_token(&(*token)->next);
}

void	frees_token(t_token **token)
{
	if (*token == NULL)
	{
		return ;
	}
	free((*token)->word);
	frees_token(&(*token)->next);
	free(*token);
}

int	main(int argc, char **argv)
{
	t_token	*token = NULL;
	char	*test_normal[] = {
		"$?",
		"hello$?",
		"hello $?",
		"$?hello",
		"hello$?world",
		"$?$?$?",
		"$? $? $?",
		"$?   $?     $?",
		NULL,
	};

	char	*test_single[] = {
		"'$?'",
		"'hello$?'",
		"'hello $?'",
		"'$?hello'",
		"'hello$?world'",
		"'$?$?$?'",
		"'$? $? $?'",
		"'$?   $?     $?'",
		NULL,
	};

	char	*test_double[] = {
		"\"$?\"",
		"\"hello$?\"",
		"\"hello $?\"",
		"\"$?hello\"",
		"\"hello$?world\"",
		"\"$?$?$?\"",
		"\"$? $? $?\"",
		"\"$?   $?     $?\"",
		NULL,
	};

	if (argc != 2)
	{
		fatal_error("Argument : normal or single or double.");
	}
	if (strcmp(argv[1], "normal") == 0)
	{
		create_token_list(&token, TK_WORD, test_normal, 0);
	}
	else if (strcmp(argv[1], "single") == 0)
	{
		create_token_list(&token, TK_WORD, test_single, 0);
	}
	else if (strcmp(argv[1], "double") == 0)
	{
		create_token_list(&token, TK_WORD, test_double, 0);
	}
	else
	{
		fatal_error("Argument : normal or single or double.");
	}
	try_remove_quote(token);
	// print_token(&token);
	frees_token(&token);
	// system("leaks -q expand");
}
