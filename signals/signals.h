/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamieta <anamieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:20:29 by anamieta          #+#    #+#             */
/*   Updated: 2024/05/22 19:38:33 by anamieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parent_signals(int sig);
void	default_child_signals(void);
void	ignore_signals(void);
void	setup_signals(void);
void 	heredoc_signals(void);