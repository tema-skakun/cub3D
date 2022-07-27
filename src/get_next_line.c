/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarkhaw <fdarkhaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 19:09:54 by jg                #+#    #+#             */
/*   Updated: 2022/07/27 21:13:12 by fdarkhaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*ft_rem(char *rem)
{
	int	i;

	i = 0;
	while (rem[i] != '\n' && rem[i] != '\0')
		i++;
	if (rem[i] == '\0')
	{
		free(rem);
		return (NULL);
	}
	rem = ft_strcpy(rem, &rem[i + 1]);
	if (rem == NULL)
		return (NULL);
	return (rem);
}

char	*ft_line(char *rem)
{
	char	*line;
	int		i;

	if (rem[0] == '\0')
		return (NULL);
	i = 0;
	while (rem[i] != '\n' && rem[i] != '\0')
		i++;
	line = (char *)ft_calloc(i + 2, sizeof(char));
	if (line == NULL)
		return (NULL);
	while (i)
	{
		i--;
		line[i] = rem[i];
	}
	return (line);
}

char	*ft_read(int fd, char *buf, char *rem)
{
	int	i;

	i = 1;
	if (!rem)
		rem = (char *)ft_calloc(1, sizeof(char));
	while (i)
	{
		i = read(fd, buf, 3000);
		if (i < 0)
		{
			free(buf);
			free(rem);
			return (NULL);
		}
		buf[i] = '\0';
		rem = ft_strjoin_gnl(rem, buf);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (rem);
}

char	*get_next_line(int fd)
{
	static char	*rem;
	char		*line;
	char		*buf;

	if (fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buf = (char *)ft_calloc(3000 + 1, sizeof(char));
	rem = ft_read(fd, buf, rem);
	if (buf)
		free(buf);
	if (!rem)
		return (NULL);
	line = ft_line(rem);
	rem = ft_rem(rem);
	return (line);
}
