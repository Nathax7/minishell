/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 21:32:35 by nagaudey          #+#    #+#             */
/*   Updated: 2025/04/21 21:38:57 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "utils.h"

t_token			*tokenize(char *input);
t_token_type	identify_operator(const char *s, int *i);
t_token_type	identify_redirect(const char *s, int *i, int flag);

// test
char			**ft_split_whitespace(const char *str);
t_cmd			*parse_line(char *line);

#endif