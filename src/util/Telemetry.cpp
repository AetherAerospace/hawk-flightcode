// write to csv file
#include "Telemetry.h"
#include <string>
#include <fstream>
#include <vector>

//Class to store flight data
class FlightData {
    public:
        int time;
        int longitude;
        int latitude; 
        int altitude;
        int roll;
        int pitch;
        int yaw;
};

// function to write to csv file with a fixed first column. the function has the parameter data. Data is a vector.
void writeToCSV(std::vector<FlightData> data) {
    std::ofstream file;
    file.open("telemetry.csv", std::ios::app);
    
    //loop through the vector and write to csv file
    for (int i = 0; i < data.size(); i++) {
        file << data[i].time << "," << data[i].longitude << "," << data[i].latitude << "," << data[i].altitude << "," << data[i].roll << "," << data[i].pitch << "," << data[i].yaw << "\n";
    }

    file.close();
}

// generate a function that gets data from the sensors and stores it in a vector as a FlightData object
// then call the writeToCSV function with the vector as a parameter
void logFlightData() { //TODO: add parameters for sensor data
    //get time from the clock
    int time = 0;
    //get longitude from the GPS
    int longitude = 0;
    //get latitude from the GPS
    int latitude = 0;
    //get altitude from the GPS
    int altitude = 0;
    //get roll from the IMU
    int roll = 0;
    //get pitch from the IMU
    int pitch = 0;
    //get yaw from the IMU
    int yaw = 0;

    //create a FlightData object
    FlightData flightDataObject;
    flightDataObject.time = time;
    flightDataObject.longitude = longitude;
    flightDataObject.latitude = latitude;
    flightDataObject.altitude = altitude;
    flightDataObject.roll = roll;
    flightDataObject.pitch = pitch;
    flightDataObject.yaw = yaw;

    //create a vector to store the flightdata object in one line as strings separated by commas
    std::vector<FlightData> data;
    data.push_back(flightDataObject);

    //call the writeToCSV function with the vector as a parameter
    writeToCSV(data);
}
