/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 14:54:42 by almeekel          #+#    #+#             */
/*   Updated: 2025/04/20 16:07:29 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

//partie parsing du main//
t_cmd	*ft_parsing(char *input, char **envp, int last_exit)
{
	t_token	*tokens;
	t_cmd	*cmd_tree;

	if (!input || !*input)
		return (NULL);
	/* 1 / tokenisation */
	tokens = tokenize(input);
	if (!tokens)
		return (NULL);
	/* 2 / quote stripping + variable expansion --------------------------- */
	process_quotes(tokens);
	expand_variables(tokens, envp, last_exit);
	/* 3 / construire l'AST */
	cmd_tree = build_cmd_list(tokens);
	// free_token(tokens, -1, NULL, NULL);
	return (cmd_tree);
}
