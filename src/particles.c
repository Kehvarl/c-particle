#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct simulation {
    int width;
    int height;
    char* world;
};

int tick(struct simulation *sim);

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
    sim.world = malloc(sizeof(char) * (width * height + 1));

    /* Read HEIGHT lines from STDIN with WIDTH chars per cell 
       Set initial simulation state */
    

    /* Tick the simulation state
       If the Tick returns no falling stones, the simulation is complete
       Otherwise repeat */
    do {
        tick_results = tick(&sim);
    } while(tick_results > 0);

    /* Call free on anything malloced */
    free(sim.world);
    
    return 0;
}

int tick(struct simulation *sim)
{
    return 0;
}