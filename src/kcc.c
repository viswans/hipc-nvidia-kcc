#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <kmeans.h>

int kccalculate(int event, int npoints, float *points[]) {
    int i,j=0;
    float subset[npoints][2];
    for(i=0; i<npoints*2; i+=2) {
        subset[j][0] = points[event][i];
        subset[j][1] = points[event][i+1];
        j++;
    }

    /* Picking up the first five points as the cluster representatives.
     * Implementing first iteration of k-means.
     */
    int bins[5][npoints],id;
    double dist=0.0, mindist,x,y;
    for(i=5; i<npoints; i++) {
        mindist=9999999;
        for(j=0; j<5; j++) {
            x = pow((subset[j][0]-subset[i][0]),2);
            y = pow((subset[j][1]-subset[i][1]),2);
            dist = sqrt((x+y));     // Distance function calculation.
            if(dist < mindist) {
                dist = mindist;
                id = j;
            }
        }
        bins[id][i] = 1;            // Appropriate bin for the point.
    }

    while(1) {
        /* Getting the new cluster centers.
        */
        double cluster_centers[5][2];
        for(i=0; i<5; i++) {
            dist = 0; x=0; y=0;
            for(j=0; j<npoints; j++) {
                if(bins[i][j] == 1) {
                    x += subset[j][0];
                    y += subset[j][1];
                    dist++;
                }
            }
            cluster_centers[i][0] = x/dist;
            cluster_centers[i][1] = y/dist;
        }

        // Redistribution of points using new cluster centers.
        for(i=0; i<npoints; i++) {
            mindist = 9999999;
            for(j=0; j<5; j++) {
                x = pow((cluster_centers[j][0]-subset[i][0]),2);
                y = pow((cluster_centers[j][1]-subset[i][1]),2);
                dist = sqrt((x+y));     // Distance function calculation.
                if(dist < mindist) {
                    dist = mindist;
                    id = j;
                }
            }
            bins[id][i] = 1;            // Appropriate bin for the point.
        }

        // Need a terminating condition.
    }


    return 0;
}



