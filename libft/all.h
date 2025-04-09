/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:37:52 by nagaudey          #+#    #+#             */
/*   Updated: 2025/03/28 04:53:49 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALL_H
# define ALL_H

# include <fcntl.h>
# include <limits.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>

// Standard Library Functions
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_atoi(const char *str);
size_t				ft_strlen(const char *s);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
unsigned int		ft_strlcat(char *dst, char *src, size_t size);
char				*ft_strchr(const char *s, int c);
int					ft_strchr2(char *str, char *find);
char				*ft_strrchr(const char *s, int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
char				*ft_strdup(const char *s);

// Memory Functions
void				*ft_memset(void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);

// String Manipulation
char				*ft_substr(char const *s, unsigned int start, size_t len);
void				ft_strmcpy(char *dest, char *src);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				**ft_freesplit(char **str);

// File Descriptor Writing
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

// Linked List Bonus Structures and Functions
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

// ft_printf function
size_t				ft_len_putaddress(void *ptr);
int					ft_len_putchar(unsigned char c);
size_t				ft_len_putnbr_hex(unsigned int nbr, int flag);
int					ft_len_putnbr(int nb);
size_t				ft_len_putstr(const char *str);
size_t				ft_len_uputnbr(unsigned int nb);
int					ft_printf(const char *format, ...);
int					ft_iterative_count(unsigned int nbr);

// ft_printf_error functions
int					len_putchar_error(unsigned char c);
size_t				len_putaddress_error(void *ptr);
size_t				len_putnbr_hex_error(unsigned int nbr, int flag);
int					len_putnbr_error(int nb);
size_t				len_putstr_error(const char *str);
size_t				len_uputnbr_error(unsigned int nb);
int					ft_printf_error(int exit, const char *format, ...);
int					iterative_count_error(unsigned int nbr);
int					exit_error(int status);

// get_next_line functions
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 256
# endif
# ifndef MAX_FD
#  define MAX_FD 1024
# endif

char				*get_next_line(int fd);

#endif
