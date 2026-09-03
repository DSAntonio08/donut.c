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

    float tilt = 0;
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

            // from here
            float rotatedX = X;
            float rotatedY = Y * cos(tilt) - Z * sin(tilt);
            float rotatedZ = Y * sin(tilt) + Z * cos(tilt);

            float multiplier = cameraDistance / (cameraDistance + rotatedZ);

            int x = coordinateX + (int)(rotatedX * multiplier);
            int y = coordinateY + (int)(rotatedY * multiplier);
            // to here
            // I don't understand SHIT

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
        tilt += 0.2;
    }
}