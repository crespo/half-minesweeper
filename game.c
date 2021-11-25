/*
 *
 * Author: Raul Crespo
 * Create date: 27 november 2018
 * Description: simple minesweeper
 * Name: Half-Minesweeper
 * Link: https://snipsave.com/raulcrespo/#/snippet/z814n424l8m6QyKmxr
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

/*
    Variables
*/
int bomb_counter = 0, move_counter = 0, bombs_around = 0;
int i = 0, j = 0, k = 0, pos = 0;
int end_game = 0;
int r, x, y, grid = 5;
int taken_space[5][5]=
{
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0}
};
int blank_space[5][5] =
{
  {-1, -1, -1, -1, -1},
  {-1, -1, -1, -1, -1},
  {-1, -1, -1, -1, -1},
  {-1, -1, -1, -1, -1},
  {-1, -1, -1, -1, -1}
};
int bombs[5][5];

void spread_bombs(){
    /*
        Distribute the bombs in the matrix bombs, where 1 is bomb, 0 isnt
    */
    srand(time(NULL)); // Resets the time, doing real random generator and not pseudorandom number generator (PNRG)

    for(j = 0; j < grid; j++){
        for(i = 0; i < grid; i++){
            r = rand()%100;
            if (r > 40)
                bombs[i][j] = 0;
            else
                bombs[i][j] = 1;
        }
    }
}

void template(){
    printf("\n\n||||||||-template-||||||||\n");
    /*
        Reading the matrix
    */
    for(j = 0; j < grid; j++){
        for(k = 0; k < grid; k++)
            printf("     ");

        printf("\n ");

        for(i = 0; i < grid; i++){
            bombs_around = 0;
            if(bombs[i][j] == 0){
                y = i;
                x = j;
                count_bombs();
                printf(" <%d> ", bombs_around);
                bombs_around = 0;
            }
            else
                printf(" <*> ");
        }
        printf("\n");
    }
}

void update(){
    /*
        Read the entire minesweeper's matrix and shows the spaces chosen by the user
        If the user chooses a space where has bomb, the procedure ends the game
    */
    if(bombs[y][x] == 0){

        blank_space[y][x] = bombs_around;

        printf("x\n");
        /*
            Reading the matrix
        */
        for(j = 0; j < grid; j++){
            for(k = 0; k < grid; k++)
                printf("     ");

            printf("\n");

            printf("%d", j);

            for(i = 0; i < grid; i++){
                if(blank_space[i][j] != -1){
                    printf(" <%d> ", blank_space[i][j]);
                }
                else
                    printf(" < > ");
            }
            printf("\n");
        }
        linha_y();
        printf("\tBombs: %d", bomb_counter);
    }
    else{
        printf("x\n");
        /*
            Reading the matrix
        */
        for(j = 0; j < grid; j++){
            for(k = 0; k < grid; k++)
                printf("     ");

            printf("\n");

            printf("%d", j);

            for(i = 0; i < grid; i++){
                if(blank_space[i][j] != -1)
                    printf(" <%d> ", blank_space[i][j]);
                else
                    printf(" < > ");

                if(i == y && j == x){
                    printf("\b\b\b\b\b <*> ");
                    end_game = 1;
                }
            }
            printf("\n");
        }
        linha_y();
        printf("\tBombs: %d", bomb_counter);
        printf("\n\n\t\t\tYOU LOSE!!!");
    }
}

void count_bombs(){
    /*
        Accounting the quantity of bombs around the position user's selected
    */

    if(x != 0)
        if(bombs[y][x-1] == 1)
            bombs_around++;

    if(y != 0)
        if(bombs[y-1][x] == 1)
            bombs_around++;

    if(x!= grid-1)
        if(bombs[y][x+1] == 1)
            bombs_around++;

    if(y!= grid-1)
        if(bombs[y+1][x] == 1)
            bombs_around++;

    if(x != 0 && y!= grid-1)
        if(bombs[y+1][x-1] == 1)
            bombs_around++;

    if(x != 0 && y != 0)
        if(bombs[y-1][x-1] == 1)
            bombs_around++;

    if(x != grid-1 && y != grid-1)
        if(bombs[y+1][x+1] == 1)
            bombs_around++;

    if(x != grid-1 && y != 0)
        if(bombs[y-1][x+1] == 1)
            bombs_around++;
}

void linha_y(){
    /*
        Shows the positions of Y
    */
    printf("\n   ");

    for (j = 0; j < grid; j++)
        printf("%d    ", j);

    printf("\by\n\n");
}

void minesweeper(){
    spread_bombs();

    /*
        Account the quantity of bombs
    */
    for(j = 0; j < grid; j++){
        for(i = 0; i < grid; i++){
            if (bombs[j][i] == 1)
                bomb_counter++;
        }
    }

    /*
        Defines the game's grid
    */
    printf("x\n");
    for(j = 0; j < grid; j++){
        for(k = 0; k < grid; k++)
            printf("     ");

        printf("\n");

        printf("%d", j);

        for(i = 0; i < grid; i++){
            printf(" < > ");
        }
        printf("\n");
    }
    linha_y();
    printf("\tBombs: %d", bomb_counter);

    /*
        Game's loop
    */
    do{
        bombs_around = 0;

        /*
            Remove the comment below to show the template
        */
        //template();

        printf("\nType the line that you want to select (x): ");
        scanf("%d", &x);
        printf("\nType the column that you want to select (y): ");
        scanf("%d", &y);

        system("cls");

        count_bombs();

        update();

        if(taken_space[y][x] == 0)
            move_counter++;

        taken_space[y][x] = 1;

        if (move_counter == (25 - bomb_counter) && end_game == 0){
            printf("\n\n\t\t\tYOU WIN!!!");
            end_game = 1;
        }
    }
    while (end_game == 0);
    getch();
}

int main()
{
    setlocale(LC_ALL, "English");
    minesweeper();
}
