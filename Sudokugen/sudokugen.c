#include "sudoku.h"

void ft_delete_numbers(int **grid, int n)
{
    int i;
    int j;
    int blocknumber;
    int blockdeletecount[9];
    int blockdelete[9];
    int linenumbercount[9];
    int columnnumbercount[9];
    int linedelecount[9];
    int columndeletecount[9];

    i = 0;
    j = 0;

    while (i < 9)
    {
        blockdelete[i] = 0;
        linenumbercount[i] = 0;
        columnnumbercount[i] = 0;
        linedelecount[i] = n;
        columndeletecount[i] = n;
        blockdeletecount[i] = n;
        i++;
    }
    i = 0;

    while (i < 9)
    {
        while (j < 9)
        {
            blocknumber = i / 3 * 3 + j / 3;

            if (2 * zufallszahl_1_bis_9() - blockdeletecount[blocknumber] - linenumbercount[i] - columnnumbercount[j] <= 2 * n - linedelecount[i] - columndeletecount[j] && blockdeletecount[blocknumber] > 0)
            {
                grid[i][j] = 0;
                blockdeletecount[blocknumber] = blockdeletecount[blocknumber] - 1;
            }
            else
            {
                linenumbercount[i] = linenumbercount[i] + 1;
                columnnumbercount[j] = columnnumbercount[j] + 1;
            }
            j++;
        }
        j = 0;
        i++;
    }
}

void ft_fillemptygrid(int **grid)
{
    int i;
    int j;

    i = 0;
    j = 0;

    while (i < 9)
    {
        while (j < 9)
        {
            grid[i][j] = 0;
            j++;
        }
        j = 0;
        i++;
    }
    i = 0;
    j = 0;
}

int ft_numbercheck(int **grid, int x, int y, int z, int Blocknumbervalue)
{
    int x0 = 0;
    int y0 = 0;
    int blocknumber;

    if (z < 1)
        return 1;

    if (z > 9)
        return 1;

    while (x0 < 9)
    {
        if (grid[x0][y] == z && x0 != x)
            return 1;
        x0++;
    }
    while (y0 < 9)
    {
        if (grid[x][y0] == z && y0 != y)
            return 1;
        y0++;
    }
    x0 = 0;
    y0 = 0;
    while (x0 < 9)
    {
        while (y0 < 9)
        {
            blocknumber = x0 / 3 + y0 / 3 * 5;
            if (grid[x0][y0] == z && blocknumber == Blocknumbervalue)
                return 1;
            y0++;
        }
        y0 = 0;
        x0++;
    }
    return 0;
}

int ft_fillgridnumber(int **grid)
{
    int i = 0;
    int j = 0;
    int z[2][1];

    z[0][0] = zufallszahl_1_bis_9();

    while (i < 9)
    {
        while (j < 9)
        {
            z[1][0] = i / 3 + j / 3 * 5;
            while (ft_numbercheck(grid, i, j, z[0][0], z[1][0]) != 0 && ft_numbercheck(grid, i, j, (z[0][0] - 9), z[1][0]) != 0)
            {
                if (z[0][0] == 18)
                    return 1;
                if (ft_numbercheck(grid, i, j, (z[0][0] - 9), z[1][0]) == 0 && z[0][0] > 9)
                    return 1;
                z[0][0]++;
            }

            if (z[0][0] < 10)
                grid[i][j] = z[0][0];
            else
                grid[i][j] = z[0][0] - 9;
            z[0][0] = zufallszahl_1_bis_9();
            j++;
        }
        j = 0;
        i++;
    }
    return 0;
}