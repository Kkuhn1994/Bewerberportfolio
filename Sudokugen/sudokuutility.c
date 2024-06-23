#include "sudoku.h"

int zufallszahl_1_bis_9()
{
    // Zufallszahlengenerator initialisieren

    // Zufallszahl zwischen 1 und 4 erzeugen und zurückgeben
    return (rand() % 9) + 1;
}

int ft_solution_compare(int **matrix1, int **matrix2)
{
    int i = 0;
    int j = 0;

    while (i < 9)
    {
        while (j < 9)
        {
            if (matrix1[i][j] != matrix2[i][j])
                return 1;
            j++;
        }
        j = 0;
        i++;
    }
    return 0;
}

void ft_save(int **matrix, int **solution)
{
    int i = 0;
    int j = 0;

    while (i < 9)
    {
        while (j < 9)
        {
            solution[i][j] = matrix[i][j];
            j++;
        }
        j = 0;
        i++;
    }
}

int sizetest(int **matrix)
{
    int i = 0;
    int j = 0;

    while (i < 9)
    {
        while (j < 9)
        {
            if (matrix[i][j] > 9 || matrix[i][j] == 0)
                return 1;
            j++;
        }
        j = 0;
        i++;
    }
    return 0;
}

void ft_print(int **matrix)
{
    int i = 0;
    int j = 0;

    while (i < 9)
    {
        while (j < 9)
        {
            printf("%d ", matrix[i][j]);
            j++;
        }
        printf("\n");
        j = 0;
        i++;
    }
}