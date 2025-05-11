/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:36:22 by almeekel          #+#    #+#             */
/*   Updated: 2025/05/11 19:07:15 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "../libft/all.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

# define CHARSET "abcdefghijklmnopqrstuvwxyz"

// struct to build a string in the second phase of parsing
typedef struct s_str_builder
{
	char			*str;
	size_t			len;
	size_t			capacity;
}					t_str_builder;

//tokenization struct
typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIRECT_IN,
	T_REDIRECT_OUT,
	T_APPEND,
	T_HEREDOC
}					t_token_type;

//typing struct
typedef enum e_type
{
	CMD,
	INFILE,
	OUTFILE,
	HEREDOC,
	APPEND,
	FD0,
	FD1
}					t_type;

//quote-typing struct
typedef enum e_quote
{
	Q_NONE,
	Q_SINGLE,
	Q_DOUBLE
}					t_quote;

// list used during tokenization
typedef struct s_token
{
	char			*value;
	t_token_type	type;
	t_quote quote;
		/* nouveau en gros c'est pour savoir si le word a des double ou single quote       */
	struct s_token	*next;
}					t_token;

// enum to indicate the presence of an env
typedef enum e_env
{
	NO_ENV,
	ENV
}					t_env;

typedef struct s_pipex
{
	pid_t			*pids;
	char			*cmd;
	char			**cmd_args;
	char			**paths;
	char			*path;
	int				infile;
	int				outfile;
	char			*infile_name;
	char			*outfile_name;
	int				fd[2];
	int				status;
	int				here_doc;
	int				append;
	int				cmd_nbr;
	int				i_wait;
	int				i;
	int				envp;
}					t_pipex;

typedef struct s_exec
{
	int				count;
	char			***groups;
	char			**cmds;
	int				i;
	int				ncmd;
	int				ng;
	char			*infile_name;
	char			*outfile_name;
	int				infile;
	int				outfile;
	char			**group;
	int				total;
	int				idx;
	int				j;
	t_pipex			pipex;
}					t_exec;

extern int g_exit_status; // For the shell's exit status
extern volatile sig_atomic_t g_signal_received; // To flag if a signal was caught

#endif