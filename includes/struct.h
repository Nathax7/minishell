/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:47:15 by nagaudey          #+#    #+#             */
/*   Updated: 2025/06/17 17:37:13 by nagaudey         ###   ########.fr       */
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
# include <limits.h>


# define CHARSET "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"

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

// NEW: Structure for a segment within a T_WORD token
// This structure will hold parts of a word, like 'abc' or "def" or $VAR
// from an input like abc"def"$VAR
typedef struct s_word_segment
{
	char					*value;     // Literal value of this segment (content *within* quotes, or unquoted part)
	t_quote					quote_type; // Original quoting style of this segment (Q_NONE, Q_SINGLE, Q_DOUBLE)
	struct s_word_segment	*next;
}							t_word_segment;

// list used during tokenization
typedef struct s_token
{
	char			*value;          // For operators, or for T_WORD *after* expansion and segment concatenation
	t_token_type	type;
	t_quote			quote;           // For operators (Q_NONE). For T_WORD *after* expansion (Q_NONE).
                                     // This field is less relevant for raw T_WORD tokens from the lexer.
	t_word_segment	*segments;       // For T_WORD tokens from the lexer: a list of its constituent parts.
                                     // Set to NULL for operators, or for T_WORD after expansion.
	struct s_token	*next;
}					t_token;

// enum to indicate the presence of an env
typedef enum e_env
{
	NO_ENV,
	ENV
}					t_env;

// typedef struct s_pipex
// {
// 	pid_t			*pids;
// 	char			*cmd;
// 	char			**cmd_args;
// 	char			**paths;
// 	char			*path;
// 	int				infile;
// 	int				outfile;
// 	int				fd[2];
// 	int				status;
// 	int				here_doc;
// 	int				append;
// 	int				cmd_nbr;
// 	int				i_wait;
// 	int				i;
// 	int				envp;
// }					t_exec;

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


extern int g_exit_status; // For the shell's exit status
extern volatile sig_atomic_t g_signal_received; // To flag if a signal was caught

#endif