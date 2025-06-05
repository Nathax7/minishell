/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:38:13 by nagaudey          #+#    #+#             */
/*   Updated: 2025/06/05 17:04:11 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

static void	unset_one(char *to_unset, char **envl)
{
	int i;

	while (envl)
	{
		if (variable_match(envl, to_unset, 0))
		{
			previous->next = envl->next;
			free_entry(envl->content);
			free(envl);
			return ;
		}
		previous = envl;
		envl = envl->next;
	}
}

int			ft_unset(t_info *cmd, t_list **envl)
{
	int		i;
	int		ret;

	if (cmd->number <= 1)
		return (0);
	i = cmd->offset + 1;
	ret = SUCCESS;
	while (cmd->argv[i])
	{
		if (authorized_char(cmd->argv[i]) && !ft_strchr(cmd->argv[i], '='))
			unset_one(cmd->argv[i], *envl);
		else
		{
			invalid_identifier(cmd->argv[i], "unset", 1);
			ret = ERROR;
		}
		i++;
	}
	return (ret);
}