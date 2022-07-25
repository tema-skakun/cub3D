/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarkhaw <fdarkhaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 20:01:43 by fdarkhaw          #+#    #+#             */
/*   Updated: 2021/10/22 20:55:41 by fdarkhaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Параметры
#1. Целое число для вывода.
#2. Файловый дескриптор, на который нужно писать.

Возвращаемое значение
Никто

Внешние факторы.
write

Описание
Выводит целое число 'n' в указанный файловый дескриптор.
*/

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	number;

	if (n < 0)
	{
		number = -n;
		ft_putchar_fd('-', fd);
	}
	else
		number = n;
	if (number < 10)
		ft_putchar_fd('0' + number, fd);
	else
	{
		ft_putnbr_fd(number / 10, fd);
		ft_putnbr_fd(number % 10, fd);
	}
}
/*
int	main(void)
{
	int	n;
	int	fd;

	n = -2147483648;
	fd = 1;
	ft_putnbr_fd(n, fd);
	return (0);
}
*/