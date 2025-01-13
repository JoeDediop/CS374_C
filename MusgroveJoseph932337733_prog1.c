#include <stdio.h>
#include <math.h>

/**
 * Main function for spherical segments program.
 * Calculates total surface area and volume for multiple spherical segments
 * based on user input, validates input, and outputs average results.
 */
int main() {
    // Constants
    const double PI = 3.14159265359;
    const int MIN_SEGMENTS = 2;
    const int MAX_SEGMENTS = 10;

    // Variables
    int n;                     // Number of spherical segments
    double R, ha, hb;          // Input parameters: Radius, heights
    double totalSurfaceArea = 0.0, totalVolume = 0.0; // Totals for averages

    // Prompt for number of spherical segments (validate range)
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

    // Process each spherical segment
    for (int i = 1; i <= n; ++i) {
        printf("Obtaining data for spherical segment number %d\n", i);

        while (1) {
            // Prompt for input values
            printf("What is the radius of the sphere (R)? \n");
            scanf("%lf", &R);
            printf("What is the height of the top area of the spherical segment (ha)? \n");
            scanf("%lf", &ha);
            printf("What is the height of the bottom area of the spherical segment (hb)? \n");
            scanf("%lf", &hb);

            // Display entered values
            printf("Entered data: R = %.2f, ha = %.2f, hb = %.2f\n", R, ha, hb);

            // Validate input
            if (R <= 0 || ha <= 0 || hb <= 0) {
                printf("Invalid Input: All values must be positive.\n\n");
            } else if (ha > R || hb > R) {
                printf("Invalid Input: ha and hb must be less than or equal to R.\n\n");
            } else if (ha < hb) {
                printf("Invalid Input: ha must be greater than or equal to hb.\n\n");
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

        // Display intermediate values
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