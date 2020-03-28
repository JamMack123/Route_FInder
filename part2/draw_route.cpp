#include "draw_route.h"
#include "map_drawing.h"

extern shared_vars shared;


void draw_route() {
  // implement this!


    for(int i = 1; i <shared.num_waypoints; i++){

        lon_lat_32 first = shared.waypoints[i-1];
        lon_lat_32 second = shared.waypoints[i];

        int32_t x0 = longitude_to_x(shared.map_number, first.lon);
        int32_t y0 = latitude_to_y(shared.map_number, first.lat);
        int32_t x1 = longitude_to_x(shared.map_number, second.lon);
        int32_t y1 = latitude_to_y(shared.map_number, second.lat);
        xy_pos offset = shared.map_coords;
        x0 -= offset.x;
        y0 -= offset.y;
        x1 -= offset.x;
        y1 -= offset.y;

        // String thing = String(x0);
        // char letter[thing.length()];
        // thing.toCharArray(letter, thing.length());
        // status_message(letter);

        
        shared.tft->drawLine(x0,y0,x1,y1,TFT_BLUE);



    }
}
