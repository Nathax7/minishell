/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 21:40:28 by almeekel          #+#    #+#             */
/*   Updated: 2025/05/10 22:35:18 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

static int	handle_char_inside_quotes(const char **line_ptr, t_str_builder *sb,
		char quote_char)
{
	char	c;

	c = **line_ptr;
	if (quote_char == '"' && c == '\\')
	{
		(*line_ptr)++;
		c = **line_ptr;
		if (c == '$' || c == '"' || c == '\\' || c == '`')
		{
			if (!sb_append_char(sb, c))
				return (0);
		}
		else // Garde le backslash si ce n'est pas un char normal
		{
			if (!sb_append_char(sb, '\\'))
				return (0);
			if (!sb_append_char(sb, c))
				return (0);
		}
	}
	else // char normal
	{
		if (!sb_append_char(sb, c))
			return (0);
	}
	return (1);
}
static int	process_quoted_segment(const char **line_ptr, t_str_builder *sb,
		char quote_char)
{
	(*line_ptr)++; // depasse la quote ouvrante
	while (**line_ptr && **line_ptr != quote_char)
	{
		if (!handle_char_inside_quotes(line_ptr, sb, quote_char))
			return (0); // Append echoue
		(*line_ptr)++;
	}
	if (**line_ptr == quote_char)
	{
		(*line_ptr)++; // depasse la quote fermante
		return (1);
	}
	// Pqs de quote fermante
	report_syntax_error_detail("unclosed quote",
		(quote_char == '"' ? "\"" : "'"));
	return (-1); // Indique une erreur de quote non fermee
}

static int	process_word_token(const char **line_ptr, t_token **head)
{
	t_str_builder	sb;
	t_quote			quote_status;
	int				ret;
	char			*token_val;

	sb_init(&sb);
	quote_status = Q_NONE;
	while (**line_ptr && is_word_char(**line_ptr)
		&& !is_operator_start(**line_ptr))
	{
		if (**line_ptr == '\'' || **line_ptr == '"')
		{
			if (quote_status == Q_NONE)
				// Regle le type de quote en fonction du premier rencontre
				quote_status = (**line_ptr == '"') ? Q_DOUBLE : Q_SINGLE;
			ret = process_quoted_segment(line_ptr, &sb, **line_ptr);
			if (ret <= 0)
			{ // 0 pour un append fail, -1 pour une quote non fermee
				sb_free(&sb);
				return (ret == -1 ? -1 : 0);
			}
		}
		else // Partie non quotee du mot
		{
			if (**line_ptr == '\\')
			{
				(*line_ptr)++;
				if (**line_ptr == '\0')
				{
					report_syntax_error_detail("unexpected EOF while looking for character after",
						"\\");
					sb_free(&sb);
					return (-1);
				}
			}
			if (!sb_append_char(&sb, **line_ptr))
			{
				sb_free(&sb);
				return (0);
			}
			(*line_ptr)++;
		}
	}
	token_val = sb_to_string(&sb);
	sb_free(&sb);
	if (!token_val)
		return (0);
	if (ft_strlen(token_val) == 0 && quote_status != Q_NONE) // Pour gerer "" ou ''
	{
		// Dans ce cas cela doit rester un token vide
	}
	else if (ft_strlen(token_val) == 0) // Si tok vrmt vide
	{
		free(token_val);
		return (1); // pas de token mais pas d'erreur
	}
	if (!create_and_append_token(head, token_val, T_WORD, quote_status))
	{
		free(token_val);
		return (0);
	}
	return (1);
}

static int	process_operator_token(const char **line_ptr, t_token **head)
{
	char			*op_val;
	t_token_type	type;

	if (**line_ptr == '|')
	{
		op_val = ft_strdup("|");
		type = T_PIPE;
		(*line_ptr)++;
	}
	else if (**line_ptr == '<')
	{
		if (*(*line_ptr + 1) == '<')
		{
			op_val = ft_strdup("<<");
			type = T_HEREDOC;
			(*line_ptr) += 2;
		}
		else
		{
			op_val = ft_strdup("<");
			type = T_REDIRECT_IN;
			(*line_ptr)++;
		}
	}
	else if (**line_ptr == '>')
	{
		if (*(*line_ptr + 1) == '>')
		{
			op_val = ft_strdup(">>");
			type = T_APPEND;
			(*line_ptr) += 2;
		}
		else
		{
			op_val = ft_strdup(">");
			type = T_REDIRECT_OUT;
			(*line_ptr)++;
		}
	}
	else
		return (0); // Ne doit pas arriver si operator_start est bon
	if (!op_val)
		return (0);
	if (!create_and_append_token(head, op_val, type, Q_NONE))
	{
		free(op_val);
		return (0);
	}
	return (1);
}

t_token	*lexer(const char *line)
{
	t_token *head;
	int status;

	head = NULL;
	status = 1;
	while (*line && status > 0)
	{
		while (*line && is_whitespace(*line))
			line++;
		if (*line == '\0')
			break ;
		if (is_operator_start(*line))
			status = process_operator_token(&line, &head);
		else if (is_word_char(*line))
			// Comprend la gestion des quotes au debut du mot
			status = process_word_token(&line, &head);
		else // CA NE DOIT PAS ARRIVER NON PLUS!!
		{
			report_syntax_error_detail("unexpected character", (char[]){*line,
				0});
			status = -1; // Erreur
		}
	}
	if (status <= 0) // 0 pour erreur malloc, -1 for erreur de syntaxe
	{
		free_token_list(head);
		return (NULL);
	}
	return (head);
}