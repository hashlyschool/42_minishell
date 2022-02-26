/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a79856 <a79856@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 17:46:12 by a79856            #+#    #+#             */
/*   Updated: 2022/02/24 03:54:44 by a79856           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

char	*ft_gap(char *str, int *i);
char	*ft_slash(char *str, int *i);
char	*ft_quotechar(char *str, int *i);
char	*ft_dollar(char *str, int *i, char *start, char *end);
char	*ft_replace(char *str, int *i, char c);

#endif
