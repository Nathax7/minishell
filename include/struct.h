/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mimoulapinou <bebefripouille@chaton.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:44:04 by almeekel          #+#    #+#             */
/*   Updated: 2025/04/12 16:23:30 by Mimoulapino      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "../libft/all.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>


# define CHARSET "abcdefghijklmnopqrstuvwxyz"

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIRECT_IN,
	T_REDIRECT_OUT,
	T_APPEND,
	T_HEREDOC
} t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
} t_token;

typedef enum
{
	NO_HEREDOC,
	HEREDOC
}	t_heredoc;

typedef enum
{
	NO_ENV,
	ENV
}	t_env;

typedef struct s_cmd
{
	t_heredoc	here_doc;
	t_env		env;
	pid_t	*pids;
	char	*cmd;
	char	**cmd_args;
	char	**paths;
	char	*path;
	int		infile;
	int		outfile;
	char	*infile_name;
	char	*outfile_name;
	int		fd[2];
	int		status;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_node
{
	void			*addr;
	struct s_node	*next;
}	t_node;

typedef struct s_signal
{
	int		signal;
	int		status;
	int		pid;
	t_node	*node;
}	t_signal;

extern t_signal	g_signal;


#endif