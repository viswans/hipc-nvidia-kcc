#include <stdio.h>
//TODO: Lets try to avoid heavy math operations directly from math.h
//They would tend to slow down the simulation
#include <math.h>
#include <stdlib.h>
#include <kmeans.h>

// some high integer
//TODO: It is assigned to a float/double
//We can use the standard FLT_MAX / FLT_MIN
const int INFTY = 9999999;

/* should return an EventResult */
/* or even possibly a success or failure */
/* and fill up the eventResult within event */

/* kcccalculate takes as an argument the
 * _event_ for which circle classification
 * needs to be done and returns an EventResult
 * _k_ is the number of circles that are
 * expected as an output
 */

EventResult kccalculate( Event* event, int num_clusters )
{
    int i, j = 0, npoints = event->no_of_points;

    /* Initialize data structures */
    EventResult res;
    res.num_circles = num_clusters;
    res.circles = ( Circle* ) malloc(
            sizeof(Circle) * num_clusters );

    Point subset[event->no_of_points];
    for(i=0; i < npoints; ++i)
        subset[i] = event->points[i];

    /* Picking up the first five points as the cluster representatives.
     * Implementing first iteration of k-means.
     */

    // TODO: why suddenly double here??
    double dist=0.0, mindist,x,y;
    int id; // id to for clasifying and finding bins
    int bin[npoints]; // bin[i] - bin# in which i is placed
    for(i = 5; i < npoints; ++i)
    {
        mindist = INFTY;
        for(j=0; j<5; j++) {
            // calculate distance between pt i and pt j
            dist = distance( subset[i], subset[j] );
            if(dist < mindist) {
                mindist = dist;
                id = j;
            }
        }
        bin[i] = id;            // Appropriate bin for the point.
    }

    while(1)
    {
        /*
         * Getting the new cluster centers.
         */
        int total_points[num_clusters];
        for( i = 0; i < num_clusters; ++i )
        {
            total_points[i] = 0;
            res.circles[i].center.xcoord = 0;
            res.circles[i].center.ycoord = 0;
        }

        for( i = 0; i < npoints; ++i )
        {
            total_points[ bin[i] ]++;
            res.circles[i].center.xcoord += subset[i].xcoord;
            res.circles[i].center.ycoord += subset[i].ycoord;
        }

        for( i = 0; i < num_clusters; ++i )
        {
            res.circles[i].center.xcoord /= total_points[i];
            res.circles[i].center.ycoord /= total_points[i];
            // TODO: find radius of circle i as well here
        }

        // Redistribution of points using new cluster centers.
        for( i = 0; i < npoints; ++i )
        {
            mindist = INFTY;
            for(j = 0; j< num_clusters ; ++j) {
                dist = distance( subset[i], res.circles[j].center);     // Distance function calculation.
                if(dist < mindist) {
                    mindist = dist;
                    id = j;
                }
            }
            bin[i] = id;            // Appropriate bin for the point.
        }

        // TODO: Need a terminating condition.
        // Calculate error as distance - radius^2
        // and sum it. If that is less than tolerance
        // break the loop

        // TODO: Loop code is large
        // tough to verify correctness
        // split into smaller bits - will help parallelizing
        // as well
     }
    return res;
}

