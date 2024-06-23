/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuhn <kkuhn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 19:15:22 by kkuhn             #+#    #+#             */
/*   Updated: 2024/04/10 17:38:28 by kkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char const *str)
{
	size_t	i;

	i = 0;
	while (*str != 0)
	{
		i++;
		str++;
	}
	return (i);
}

char	*ft_strdup(char *s1)
{
	char	*stringcopy;
	size_t	i;
	size_t	size;

	i = 0;
	size = ft_strlen(s1) + 1;
	stringcopy = (char *)malloc(size);
	if (stringcopy == 0)
		return (0);
	while (s1[i] != 0)
	{
		stringcopy[i] = s1[i];
		i++;
	}
	stringcopy[i] = 0;
	return (stringcopy);
}

t_list	*ft_lstnew(void *content)
{
	t_list	*next_node;

	next_node = (t_list *)malloc(sizeof(t_list));
	if (next_node == 0)
		return (0);
	next_node->content = content;
	next_node->next = 0;
	return (next_node);
}

void	ft_lstadd_back(t_list **lst, t_list *neu)
{
	t_list	*last;

	if (lst == 0 || neu == 0)
		return ;
	if (*lst == 0)
	{
		*lst = neu;
		return ;
	}
	last = (*lst);
	while (last->next != 0)
		last = last->next;
	last->next = neu;
}

long long	newline_found(char *buffer)
{
	long long	i;

	i = 0;
	while (i < BUFFER_SIZE && buffer[i] != 0)
	{
		if (buffer[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}
