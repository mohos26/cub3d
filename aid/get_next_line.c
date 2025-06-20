/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoussas <mhoussas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 12:55:57 by mhoussas          #+#    #+#             */
/*   Updated: 2025/06/19 12:59:54 by mhoussas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static int	ft_find_new_line(char *s, size_t len)
{
	if (!s)
		return (0);
	while (*s != '\n' && len--)
		s++;
	return (*s == '\n');
}

static int	ft_get_list(char *s, size_t len, char **s1, char **s2)
{
	size_t	aid;

	s = ft_strdup(s);
	if (!s)
		return (0);
	aid = 0;
	while (s[aid] != '\n' && aid < len)
		aid++;
	*s1 = ft_calloc(aid + 2);
	ft_memcpy(*s1, s, aid + 1);
	(*s1)[aid + 1] = '\0';
	*s2 = ft_calloc(len - aid);
	ft_memcpy(*s2, s + aid + 1, len - aid - 1);
	(*s2)[len - aid - 1] = '\0';
	return (1);
}

static int	ft_aid(int *running, char **s, char **cache, int fd)
{
	*s = ft_calloc((size_t)BUFFER_SIZE + ft_strlen(*cache) + 1);
	if (*cache)
		ft_memcpy(*s, *cache, ft_strlen(*cache));
	if (!read(fd, *s + ft_strlen(*cache), BUFFER_SIZE))
		*running = 0;
	*cache = NULL;
	if (ft_find_new_line(*s, ft_strlen(*s)))
	{
		if (!ft_get_list(*s, ft_strlen(*s), s, cache))
			return (0);
		*running = 0;
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*cache;
	int			running;
	char		*res;
	char		*s;

	if (BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	running = 1;
	res = NULL;
	while (running)
	{
		if (cache && ft_find_new_line(cache, ft_strlen(cache)))
		{
			if (!ft_get_list(cache, ft_strlen(cache), &s, &cache))
				return (NULL);
			running = 0;
		}
		else
			if (!ft_aid(&running, &s, &cache, fd))
				return (NULL);
		res = ft_strjoin(res, s);
	}
	if (!ft_strlen(res))
		return (NULL);
	return (res);
}
