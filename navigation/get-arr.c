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
 
bool array[700][700];

#define PI 3.141592653589793	//I only remeber 15 decimal points :)

void save_frame(int frame, uint8_t * data) // Saves image
{
    char file[PATH_MAX];
    sprintf (file, "%06d.png", frame);
    stbi_write_png(file, 700, 700, 3, data, 700 * 3);
}

void create_image()
{
    uint8_t image_data[700 * 700 * 3];

    int rad = 128;
    
    for (int y=0; y<700; ++y){
        for (int x=0; x<700; ++x){
            if (array[y][x]){
                int res = 3 * (y * 700 + x);
                image_data[res] = 0;
                image_data[res + 1] = 0;
                image_data[res + 2] = 0;
            }
            else {
                int res = 3 * (y * 700 + x);
                image_data[res] = 255;
                image_data[res + 1] = 255;
                image_data[res + 2] = 255;
            }
        }
    }

    rad = 5;
    
    for (int y=340; y<360; ++y){
        for (int x=340; x<360; ++x){
            if (pow(x-350, 2) + pow(y-350, 2) <= rad * rad){
                int res = 3 * (y * 700 + x);
                image_data[res] = 200;
                image_data[res + 1] = 0;
                image_data[res + 2] = 0;
            }
        }
    }

    save_frame(1, image_data);
}

int main(int argc, char *argv[]) //argv[1] = input file
{
        memset(array, 0, sizeof(array[0][0]) * (700) * (700));
        int AB, OA;
        double OB;
        double a,aa; //a in degrees, aa in radians

        //OB = atof(argv[2]);
        //a = atof(argv[1]);
        FILE *fp = fopen(argv[1],"r");
        for (int i = 0; i < 10000; ++i) { //print 2d array
                fscanf(fp,"%lf %lf\n", &a, &OB);
                OB = OB/10; //convert to centimeters
                //printf("++++++a=%lf OB=%lf\n", a, OB);
                aa = a * PI/180; //find a in radians
                //printf("a in rad=%f\n",aa);
                AB = sin(aa) * OB;
                OA = cos(aa) * OB;
               // printf("OA=%d AB=%d\n", OA, AB);
                array[AB+350][OA+350] = 1; //set the point
        }
        fclose(fp);

        create_image();

        return 0;
}
