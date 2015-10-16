/*Author: Lucas Joyal
 *Date: 2015-10-15
 *
 * Project: Terminal based conway's game of life
 * */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define WORLDLENGTH 60 // The universe size
#define LIVE 35
#define DEAD 32

typedef struct universe_struct{
    char cell[WORLDLENGTH][WORLDLENGTH];
} universe;


void update_universe(universe *);
void create_universe(universe *);
void show_universe(universe *);


universe temp;
int main()
{

    printf("Starting program...\n");
    universe u;
    printf("Creating universe...\n");
    create_universe(&u);
    while(1){
        
        printf("Updating universe...\n");
        show_universe(&u);
        update_universe(&u);
        printf("Going to sleep\n");
        usleep(50 * 1000);


    }

    return 0;

}

void create_universe(universe *u)
{
    int i, j;
    srand(10);
    for(i = 0; i < WORLDLENGTH; ++i){
        for(j = 0; j < WORLDLENGTH; ++j){
 // black square or a space
            u->cell[i][j] = (rand() % 2 ? (char)LIVE : (char)DEAD);
        }
    }     
}

void show_universe(universe *u)
{
    int i,j;
    for(i = 0;i < WORLDLENGTH; ++i){

        for(j = 0;j < WORLDLENGTH; ++j)
            printf("%c", (u->cell[i][j]));
        printf("\n");
    }
}
/*Standard rule is if a cell has less than 3 live neighbour, it dies*/
char check_cell(universe *u, int x, int y)
{
    int live_count = 0;
    int i,j;
    for (i = x-1; i <= x+1; ++i)
    {
        for(j = (y-1); j <= y+1; ++j)
        {
            if(x == i && y == j) continue; // ignore own cell
            if(!(0 < i || i < WORLDLENGTH || 0 < y || y < WORLDLENGTH)) continue;
            live_count += (u->cell[i][j] == LIVE ? 1 : 0);
        }
    }
    //printf("cell %d %d is %s\n", x,y, (u->cell[x][y] == LIVE ? "alive" : "dead"));
    if((u->cell[x][y] == LIVE && live_count < 2) ||
    (u->cell[x][y] == LIVE && live_count > 3))
        return DEAD;
    else if(u->cell[x][y] == LIVE)
        return LIVE;
    else if(u->cell[x][y] == DEAD && live_count == 3)
        return LIVE;
    else
        return DEAD;
        
}
void update_universe(universe *u)
{
    // update each cell
    int i,j;
    
    for(i = 0; i < WORLDLENGTH; ++i){
        for(j = 0; j < WORLDLENGTH; ++j){
 // black square or a space
            temp.cell[i][j] = check_cell(u, i,j);

        }
    } 
    *u = temp;
}
