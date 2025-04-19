/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:44:00 by almeekel          #+#    #+#             */
/*   Updated: 2025/04/19 19:27:53 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "utils.h"

t_token			*tokenize(char *input);
t_token_type	identify_operator(const char *s, int *i);
t_token_type	identify_redirect(const char *s, int *i, int flag);

#endif