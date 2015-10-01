
#include <kmeans.h>
/* utils.c - contains some utility functions needed
 * to do computations for kmeans */

float distance( Point p1, Point p2 )
{
    float xdiff = p1.xcoord - p2.xcoord;
    float ydiff = p1.ycoord - p2.ycoord;
    return xdiff * xdiff + ydiff * ydiff;
}