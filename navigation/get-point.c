#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.141592653589793	//I only remeber 15 decimal points :)

int main(int argc, char *argv[]) //argv[1] = distance | argv[2] = theta
{
        int array[9][10];
        memset(array, 0, sizeof(array[0][0]) * 9 * 10);
        int AB, OA;
        double OB;
        double a,aa; //a in degrees, aa in radians

        OB = atof(argv[1]);
        a = atof(argv[2]);
        printf("OB=%f a=%f\n", OB, a);

        aa = a * PI/180; //find a in radians
        printf("a in rad=%f\n",aa);
        AB = sin(aa) * OB;
        OA = cos(aa) * OB;

        printf("OA=%d AB=%d\n", OA, AB);

        array[AB][OA] = 1; //set the point

        for (int i = 0; i < 10; i++) { //print 2d array
                for (int j = 0; j < 10; j++) {
                        if (array[i][j] == 1) {
                                printf("%d ", array[i][j]);
                        } else printf("0 ");
                }
        printf("\n");
        }
}
