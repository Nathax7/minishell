/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_secure.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:53:40 by almeekel          #+#    #+#             */
/*   Updated: 2025/05/23 17:02:51 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/parsing.h"

char	*secure_readline(const char *prompt)
{
	char *line_read;

	line_read = readline(prompt);
	if (line_read == NULL)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		return (NULL);
	}
	if (line_read && *line_read)
	{
		add_history(line_read);
	}
	return (line_read);
}