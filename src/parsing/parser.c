/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:02:41 by almeekel          #+#    #+#             */
/*   Updated: 2025/04/20 14:35:23 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

// j'initialise cmd
static t_cmd	*cmd_new(void)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->infile = STDIN_FILENO;
	cmd->outfile = STDOUT_FILENO;
	cmd->here_doc = NO_HEREDOC;
	cmd->env = NO_ENV;
	cmd->fd[0] = -1;
	cmd->fd[1] = -1;
	return (cmd);
}

static int	cmd_add_arg(t_cmd *cmd, char *arg)
{
	size_t	len;
	char	**tmp;

	len = 0;
	while (cmd->cmd_args && cmd->cmd_args[len])
		len++;
	tmp = ft_calloc(len + 2, sizeof(char *));
	if (!tmp)
		return (1);
	while (cmd->cmd_args && len--)
		tmp[len] = cmd->cmd_args[len];
	tmp[++len] = arg;
	cmd->cmd_args = tmp;
	if (!cmd->cmd)
		cmd->cmd = arg;
	return (0);
}

static int	parse_redir(t_cmd *cmd, t_token **tk)
{
	t_token	*op;
	t_token	*word;

	op = *tk;
	if (!op->next || op->next->type != T_WORD)
		return (ft_putstr_fd("minishell: syntax error\n", 2), 258);
	word = op->next;
	if (op->type == T_REDIRECT_IN)
		cmd->infile_name = word->value;
	else if (op->type == T_REDIRECT_OUT || op->type == T_APPEND)
		cmd->outfile_name = word->value;
	else if (op->type == T_HEREDOC)
	{
		cmd->here_doc = HEREDOC;
		cmd->infile_name = word->value; /* retenir la delim        */
	}
	*tk = word; /* passer le token du filename   */
	return (0);
}

t_cmd	*build_cmd_list(t_token *tk)
{
	t_cmd	*head = NULL;
	t_cmd	*cur  = NULL;

	while (tk)
	{
		if (!cur) /* nouvelle commande simple    */
		{
			cur = cmd_new();
			ft_lstadd_back((t_list **)&head, (t_list *)cur);
		}
		if (tk->type == T_WORD)
			if (cmd_add_arg(cur, tk->value))
				return (NULL);
		if (tk->type >= T_REDIRECT_IN && tk->type <= T_HEREDOC)
			if (parse_redir(cur, &tk))
				return (NULL);
		if (tk->type == T_PIPE)
			cur = NULL;
		tk = tk->next;
	}
	return (head);
}

