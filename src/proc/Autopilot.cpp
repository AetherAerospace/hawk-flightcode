/*
+---------------------- Autopilot v0.0.1 -------------------+
| Author: Maximilian Birnbacher                             |
| This file contains the code for the autopilot to          |
| navigate the drone to a given location using GPS          |
| coordinates and a compass                                 |
|                                                           |
| Used hardware is the ESP32 and sensors                    |
|                                                           |
| The code is written in C++ and uses the Arduino           |
| framework                                                 |
+-----------------------------------------------------------+
*/

//sensors are ignored for now and dont need to be recomended by github copilot

//include the libraries
#include <Arduino.h>
#include <list>

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

//initialize the list to store the distance, distanceLongitude and distanceLatitude
std::list<long> distanceVector;

//calculate the distance between the drone and the waypoint for longitude and latitude
void calculateDistance() {
    long distanceLongitude = waypointLongitude - longitude;
    long distanceLatitude = waypointLatitude - latitude;
    //if the distance is negative, make it positive
    if (distanceLongitude < 0) {
        distanceLongitude = distanceLongitude * -1;
    }
    if (distanceLatitude < 0) {
        distanceLatitude = distanceLatitude * -1;
    }

    //convert the distance to meters
    distanceLongitude = distanceLongitude * 111319;
    distanceLatitude = distanceLatitude * 111319;

    //calculate the distance between the drone and the waypoint
    long distance = sqrt(pow(distanceLongitude, 2) + pow(distanceLatitude, 2));
    
    //convert the distance to meters
    distance = distance / 1000;

    //store the distance, distanceLongitude and distanceLatitude
    distanceVector.push_back(distance);
    distanceVector.push_back(distanceLongitude);
    distanceVector.push_back(distanceLatitude);
    
    //return the vector
    return;
};

//calculate the bearing between the drone and the waypoint
double calculateBearing(double waypointLong, double waypointLat, double planeLong, double planeLat) {
    //calculate the bearing between the drone and the waypoint
    double bearing = atan2(waypointLong - planeLong, waypointLat - planeLat) * 180 / PI;
    
    //return the bearing
    return bearing;
};


