/*
 * Copyright (C) 2023 ikozyris
 * Copyright (C) 2023 gkozyris
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <cstdio>
#include <cstring>

#include "libs/sl_lidar.h"
#include "libs/sl_lidar_driver.h"

#define _countof(_Array) (int)(sizeof(_Array) / sizeof(_Array[0]))

#include <unistd.h>

sl_result op_result;
sl::IChannel *_channel;
// driver instance
sl::ILidarDriver *drv;

int connect()
{
    std::string port = "/dev/ttyUSB0"; int baudrate = 115200;
    sl_lidar_response_device_info_t devinfo;
    bool CS = false; // connected
    drv = *sl::createLidarDriver();

    //connect to lidar on /dev/ttyUSB0@115200
    _channel = (*sl::createSerialPortChannel(port, baudrate));

    if (access(port.c_str(), F_OK) != 0) {
        fprintf(stderr, "Lidar not connected!\n");
        goto error;
    } if (SL_IS_OK((drv)->connect(_channel))) { //start of checks
        op_result = drv->getDeviceInfo(devinfo);
        if (SL_IS_OK(op_result)) {
	        CS = true;
        } else {
            fprintf(stderr, "Couldn't get device info!\n");
            CS = true;
            goto error;
        }
    } if (CS == false) {
        fprintf(stderr, "Error, cannot bind to the specified serial port /dev/ttyUSB0.\n"); //end of checks
        goto error;
    }

    drv->setMotorSpeed();
    // start scan...
    //drv->startScan(0, 1);
    return 0;

error:
    delete drv;
	drv = NULL;
    return -1;
}


int write_distances(char *output)
{
    sl_lidar_response_measurement_node_hq_t nodes[8192];
    // fetch result and print it out...
    size_t count = _countof(nodes);    
    op_result = drv->grabScanDataHq(nodes, count);    
    drv->ascendScanData(nodes, count);

    std::FILE *pr = fopen(output, "w");
    for (size_t pos = 0; pos < count; ++pos) {
    //e.g. 0.15 00216.00 
        if(nodes[pos].quality != 0) {
            std::fprintf(pr, "%03.2f %08.2f\n",  // print to raw-out
            (nodes[pos].angle_z_q14 * 90.f) / 16384.f, //angle
            nodes[pos].dist_mm_q2 / 4.0f); // distance
        }
    }
    fclose(pr);

    return 0;
}

int _disconnect()
{
    drv->stop();
    drv->setMotorSpeed();
    // done!
    drv = NULL;
    delete drv;
    return 0;
}

