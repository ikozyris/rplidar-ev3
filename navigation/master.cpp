#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cstdbool>
#include <cstdint>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <ctime>
#include <unistd.h>

#include "lidar-utils.cpp"
#include <csignal>

#define PI	3.141592653589793	  // I only remeber 15 decimal points :)
#define p 	0.0174532925199432958 // π / 180

uint8_t image_data[1300 * 1300 + 3];

bool ctrl_c_pressed;
void ctrlc(int)
{
    ctrl_c_pressed = true;
}

void save_frame(int frame) // Saves image
{
    char file[PATH_MAX];
    sprintf(file, "%06d.bmp", frame);
    stbi_write_bmp(file, 1300, 1300, 1, image_data);
}

int create_image2()
{
    sl_lidar_response_measurement_node_hq_t nodes[8192];
    // fetch result and print it out...
    size_t count = _countof(nodes);    
    op_result = drv->grabScanDataHq(nodes, count);    
    drv->ascendScanData(nodes, count);

    memset(image_data, 255, 1'690'000);
    int AB, OA;
    float OB;
    float a; // in radians

    for (size_t i = 0; i < count; ++i) {
    	if (nodes[i].quality == 0 || (nodes[i].dist_mm_q2 / 4.0f) > 1800)
			continue;
        OB = (nodes[i].dist_mm_q2 / 4.0f) / 3;
        //printf("++++++a=%lf OB=%lf\n", a, OB);
        a = ((nodes[i].angle_z_q14 * 90.f) / 16384.f) * p; //find a in radians
        //printf("a in rad=%f\n",aa);
        AB = sin(a) * OB;
        OA = cos(a) * OB;
        // printf("OA=%d AB=%d\n", OA, AB);
        image_data[(AB + 650) * 1300 + OA + 650] = 0;
    }

    save_frame(1);
    return 0;
}

int main() 
{
	signal(SIGINT, ctrlc);

	if(::connect("/dev/ttyUSB0", 115200) == 0) {
		puts(" > Connected");
		do {
			create_image2();
			//get_distances((char*)"raw_output");
			//create_image((char*)"raw_output");
			sleep(1);
			if (ctrl_c_pressed)
				break;
		} while (1);
		puts(" > Exiting");
		disconnect();
	}
	return 0;
}

