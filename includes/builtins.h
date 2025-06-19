/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:55:28 by almeekel          #+#    #+#             */
/*   Updated: 2025/06/19 16:08:34 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "utils.h"

int		builtin_echo(char **args);
int		builtin_cd(char **args, char ***env_ptr);
int		builtin_pwd(void);
int		builtin_export(char **args, char ***env_ptr);
int		builtin_unset(char **args, char ***env_ptr);
int		builtin_env(char ***env_ptr);
int		builtin_exit(char **args);
int		is_valid_var_name(const char *name);

#endif