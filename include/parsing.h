/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mimoulapinou <bebefripouille@chaton.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:44:00 by almeekel          #+#    #+#             */
/*   Updated: 2025/04/12 12:47:37 by Mimoulapino      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "struct.h"

t_token			*tokenize(char *input);
t_token_type	identify_operator(const char *s, int *i);
t_token_type	identify_redirect(const char *s, int *i, int flag);

#endif