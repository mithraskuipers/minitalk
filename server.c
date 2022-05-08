/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/22 10:54:06 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/04/24 20:26:51 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

#include <stdio.h> //printf
#include <unistd.h> //getpid

//fd = 2
static void	msg(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putstr_fd("\n", fd);
}

typedef struct s_env
{
	int	nbits;
}				t_env;






int	get_base_length(char *base)
{
	int	base_length;
	int	j;

	base_length = 0;
	while (base[base_length])
	{
		if (base[base_length] == '-' || base[base_length] == '+')
			return (0);
		j = base_length + 1;
		while (base[j])
		{
			if (base[base_length] == base[j])
				return (0);
			++j;
		}
		++base_length;
	}
	if (base_length < 2)
		return (0);
	return (base_length);
}

int	check_errors(char *str, char *base)
{
	int	i;
	int	j;
	int	start;

	start = 0;
	while (str[start] != '\0' && (str[start] == ' ' || str[start] == '\t' ||
		str[start] == '\r' || str[start] == '\n' || str[start] == '\v' ||
		str[start] == '\f'))
		start++;
	i = start;
	while (str[i])
	{
		j = 0;
		while (base[j] && (str[i] != base[j] ||
				(str[i] == '-' || str[i] == '+')))
			++j;
		if (str[i] != base[j] && str[i] != '-' && str[i] != '+')
			return (0);
		i++;
	}
	if (i == 0)
		return (0);
	return (1);
}

int	get_nb(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i] && base[i] != c)
		i++;
	return (i);
}

int	ft_atoi_base(char *str, char *base)
{
	int	s;
	int	i;
	int	res;
	int	negative;
	int	base_length;

	if (!(base_length = get_base_length(base)) || !check_errors(str, base))
		return (0);
	s = 0;
	while (str[s] != '\0' && (str[s] == ' ' || str[s] == '\t' || str[s] == '\r'
			|| str[s] == '\n' || str[s] == '\v' || str[s] == '\f'))
		s++;
	i = s - 1;
	res = 0;
	negative = 1;
	while (str[++i] && (((str[i] == '-' || str[i] == '+') && i == s) ||
			(str[i] != '-' && str[i] != '+')))
	{
		if (str[i] == '-')
			negative = -1;
		else if (str[i] != '+')
			res = (res * base_length) + (get_nb(str[i], base));
	}
	return (res * negative);
}











static void	sig_handler(int sig)
{
	static int	nbits;
	static char	*bitlist;

	nbits++;
	if (bitlist == NULL)
	{
		bitlist = ft_strdup("");
		nbits = 0;
	}
	if (sig == SIGUSR1)
		ft_strlcat(bitlist, "1", 1);
	else
		ft_strlcat(bitlist, "0", 1);
	
	if (nbits == 8)
	{
		//printf("%s\n", bitlist);
		write(1, &bitlist, 8);
		free(bitlist);
		bitlist = NULL;
	}
	
	/*
	if (nbits == 8)
	{
		//printf("%s\n",bitlist);
		//ft_convert(bitlist);
		//ft_putchar_fd(ft_atoi_base(bitlist, "01"), 1);
		char c = strtol(bitlist, (char **)NULL, 2);
		write(1, &c, 1);
		free(bitlist);
		bitlist = NULL;	
	}
	*/
}

int	main(int argc, char **argv)
{
	pid_t	pid;
	t_env	*env;

	(void)argv;

	env = ft_calloc(1, sizeof(t_env));

	(void)env;

	if ((argc != 1))
	{
		msg("Error. Usage: ./server", 2);
		return (1);
	}
	pid = getpid();
	msg(ft_itoa(pid), 1);
	while (1)
	{
		signal(SIGUSR1, sig_handler);
		signal(SIGUSR2, sig_handler);
	}
	return (0);
}

/*
SIGUSR1 and SIGUSR2 are signals that are set aside
for use in any way that you want. If you write a signal handler function
in the program that receives the signal it can be useful for interprocess
communication.
*/

/*
The signal() will call sig_handler() if the process
receives a signal SIGUSR1. If successful, it returns
a pointer to sig_handler(), or it returns -1.
*/