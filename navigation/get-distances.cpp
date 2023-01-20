#include <stdio.h>
#include <string.h>

#include "sl_lidar.h" 
#include "sl_lidar_driver.h"

#define _countof(_Array) (int)(sizeof(_Array) / sizeof(_Array[0]))


#include <unistd.h>

int main(int argc, const char * argv[]) {
    sl_result     op_result;
    sl::IChannel* _channel;

    // create the driver instance
    sl::ILidarDriver * drv = *sl::createLidarDriver();

    _channel = (*sl::createSerialPortChannel("/dev/ttyUSB0", 115200)); //connect to lidar on /dev/ttyUSB0@115200
    (drv)->connect(_channel);
    std::printf("Connected\n");

    drv->setMotorSpeed();
    // start scan...
    drv->startScan(0,1);

    // fetch result and print it out...
    sl_lidar_response_measurement_node_hq_t nodes[8192];
    size_t   count = _countof(nodes);    
    op_result = drv->grabScanDataHq(nodes, count);    
    drv->ascendScanData(nodes, count);

    std::printf("nodes: %d count: %ld\n",nodes,count);//
    sleep(2);

    for (int pos = 0; pos < (int)count ; ++++++pos) { //+3 to pos each time to print every degree.
    //e.g. theta: 0.15 Dist: 00216.00 \n theta: 1.17 Dist: 00217.00 
        if(nodes[pos].quality != 0) {      
            std::printf("theta: %03.2f Dist: %08.2f \n",  
            (nodes[pos].angle_z_q14 * 90.f) / 16384.f,
            nodes[pos].dist_mm_q2/4.0f);
        }
    }

    drv->stop();
	printf("360 degrees scan was succesful, Goodbye!");
        drv->setMotorSpeed(0);
    // done!
        delete drv;
        drv = NULL;
    return 0;
}

