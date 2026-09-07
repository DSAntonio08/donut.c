#include <math.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {

    int areaX = 56;
    int areaY = 33;

    // coordinates of Cirle inside canvas
    int coordinateX = 28;
    int coordinateY = 16;

    float tilt = 0; // X-axis rotation
    float spin = 0; // Y-axis rotation
    int cameraDistance = 30;

    char canvas[areaY][areaX];

    while (1) {
        // clear canvas
        for (int row = 0; row < areaY; row++) {
            for (int column = 0; column < areaX; column++) {
                canvas[row][column] = ' ';
            }
        }
        char shades[] = ".,-~:;=!*#$@";

        float R = 12; // Distance from center to the middle of the tube
        float r = 5;  // Thickness of the tube itself

        float zBuffer[areaY][areaX];  // Track depth for each pixel
        
        // Initialize to "very far away"
        for (int row = 0; row < areaY; row++) {
            for (int col = 0; col < areaX; col++) {
                zBuffer[row][col] = -999999; // Very negative = far away
            }
        }

        // 6.28 = 2pi
        for (float theta = 0; theta < 6.28; theta += 0.03) {
            for (float phi = 0; phi < 6.28; phi += 0.03) {
                float X = (R + r * cos(theta)) * cos(phi);
                float Y = (R + r * cos(theta)) * sin(phi);
                float Z = r * sin(theta);

                // Step 1: Rotate around X-axis (tilt)
                float rotX = X;
                float rotY = Y * cos(tilt) - Z * sin(tilt);
                float rotZ = Y * sin(tilt) + Z * cos(tilt);

                // Step 2: Rotate those results around Y-axis (spin)
                float finalX = rotX * cos(spin) + rotZ * sin(spin);
                float finalY = rotY;
                float finalZ = -rotX * sin(spin) + rotZ * cos(spin);

                float multiplier = cameraDistance / (cameraDistance + finalZ);

                int x = coordinateX + (int)(finalX * multiplier);
                int y = coordinateY + (int)(finalY * multiplier);

                // Pick character based on depth
                int shadeIndex =
                    (int)((finalZ + 15) / 30 * 11); // Maps finalZ to 0-11
                if (shadeIndex < 0) shadeIndex = 0;
                if (shadeIndex > 11) shadeIndex = 11;

                // When drawing a point:
                if (x >= 0 && x < areaX && y >= 0 && y < areaY) {
                    if (finalZ > zBuffer[y][x]) {
                        zBuffer[y][x] = finalZ;
                        canvas[y][x] = shades[shadeIndex];
                    }
                }
            }
        }

        // "print" out everything
        printf("\033[H\033[J"); // clear the whole terminal

        for (int row = 0; row < areaY; row++) {
            for (int column = 0; column < areaX; column++) {
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