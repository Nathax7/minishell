/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:06:39 by nagaudey          #+#    #+#             */
/*   Updated: 2025/04/11 18:46:19 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

#include <stdlib.h>
#include <stdio.h>

// Libère toute la mémoire enregistrée dans la liste
void delete_list(t_node *head)
{
    t_node *tmp;

    while (head)
	{
        tmp = head->next;
        free(head->addr);
        free(head);
        head = tmp;
    }
	free_parent_utils(NULL, 1, NULL, "Error malloc");
}

// Ajoute un nouveau bloc à la fin de la liste
t_node	*insert_node(t_node *head, void *addr)
{
    t_node *new_node = malloc(sizeof(t_node));
    t_node *current;

    if (!new_node)
        delete_list(head);
    new_node->addr = addr;
    new_node->next = NULL;
    if (!head)
        return (new_node);
    current = head;
    while (current->next)
        current = current->next;
    current->next = new_node;
    return (head);
}

// Allocation protégée avec suivi dans la liste
void	*ft_malloc(size_t size, t_node **head)
{
    void *block = malloc(size);

    if (!block)
        delete_list(*head);
    *head = insert_node(*head, block);
    return (block);
}

