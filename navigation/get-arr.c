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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <time.h>
#include <unistd.h>

#define p 0.0174532925199432958	// π / 180

uint8_t image_data[1300 * 1300 * 3];

void save_frame(int frame) // Saves image
{
    char file[16];
    sprintf(file, "%06d.bmp", frame);
    stbi_write_bmp(file, 1300, 1300, 3, image_data);
}

int create_image(char *input)
{
    memset(image_data, 255, 1300 * 1300);
    int AB, OA;
    float OB, a;

    FILE *fp = fopen(input, "r");
    for (int i = 0; i < 10000; ++i) { //print 2d array
        fscanf(fp,"%lf %lf\n", &a, &OB);
       	OB = OB/10; //convert to centimeters
       	//printf("++++++a=%lf OB=%lf\n", a, OB);
    	a *= p; //find a in radians
	   	//printf("a in rad=%f\n",aa);
	   	AB = sin(a) * OB;
	   	OA = cos(a) * OB;
    	// printf("OA=%d AB=%d\n", OA, AB);
    	image_data[(AB + 650) * 1300 + OA + 650] = 0;
	}

    save_frame(1);
    return 0;
}
