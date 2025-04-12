
void	handle_heredocs(t_token *tokens)
{
	int		fd;
	char	*delim;
	char	*line;

	while (tokens)
	{
		if (tokens->type == T_HEREDOC && tokens->next
			&& tokens->next->type == T_WORD)
		{
			delim = tokens->next->value;
			fd = open("/tmp/.heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd < 0)
				return ;
			while (1)
			{
				line = readline("> ");
				if (!line || ft_strcmp(line, delim) == 0)
					break ;
				write(fd, line, ft_strlen(line));
				write(fd, "\n", 1);
				free(line);
			}
			free(line);
			close(fd);
			// Ensuite,
				stocker le chemin vers le fichier dans la structure de commande
		}
		tokens = tokens->next;
	}
}
