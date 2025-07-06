/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 23:10:35 by amouhand          #+#    #+#             */
/*   Updated: 2024/09/05 10:48:37 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

t_parser	*init_parser(char **env)
{
	t_parser	*parser;

	parser = get_parser();
	parser->alloc = NULL;
	parser->env = set_env(env);
	if (!parser->env)
		parser->env = check_env();
	parser->prompt = set_cwd();
	parser->heredoc_abort = 0;
	parser->expand = NULL;
	parser->line = NULL;
	parser->result = NULL;
	parser->head = NULL;
	parser->cmd = NULL;
	return (parser);
}

int	read_input(t_parser *parser)
{
	parser->prompt = set_cwd();
	parser->line = readline(parser->prompt);
	if (!parser->line)
	{
		free_parser(parser);
		exit(0);
	}
	if (ft_strlen(parser->line))
	{
		add_history(parser->line);
		add_alloc(parser->line);
	}
	if (unclosed_quotes(parser->line))
	{
		print_error("Error: Unclosed Quotes\n", 0);
		return (0);
	}
	return (1);
}

int	parse_input(t_parser *parser)
{
	int	*expand_check;

	expand_check = NULL;
	parser->result = mini_parsing(parser->line, &expand_check);
	if (!parser->result)
	{
		parser_subfree(parser);
		if (expand_check)
			ft_free(expand_check);
		expand_check = NULL;
		return (0);
	}
	parser->head = tokenizer(parser->result, expand_check);
	if (!parser->head)
		return (ft_free(expand_check), 0);
	ft_free(expand_check);
	return (1);
}

int	tokenize_input(t_parser *parser)
{
	int	flag;

	parser->cmd = parse_cmd(parser->head);
	if (!parser->cmd)
		return (0);
	flag = checking_parsing(parser->head);
	if (heredoc_configuring(parser->cmd))
		return (0);
	if (flag)
		return (0);
	if (expander(parser->cmd))
		return (0);
	fd_init(parser->cmd);
	set_path(parser->cmd, parser->env);
	return (1);
}
