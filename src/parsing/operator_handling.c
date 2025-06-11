/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_handling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:44:30 by almeekel          #+#    #+#             */
/*   Updated: 2025/06/04 18:21:16 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

int	handle_pipe_operator(const char **line, t_token **head)
{
	char	*op_val;

	op_val = ft_strdup("|");
	if (!op_val)
		return (0);
	(*line)++;
	return (create_and_append_token(head, op_val, T_PIPE, Q_NONE));
}

int	handle_lesser_operator(const char **line, t_token **head)
{
	char			*op_val;
	t_token_type	type;

	if (*(*line + 1) == '<')
	{
		op_val = ft_strdup("<<");
		type = T_HEREDOC;
		*line += 2;
	}
	else
	{
		op_val = ft_strdup("<");
		type = T_REDIRECT_IN;
		(*line)++;
	}
	if (!op_val)
		return (0);
	return (create_and_append_token(head, op_val, type, Q_NONE));
}

int	handle_greater_operator(const char **line, t_token **head)
{
	char			*op_val;
	t_token_type	type;

	if (*(*line + 1) == '>')
	{
		op_val = ft_strdup(">>");
		type = T_APPEND;
		*line += 2;
	}
	else
	{
		op_val = ft_strdup(">");
		type = T_REDIRECT_OUT;
		(*line)++;
	}
	if (!op_val)
		return (0);
	return (create_and_append_token(head, op_val, type, Q_NONE));
}
