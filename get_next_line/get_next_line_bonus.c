/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuhn <kkuhn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:54:05 by kkuhn             #+#    #+#             */
/*   Updated: 2024/04/10 19:15:56 by kkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

long long	alloc_str_size(t_list *list)
{
	long long	str_size;

	str_size = 0;
	while (list != NULL)
	{
		if (list->content != NULL)
		{
			if (newline_found(list->content) != -1)
				str_size += newline_found(list->content) + 1;
			else
				str_size += ft_strlen(list->content);
		}
		list = list->next;
	}
	return (str_size);
}

t_list	*create_linked_list(int fd, t_list *lst)
{
	int		bytes_read;
	char	*buffer;

	if (lst != 0)
		if (newline_found(lst->content) != -1)
			return (lst);
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (buffer == 0)
		return (0);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = 0;
		if (!(lst))
			lst = ft_lstnew(ft_strdup(buffer));
		else
			ft_lstadd_back(&lst, ft_lstnew(ft_strdup(buffer)));
		if (newline_found(buffer) != -1)
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	return (lst);
}

char	*create_string(char *nextline, t_list *list)
{
	char	*liststring;
	int		i;

	i = 0;
	while (list != 0)
	{
		liststring = list->content;
		while (*liststring != 0)
		{
			if (*liststring != '\n')
				nextline[i] = *liststring;
			else
				break ;
			liststring++;
			i ++;
		}
		list = list->next;
	}
	if (*liststring == '\n')
		return (nextline[i] = '\n', nextline[i + 1] = 0,
			ft_strdup(&liststring[1]));
	if (*liststring == 0)
		nextline[i] = 0;
	return (ft_strdup(liststring));
}

t_list	*clean_list(t_list *list, char *liststring)
{
	t_list	*next;

	if (list == 0)
		return (0);
	while (list->next != 0)
	{
		next = list->next;
		if (list->content != 0)
			free(list->content);
		list->content = 0;
		free(list);
		list = next;
	}
	if (list->content != 0)
		free(list->content);
	list->content = ft_strdup(liststring);
	if (ft_strlen(liststring) == 0)
	{
		free(list->content);
		list->content = 0;
		free(list);
		return (0);
	}
	return (list);
}

char	*get_next_line(int fd)
{
	static t_list	*list[1024];
	char			*nextline;
	char			*lsstr;

	if (read(fd, 0, 0) < 0)
	{
		if (list[fd] != NULL)
		{
			if (list[fd]->content != 0)
				free(list[fd]->content);
			list[fd]->content = 0;
			list[fd] = clean_list(list[fd], "");
		}
		return (0);
	}
	list[fd] = create_linked_list(fd, list[fd]);
	if (list[fd] == 0)
		return (0);
	nextline = malloc(alloc_str_size(list[fd]) + 1);
	if (nextline == 0)
		return (0);
	lsstr = create_string(nextline, list[fd]);
	if (nextline == 0)
		free(nextline);
	return (list[fd] = clean_list(list[fd], lsstr), free(lsstr), nextline);
}
// int main(void)
// {
// 	int fd = open("1char.txt", O_RDWR | O_CREAT, 0666);
// 	// int fd2 = open("lines_around_10.txt", O_RDWR | O_CREAT, 0666);
// 	int i;
// 	char *nextline;

// 	i = 0;
// 	nextline = get_next_line(fd);
// 	// while (i < 2)
// 	// {
// 	//printf("%s", get_next_line(fd2));
// 	// printf("%s", get_next_line(fd2));
// 	printf("%s", nextline);
// 	free(nextline); 
// 	//system("leaks a.out");
// 	// fd = open("read_error.txt", O_RDWR | O_CREAT, 0666);
// 	// printf("%s", get_next_line(fd));
// 	// 	printf("%s", get_next_line(fd));
// 	// printf("%s", get_next_line(fd));
// 	// printf("%s", get_next_line(fd));
// 	// printf("%s", get_next_line(fd));
// 	// printf("%s", get_next_line(fd));
// 	// printf("%s", get_next_line(fd));
// 	//	printf("%s", get_next_line(fd2));
// 	//printf("%s", get_next_line(fd2));
// 	// 	printf("%s", get_next_line(fd2));
// 	// printf("%s", get_next_line(fd2));
// 	//get_next_line(fd2);
// 	 //get_next_line(fd);
// 		//get_next_line(fd2);
// 	//get_next_line(fd2);
// }
