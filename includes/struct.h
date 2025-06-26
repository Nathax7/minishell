/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:36:22 by almeekel          #+#    #+#             */
/*   Updated: 2025/06/25 21:39:28 by nagaudey         ###   ########.fr       */
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
# include <dirent.h>
# include <sys/wait.h>
# include <unistd.h>
#include <sys/stat.h>
# define CHARSET "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"

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

typedef struct s_args
{
	char	*cmd_args;
	struct s_args	*next;
	struct s_args	*prev;
}	t_args;
typedef struct s_files // Un seul fichier par node
{
	char	*infile_name;
	char	*outfile_name;
	int				heredoc;
	int				append;
	struct s_files	*next;
	struct s_files	*prev;
}	t_files;

typedef struct s_cmd
{
	t_args			*args;
	char			*cmd_path;		// Chemin complet de la commande
	t_files			*files;			// Liste des fichier (in/out)
	int				is_builtin;		// 1 si c'est un builtin
	int				fd_input;		// -1 si c'est STDIN
	int				fd_output;		// -1 si c'est STDOUT
	struct s_cmd	*next;			// Pour chaîner avec des pipes
	struct s_cmd	*prev;			// Pour chaîner avec des pipes
} t_cmd;

typedef struct s_exec
{
    t_cmd		*cmd_list; // Liste des commandes
    char		**envp; // Variables d'environnement
    char		**paths; // Chemins du PATH
    pid_t		*pids; // PIDs des processus fils
    int			**pipes; // Pipes pour communication
    int			cmd_count;
    int			exit_status; // Status de sortie
    int			envp_exists;
    int			stdin_backup; // Sauvegarde stdin
    int			stdout_backup;  // Sauvegarde stdout
} t_exec;

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