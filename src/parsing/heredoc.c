/* ************************************************************************** *//* ************************************************************************** */
/*  heredoc.c – realise every << found during parsing                         */
/* ************************************************************************** */

#include "struct.h"

static int	ft_strcmp(char *s1, char *s2)
{
	char	*str;
	int		k;
	int		i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	str = get_string(ft_strdup(s2), 0, 0, get_size(s2));
	while (s1[i] == str[i] && s1[i] != '\0' && str[i] != '\0')
		i++;
	k = s1[i] - str[i];
	free(str);
	return (k);
}

static int	open_tmp(char **path_out)
{
	static int	idx;
	char		*name;

	name = ft_strjoin("/tmp/msh_hd_", ft_itoa(idx++));
	if (!name)
		return (-1);
	*path_out = name;
	return (open(name, O_WRONLY | O_CREAT | O_TRUNC, 0600));
}

int	fill_heredocs(t_cmd *cmds)
{
	char	*line;
	int		fd;

	while (cmds)
	{
		if (cmds->here_doc == HEREDOC)
		{
			fd = open_tmp(&cmds->infile_name);
			if (fd < 0)
				return (perror("heredoc"), 1);
			while (1)
			{
				line = readline("> ");
				if (!line || !ft_strcmp(line, cmds->infile_name) )
					break ;
				ft_putendl_fd(line, fd);
				free(line);
			}
			free(line);
			close(fd);
			cmds->infile = open(cmds->infile_name, O_RDONLY);
		}
		cmds = cmds->next;
	}
	return (0);
}