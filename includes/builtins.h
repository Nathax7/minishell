/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mimoulapinou <bebefripouille@chaton.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:55:28 by almeekel          #+#    #+#             */
/*   Updated: 2025/07/05 20:39:53 by Mimoulapino      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "utils.h"

int	builtin_echo(t_args *args);
int	builtin_cd(t_args *args, char ***env_ptr);
int	builtin_pwd(void);
int	builtin_export(t_args *args, char ***env_ptr);
int	builtin_unset(t_args *args, char ***env_ptr);
int	builtin_env(char ***env_ptr);
int	builtin_exit(t_args *args);
int	is_valid_var_name(const char *name);

#endif