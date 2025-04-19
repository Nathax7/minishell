/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 19:19:44 by almeekel          #+#    #+#             */
/*   Updated: 2025/04/19 19:32:46 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

t_cmd	*ft_parsing(char *input, t_env *env)
{
	t_list *lexed;
	t_list *tokens;
	t_cmd *cmd_tree;

	if (!input || !*input)
		return (NULL);

	lexed = lexer(input);
	if (!lexed)
		return (NULL);

	tokens = tokenize(lexed);
	ft_lstclear(&lexed, free);
	if (!tokens)
		return (NULL);

	if (handle_quotes(tokens) != 0)
	{
		ft_lstclear(&tokens, free_token);
		return (NULL);
	}

	if (expand_tokens(tokens, env) != 0)
	{
		ft_lstclear(&tokens, free_token);
		return (NULL);
	}

	cmd_tree = parse(tokens);
	ft_lstclear(&tokens, free_token);
	return (cmd_tree);
}