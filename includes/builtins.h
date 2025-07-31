/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:55:28 by almeekel          #+#    #+#             */
/*   Updated: 2025/07/28 16:09:15 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "utils.h"

int	builtin_echo(t_args *args);
int	builtin_cd(t_args *args, char ***env_ptr);
int	builtin_pwd(t_args *args);
int	builtin_export(t_args *args, char ***env_ptr);
int	builtin_unset(t_args *args, char ***env_ptr);
int	builtin_env(t_args *args, char ***env_ptr);
int	builtin_exit(t_exec *exec, int parent);
int	is_valid_var_name(const char *name);

#endif