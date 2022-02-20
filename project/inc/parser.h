/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a79856 <a79856@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 17:46:12 by a79856            #+#    #+#             */
/*   Updated: 2022/02/19 17:54:15 by a79856           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "minishell.h"

char	*ft_gap(char *str, int i);
char	*ft_slash(char *str, int i);
char	*ft_quotechar(char *str, int i, char **env);

#endif
