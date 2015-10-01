#include <stdio.h>
#include <kmeans.h>
#include <stdlib.h>

// TODO:
// 1. Add code for finding out number of circles
// given an event
// 2. Add timer code to benchmark code
int main(int argc, const char *argv[])
{
    unsigned int no_of_events = 0, no_of_points, i, j;
    scanf("%d", &no_of_events);
    fprintf(stderr, "DEBUG: No of events: %d", no_of_events);

    float xcoord, ycoord;
    Event events[no_of_events];

    for(i = 0; i < no_of_events ; ++i ) {
        fprintf(stderr, "i: %d\n No of points: ",i);
        scanf("%d", &no_of_points);
        events[i].no_of_points = no_of_points;
        events[i].points = ( Point* ) malloc(
                no_of_points * sizeof(Point) );

        for(j = 0; j < no_of_points; j++) {
            float xcoord, ycoord;
            scanf("%f %f", &xcoord, &ycoord);     // Can be optimized.
            events[i].points[j].xcoord = xcoord;
            events[i].points[j].xcoord = xcoord;
        }
        fprintf(stderr, "DEBUG: \n");
    }


    // hard code to 5 right now
    // TODO: improve algorithm here
    int num_circles = 5;
    for(i = 0; i < no_of_events ; ++i)
    {
        EventResult r = kccalculate( &(events[i]), num_circles );
    }
    return 0;
}
