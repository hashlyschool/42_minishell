/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 17:46:12 by a79856            #+#    #+#             */
/*   Updated: 2022/02/20 20:22:50 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

char	*ft_gap(char *str, int i);
char	*ft_slash(char *str, int i);
char	*ft_quotechar(char *str, int i, char **env);

#endif
