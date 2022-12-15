//header file for the autopilot
#include <Arduino.h>
#include <list>
#include <math.h>

//get the GPS coordinates from the waypoint
double waypointLatitude = 46.603463;
double waypointLongitude = 13.843084;
double waypointAltitude = 500;

//get the GPS coordinates from the GPS sensor and store them in variables (use static variables for now)
double latitude = 46.60131;
double longitude = 13.84496;
double altitude = 500;

//get the compass heading from the compass sensor and store it in a variable (use static variable for now)
long bearing = 0;

//initialize the function to calculate the distance between the drone and the waypoint
void calculateDistance();

//initialize the function to calculate the bearing between the drone and the waypoint
double calculateBearing(double waypointLong, double waypointLat, double planeLong, double planeLat);

