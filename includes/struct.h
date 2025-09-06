/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mimoulapinou <bebefripouille@chaton.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:36:22 by almeekel          #+#    #+#             */
/*   Updated: 2025/08/14 13:41:38 by Mimoulapino      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "../libft/all.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

# define CHARSET "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"

typedef struct s_expand_context
{
	char	**envp;
	int		exit_status;
}	t_expand_context;
typedef enum e_parse_status
{
	PARSE_OK,
	PARSE_SYNTAX_ERROR,
	PARSE_MEMORY_ERROR
}					t_parse_status;

typedef enum e_parse_result
{
	PARSE_ERROR = -1,
	PARSE_SUCCESS = 1
}					t_parse_result;

typedef struct s_str_builder
{
	char			*str;
	size_t			len;
	size_t			capacity;
}					t_str_builder;

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIRECT_IN,
	T_REDIRECT_OUT,
	T_APPEND,
	T_HEREDOC,
}					t_token_type;

typedef struct s_quote_flags
{
	int				has_single;
	int				has_double;
	int				has_unquoted;
}					t_quote_flags;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}					t_token;
typedef struct s_syntax_result
{
	t_parse_status	status;
	char			*error_token;
	t_token			*tokens;
	t_token			*expanded_tokens;
}					t_syntax_result;

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

typedef struct s_args
{
	char			*cmd_args;
	struct s_args	*next;
	struct s_args	*prev;
}					t_args;

typedef struct s_files
{
	char			*infile_name;
	char			*outfile_name;
	int				heredoc;
	int				append;
	struct s_files	*next;
	struct s_files	*prev;
}					t_files;

typedef struct s_cmd
{
	t_args			*args;
	char			*cmd_path;
	t_files			*files;
	int				is_builtin;
	int				fd_input;
	int				fd_output;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

typedef struct s_exec
{
	t_cmd			*cmd_list;
	char			**envp;
	char			**paths;
	pid_t			*pids;
	int				**pipes;
	int				cmd_count;
	int				exit_status;
	int				envp_exists;
	int				stdin_backup;
	int				stdout_backup;
	int				has_input_error;
}					t_exec;

#endif