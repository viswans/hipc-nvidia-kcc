#include <stdio.h>
#include <kmeans.h>
#include <stdlib.h>

int main() {
    int no_of_events=0, no_of_points, i,j;
    //printf("No of events: ");
    scanf("%d",&no_of_events);

    float *point_store[no_of_events],k;
    int event_store[no_of_events];
    for(i=0; i<no_of_events; i++) {
        //printf("i: %d\n No of points: ",i);
        scanf("%d",&no_of_points);
        event_store[i] = no_of_points;
        printf("\n");
        point_store[i] = (float*)malloc((no_of_points*2) * sizeof(float));
        for(j=0; j<no_of_points*2; j++) {
            //printf("j: %d",j);
            scanf("%f",&k);     // Can be optimized.
            printf("\n");
            point_store[i][j] = k;
        }
        printf("\n");
    }


    for(i=0; i<no_of_events; i++) {
        kccalculate(i,event_store[i],point_store);
    }

    //printf("\n");
    //for(i=0; i<no_of_events; i++) {
    //  printf("Event %d: ",i);
    //  for(j=0; j<event_store[i]*2; j=j+2) {
    //      printf("Point: x-cord: %d  y-cord: %d",point_store[i][j],point_store[i][j+1]);
    //  }
    //}
    return 0;
}
