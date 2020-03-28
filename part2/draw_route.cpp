#include "draw_route.h"
#include "map_drawing.h"

extern shared_vars shared;
/*
    This function draws the route found and communicated between the client and server
    It displays the route on the arduino
    Inputs: NONE
    Outputs: NONE
*/

void draw_route()
{

    // Case where there are no waypoints
    if(shared.num_waypoints == 0)
    {
        status_message("Unable to find route");
        delay(1000);
    }
    // Iterating through each waypoint in the shared variable
    for(int i = 1; i < shared.num_waypoints; i++)
    {

        // Storing the two points to draw a line between
        lon_lat_32 first = shared.waypoints[i - 1];
        lon_lat_32 second = shared.waypoints[i];

        // Converting points to x/y
        int32_t x0 = longitude_to_x(shared.map_number, first.lon);
        int32_t y0 = latitude_to_y(shared.map_number, first.lat);
        int32_t x1 = longitude_to_x(shared.map_number, second.lon);
        int32_t y1 = latitude_to_y(shared.map_number, second.lat);

        // Finding the orientation of the screen in terms of the map
        xy_pos offset = shared.map_coords;

        // Altering points in accordance with the offset
        x0 -= offset.x;
        y0 -= offset.y;
        x1 -= offset.x;
        y1 -= offset.y;

        // Displaying route
        shared.tft->drawLine(x0, y0, x1, y1, TFT_BLUE);



    }
    status_message("FROM?");
}
