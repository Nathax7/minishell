/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:44:00 by almeekel          #+#    #+#             */
/*   Updated: 2025/04/20 17:34:05 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "utils.h"

t_token			*tokenize(char *input);
t_token_type	identify_operator(const char *s, int *i);
t_token_type	identify_redirect(const char *s, int *i, int flag);
int				fill_heredocs(t_cmd *cmds);
char			*identify_word(const char *str, int *i, t_quote *qk);
// static t_quote	get_quote_kind(const char *s, int start, int end);
t_cmd			*ft_parsing(char *input, char **envp, int last_exit);
void			process_quotes(t_token *tokens);
void			expand_variables(t_token *token, char **env, int last_exit);
t_cmd			*build_cmd_list(t_token *tk);


#endif