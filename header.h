/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoussas <mhoussas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:27:00 by mhoussas          #+#    #+#             */
/*   Updated: 2025/06/21 21:43:36 by mhoussas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H

# define HEADER_H

# include <unistd.h>
# include <stdio.h>
# include <time.h>
# include <math.h>
# include <limits.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdbool.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_data
{
	char	*img_no;
	char	*img_so;
	char	*img_we;
	char	*img_ea;
	int		ceil_color;
	int		floor_color;
}			t_data;

/* aid files */
bool	ft_isdigit(int c);
char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
void	ft_bzero(void *s, size_t n);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_memcpy(void *dst, const void *src, size_t n);
/* -------------------------------------------------------------------------- */

/* src */
void	ft_exit(int status);
void	*ft_calloc(size_t size);
char	*ft_get_file(char *file_name);
bool	ft_valid_file(char *file_name);
char	*ft_append_str(char	*s, char c);
t_data	*ft_parse_map(t_data *ptr, int fd);
t_data	*ft_init_scene_data(char *file_name);
bool	ft_parse_instruction(t_data *ptr, char *s);
bool	ft_validate_line(char *line, char *prev_line, char *next_line);

#endif
