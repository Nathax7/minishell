
char	*get_env_value(const char *name, char **env)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(name);
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

char	*expand_one(const char *src, char **env, int last_exit)
{
	char	*res;
	int		i;
	char	*code;
	int		start;
	char	*var;
	char	*val;

	res = ft_calloc(1, 1);
	i = 0;
	while (src[i])
	{
		if (src[i] == '$' && src[i + 1])
		{
			if (src[i + 1] == '?')
			{
				code = ft_itoa(last_exit);
				res = ft_strjoin_free(res, code);
				free(code);
				i += 2;
			}
			else if (ft_isalpha(src[i + 1]) || src[i + 1] == '_')
			{
				start = ++i;
				while (src[i] && (ft_isalnum(src[i]) || src[i] == '_'))
					i++;
				var = ft_substr(src, start, i - start);
				val = get_env_value(var, env);
				if (val)
					res = ft_strjoin_free(res, val);
				free(var);
			}
			else
				res = ft_strjoin_free_c(res, src[i++]);
		}
		else
			res = ft_strjoin_free_c(res, src[i++]);
	}
	return (res);
}

void	expand_variables(t_token *tokens, char **env, int last_exit)
{
	char *expanded;
	while (tokens)
	{
		if (tokens->type == T_WORD && ft_strchr(tokens->value, '$'))
		{
			expanded = expand_one(tokens->value, env, last_exit);
			free(tokens->value);
			tokens->value = expanded;
		}
		tokens = tokens->next;
	}
}