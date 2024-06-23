/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuhn <kkuhn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 20:19:54 by kkuhn             #+#    #+#             */
/*   Updated: 2024/04/11 18:13:41 by kkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <unistd.h>
# include <stdlib.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;

}	t_list;

size_t		ft_strlen(char const *str);
char		*ft_strdup(char *s1);
t_list		*ft_lstnew(void *content);
void		ft_lstadd_back(t_list **lst, t_list *neu);
long long	newline_found(char *buffer);
t_list		*create_linked_list(int fd, t_list *lst);
char		*create_string(char *nextline, t_list *list);
t_list		*clean_list(t_list *list, char *liststring);
long long	alloc_str_size(t_list *list);
char		*get_next_line(int fd);

#endif
