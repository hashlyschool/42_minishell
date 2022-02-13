/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 12:19:59 by hashly            #+#    #+#             */
/*   Updated: 2022/02/13 16:31:40 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# define TERM_BLACK		"\033[1;90m"
# define TERM_RED		"\033[1;91m"
# define TERM_GREEN		"\033[1;92m"
# define TERM_YELLOW	"\033[1;93m"
# define TERM_BLUE		"\033[1;94m"
# define TERM_PURPLE	"\033[1;95m"
# define TERM_CYAN		"\033[1;96m"
# define TERM_WHITE		"\033[1;97m"
# define TERM_RESET		"\033[0m"

# define RL_BLACK		"\001\033[1;90m\002"
# define RL_RED			"\001\033[1;91m\002"
# define RL_GREEN		"\001\033[1;92m\002"
# define RL_YELLOW		"\001\033[1;93m\002"
# define RL_BLUE		"\001\033[1;94m\002"
# define RL_PURPLE		"\001\033[1;95m\002"
# define RL_CYAN		"\001\033[1;96m\002"
# define RL_WHITE		"\001\033[1;97m\002"
# define RL_RESET		"\001\033[0m\002"

# define OK				TERM_GREEN
# define WARNING		TERM_YELLOW
# define ERROR			TERM_RED
# define RESET			TERM_RESET

#endif
