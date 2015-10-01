#ifndef __KMEANS_ALGORITHM_
#define __KMEANS_ALGORITHM_

#define DEF(T) typedef struct T T

struct Point {
    float xcoord, ycoord;
};
DEF(Point);

// pass by value or pass by reference ?
float distance( Point p1, Point p2 );

struct Circle {
    // not choosing a pointer for center
    // because Point seems light enough
    Point center;
    float radius;
};
DEF(Circle);

struct EventResult {
    int num_circles;
    Circle *circles;
};
DEF(EventResult);

// Each event consists of an array of points
// no_of_points contains number of points for this event
// Should EventResult be here?
struct Event {
    int no_of_points;
    Point* points;
    EventResult* result;
};
DEF(Event);

EventResult kccalculate( Event* e, int num_clusters );

#undef DEF
#endif
