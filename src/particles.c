#include <stdio.h>

struct simulation {
    int width;
    int height;
    char world[];
};

int main(void)
{
    /* Read first line from STDIN
       Looking for INT INT \n
       providing width, height*/

    /* Initialize simulation cells*/
    struct simulation sim;


    /* Read HEIGHT lines from STDIN with WIDTH chars per cell 
       Set initial simulation state */
    
    /*Tick the simulation state
      If the Tick returns no falling stones, the simulation is complete
      Otherwise repeat*/

    return 0
}

int tick(struct simulation sim)
{
    return 0;
}