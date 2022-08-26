/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarkhaw <fdarkhaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 21:00:37 by fdarkhaw          #+#    #+#             */
/*   Updated: 2022/08/26 20:48:45 by fdarkhaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*return_word_and_plus_i(char *line, int *i)
{
	char	*str;

	str = ft_substr(line, 0, ft_strlen(line));
	if (NULL == str)
		ft_error("Error: memory was not allocated properly");
	*i += 1;
	return (str);
}

void	ft_bzero_8(void *s, size_t n)
{
	char	*ptr;

	ptr = (char *)s;
	while (n--)
		*ptr++ = '8';
	*ptr = '\0';
}

// void	ft_bzero_8(void *s, size_t n)
// {
// 	char	*ptr;
// 	int		i = 0;

// 	ptr = (char *)s;
// 	while (n--)
// 		ptr[i++] = '8';
// 	ptr[i] = '\0';
// 	printf("ft_8 i = %d\n", i);
// }

void	*ft_calloc_8(size_t count, size_t size)
{
	void	*mem;

	mem = malloc(count * size);
	if (mem == NULL)
		ft_error("Error: memory was not allocated properly");
	ft_bzero_8(mem, size * count);
	return (mem);
}

void	from_file_to_map(char **map, char **file, int *i, int *j)
{
	*map = ft_substr(*file, 0, ft_strlen(*file));
	if (NULL == map)
		ft_error("Error: memory was not allocated properly");
	*j += 1;
	*i += 1;
}
