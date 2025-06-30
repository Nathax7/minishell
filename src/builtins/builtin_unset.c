/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:55:14 by almeekel          #+#    #+#             */
/*   Updated: 2025/06/27 15:59:01 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

static int	remove_env_var(char ***env_ptr, char *name)
{
	char	**new_env;
	int		index;
	int		count;
	int		i;
	int		j;

	index = find_env_index(*env_ptr, name);
	if (index == -1)
		return (0);
	count = count_env_vars(*env_ptr);
	new_env = malloc(sizeof(char *) * count);
	if (!new_env)
		return (1);
	i = 0;
	j = 0;
	while (i < count)
	{
		if (i != index)
		{
			new_env[j] = (*env_ptr)[i];
			j++;
		}
		else
			free((*env_ptr)[i]);
		i++;
	}
	new_env[j] = NULL;
	free(*env_ptr);
	*env_ptr = new_env;
	return (0);
}

int	builtin_unset(t_args *args, char ***env_ptr)
{
    int		exit_status;
    t_args	*current;

    if (!args || !env_ptr || !*env_ptr)
        return (0);  // ✅ RETOURNER 0 même si pas d'args

    exit_status = 0;
    current = args->next; // Passer "unset"

    while (current)
    {
        if (!is_valid_var_name(current->cmd_args))
        {
            ft_putstr_fd("minishell: unset: `", STDERR_FILENO);  // ✅ AJOUTER "minishell:"
            ft_putstr_fd(current->cmd_args, STDERR_FILENO);
            ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
            exit_status = 1;
        }
        else
        {
            // ✅ UNSET réussit TOUJOURS, même pour des variables importantes
            remove_env_var(env_ptr, current->cmd_args);
            // Pas de vérification d'erreur - unset réussit toujours
        }
        current = current->next;
    }
    return (exit_status);
}