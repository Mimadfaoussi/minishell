/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamieta <anamieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:37:48 by anamieta          #+#    #+#             */
/*   Updated: 2024/05/24 16:38:16 by anamieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redirection_correct(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
		{
			if (str[i + 1] == str[i])
			{
				if (!str[i + 2] || !(isalnum(str[i + 2])
						|| str[i + 2] == ' ' || str[i + 2] == '_'))
					return (1);
				i += 3;
			}
			else
			{
				if (!str[i + 1] || !(isalnum(str[i + 1])
						|| str[i + 1] == ' ' || str[i + 1] == '_'))
					return (1);
				i += 2;
			}
		}
		else
			i++;
	}
	return (0);
}
