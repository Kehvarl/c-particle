
#define MAX_ROCKS 2
/*#define DEBUG 1*/

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

struct simulation {
    int width;
    int height;
    int* world;
};

int main(int argc, char * argv[]);
int simulate(int print_input, int print_ticks, int pretty);
int get_input(struct simulation *sim);
int tick(struct simulation *sim);
int print_world(struct simulation *sim, int pretty);