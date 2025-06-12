/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:36:22 by almeekel          #+#    #+#             */
/*   Updated: 2025/06/12 19:06:48 by almeekel         ###   ########.fr       */
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
# include <sys/wait.h>
# include <unistd.h>

# define CHARSET "abcdefghijklmnopqrstuvwxyz"

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

typedef enum e_prompt_type
{
	PROMPT_MAIN,
	PROMPT_PIPE,
	PROMPT_QUOTE,
	PROMPT_REDIR,
	PROMPT_HEREDOC
}					t_prompt_type;
typedef enum e_parser_state
{
	STATE_START,
	STATE_EXPECT_COMMAND,
	STATE_EXPECT_ARG,
	STATE_EXPECT_FILENAME
}					e_parser_state;

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
	T_HEREDOC
}					t_token_type;

typedef enum e_quote
{
	Q_NONE,
	Q_SINGLE,
	Q_DOUBLE,
	Q_MIXED
}					t_quote;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	t_quote			quote;
	struct s_token	*next;
}					t_token;
typedef struct s_syntax_result
{
	t_parse_status	status;
	char			*error_token;
	t_token			*tokens;
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
	char			**group;
	char			*infile_name;
	char			*outfile_name;
	int				infile;
	int				outfile;
	int				append;
	int				heredoc;
	t_pipex			pipex;
	struct s_exec	*next;
	struct s_exec	*prev;

}					t_exec;

typedef struct s_cmd
{
	char			**cmds;
	int				ncmd;
	int				max;
}					t_cmd;

typedef struct s_exec_list_builder_state
{
	t_token			*current_token;
	t_exec			*list_head;
	t_exec			*current_exec_node;
	t_list			*temp_arg_list;
	int				build_status;
}					t_exec_list_builder_state;

extern int			g_signal_test;

#endif