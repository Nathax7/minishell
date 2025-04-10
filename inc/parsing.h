/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:44:00 by almeekel          #+#    #+#             */
/*   Updated: 2025/04/10 12:59:22 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../libft/all.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
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
}	t_cmd;

void	minishell_init(t_cmd *cmd, char **envp);
void	free_parent(t_cmd *cmd, int status, char *str, char *str2);
void	msg_cmd(char *str, char *str2);
void	is_here_doc(t_cmd *cmd, char **av, int ac);
void	open_infile(t_cmd *cmd, char *infile);
void	open_outfile(t_cmd *cmd, char *outfile, int mode);
void	usage(void);
int			is_operator(char c);
t_token		*tokenize(char *input);

#endif