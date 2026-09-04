#include <stdio.h>
#include <math.h>
#include <unistd.h>

int main(void)
{

    int areaX = 42;
    int areaY = 22;

    int radiusX = 15;
    int radiusY = 8;

    // coordinates of Cirle inside canvas
    int coordinateX = 20;
    int coordinateY = 10;

    float tilt = 0; // X-axis rotation
    float spin = 0; // Y-axis rotation
    int cameraDistance = 30;

    char canvas[areaY][areaX];

    while (1)
    {
        // clear canvas
        for (int row = 0; row < areaY; row++)
        {
            for (int column = 0; column < areaX; column++)
            {
                canvas[row][column] = ' ';
            }
        }

        // calculate circle
        for (float pointAngle = 0; pointAngle < 6.28; pointAngle += 0.1) // 6.28 = 2pi = 360deg but in radians
        {
            // calculate next x,y,z (point on the circus circumference) using radius * cos/sin(Angle)
            float X = radiusX * cos(pointAngle);
            float Y = radiusY * sin(pointAngle);
            float Z = 0;

            /*newX = oldX * cos(angle) - oldY * sin(angle);
            newY = oldX * sin(angle) + oldY * cos(angle);*/

            float rotatedX_X = X;
            float rotatedX_Y = Y * cos(tilt) - Z * sin(tilt);
            float rotatedX_Z = Y * sin(tilt) + Z * cos(tilt);

            float rotatedY_Y = Y;
            float rotatedY_X = X * cos(tilt) - Z * sin(tilt);
            float rotatedY_Z = X * sin(tilt) + Z * cos(tilt);

            float finalX = rotatedX_X * cos(spin) - rotatedX_Z * sin(spin);
            float finalY = rotatedX_Y;
            float finalZ = rotatedX_X * sin(spin) + rotatedX_Z * cos(spin);

            float multiplier = cameraDistance / (cameraDistance + finalZ);

            int x = coordinateX + (int)(finalX * multiplier);
            int y = coordinateY + (int)(finalY * multiplier);

            if (x >= 0 && x < areaX &&
                y >= 0 && y < areaY)
            {
                // row lies across X, but y selects the row
                // column lies down Y, but x selects the column
                canvas[y][x] = '*';
            }
        }

        // "print" out everything
        printf("\033[H\033[J"); // clear the whole terminal

        for (int row = 0; row < areaY; row++)
        {
            for (int column = 0; column < areaX; column++)
            {
                putchar(canvas[row][column]);
            }
            putchar('\n');
        }
        fflush(stdout);
        usleep(10000);

        // increase tilt after printing
        tilt += 0.04;
        spin += 0.02;
    }
}