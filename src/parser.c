/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarkhaw <fdarkhaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 21:15:49 by fdarkhaw          #+#    #+#             */
/*   Updated: 2022/07/27 22:08:12 by fdarkhaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// int	get_next_line(char **line)
// {
// 	int rd = 0;
// 	int i = 0;
// 	char ch;

// 	char *buffer = malloc(100000);
// 	*line = buffer;
// 	while ((rd = read(0, &ch, 1)) > 0 && ch != '\n')
// 	buffer[i++] = ch;
// 	buffer[i] = '\0';
// 	return (rd);
// }

int	check_extension(char *str)
{
	int	i;

	i = ft_strlen(str);
	if (i < 4)
		return (1);
	while (i - 4)
	{
		str++;
		i--;
	}
	if (ft_strncmp(str, ".cub", 4))
		return (1);
	return (0);
}

int	parser(int argc, char *av)
{
	int	fd;

	if (argc != 2)
		return (ft_error("Error: invalid number of arguments"));
	if (check_extension(av))
		return (ft_error("Error: file must be in .cub extension"));
	fd = open(av, O_RDONLY);
	if (fd == -1)
		return (ft_error("Error: file not exist"));
	printf("%d\n", fd);
	printf("parser is OK\n");
	return (0);
}
