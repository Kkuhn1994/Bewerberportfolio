#include "sudoku.h"
#include <stdio.h>

int failednumbercontrol(int *fail, int n)
{
    int i = 0;

    while (i < 9)
    {
        if (fail[i] == n)
            return 1;
    }
    return 0;
}

int ft_solve(int **grid)
{
    int z[2][1];
    int i = 0;
    int j = 0;
    int fail[9];
    int c = 0;

    z[0][0] = 1;
    // while(c < 9)
    // {
    //     fail[c] = -1;
    //     c ++;
    // }
    // c = 0;

    while (sizetest(grid) == 1)
    {

        while (grid[i][j] != 0)
        {
            j++;

            if (j == 9)
            {
                i++;
                j = 0;
            }
        }
        // printf("%d", ft_numbercheck(grid, i, j, z[0][0], z[1][0]));
        //     printf("\n");

        z[1][0] = i / 3 + j / 3 * 5;
        while (sizetest(grid) == 1)
        {
            while (ft_numbercheck(grid, i, j, z[0][0], z[1][0]) == 1 && z[0][0] < 10)
                z[0][0]++;

            if (z[0][0] == 10)
            {

                return 1;
            }

            if (z[0][0] <= 9)
                grid[i][j] = z[0][0];
            if (ft_solve(grid) == 1)
            {
                grid[i][j] = 0;

                z[0][0]++;
            }
        }
    }

    return 0;
}

int ft_solve_downwards(int **grid)
{
    int z[2][1];
    int i = 0;
    int j = 0;
    int fail[9];
    int c = 0;

    z[0][0] = 9;
    // while(c < 9)
    // {
    //     fail[c] = -1;
    //     c ++;
    // }
    // c = 0;

    while (sizetest(grid) == 1)
    {

        while (grid[i][j] != 0)
        {
            j++;

            if (j == 9)
            {
                i++;
                j = 0;
            }
        }
        // printf("%d", ft_numbercheck(grid, i, j, z[0][0], z[1][0]));
        //     printf("\n");

        z[1][0] = i / 3 + j / 3 * 5; // blockzahl
        while (sizetest(grid) == 1)
        {
            while (ft_numbercheck(grid, i, j, z[0][0], z[1][0]) == 1 && z[0][0] > 0)
                z[0][0]--;

            if (z[0][0] == 0)
            {

                return 1;
            }

            if (z[0][0] >= 1)
                grid[i][j] = z[0][0];
            if (ft_solve_downwards(grid) == 1)
            {
                grid[i][j] = 0;

                z[0][0]--;
            }
        }
    }

    return 0;
}
