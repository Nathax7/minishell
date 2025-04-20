/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:02:41 by almeekel          #+#    #+#             */
/*   Updated: 2025/04/20 20:08:01 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

// j'initialise cmd
static t_cmd	*cmd_new(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	*cmd = (t_cmd){0};
	cmd->i = -1;
	cmd->i_wait = -1;
	cmd->env = 1;
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
	for (size_t i = 0; i < len; i++)
		tmp[i] = cmd->cmd_args[i];
	tmp[len] = ft_strdup(arg);
	tmp[len + 1] = NULL;
	free(cmd->cmd_args);
	cmd->cmd_args = tmp;
	if (!cmd->cmd)
		cmd->cmd = tmp[0];
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
	t_cmd	*head;
	t_cmd	*cur;

	head = NULL;
	cur = NULL;
	while (tk)
	{
		if (!cur) /* nouvelle commande simple    */
		{
			cur = cmd_new();
			if (!cur)
				return (free_cmd_list(head), NULL);
			ft_lstadd_back(&head, cur);
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
