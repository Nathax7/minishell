/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:06:39 by nagaudey          #+#    #+#             */
/*   Updated: 2025/04/19 19:58:03 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

// Allocation protégée
void	*ft_malloc(t_minishell *shell, size_t size)
{
	void	*block;

	block = malloc(size);
	if (!block)
	    free_all(shell, 1, NULL, "Error malloc");
	return (block);
}
