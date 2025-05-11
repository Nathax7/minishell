/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:08:05 by almeekel          #+#    #+#             */
/*   Updated: 2025/05/11 19:41:41 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

// Expand les variables dans un seul string.
// Retourne une nvl string expansee, l'appel doit free ensuite.
// La string originale n est pas modifiee.
static char	*process_variable_expansion(const char **str_ptr, char **envp,
		int last_exit_status)
{
	const char		*start;
	char			*var_name;
	char			*var_value;
	t_str_builder	var_name_sb;

	(*str_ptr)++; // Skip le symbole '$'
	if (**str_ptr == '?')
	{
		(*str_ptr)++; // Skip le symbole '?'
		return (get_env_var_value("?", envp, last_exit_status));
	}
	if (**str_ptr == '{') // Support basique de la VAR (a ameliorer)
	{
		(*str_ptr)++; // Ski '{'
		start = *str_ptr;
		while (**str_ptr && **str_ptr != '}')
			(*str_ptr)++;
		if (**str_ptr == '}') // quand trouve le close
		{
			var_name = ft_substr(start, 0, *str_ptr - start);
			(*str_ptr)++; // Skip '}'
		}
		else
			return (ft_strdup("$")); // Or handle error
	}
	else // $VAR basique
	{
		sb_init(&var_name_sb);
		while (is_valid_var_char(**str_ptr))
		{
			sb_append_char(&var_name_sb, **str_ptr);
			(*str_ptr)++;
		}
		var_name = sb_to_string(&var_name_sb);
		sb_free(&var_name_sb);
	}
	if (!var_name)
		return (ft_strdup("$")); // Ne doit pas arriver !!
	var_value = get_env_var_value(var_name, envp, last_exit_status);
	free(var_name);
	return (var_value);
}
// input str c'est le char * original qui contient des var a expand
// on oublie pas de passer le last_exit_status qui contient lexit de la derniere
// commande executee ! 
char	*expand_variables_in_str(const char *input_str, t_quote quote_type,
		char **envp, int last_exit_status)
{
	t_str_builder	sb;
	const char		*ip;
	char			*expanded_part;

	if (!input_str)
		return (NULL); // logik si ya pas de string on return null
	sb_init(&sb);
	ip = input_str; // iterateur
	while (*ip)
	{
		if (*ip == '$' && quote_type != Q_SINGLE && (is_valid_var_char(*(ip + 1))
				|| *(ip + 1) == '?' || *(ip + 1) == '{')) // verifie si ya une var dans le cas ou p est $ et si c un cas valide
		{
			expanded_part = process_variable_expansion(&ip, envp,
					last_exit_status);
			if (expanded_part)
			{
				sb_append_str(&sb, expanded_part);
				free(expanded_part);
			}
		}
		else
		{
			sb_append_char(&sb, *ip);
			ip++;
		}
	}
	return (sb_to_string(&sb));
}
