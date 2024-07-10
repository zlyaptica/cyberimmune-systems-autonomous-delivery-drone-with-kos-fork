#include "../include/security.h"

Security::Security(uint32_t cNum, MissionCommand *c)
{
    commandNum = cNum;
    commands = c;

    uint32_t currentWaypoint = getNextCommandNumByType(0, 'W');
    currentDropCargoWaypoint = getNextCommandNumByType(0, 'S');
    reachedWaypoint = 0;

    // first point - HOME
    previousWaypointCoordinates.latitude = convertCoordinatesToFloat(commands[0].content.waypoint.latitude);
    previousWaypointCoordinates.longitude = convertCoordinatesToFloat(commands[0].content.waypoint.longitude);
    previousWaypointCoordinates.altitude = convertCoordinatesToFloat(commands[1].content.waypoint.altitude);

    // second point
    if (currentWaypoint == commandNum)
    {
        fprintf(stderr, "[%s] Warning: You are at the last waypoint\n", ENTITY_NAME);
    }
    else
    {
        nextWaypointCoordinates.latitude = convertCoordinatesToFloat(commands[currentWaypoint].content.waypoint.latitude);
        nextWaypointCoordinates.longitude = convertCoordinatesToFloat(commands[currentWaypoint].content.waypoint.longitude);
        nextWaypointCoordinates.altitude = convertCoordinatesToFloat(commands[currentWaypoint].content.waypoint.altitude);
    }

    currentMaximumDroneAltitude = 0;
    altitudeDifference = 0;

    currentHorizontalDroneSpeed = 0;
    currentMaximumHorizontalDroneSpeed = 0;
    currentMaximumVerticalDroneSpeed = 0;
    currentVerticalDroneSpeed = 0;
    fprintf(stderr, "[%s] Info: Success initialization security.\n", ENTITY_NAME);

    if (!setCargoLock(0))
    {
        fprintf(stderr, "[%s] Warning: Unable to lock the cargo\n", ENTITY_NAME);
    }
}

bool Security::isDroneFlying()
{
    bool isDroneFlying = false;
    float *formattedCoordinates = getFormattedCoordinates(); // массив, который хранит возвращенный getCoords() в нулевом индексе и координаты в 1-3

    pointCoordinates startDroneCoordinates; // координаты стартоовой позиции дрона

    if (!formattedCoordinates[0]) // [0] - value returned from getCoord()
    {
        fprintf(stderr, "[%s] Warning: Not get drone start coordinates\n", ENTITY_NAME);
    }
    else
    {
        startDroneCoordinates.latitude = formattedCoordinates[1];
        startDroneCoordinates.longitude = formattedCoordinates[2];
        startDroneCoordinates.altitude = formattedCoordinates[3];
    }

    formattedCoordinates = getFormattedCoordinates();
    if (formattedCoordinates[0]) // [0] - value returned from getCoord()
    {
        currentDroneCoordinates.latitude = formattedCoordinates[1];
        currentDroneCoordinates.longitude = formattedCoordinates[2];
        currentDroneCoordinates.altitude = formattedCoordinates[3];

        // difference berween drone start coordinates and current drone coordinates
        float latitudeDifferenceByStart = abs(currentDroneCoordinates.latitude - startDroneCoordinates.latitude);
        float longitudeDifferenceByStart = abs(currentDroneCoordinates.longitude - startDroneCoordinates.longitude);
        float altitudeDifferenceByStart = abs(currentDroneCoordinates.altitude - startDroneCoordinates.altitude);

        fprintf(stderr, "[%s] Info: Get start coord: %f, %f, %f\n", ENTITY_NAME, latitudeDifferenceByStart, longitudeDifferenceByStart, altitudeDifferenceByStart);
        if (latitudeDifferenceByStart > 0.00005 || longitudeDifferenceByStart > 0.0005 || altitudeDifferenceByStart > 0.0005)
        {
            isDroneFlying = true;
        }
    }
    else
    {
        fprintf(stderr, "[%s] Warning: Could not get coordinates\n", ENTITY_NAME);
    }

    return isDroneFlying;
}
void Security::getNextWaypoint()
{
    float dToN = getDistanceToPoint(currentDroneCoordinates.latitude, currentDroneCoordinates.longitude, nextWaypointCoordinates.latitude, nextWaypointCoordinates.longitude);
    fprintf(stderr, "[%s] Info: prev coordinates: %f %f. Go to %d  waypoint.\n", ENTITY_NAME, previousWaypointCoordinates.latitude, previousWaypointCoordinates.longitude, currentWaypoint);
    fprintf(stderr, "[%s] Info: next coordinates: %f %f\n", ENTITY_NAME, nextWaypointCoordinates.latitude, nextWaypointCoordinates.longitude);

    if (dToN <= WAYPOINT_RADIUS)
    {
        reachedWaypoint = currentWaypoint;
        currentWaypoint = getNextCommandNumByType(currentWaypoint + 1, 'W');

        if (currentWaypoint == commandNum)
        {
            fprintf(stderr, "[%s] Warning: You are at the last waypoint\n", ENTITY_NAME);
        }
        else
        {
            previousWaypointCoordinates.latitude = nextWaypointCoordinates.latitude;
            previousWaypointCoordinates.longitude = nextWaypointCoordinates.longitude;
            previousWaypointCoordinates.altitude = nextWaypointCoordinates.altitude;

            nextWaypointCoordinates.latitude = convertCoordinatesToFloat(commands[currentWaypoint].content.waypoint.latitude);
            nextWaypointCoordinates.longitude = convertCoordinatesToFloat(commands[currentWaypoint].content.waypoint.longitude);
            nextWaypointCoordinates.altitude = convertCoordinatesToFloat(commands[currentWaypoint].content.waypoint.altitude);
        }
    }
}

void Security::calculateSpeed()
{
    if (elapsedTime > 0)
    {
        currentHorizontalDroneSpeed = travelledDistancePerTick / elapsedTime;
        currentVerticalDroneSpeed = altitudeDifference / elapsedTime;
    }
    else
    {
        currentHorizontalDroneSpeed = 0;
        currentVerticalDroneSpeed = 0;
    }
}

void Security::secure()
{
    Stopwatch stopwatch = Stopwatch();
    float *formattedCoordinates;

    while (currentWaypoint != commandNum)
    {
        stopwatch.start();
        formattedCoordinates = getFormattedCoordinates();
        if (!formattedCoordinates[0]) // [0] - value returned from getCoord()
        {
            fprintf(stderr, "[%s] Warning: Could not get coordinates\n", ENTITY_NAME);
        }
        else
        {
            previousDroneCoordinates.latitude = currentDroneCoordinates.latitude;
            previousDroneCoordinates.longitude = currentDroneCoordinates.longitude;
            previousDroneCoordinates.altitude = currentDroneCoordinates.altitude;

            currentDroneCoordinates.latitude = formattedCoordinates[1];
            currentDroneCoordinates.longitude = formattedCoordinates[2];
            currentDroneCoordinates.altitude = formattedCoordinates[3];

            controlHorizontalSpeed();
            controlVerticalSpeed();
            controlCargoLock();
            controlAltitude();
            controlCorridor();

            altitudeDifference = altitudeDifference - currentDroneCoordinates.altitude;
            travelledDistancePerTick = getDistanceToPoint(previousDroneCoordinates.latitude, previousDroneCoordinates.longitude, currentDroneCoordinates.latitude, currentDroneCoordinates.longitude);

            elapsedTime = stopwatch.getELapsedTime();
            calculateSpeed();

            printLog();
        }

        sleep(1);
        stopwatch.restart();
    }
}

void Security::controlVerticalSpeed()
{
}

void Security::controlHorizontalSpeed()
{
    if (currentHorizontalDroneSpeed > MAXIMUM_DRONE_SPEED && currentMaximumHorizontalDroneSpeed > currentHorizontalDroneSpeed)
    {
        fprintf(stderr, "[%s] Warning: The drone's flying too fast: %f(max: %f). Pause flight...\n", ENTITY_NAME, currentHorizontalDroneSpeed, MAXIMUM_DRONE_SPEED);

        lockServo();
    }

    if (currentHorizontalDroneSpeed > MAXIMUM_DRONE_SPEED)
    {
        fprintf(stderr, "[%s] Warning: The drone's flying too fast: %f(max: %f). Trying to slow down.\n", ENTITY_NAME, currentHorizontalDroneSpeed, MAXIMUM_DRONE_SPEED);
        currentMaximumHorizontalDroneSpeed = currentHorizontalDroneSpeed;

        if (!changeSpeed(MAXIMUM_DRONE_SPEED))
        {
            fprintf(stderr, "[%s] Warning: Speed change error\n", ENTITY_NAME);

            lockServo();
        }
        else
        {
            fprintf(stderr, "[%s] Info: Current drone speed: %f\n", ENTITY_NAME, currentHorizontalDroneSpeed);
        }
    }
}

void Security::controlCargoLock()
{
    if (currentDropCargoWaypoint != commandNum)
    {
        if (currentDropCargoWaypoint == reachedWaypoint + 2 || currentDropCargoWaypoint == reachedWaypoint - 1)
        {
            if (!setCargoLock(1))
            {
                fprintf(stderr, "[%s] Warning: Unable to unlock the cargo\n", ENTITY_NAME);
            }
            else
            {
                fprintf(stderr, "[%s] Info: Success unlock the cargo\n", ENTITY_NAME);
            }
        }
        else
        {
            if (!setCargoLock(0))
            {
                fprintf(stderr, "[%s] Warning: Unable to lock the cargo\n", ENTITY_NAME);
            }
            else
            {
                fprintf(stderr, "[%s] Info: Success lock the cargo\n", ENTITY_NAME);
            }
        }
    }
}

void Security::controlAltitude()
{
    if (currentDroneCoordinates.altitude > MAX_DRONE_ALTITUDE && currentMaximumDroneAltitude > currentDroneCoordinates.altitude)
    {
        fprintf(stderr, "[%s] Warning: The drone is flying too high and landing: %f m.\n", ENTITY_NAME, currentDroneCoordinates.altitude);

        lockServo();
    }

    if (currentDroneCoordinates.altitude > MAX_DRONE_ALTITUDE)
    {
        fprintf(stderr, "[%s] Warning: The drone is flying too high: %f m. Trying to lower the altitude\n", ENTITY_NAME, currentDroneCoordinates.altitude);
        currentMaximumDroneAltitude = currentDroneCoordinates.altitude;

        if (!changeAltitude(MAX_DRONE_ALTITUDE))
        {
            fprintf(stderr, "[%s] Warning: Can not change altitude. Pause flight.\n", ENTITY_NAME);

            lockServo();
        }
        else
        {
            fprintf(stderr, "[%s] Info: Succesfully change drone altitudeto %f.\n", ENTITY_NAME, MAX_DRONE_ALTITUDE);
        }
    }
}

void Security::controlCorridor()
{
    getPointsBetween2Waypoints(previousWaypointCoordinates.latitude, previousWaypointCoordinates.longitude, nextWaypointCoordinates.latitude, nextWaypointCoordinates.longitude, latitudeCoordinates, longitudeCoordinates);
    if (!isInsideTheBorders(currentDroneCoordinates.latitude, currentDroneCoordinates.longitude, latitudeCoordinates, longitudeCoordinates))
    {
        fprintf(stderr, "[%s] Warning: the drone's out of the corridor and landing.\n", ENTITY_NAME);

        lockServo();
    }
}

void Security::lockServo()
{
    // try to lock drop cargo
    if (!setCargoLock(0))
    {
        fprintf(stderr, "[%s] Warning: Can not lock drop cargo\n", ENTITY_NAME);
    }
    else
    {
        fprintf(stderr, "[%s] Info: Succesfully lock drop cargo\n", ENTITY_NAME);
    }

    // try to pause flight
    if (!pauseFlight())
    {
        fprintf(stderr, "[%s] Warning: Can not pause flight\n", ENTITY_NAME);
    }
    else
    {
        fprintf(stderr, "[%s] Info: Succesfully pause flight\n", ENTITY_NAME);
    }
}

void Security::printLog()
{
    fprintf(stderr, "[%s] Info: Current drone coordinates: %f %f, altitude: %f \n", ENTITY_NAME, currentDroneCoordinates.latitude, currentDroneCoordinates.longitude, currentDroneCoordinates.altitude);
    fprintf(stderr, "[%s] Info: The drone flies for %f seconds. Current horizontal speed: %f, vertical: %f. Distance covered per tick: %f\n", ENTITY_NAME, elapsedTime, currentHorizontalDroneSpeed, currentVerticalDroneSpeed, travelledDistancePerTick);
    fprintf(stderr, "[%s] Info: prev coordinates: %f %f. Go to %d  waypoint.\n", ENTITY_NAME, previousWaypointCoordinates.latitude, previousWaypointCoordinates.longitude, currentWaypoint);
    fprintf(stderr, "[%s] Info: next coordinates: %f %f\n", ENTITY_NAME, nextWaypointCoordinates.latitude, nextWaypointCoordinates.longitude);
}
