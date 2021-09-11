
#define MAX_ROCKS 2

#define MIN(a,b) (((a)<(b))?(a):(b))

struct simulation {
    int width;
    int height;
    int* world;
};

int tick(struct simulation *sim);
int print_world(struct simulation *sim);