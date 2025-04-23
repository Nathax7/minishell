/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:36:22 by almeekel          #+#    #+#             */
/*   Updated: 2025/04/23 18:31:34 by nagaudey         ###   ########.fr       */
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
# include <signal.h>


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

typedef enum e_type
{
	CMD,
	INFILE,
	OUTFILE,
	HEREDOC,
	APPEND,
	FD0,
	FD1
}	t_type;

typedef enum e_quote
{
	Q_NONE,
	Q_SINGLE,
	Q_DOUBLE
}	t_quote;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	t_quote			quote;    /* nouveau en gros c'est pour savoir si le word a des double ou single quote       */
	struct s_token	*next;
}	t_token;

typedef enum e_env
{
	NO_ENV,
	ENV
}	t_env;

typedef struct s_pipex
{
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
	int		here_doc;
	int		cmd_nbr;
	int		i_wait;
	int		i;
	int		envp;
}			t_pipex;

extern int	g_signal;


#endif