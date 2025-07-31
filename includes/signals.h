/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:42:53 by almeekel          #+#    #+#             */
/*   Updated: 2025/07/28 14:56:37 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "struct.h"

extern int	g_signal_status;

void		handle_sigint_heredoc(int sig);
void		setup_interactive_signals(void);
void		setup_child_signals(void);
void		setup_heredoc_signals(void);
void		setup_postheredoc_signals(void);
void		setup_parent_signals(void);
void		setup_noninteractive_signals(void);
void		setup_signal(int signo, void (*handler)(int));
void		handle_sigint(int sig);
int			handle_event_hook(void);

#endif