/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secure_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:53:40 by almeekel          #+#    #+#             */
/*   Updated: 2025/06/11 16:55:46 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

// char	*secure_readline(const char *prompt)
// {
// 	char	*line_read;

// 	line_read = readline(prompt);
// 	if (line_read == NULL)
// 		return (NULL);
// 	if (g_signal_test == 130)
// 	{
// 		free(line_read);
// 		return (ft_strdup(""));
// 	}
// 	return (line_read);
// }

char	*cleanup_and_return_char(char *to_free, int to_close,
		char *to_free_optional, int option_flag)
{
	if (to_free)
		free(to_free);
	if (to_close >= 0)
		close(to_close);
	if (!option_flag && to_free_optional)
	{
		unlink(to_free_optional);
		free(to_free_optional);
		return (NULL);
	}
	return (to_free_optional);
}
