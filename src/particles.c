#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ROCKS 2;

struct simulation {
    int width;
    int height;
    int* world;
};

int tick(struct simulation *sim);
int print_world(struct simulation *sim);

int main(void)
{
    struct simulation sim;
    int tick_results = 0;

    char *line = NULL;
    size_t size;
    char *ptr;
    char *search = "    \n";
    int width, height;

    /* Read first line from STDIN
       Tokenize on whitespace:
       Looking for INT INT providing width, height
       Use strtol to convert string numbers to ints */

    if(getline(&line, &size, stdin) == -1){
        printf("No initial Line Provided.");
    } else {
        width = strtol(strtok(line, search), &ptr, 10);
        height = strtol(strtok(NULL, search), &ptr, 10);
        printf("%d  %d\n", width, height);
    }

    /* Initialize simulation cells*/
    sim.width = width;
    sim.height = height;
    sim.world = malloc(sizeof(int) * (width * height + 1));

    /* Read HEIGHT lines from STDIN with WIDTH chars per cell 
       Set initial simulation state 
       
       Cell Contents Representation:
       * "T": -1
       * " ":  0
       * ".":  1
       * ":":  2
    */

   for(int r = 0; r < sim.height; l++){
       getline(&line, &size, stdin);
       for(int c = 0; c < sim.width; c++){
           if(strcmp(line[c], " ") == 0){
               sim.world[r*c] = 0;
           }else if(strcmp(line[c], ".") == 0){
               sim.world[r*c] = 1;
           }else if(strcmp(line[c], ":") == 0){
               sim.world[r*c] = 2;
           }else if(strcmp(line[c], "T") == 0){
               sim.world[r*c] = -1;
           }
       }
   }
    

    /* Tick the simulation state
       If the Tick returns no falling stones, the simulation is complete
       Otherwise repeat */
    do {
        tick_results = tick(&sim);
    } while(tick_results > 0);

    print_world(&sim);

    /* Call free on anything malloced */
    free(sim.world);

    return 0;
}

int tick(struct simulation *sim)
{
    char *temp = malloc(sizeof(int) * (sim->width * sim->height + 1));

    for(int row=0; row < sim->height; row++){
        for(int col=0; col < sim->width; col++){
            /* Current cell: sim->world[r*c]
               Target cell:  sim->world[r*c+sim->width]
               If Current Cell is 0 or -1 or Target Cell is -1: skip
               else: Move rocks from Current to Target 
                     until Target is at MAX or Current is at 0
               */
        }
    }

    free(temp);
    return 0;
}

int print_world(struct simulation *sim)
{
    for(int row=0; row < sim->height; row++){
        for(int col=0; col < sim->width; col++){
            if(sim->world[row*col] == -1){
                printf("T");
            } else if(sim->world[row*col] == 0){
                printf(" ");
            } else if(sim->world[row*col] == 1){
                printf(".");
            } else if(sim->world[row*col] == 2){
                printf(":");
            }

        }
        printf("\n");
    }
    return 0;
}