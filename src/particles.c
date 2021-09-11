#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/******************************************************
 * Particles.C
 * Implementation of a simple Falling-Rocks simulation
 * Expects input on STDIN
 *   First line: 2 Space-separated INTS indicating
 *   Width and Height of the plane
 * 
 *   <Height> Lines of <Width> chars displaying the
 *   Initial world state
 * 
 *   State Chars are:
 *     ' ' - No rock
 *     '.' - 1 rock
 *     ':' - 2 rocks
 *     'T' - Table (fixed in space)
 *****************************************************/

#define MAX_ROCKS 2

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
   for(int row = 0; row < sim.height; row++){
       getline(&line, &size, stdin);
       for(int col = 0; col < sim.width; col++){
           if(line[col] == ' '){
               sim.world[row*sim.width+col] = 0;
           }else if(line[col] == '.'){
               sim.world[row*sim.width+col] = 1;
           }else if(line[col] == ':'){
               sim.world[row*sim.width+col] = 2;
           }else if(line[col] == 'T'){
               sim.world[row*sim.width+col] = -1;
           }else{
               printf("%c doesn't match any allowed character for %dx%d\n", line[col], row, col);
               sim.world[row*sim.width+col] = 0;
           }
       }
   }
    

    /* Tick the simulation state
       If the Tick returns no falling stones, the simulation is complete
       Otherwise repeat */
    do {
        tick_results = tick(&sim);
        print_world(&sim);
    } while(tick_results > 0);

    print_world(&sim);

    /* Call free on anything malloced */
    free(sim.world);

    return 0;
}

int tick(struct simulation *sim)
{
    int *temp = malloc(sizeof(sim->world)+1);
    memcpy(temp, sim->world, sizeof(sim->world)+1);

    int current=0, target=0, fall=0;

    for(int row=0; row < sim->height-1; row++){
        for(int col=0; col < sim->width; col++){
            /* Current cell: sim->world[r*c]
               Target cell:  sim->world[r*c+sim->width]
               If Current Cell is 0 or -1 or Target Cell is -1: skip
               else: Move rocks from Current to Target 
                     until Target is at MAX or Current is at 0
            */
            current = sim->world[row*sim->width+col];
            target = temp[row*sim->width+col+sim->width];
            if(current > 0){
                if((target > -1) && (target <= MAX_ROCKS)){
                    fall = max(current, current - (MAX_ROCKS - target));
                    current = current - fall;
                    target = target + fall;

                    temp[row*sim->width+col] = current;
                    temp[row*sim->width+col+sim->width] = current;
                }
            }
        }
    }

    memcpy(sim->world, temp,sizeof(sim->world)+1);
    free(temp);
    return 0;
}

int print_world(struct simulation *sim)
{
    printf("---------\n");
    for(int row=0; row < sim->height; row++){
        for(int col=0; col < sim->width; col++){
            if(sim->world[row*sim->width+col] == -1){
                printf("T");
            } else if(sim->world[row*sim->width+col] == 0){
                printf(" ");
            } else if(sim->world[row*sim->width+col] == 1){
                printf(".");
            } else if(sim->world[row*sim->width+col] == 2){
                printf(":");
            }
        }
        printf("\n");
    }
    printf("\n\n");
    return 0;
}