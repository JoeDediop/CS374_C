#include <stdio.h>
#include <math.h>

/**
 * Main function for the spherical segments program which will calculate the total surface area and volume for specific amount of spherical segments based on user input.
 */

int main() {
    // Constants
    const double PI = 3.14159265359;
    const int MIN_SEGMENTS = 2;
    const int MAX_SEGMENTS = 10;

    // Variables
    int n;                     // Number of spherical segments
    double R, ha, hb;          // Input parameters: Radius and both heights
    double totalSurfaceArea = 0.0, totalVolume = 0.0; // Totals for averages

    // Obtain the number of spherical segments from user, validate the range
    printf("How many spherical segments you want to evaluate [%d-%d]? \n", MIN_SEGMENTS, MAX_SEGMENTS);
    while (1) {
        scanf("%d", &n);
        if (n >= MIN_SEGMENTS && n <= MAX_SEGMENTS) {
            printf("You entered: %d spherical segments\n\n", n);
            break;
        } else {
            printf("Invalid input. How many spherical segments you want to evaluate [%d-%d]? \n", MIN_SEGMENTS, MAX_SEGMENTS);
        }
    }

    // Process and validate each spherical segment
    for (int i = 1; i <= n; ++i) {
        printf("Obtaining data for spherical segment number %d\n", i);

        while (1) {
            // Gather input values
            printf("What is the radius of the sphere (R)? \n");
            scanf("%lf", &R);
            printf("What is the height of the top area of the spherical segment (ha)? \n");
            scanf("%lf", &ha);
            printf("What is the height of the bottom area of the spherical segment (hb)? \n");
            scanf("%lf", &hb);

            // Display the entered values
            printf("Entered data: R = %.2f, ha = %.2f, hb = %.2f\n", R, ha, hb);

            // Validate each input to ensure they are within the correct range
            if (R <= 0 || ha <= 0 || hb <= 0) {
                printf("Invalid Input: R = %.2f, ha = %.2f, hb = %.2f. All values must be positive.\n\n", R, ha, hb);
            } else if (ha > R) {
                printf("Invalid Input: R = %.2f, ha = %.2f. R must be greater than or equal to ha\n\n", R, ha);
            } else if (hb > R) {
                printf("Invalid Input: R = %.2f, hb = %.2f. R must be greater than or equal to hb\n\n", R, hb);
            } else if (ha < hb) {
                printf("Invalid Input: ha = %.2f, hb = %.2f. ha must be greater than or equal to hb.\n\n", ha, hb);
            } else {
                break;
            }
                printf("Obtaining data for spherical segment number %d\n", i);
        }

        // Calculate intermediate values
        double a = sqrt(pow(R, 2) - pow(ha, 2));
        double b = sqrt(pow(R, 2) - pow(hb, 2));
        double h = ha - hb;

        // Calculate surface areas and volume
        double topSurfaceArea = PI * pow(a, 2);
        double bottomSurfaceArea = PI * pow(b, 2);
        double lateralSurfaceArea = 2 * PI * R * h;
        double surfaceArea = topSurfaceArea + bottomSurfaceArea + lateralSurfaceArea;
        double volume = (PI * h / 6) * (3 * pow(a, 2) + 3 * pow(b, 2) + pow(h, 2));

        // Display relevant values
        printf("Total Surface Area = %.2f, Volume = %.2f\n\n", surfaceArea, volume);

        // Add to totals
        totalSurfaceArea += surfaceArea;
        totalVolume += volume;
    }

    // Calculate and display averages
    double averageSurfaceArea = totalSurfaceArea / n;
    double averageVolume = totalVolume / n;
    printf("Total average results:\n");
    printf("Average Surface Area = %.2f, Average Volume = %.2f\n", averageSurfaceArea, averageVolume);

    return 0;
}
