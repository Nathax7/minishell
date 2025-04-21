/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 22:22:12 by nagaudey          #+#    #+#             */
/*   Updated: 2025/04/20 22:23:31 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

void	child_sigint(int signal)
{
	if (signal == SIGINT)
	{
		(void)signal;
		g_signal = 130;
		write(2, "\n", 1);
	}
	else if (signal == SIGQUIT)
	{
		(void)signal;
		g_signal = 131;
		write(2, "Quit : core dumped\n", 19);
	}
}

void	manage_sigint(int signum)
{
	if (signum == SIGINT)
	{
		g_signal = 130;
		write(2, "^C\n", 3);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signals_monitoring(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, manage_sigint);
	signal(SIGQUIT, SIG_IGN);
}
