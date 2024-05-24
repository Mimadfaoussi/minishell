/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamieta <anamieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:18:17 by mfaoussi          #+#    #+#             */
/*   Updated: 2024/05/24 13:40:37 by anamieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	shell_init(t_shell *shell, char **env)
{
	shell->env = ft_get_env(env);
	shell->exit_code = 0;
	shell->builtins = init_builtins();
}

void	shell_setup(t_shell *shell, char *line)
{
	shell->path = get_path(shell);
	shell->tokens = tokenize(line);
	set_hd_expanded(&(shell->tokens));
	expand_all(shell);
	shell->s_cmd = NULL;
	// if (shell->tokens == NULL)
	// 	// printf("can't print tokens because it null\n");
	// else
	// 	print_tokens(shell->tokens);
	parser(&(shell->tokens), &(shell->s_cmd));
}

void	set_hd_expanded(t_token **tokens)
{
	t_token	*index;

	index = *tokens;
	while (index)
	{
		if (index->type == HEREDOC)
		{
			if (index->next)
				if (include_quotes(index->next->content) == 1)
					index->hd_expanded = 1;
		}
		index = index->next;
	}

}

int	include_quotes(char *str)
{
	int	i;

	if (!str || str[0] == '\0')
		return (0);
	i = 0;
	while (str[i])
	{
		if (is_quote(str[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

char	**init_builtins(void)
{
	char	**builtins;

	builtins = malloc(7 * sizeof(char *));
	if (!builtins)
		return (NULL);
	builtins[0] = ft_strdup("echo");
	builtins[1] = ft_strdup("cd");
	builtins[2] = ft_strdup("pwd");
	builtins[3] = ft_strdup("export");
	builtins[4] = ft_strdup("unset");
	builtins[5] = ft_strdup("env");
	builtins[6] = NULL;
	return (builtins);
}
