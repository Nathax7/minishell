/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 20:15:31 by almeekel          #+#    #+#             */
/*   Updated: 2025/05/11 20:18:07 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

// Utils pour l'expaneur

// Retrouve la valeur d'une variable d'envrionnement
//l'appel doit clear la chaine retournee si c'est un dup !!!
// Pour $? ca retourne un char* representant g_exit_status.
char	*get_env_var_value(const char *var_name, char **envp,
		int last_exit_status)
{
	int		i;
	size_t	name_len;
	char	*value;

	if (ft_strcmp(var_name, "?") == 0)
		return (ft_itoa(last_exit_status));
	if (!envp)
		return (ft_strdup("")); // Pas d'envp, retourne char * vide
	name_len = ft_strlen(var_name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var_name, name_len) == 0
			&& envp[i][name_len] == '=')
		{
			value = ft_strdup(envp[i] + name_len + 1);
			return (value);
		}
		i++;
	}
	return (ft_strdup("")); // Variable nn trouvee, retourne char * vide
}

int	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}