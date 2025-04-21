/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 14:05:36 by almeekel          #+#    #+#             */
/*   Updated: 2025/04/21 16:14:08 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int				g_signal;

static t_cmd	*clean_and_null(t_cmd *head)
{
	free_cmd_list(head);
	return (NULL);
}

t_cmd	*build_cmd_list(t_token *tk)
{
	t_cmd	*head;
	t_cmd	*cur;

	head = NULL;
	cur = NULL;
	while (tk)
	{
		if (!cur)
		{
			cur = cmd_new();
			if (!cur)
				return (clean_and_null(head));
			cmd_add_back(&head, cur);
		}
		if (tk->type == T_WORD && cmd_add_arg(cur, tk->value))
			return (clean_and_null(head));
		if (tk->type >= T_REDIR_IN && tk->type <= T_HEREDOC)
			if (parse_redir(cur, &tk))
				return (clean_and_null(head));
		if (tk->type == T_PIPE)
			cur = NULL;
		tk = tk->next;
	}
	return (head);
}
