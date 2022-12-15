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

//calculate the distance between the drone and the waypoint for longitude and latitude
double calculateDistance(double waypointLong, double waypointLat, double planeLong, double planeLat) {
    long distanceLongitude = waypointLong - planeLong;
    long distanceLatitude = waypointLat - planeLat;
    //if the distance is negative, make it positive
    if (distanceLongitude < 0) {
        distanceLongitude = distanceLongitude * -1;
    }
    if (distanceLatitude < 0) {
        distanceLatitude = distanceLatitude * -1;
    }

    //convert the distance from degree (wsg84) to meters
    distanceLongitude = distanceLongitude * 111317;
    distanceLatitude = distanceLatitude * 111317;

    //calculate the distance between the drone and the waypoint
    double distance = sqrt(pow(distanceLongitude, 2) + pow(distanceLatitude, 2));
    //print the distance to the console
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println("m");
    //return the distance
    return distance;
};

//calculate the bearing between the drone and the waypoint
double calculateBearing(double waypointLong, double waypointLat, double planeLong, double planeLat) {
    //calculate the bearing between the drone and the waypoint
    double bearing = atan2(waypointLong - planeLong, waypointLat - planeLat) * 180 / PI;
    
    //return the bearing
    return bearing;
};


