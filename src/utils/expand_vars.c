#include "utils.h"

char *expand_variable(char *str, char **envp)
{
    if (!str || !envp)
        return (str);

    if (ft_strncmp(str, "$PWD", 4) == 0)
    {
        char *pwd = getenv("PWD");
        if (pwd)
            return (ft_strdup(pwd));
    }
    else if (ft_strncmp(str, "$OLDPWD", 7) == 0)
    {
        char *oldpwd = getenv("OLDPWD");
        if (oldpwd)
            return (ft_strdup(oldpwd));
    }
    else if (str[0] == '$')
    {
        char *var_name = str + 1;
        char *value = getenv(var_name);
        if (value)
            return (ft_strdup(value));
    }

    return (ft_strdup(str));
}

void expand_args(t_args *args, char **envp)
{
    t_args *current = args;

    while (current)
    {
        if (current->cmd_args && ft_strchr(current->cmd_args, '$'))
        {
            char *expanded = expand_variable(current->cmd_args, envp);
            if (expanded)
            {
                free(current->cmd_args);
                current->cmd_args = expanded;
            }
        }
        current = current->next;
    }
}