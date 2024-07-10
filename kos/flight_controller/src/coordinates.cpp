#include "../include/coordinates.h"

void getPointsBetween2Waypoints(float x1, float y1, float x2, float y2, float *latitudeCoordinates, float *longitudeCoordinates)
{
    latitudeCoordinates[0] = x1;
    latitudeCoordinates[POINTS_IN_BETWEEN - 1] = x2;

    longitudeCoordinates[0] = y1;
    longitudeCoordinates[POINTS_IN_BETWEEN - 1] = y2;
    for (int i = 1; i < POINTS_IN_BETWEEN - 1; i++)
    {
        float lambda = (float)i / (POINTS_IN_BETWEEN - 1 - (float)i);
        float x_m = (x1 + lambda * x2) / (1 + lambda);
        float y_m = (y1 + lambda * y2) / (1 + lambda);

        latitudeCoordinates[i] = x_m;
        longitudeCoordinates[i] = y_m;
    }
}

float getDistanceToPoint(float x1, float y1, float x2, float y2)
{
    float rToD = (M_PI / 180);
    float earthRadius = 6378.1370;

    float dlong = (y2 - y1) * rToD;
    float dlat = (x2 - x1) * rToD;

    float a = pow(sin(dlat / 2), 2) + cos(x1 * rToD) * cos(x2 * rToD) * pow(sin(dlong / 2), 2);
    float c = 2 * atan2(sqrt(a), sqrt(1 - a));
    float distance = earthRadius * c * 1000;
    return distance;
}

bool isInsideTheBorders(float currentLatitude, float currentLongitude, float *latitudeCoordinates, float *longitudeCoordinates)
{
    float distance;
    for (int i = 1; i < POINTS_IN_BETWEEN - 1; i++)
    {
        distance = getDistanceToPoint(currentLatitude, currentLongitude, latitudeCoordinates[i], longitudeCoordinates[i]);
        // fprintf(stderr, "distance = %f. cur lat = %f, cur long = %f, lat coord = %f, long coord = %f\n", distance, currentLatitude, currentLongitude, latitudeCoordinates[i], longitudeCoordinates[i]);
        if (distance < 5)
            return true;
    }
    return false;
}

float convertCoordinatesToFloat(int32_t value)
{
    return (float)value * 1e-7;
}

float *getFormattedCoordinates()
{
    int32_t latitude, longitude, altitude;

    static float coordinates[4];

    if (!getCoords(latitude, longitude, altitude))
    {
    coordinates[0] = 0; // error status
    }

    coordinates[0] = 1; // success status
    coordinates[1] = convertCoordinatesToFloat(latitude);
    coordinates[2] = convertCoordinatesToFloat(longitude);
    coordinates[3] = convertCoordinatesToFloat(altitude);
    return coordinates;
}