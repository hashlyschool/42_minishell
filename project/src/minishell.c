/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 19:45:08 by hashly            #+#    #+#             */
/*   Updated: 2022/01/09 01:52:08 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include <curses.h>
#include <term.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char	room_termtype[2048];
char	*termtype;
char	buf[100];
char	*buffer;

//необходима для tputs
int	ft_putint(int c)
{
	return (write(STDOUT_FILENO, &c, 1));
}

void        test_tgetnum(void)
{
   int     col;
   int     li;

   col = tgetnum("co");
   li = tgetnum("li");
   printf("Columns = %d, lines = %d\n", col, li);
}

void        test_tgetflag(void)
{
   int     flag_overstrike;
   int     flag_home;

   flag_overstrike = tgetflag("os");
   flag_home = tgetflag("hz");

   if (flag_overstrike == 0)
       printf("При выводе символа, то, что было на той же позиции, стирается - не перегружается\n");
   else
       printf("При выводе символа, то, что было на той же позиции, не стирается - может перегружаться\n");

   if (flag_home == 0)
       printf("Терминал может печатать тильду\n");
   else
       printf("Терминал не может печатать тильду\n");
}

void        test_clean_screen(void)
{
   char    *clean_screen;

   buffer = buf;
   clean_screen = tgetstr("cl", &buffer);

   tputs(clean_screen, 1, ft_putint);

   buffer = buf;
   bzero(buffer, 100);
}

void        padding_tputs(void)
{
   extern char PC;
   char        *temp;

   buffer = buf;
   temp = tgetstr ("pc", &buffer);
   PC = temp ? *temp : 0;
   if (PC == 0)
       printf("PC не задан\n");
   buffer = buf;
   bzero(buffer, 100);
}

void        test_absolute_cursor_position(void)
{
   buffer = buf;
   tputs(tgoto(tgetstr("cm", &buffer), 2, 2), 1, ft_putint);
   buffer = buf;
   bzero(buffer, 100);

   printf("\033[1;34mCursor was here\033[0m\n");
}

void	ft_putstr(char *str)
{
	if (!str)
		return ;
	write(1, str, strlen(str));
	return ;
}

void        test_relative_cursor_position(void)
{
   char    *line;

   line = "Cursor was here";
   //так как у printf есть своя буферизация, он не всегда воспринимает игры с курсором
   ft_putstr("\033[1;34m");
   ft_putstr(line);
   ft_putstr("\033[0m");

   buffer = buf;
   //ставим на третий символ в той строке, где мы находимся
   tputs(tgoto(tgetstr("ch", &buffer), 0, 3), 1, ft_putint);
   //удаляем на длину оставшейся строки с позиции курсора, позиция курсора не меняется
   tputs(tgoto(tgetstr("DC", &buffer), 0, strlen(line) - 3), 1, ft_putint);
   buffer = buf;
   bzero(buffer, 100);

   //printf при этом можно использовать для демонстрации содеянного
   printf("\033[1;33m%s\033[0m\n", line);
}


int	main(int argc, char **argv)
{
	//define the terminal
	if (!isatty(STDIN_FILENO))
		return(1);
//чтобы было удобнее тестировать, будут использоваться аргументы
	if (argc < 2)
		return (1);
	termtype = getenv("TERM");
	if (termtype == NULL || tgetent(room_termtype, termtype) != 1)
		return (1);
	//далее будут вызываться функции
	if (strcmp(argv[1], "tgetnum") == 0)
		test_tgetnum();
	else if (strcmp(argv[1], "tgetflag") == 0)
		test_tgetflag();
	else if (strcmp(argv[1], "full_screen") == 0)
		test_clean_screen();
	else if (strcmp(argv[1], "any") == 0)
		padding_tputs();
	else if (strcmp(argv[1], "relative_position") == 0)
		test_relative_cursor_position();
	else if (strcmp(argv[1], "absolute_position") == 0)
		test_absolute_cursor_position();

	return (0);
}
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <signal.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

char *line_read;

void sighnd(int signo)
{
	free(line_read);
	write(1, "exit\n", 6);
	exit(0);
}

void sigint(int signo)
{
	write(1, "\n", 1);
	write(1, "hashly@minishell: pwd$ ", 23);
}

void sigquit(int signo)
{
	return ;
}

int main(void)
{
	signal(SIGINT, sigint);
	signal(SIGQUIT, sigquit);
	while (1)
	{
		line_read = readline("hashly@minishell: pwd$ ");
		if (line_read && *line_read)
		{
			add_history (line_read);
			rl_on_new_line();
			rl_replace_line(line_read, 0);
		}
		if (!line_read)
			sighnd(0);
		free(line_read);
		line_read = (char *)NULL;
	}
	free(line_read);
	write(1, "\n", 1);
	return 0;
}
