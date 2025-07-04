/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:42:53 by almeekel          #+#    #+#             */
/*   Updated: 2025/07/04 15:20:24 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "struct.h"

extern int	g_signal_test;

void		setup_interactive_signals(void);
void		setup_child_signals(void);
void		setup_heredoc_signals(void);
void		reset_signals(void);
void		setup_interactive_signals(void);
void		setup_child_signals(void);
void		setup_parent_signals(void);

#endif