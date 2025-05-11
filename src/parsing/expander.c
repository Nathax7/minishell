/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:07:26 by almeekel          #+#    #+#             */
/*   Updated: 2025/05/11 21:22:22 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

// Main pour faire les expansions sur la liste token, 
// retourne une liste de token sans free la liste originale
// ELLE NEXPAND QUE LA VAR POUR LINSTANT AJOUTER LA TILDE GLOBBING ETC !!!!
// IL MANQUE AUSSI LE SPLIT DES MOTS APRES UNE EXPANSION SANS QUOTE !
t_token	*perform_all_expansions(t_token *raw_list_head, char **envp,
		int current_exit_status)
{
	t_token *current_raw;
	t_token *expanded_list_head;
	char *original_value;
	char *expanded_value;

	current_raw = raw_list_head;
	expanded_list_head = NULL;
	while (current_raw)
	{
		original_value = current_raw->value;
		expanded_value = NULL; // Expansion des variables qui s'applique a Q NONE et Q double
		if (current_raw->quote != Q_SINGLE)
			expanded_value = expand_variables_in_str(original_value,
					current_raw->quote, envp, current_exit_status);
		else
			expanded_value = ft_strdup(original_value);
		if (!expanded_value)
		{
			free_token_list(expanded_list_head); // Clean up deja fait du coup donc on est bon pour free
			// display_error("expander", "memory allocation failure", 0); A AJOUTER AVEC l'ERROR
			// g_exit_status a set ici ...
			return (NULL);
		}
		// pour l'instant pas de word splitting ou de globbing donc un token raw -> un token expanse
		// Si la value expanee est vide et ans quote, comme dans le cas $UNSET_VAR,
		// Bash la supprime. Ce n'est pas implemente pour l'instant.
		// On cree un token meme si la valeur expansee est vide.
		if (!create_and_append_token(&expanded_list_head, expanded_value,
				current_raw->type, current_raw->quote))
			// Le quote status va changer apres l'enlevement des quote
		{
			free(expanded_value);
			free_token_list(expanded_list_head);
			// display_error("expander", "token creation failure", 0); A AJOUTER AVEC l'ERROR
			// g_exit_status a set ici aussi
			return (NULL);
		}
		// create_and_append_token possede la expanded_value si bon.
		current_raw = current_raw->next;
	}
	return (expanded_list_head);
}