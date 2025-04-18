/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:06:39 by nagaudey          #+#    #+#             */
/*   Updated: 2025/04/18 17:52:04 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"
#include <stdio.h>
#include <stdlib.h>

// Allocation protégée
void	*ft_malloc(t_minishell *shell, size_t size)
{
	void	*block;

	block = malloc(size);
	if (!block)
	    free_parent_utils(shell, 1, NULL, "Error malloc");
	return (block);
}
