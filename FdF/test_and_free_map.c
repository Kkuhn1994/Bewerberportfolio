#include "fdf.h"

int *count_ints(int *old_array, int nr_newline)
{
	int *newarray;
	int i;

	i = 0;
	newarray = malloc(nr_newline * sizeof(int));
	while (i < nr_newline - 1)
	{
		newarray[i] = old_array[i];
		i++;
	}
	newarray[i] = 0;
	free(old_array);
	return newarray;
}

int is_rectangular(int *int_per_line, int size)
{
	int i;
	int store;

	i = 1;
	store = int_per_line[0];
	while (i < size - 1)
	{
		if (int_per_line[i] != store)
			return 1;
		i++;
	}
	return 0;
}

void free_map(long double **map)
{
	int i;

	i = 0;
	if (map == 0)
		return;
	while (map[i] != 0)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void free_map2(matrix **map)
{
	int i;

	i = 0;
	if (map == 0)
		return;
	while (map[i] != 0)
	{
		free(map[i]);
		i++;
	}
	free(map);
}