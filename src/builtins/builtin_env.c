/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:58:59 by almeekel          #+#    #+#             */
/*   Updated: 2025/06/28 19:32:00 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	builtin_env(char ***env_ptr)
{
    char	**envp;
    int i;
	
    if (!env_ptr || !*env_ptr)
        return (1);
    envp = *env_ptr;
    if (!envp)
        return (1);

    i = 0;
    while (envp[i])
    {
        ft_putstr_fd(envp[i], STDOUT_FILENO);
        ft_putchar_fd('\n', STDOUT_FILENO);
        i++;
    }
    return (0);
}
