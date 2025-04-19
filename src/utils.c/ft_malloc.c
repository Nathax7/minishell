/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:06:39 by nagaudey          #+#    #+#             */
/*   Updated: 2025/04/19 19:33:39 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include <stdio.h>
#include <stdlib.h>

// Allocation protégée
void	*ft_malloc(t_minishell *shell, size_t size)
{
	void	*block;

	block = malloc(size);
	if (!block)
	    free_all(shell, 1, NULL, "Error malloc");
	return (block);
}
