/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:44:04 by almeekel          #+#    #+#             */
/*   Updated: 2025/04/20 16:51:58 by almeekel         ###   ########.fr       */
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
	pid_t	*pids;
	t_heredoc	here_doc;
	t_env		env;
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

extern int	g_signal;


#endif