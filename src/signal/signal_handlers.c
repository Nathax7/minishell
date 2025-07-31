/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:41:17 by almeekel          #+#    #+#             */
/*   Updated: 2025/07/23 15:41:20 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	handle_sigint_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_signal_status = 130;
		rl_replace_line("", 0);
		rl_done = 1;
	}
}

int	handle_event_hook(void)
{
	if (g_signal_status == 130 || g_signal_status == 0)
	{
		rl_done = 1;
	}
	return (0);
}

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		g_signal_status = 130;
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	setup_interactive_signals(void)
{
	setup_signal(SIGINT, handle_sigint);
	setup_signal(SIGQUIT, SIG_IGN);
}
