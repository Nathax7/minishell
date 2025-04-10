/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:44:04 by almeekel          #+#    #+#             */
/*   Updated: 2025/04/09 17:40:46 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifndef	STRUCT_H
#define STRUCT_H





































//parsing structures and chained lists//

typedef enum e_token_type {
	T_WORD,
	T_PIPE,
	T_REDIRECT_IN,
	T_REDIRECT_OUT,
	T_HEREDOC,
	T_APPEND,
	// Add other token types as needed
} t_token_type;

typedef struct s_token {
	char          *value;
	t_token_type  type;
	struct s_token *next;
} t_token;

typedef struct s_command {
	char            **args;
	char            *input_file;
	char            *output_file;
	char			envp;
	int				cmd_amt;
	int             append;       // Boolean flag for '>>'
	struct s_command *prev;
	struct s_command *next;
} t_command;

#endif