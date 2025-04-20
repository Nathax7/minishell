/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:07:25 by almeekel          #+#    #+#             */
/*   Updated: 2025/04/20 14:43:00 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

static char	*get_env_val(const char *name, char **env)
{
	size_t	n;

	n = ft_strlen(name);
	for (int i = 0; env[i]; i++)
		if (!ft_strncmp(env[i], name, n) && env[i][n] == '=')
			return (env[i] + n + 1);
	return (NULL);
}

static char	*expand_one(const char *src, char **env, int last_exit)
{
	char	*dst;
	size_t	i;
	size_t	start;
	char	*name;
	char	*val;

	dst = ft_calloc(1, 1);
	i = 0,
	start = 0;
	while (src[i])
	{
		if (src[i] == '$' && src[i + 1]) /* si expand   */
		{
			if (src[i + 1] == '?') /* $?>  */
			{
				dst = ft_strjoin_free(dst, ft_itoa(last_exit));
				i += 2;
			}
			else if (ft_isalpha(src[i + 1]) || src[i + 1] == '_') /* $VAR      */
			{
				start = ++i;
				while (src[i] && (ft_isalnum(src[i]) || src[i] == '_'))
					i++;
				name = ft_substr(src, start, i - start);
				val = get_env_val(name, env);
				if (val)
					dst = ft_strjoin_free(dst, val);
				free(name);
			}
			else /* just "$x"   */
				dst = ft_strjoin_free_c(dst, src[i++]);
		}
		else /* normal char */
			dst = ft_strjoin_free_c(dst, src[i++]);
	}
	return (dst);
}

void	expand_variables(t_token *token, char **env, int last_exit)
{
	char	*e;

	while (token)
	{
		if (token->type == T_WORD && token->quote != Q_SINGLE
			&& ft_strchr(token->value, '$'))
		{
			e = expand_one(token->value, env, last_exit);
			free(token->value);
			token->value = e;
		}
		token = token->next;
	}
}
