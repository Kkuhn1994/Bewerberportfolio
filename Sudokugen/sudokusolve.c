#include "sudoku.h"

int ft_solve_grid(int **grid)
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
            while (ft_numbercheck(grid, i, j, z[0][0], z[1][0]) != 0 && ft_numbercheck(grid, i, j, (z[0][0] - 9), z[1][0]) != 0 && grid[i][j] == 0)
            {
                if (z[0][0] == 18)
                    return 1;
                if (ft_numbercheck(grid, i, j, (z[0][0] - 9), z[1][0]) == 0 && z[0][0] > 9 && grid[i][j] == 0)
                    return 1;
                z[0][0]++;
            }

            if (z[0][0] < 10 && grid[i][j] == 0)
                grid[i][j] = z[0][0];
            else if (grid[i][j] == 0)
                grid[i][j] = z[0][0] - 9;
            z[0][0] = zufallszahl_1_bis_9();
            j++;
        }
        j = 0;
        i++;
    }
    return 0;
}

// void    ft_delete_numbers(int **grid,int n)
// {
//     int i;
//     int j;
//     int blocknumber;
//     int blockdeletecount[9];
//     int blockdelete[9];
//     int linenumbercount[9];
//     int columnnumbercount[9];
//     int linedelecount[9];
//     int columndeletecount[9];

//     i = 0;
//     j = 0;

//     while(i < 9)
//     {
//         blockdelete[i] = 0;
//         linenumbercount[i] = 0;
//         columnnumbercount[i] = 0;
//         linedelecount[i] = n;
//         columndeletecount[i] = n;
//         blockdeletecount[i] = n;
//         i ++;
//     }
//     i = 0;

//     while(i < 9)
//     {
//         while(j < 9)
//         {
//             blocknumber = i / 3 * 3 + j / 3 ;

//             if(2 * zufallszahl_1_bis_9() - blockdeletecount[blocknumber] - linenumbercount[i] -  columnnumbercount[j] <= 2 * n - linedelecount[i] - columndeletecount[j]
//             && blockdeletecount[blocknumber] > 0)
//             {
//             grid[i][j] = 0;
//             blockdeletecount[blocknumber] = blockdeletecount[blocknumber] - 1;
//             }
//             else
//             {
//                 linenumbercount[i] = linenumbercount[i] + 1;
//                 columnnumbercount[j] = columnnumbercount[j] + 1;
//             }
//             j ++;
//         }
//         j = 0;
//         i ++;
//     }
// }
