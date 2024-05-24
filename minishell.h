/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamieta <anamieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:14:12 by mfaoussi          #+#    #+#             */
/*   Updated: 2024/05/24 13:37:33 by anamieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <signal.h>
# include <termios.h>
# include <fcntl.h>

# include "signals/signals.h"
# include "structs.h"
# include "builtins/builtins.h"
# include "checks/checks.h"
# include "lexer/lexer.h"
# include "libft/libft.h"
# include "lists/lists.h"
# include "parser/parser.h"
# include "init/init.h"
# include "executor/executor.h"
# include "expander/expand.h"

int						check_quotes(char *input);
// int						check_single_quotes(char *input);
// int						check_double_quotes(char *input);
void					print_tokens(t_token *lst);

#endif