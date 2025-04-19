/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:44:00 by almeekel          #+#    #+#             */
/*   Updated: 2025/04/19 19:55:51 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "utils.h"

t_token			*tokenize(char *input);
t_token_type	identify_operator(const char *s, int *i);
t_token_type	identify_redirect(const char *s, int *i, int flag);

#endif