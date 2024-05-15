/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaoussi <mfaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:14:12 by mfaoussi          #+#    #+#             */
/*   Updated: 2024/05/15 13:14:46 by mfaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include "structs.h"
# include "checks/checks.h"
# include "lexer/lexer.h"
# include "libft/libft.h"
# include "lists/lists.h"
# include "parser/parser.h"


int						check_quotes(char *input);
int						check_single_quotes(char *input);
int						check_double_quotes(char *input);
void					print_tokens(t_token *lst);

#endif