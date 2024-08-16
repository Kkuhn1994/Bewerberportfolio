#include "fdf.h"

char *ft_strjoin2(char *s1, char *s2)
{
	char *result;
	int i;

	i = 0;
	if (s1 == 0)
		return (strdup(s2));
	result = malloc(strlen(s1) + 2);
	while (s1[i] != 0)
	{
		result[i] = s1[i];
		i++;
	}
	result[i] = s2[0];
	result[i + 1] = 0;
	free(s1);
	return result;
}

long double *ft_join_double_ptr(long double *ptr1, long double ptr2, int arraysize)
{
	long double *joined;
	int i;

	i = 0;
	if (ptr1 == 0)
	{
		joined = malloc(sizeof(long double));
		joined[0] = ptr2;
		return joined;
	}
	joined = malloc(arraysize * sizeof(long double));
	// printf("%d", arraysize);
	while (i < arraysize - 1)
	{

		joined[i] = ptr1[i];
		i++;
	}
	joined[i] = ptr2;
	free(ptr1);
	return joined;
}

long double *gnl(int fd, int i, int *int_per_line)
{
	char *line_chars;
	long double *line;
	char buffer[1];

	line_chars = 0;
	line = 0;
	while (read(fd, buffer, 1) != 0)
	{
		if (strncmp("\n", buffer, 1) == 0)
			break;
		else
			line_chars = ft_strjoin2(line_chars, buffer);
	}
	if (line_chars == 0)
		return 0;
	while (line_chars[i] != 0)
	{
		// printf("%s\n", &line_chars[i]);
		// printf("%d\n", atoi(&line_chars[i]));
		*int_per_line += 1;
		line = ft_join_double_ptr(line, (long double)atoi(&line_chars[i]), *int_per_line);
		while (line_chars[i] == ' ')
			i++;
		while (line_chars[i] != ' ' && line_chars[i] != 0)
			i++;
	}
	free(line_chars);
	return line;
}

long double **loadmap(char *file, int **int_per_line, int *nr_line)
{
	int fd;
	long double **map;
	long double *line;
	int i;

	map = 0;
	fd = open(file, O_RDONLY);
	*nr_line = 1;
	line = gnl(fd, 0, &int_per_line[0][0]);

	i = 1;
	map = 0;
	while (line != 0)
	{
		*nr_line += 1;
		int_per_line[0] = count_ints(int_per_line[0], *nr_line);
		map = add_line(map, line);
		line = gnl(fd, 0, &int_per_line[0][i]);
		i++;
	}
	map = add_line(map, NULL);
	if (is_rectangular(int_per_line[0], *nr_line) != 0)
		return map;
	free_map(map);
	return 0;
}

long double **add_line(long double **map, long double *line)
{
	int i;
	long double **map_with_added_line;

	i = 0;
	if (map == 0)
	{
		map_with_added_line = malloc(sizeof(long double *));
		map_with_added_line[0] = line;
		line = 0;
		return map_with_added_line;
	}
	while (map[i] != 0)
		i++;
	map_with_added_line = malloc((i + 2) * sizeof(long double *));
	i = 0;
	while (map[i] != 0)
	{
		map_with_added_line[i] = map[i];
		map[i] = NULL;
		i++;
	}
	free(map[i]);
	free(map);
	map_with_added_line[i] = line;
	line = NULL;
	map_with_added_line[i + 1] = NULL;
	return (map_with_added_line);
}