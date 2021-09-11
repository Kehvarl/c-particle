#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <getopt.h>
#include "particles.h"

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


int main( int argc, char *argv[]) {
    int opt;
    int i=0, t=0, p=0; 
    const char *short_opt = "hitp";
    struct option long_opt[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"input", no_argument, NULL, 'i'},
        {"tick", no_argument, NULL, 't'},
        {"pretty", no_argument, NULL, 'p'}
    };

    while ((opt = getopt_long (argc, argv, short_opt, long_opt, NULL)) != -1){
        switch(opt)
        {
            case -1: /*No remaining args*/
            case 0: /* long options */
            break;

            case 'p':
            p = 1;
            break;

            case 't':
            t = 1;
            break;

            case 'i':
            i = 1;
            break;

            case 'h':
            printf("Usage: %s [OPTIONS]\n", argv[0]);
            printf("  -i --init                 print the initial state\n");
            printf("  -t --tick                 print each intermediary state\n");
            printf("  -p --pretty               Use \"pretty print\" to make output more human readable\n");
            printf("  -h, --help                print this help and exit\n");
            printf("\n");
            return(0);

            case ':':
            case '?':
            fprintf(stderr, "Try `%s --help' for more information.\n", argv[0]);
            return(-2);

            default:
            fprintf(stderr, "%s: invalid option -- %c\n", argv[0], opt);
            fprintf(stderr, "Try `%s --help' for more information.\n", argv[0]);
            return(-2);
        }
    }
    return simulate(i, t, p);
}

/*simulate -- process our simulated world
* print_input: Display our initial state on STDOUT
* print_ticks: Display intermediate states on STDOUT
* pretty:      Add additional formatting to printed output
*/
int simulate(int print_input, int print_ticks, int pretty)
{
    struct simulation sim;
    int tick_results = 0;

    /*Load input from STDIN*/
    if(get_input(&sim) != 0){
        return -1;
    }

   if(print_input == 1){
       print_world(&sim, pretty);       
   }   

    /* Tick the simulation state
       If the Tick returns no falling stones, the simulation is complete
       Otherwise repeat */
    do {
        tick_results = tick(&sim);
        if(print_ticks == 1){
            print_world(&sim, pretty);
        }
    } while(tick_results > 0);

    /*Output*/
    print_world(&sim, pretty);

    /* Call free on anything malloced */
    free(sim.world);

    return 0;
}

int get_input(struct simulation *sim)
{
    char *line = NULL;
    size_t size;
    char *ptr;
    char *search = "    \n";
    char *token;
    int width, height;

    /* Read first line from STDIN
       Tokenize on whitespace:
       Looking for INT INT providing width, height
       Use strtol to convert string numbers to ints */

    if(getline(&line, &size, stdin) == -1){
        printf("No initial Line Provided.");
    } else {
        token = strtok(line, search);
        if(token == NULL)
        {
            printf("Unable to read WIDTH parameter\n");
            return -1;
        }else{
            errno = 0;
            width = strtol(token, &ptr, 10);
            if(ptr == token){
                printf("No numeric WIDTH Provided\n");
                return -1;   
            }
            else if(errno != 0){
                printf("Problem understanding WIDTH parameter\n");
                return -1;   
            }

        }
        
        token = strtok(NULL, search);
        if(token == NULL)
        {
            printf("Unable to read HEIGHT parameter\n");
            return -1;
        }else{
            errno = 0;
            height = strtol(token, &ptr, 10);
            if(ptr == token){
                printf("No numeric HEIGHT Provided\n");
                return -1;   
            }
            else if(errno != 0){
                printf("Problem understanding HEIGHT parameter\n");
                return -1;   
            }
        }
    }

    /* Initialize simulation cells*/
    sim->width = width;
    sim->height = height;
    sim->world = malloc(sizeof(int) * (width * height + 1));

    /* Read HEIGHT lines from STDIN with WIDTH chars per cell 
       Set initial simulation state 
    */
   for(int row = 0; row < sim->height; row++){
       getline(&line, &size, stdin);
       for(int col = 0; col < sim->width; col++){
           if(line[col] == ' '){
               sim->world[row*sim->width+col] = 0;
           }else if(line[col] == '.'){
               sim->world[row*sim->width+col] = 1;
           }else if(line[col] == ':'){
               sim->world[row*sim->width+col] = 2;
           }else if(line[col] == 'T'){
               sim->world[row*sim->width+col] = -1;
           }else{
               printf("%c doesn't match any allowed character for %dx%d\n", line[col], row, col);
               sim->world[row*sim->width+col] = 0;
           }
       }
   }

   return 0;
}

int tick(struct simulation *sim)
{
    int result = 0;
    int *temp = malloc(sizeof(int)*(sim->height*sim->width)+1);
    memcpy(temp, sim->world, sizeof(int)*(sim->height*sim->width)+1);

    int current=0, target=0, fall=0;

    for(int row=0; row < sim->height-1; row++){
        for(int col=0; col < sim->width; col++){
            /* Current cell: sim->world[r*c]
               Target cell:  sim->world[r*c+sim->width]
               If Current Cell is 0 or -1 or Target Cell is -1: skip
               else: Move rocks from Current to Target 
                     until Target is at MAX or Current is at 0
            */
            current = temp[row*sim->width+col];
            target = temp[row*sim->width+col+sim->width];
            if(current > 0){
                if((target > -1) && (target < MAX_ROCKS)){

                    fall = MIN(current, (MAX_ROCKS - target));
                    current = current - fall;
                    target = target + fall;

                    temp[row*sim->width+col] = current;
                    temp[row*sim->width+col+sim->width] = target;
                }
            }
        }
    }

    result = memcmp(sim->world, temp, sizeof(int)*(sim->height*sim->width)+1);

    memcpy(sim->world, temp, sizeof(int)*(sim->height*sim->width)+1);
    free(temp);
    return result;
}

int print_world(struct simulation *sim, int pretty)
{
    
    if(pretty == 1) {
        printf("---------\n");
    }
    for(int row=0; row < sim->height; row++){
        if(pretty == 1) {
            printf("|");
        }
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
    return 0;
}