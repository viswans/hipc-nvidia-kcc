#include <stdio.h>
//TODO: Lets try to avoid heavy math operations directly from math.h
//They would tend to slow down the simulation
#include <math.h>
#include <stdlib.h>
#include <kmeans.h>

//TODO: It is assigned to a float/double
//We can use the standard FLT_MAX / FLT_MIN
const float INFTY = 9999999.0;

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

    fprintf(stderr, "DEBUG: KCC for %d points - Looking for %d circles\n",
            npoints, num_clusters);

    Point subset[event->no_of_points];
    // is a memcpy required here?
    for(i = 0 ; i < npoints; ++i )
        subset[i] = event->points[i];

    /* Picking up the first five points as the cluster representatives.
     * Implementing first iteration of k-means.
     */

    // TODO: why suddenly double here??
    double error =0.0, minerror;
    int id = 0; // id to for clasifying and finding bins
    int bin[npoints]; // bin[i] - bin# in which i is placed
    for(i = 0; i < npoints; ++i)
    {
        minerror = INFTY;
        for(j=0; j < num_clusters; ++j) {
            // calculate distance between pt i and pt j
            error = fabs( distance( subset[i], subset[j] ) );
            if( error < minerror ) {
                minerror = error;
                id = j;
            }
        }
        bin[i] = id;            // Appropriate bin for the point.
        fprintf( stderr, "DEBUG: Point %d => Bin %d Error %f\n",
                i, bin[i], minerror );
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
            res.circles[i].radius = 0;
        }

        for( i = 0; i < npoints; ++i )
        {
            total_points[ bin[i] ]++;
            res.circles[bin[i]].center.xcoord += subset[i].xcoord;
            res.circles[bin[i]].center.ycoord += subset[i].ycoord;
        }

        for( i = 0; i < num_clusters; ++i )
        {
            if( total_points[i] != 0 ) {
            res.circles[i].center.xcoord /= total_points[i];
            res.circles[i].center.ycoord /= total_points[i];
            // radius comptuation would be just a mean of
            // distance from centers to all the points
            // caveat being that this might not work for
            // situations when there are 2 concentric circles
            }
        }

        for( i = 0; i < npoints; ++i ) {
            Point* center = &(res.circles[i].center);
            double d = distance( *(center), subset[i]);
            res.circles[bin[i]].radius += d * d;
        }

        for(i = 0; i < num_clusters; ++i )
        {
            // TODO : Check for division by 0
            if( total_points[i] != 0 )
            res.circles[i].radius /= total_points[i];
            res.circles[i].radius = sqrt(res.circles[i].radius);
        }

        // Redistribution of points using new cluster centers.
        for( i = 0; i < npoints; ++i )
        {
            minerror = INFTY;
            for(j = 0; j< num_clusters ; ++j) {
                error = fabs( distance( subset[i], res.circles[j].center)
                        - res.circles[j].radius );     // Distance function calculation.
                if( error < minerror ) {
                    minerror = error;
                    id = j;
                }
            }
            bin[i] = id;            // Appropriate bin for the point.
            fprintf( stderr, "DEBUG: Point %d => Bin %d Error %f\n",
                    i, bin[i], minerror );
        }

        for( i = 0; i < num_clusters; ++i) {
            fprintf( stderr, "DEBUG: %d bin => %d points\n", i, total_points[i]);
            fprintf( stderr, "DEBUG: Circle: %.4f, %.4f, %.4f\n",
                    res.circles[i].center.xcoord, res.circles[i].center.ycoord,
                    res.circles[i].radius );
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

