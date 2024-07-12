#include "../include/constants.h"
#include "../include/mission.h"
#include "../include/stopwatch.h"
// #include "../include/coordinates.h"
// #include "../include/security.h"
#include "../../shared/include/initialization_interface.h"
#include "../../shared/include/ipc_messages_initialization.h"
#include "../../shared/include/ipc_messages_autopilot_connector.h"
#include "../../shared/include/ipc_messages_credential_manager.h"
#include "../../shared/include/ipc_messages_navigation_system.h"
#include "../../shared/include/ipc_messages_periphery_controller.h"
#include "../../shared/include/ipc_messages_server_connector.h"

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <chrono>

#define RETRY_DELAY_SEC 1
#define RETRY_REQUEST_DELAY_SEC 5
#define FLY_ACCEPT_PERIOD_US 500000

extern uint32_t commandNum; // count waypoints in mission plan
extern MissionCommand *commands;

struct pointCoordinates // координаты точки float типа
{
    float latitude;
    float longitude;
    float altitude;
};

void getPointsBetween2Waypoints(float x1, float y1, float x2, float y2, float *latitudeCoordinates, float *longitudeCoordinates)
{
    latitudeCoordinates[0] = x1;
    latitudeCoordinates[POINTS_IN_BETWEEN - 1] = x2;

    longitudeCoordinates[0] = y1;
    longitudeCoordinates[POINTS_IN_BETWEEN - 1] = y2;
    for (int i = 1; i < POINTS_IN_BETWEEN; i++)
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
    for (int i = 1; i < POINTS_IN_BETWEEN; i++)
    {
        distance = getDistanceToPoint(currentLatitude, currentLongitude, latitudeCoordinates[i], longitudeCoordinates[i]);
        // fprintf(stderr, "i = %d. distance = %f. cur lat = %f, cur long = %f, lat coord = %f, long coord = %f\n", i, distance, currentLatitude, currentLongitude, latitudeCoordinates[i], longitudeCoordinates[i]);
        if (distance < 3)
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

int sendSignedMessage(char *method, char *response, char *errorMessage, uint8_t delay)
{
    char message[512] = {0};
    char signature[257] = {0};
    char request[1024] = {0};
    snprintf(message, 512, "%s?%s", method, BOARD_ID);

    while (!signMessage(message, signature))
    {
        fprintf(stderr, "[%s] Warning: Failed to sign %s message at Credential Manager. Trying again in %ds\n", ENTITY_NAME, errorMessage, delay);
        sleep(delay);
    }
    snprintf(request, 1024, "%s&sig=0x%s", message, signature);

    while (!sendRequest(request, response))
    {
        fprintf(stderr, "[%s] Warning: Failed to send %s request through Server Connector. Trying again in %ds\n", ENTITY_NAME, errorMessage, delay);
        sleep(delay);
    }

    uint8_t authenticity = 0;
    while (!checkSignature(response, authenticity) || !authenticity)
    {
        fprintf(stderr, "[%s] Warning: Failed to check signature of %s response received through Server Connector. Trying again in %ds\n", ENTITY_NAME, errorMessage, delay);
        sleep(delay);
    }

    return 1;
}

int main(void)
{
    // Before do anything, we need to ensure, that other modules are ready to work
    while (!waitForInit("periphery_controller_connection", "PeripheryController"))
    {
        sleep(RETRY_DELAY_SEC);
    }
    while (!waitForInit("autopilot_connector_connection", "AutopilotConnector"))
    {
        fprintf(stderr, "[%s] Warning: Failed to receive initialization notification from Autopilot Connector. Trying again in %ds\n", ENTITY_NAME, RETRY_DELAY_SEC);
        sleep(RETRY_DELAY_SEC);
    }
    while (!waitForInit("navigation_system_connection", "NavigationSystem"))
    {
        fprintf(stderr, "[%s] Warning: Failed to receive initialization notification from Navigation System. Trying again in %ds\n", ENTITY_NAME, RETRY_DELAY_SEC);
        sleep(RETRY_DELAY_SEC);
    }
    while (!waitForInit("server_connector_connection", "ServerConnector"))
    {
        fprintf(stderr, "[%s] Warning: Failed to receive initialization notification from Server Connector. Trying again in %ds\n", ENTITY_NAME, RETRY_DELAY_SEC);
        sleep(RETRY_DELAY_SEC);
    }
    while (!waitForInit("credential_manager_connection", "CredentialManager"))
    {
        fprintf(stderr, "[%s] Warning: Failed to receive initialization notification from Credential Manager. Trying again in %ds\n", ENTITY_NAME, RETRY_DELAY_SEC);
        sleep(RETRY_DELAY_SEC);
    }
    fprintf(stderr, "[%s] Info: Initialization is finished\n", ENTITY_NAME);
    setKillSwitch(1);

    // Enable buzzer to indicate, that all modules has been initialized
    if (!enableBuzzer())
        fprintf(stderr, "[%s] Warning: Failed to enable buzzer at Periphery Controller\n", ENTITY_NAME);

    // Copter need to be registered at ORVD
    char authResponse[1024] = {0};
    sendSignedMessage("/api/auth", authResponse, "authentication", RETRY_DELAY_SEC);
    fprintf(stderr, "[%s] Info: Successfully authenticated on the server\n", ENTITY_NAME);

    // Constantly ask server, if mission for the drone is available. Parse it and ensure, that mission is correct
    while (true)
    {
        char missionResponse[1024] = {0};
        if (sendSignedMessage("/api/fmission_kos", missionResponse, "mission", RETRY_DELAY_SEC) && parseMission(missionResponse))
        {
            fprintf(stderr, "[%s] Info: Successfully received mission from the server\n", ENTITY_NAME);
            printMission();
            break;
        }
        sleep(RETRY_REQUEST_DELAY_SEC);
    }

    // The drone is ready to arm
    fprintf(stderr, "[%s] Info: Ready to arm\n", ENTITY_NAME);
    while (true)
    {
        // Wait, until autopilot wants to arm (and fails so, as motors are disabled by default)
        while (!waitForArmRequest())
        {
            fprintf(stderr, "[%s] Warning: Failed to receive an arm request from Autopilot Connector. Trying again in %ds\n", ENTITY_NAME, RETRY_DELAY_SEC);
            sleep(RETRY_DELAY_SEC);
        }
        fprintf(stderr, "[%s] Info: Received arm request. Notifying the server\n", ENTITY_NAME);

        // When autopilot asked for arm, we need to receive permission from ORVD
        char armRespone[1024] = {0};
        sendSignedMessage("/api/arm", armRespone, "arm", RETRY_DELAY_SEC);

        if (strstr(armRespone, "$Arm: 0#") != NULL)
        {
            // If arm was permitted, we enable motors
            fprintf(stderr, "[%s] Info: Arm is permitted\n", ENTITY_NAME);
            while (!setKillSwitch(true))
            {
                fprintf(stderr, "[%s] Warning: Failed to permit motor usage at Periphery Controller. Trying again in %ds\n", ENTITY_NAME, RETRY_DELAY_SEC);
                sleep(RETRY_DELAY_SEC);
            }
            if (!permitArm())
                fprintf(stderr, "[%s] Warning: Failed to permit arm through Autopilot Connector\n", ENTITY_NAME);
            break;
        }
        else if (strstr(armRespone, "$Arm: 1#") != NULL)
        {
            fprintf(stderr, "[%s] Info: Arm is forbidden\n", ENTITY_NAME);
            if (!forbidArm())
                fprintf(stderr, "[%s] Warning: Failed to forbid arm through Autopilot Connector\n", ENTITY_NAME);
        }
        else
            fprintf(stderr, "[%s] Warning: Failed to parse server response\n", ENTITY_NAME);
        fprintf(stderr, "[%s] Warning: Arm was not allowed. Waiting for another arm request from autopilot\n", ENTITY_NAME);
    };

    // If we get here, the drone is able to arm and start the mission
    // The flight is need to be controlled from now on
    // Also we need to check on ORVD, whether the flight is still allowed or it is need to be paused    

    printMission();
    int32_t reachedWaypoint = 0; // вейпонт, который пролетел дрон

    float elapsedTime = 0;              // время, затраченное дроном на один тик
    float travelledDistancePerTick = 0; // пройденная дроном дистанция за один тик

    float latitudeCoordinates[POINTS_IN_BETWEEN];  // массив с промежуточными координатами широты между контрольными точками для идентификации середины коридора
    float longitudeCoordinates[POINTS_IN_BETWEEN]; // массив с промежуточными координатами долгоа между контрольными точками для идентификации середины коридора

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
        fprintf(stderr, "[%s] Info: Get start coord: %f, %f, %f\n", ENTITY_NAME, startDroneCoordinates.latitude, startDroneCoordinates.longitude, startDroneCoordinates.altitude);
    }

    if (!setCargoLock(0))
    {
        fprintf(stderr, "[%s] Warning: Unable to lock the cargo\n", ENTITY_NAME);
    }

    // HOME point:
    pointCoordinates previousWaypointCoordinates; // координаты вейпоинта, который пролетел дрон. Первая точка - старт

    previousWaypointCoordinates.latitude = convertCoordinatesToFloat(commands[0].content.waypoint.latitude);
    previousWaypointCoordinates.longitude = convertCoordinatesToFloat(commands[0].content.waypoint.longitude);
    previousWaypointCoordinates.altitude = convertCoordinatesToFloat(commands[1].content.waypoint.altitude);

    pointCoordinates nextWaypointCoordinates; // координаты вейпоинта, на который должен прилететь дрон
    uint32_t currentWaypoint = getNextCommandNumByType(0, 'W');
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

    Stopwatch stopwatch = Stopwatch();
    float currentMaximumDroneSpeed = 0; // максимальная скорость, с которой летел дрон
    float altitudeDifference = 0;       // разница высота за тик для вычисления вертикальной скорости. Рассчитывается как разница между текущей высотой и значением данной переменной

    pointCoordinates currentDroneCoordinates;
    bool isPauseFlight = false;

    while (currentWaypoint != commandNum)
    {
        formattedCoordinates = getFormattedCoordinates();
        if (!formattedCoordinates[0]) // [0] - value returned from getCoord()
        {
            fprintf(stderr, "[%s] Warning: Could not get coordinates\n", ENTITY_NAME);
        }
        else
        {
            if (currentWaypoint == commandNum - 1)
            {
                if (!setKillSwitch(0))
                {
                    fprintf(stderr, "[%s] Warning: Could not kill switch\n", ENTITY_NAME);
                }
            }

            pointCoordinates previousDroneCoordinates;

            previousDroneCoordinates.latitude = currentDroneCoordinates.latitude;
            previousDroneCoordinates.longitude = currentDroneCoordinates.longitude;
            previousDroneCoordinates.altitude = currentDroneCoordinates.altitude;

            currentDroneCoordinates.latitude = formattedCoordinates[1];
            currentDroneCoordinates.longitude = formattedCoordinates[2];
            currentDroneCoordinates.altitude = formattedCoordinates[3];

            // difference berween drone start coordinates and current drone coordinates
            float latitudeDifferenceByStart = abs(currentDroneCoordinates.latitude - startDroneCoordinates.latitude);
            float longitudeDifferenceByStart = abs(currentDroneCoordinates.longitude - startDroneCoordinates.longitude);
            float altitudeDifferenceByStart = abs(currentDroneCoordinates.altitude - startDroneCoordinates.altitude);

            if (latitudeDifferenceByStart < 0.00005 && longitudeDifferenceByStart < 0.0005 && altitudeDifferenceByStart < 0.0005)
            {
                continue;
            }
            stopwatch.start();

            float currentHorizontalDroneSpeed;
            float currentVerticalDroneSpeed;

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
            fprintf(stderr, "[%s] Info: Started coordinates: %f %f %f\n", ENTITY_NAME, startDroneCoordinates.latitude, startDroneCoordinates.longitude, startDroneCoordinates.altitude);
            fprintf(stderr, "[%s] Info: Current drone coordinates: %f %f, altitude: %f \n", ENTITY_NAME, currentDroneCoordinates.latitude, currentDroneCoordinates.longitude, currentDroneCoordinates.altitude);
            fprintf(stderr, "[%s] Info: The drone flies for %f seconds. Current horizontal speed: %f, vertical: %f. Distance covered per tick: %f\n", ENTITY_NAME, elapsedTime, currentHorizontalDroneSpeed, currentVerticalDroneSpeed, travelledDistancePerTick);

            // control cargo lock
            uint32_t currentDropCargoWaypoint = getNextCommandNumByType(0, 'S');

            if (currentDropCargoWaypoint != commandNum)
            {
                // if there are less than 10 meters to the load dumping point, the load can be dumped
                if (currentDropCargoWaypoint == reachedWaypoint + 2)
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
            }

            // control horizontal speed
            // if (currentHorizontalDroneSpeed > MAXIMUM_DRONE_SPEED && currentMaximumDroneSpeed > currentHorizontalDroneSpeed)
            // {
            //     fprintf(stderr, "[%s] Warning: The drone's flying too fast: %f(max: %f). Pause flight...\n", ENTITY_NAME, currentHorizontalDroneSpeed, MAXIMUM_DRONE_SPEED);

            //     // try to lock drop cargo
            //     if (!setCargoLock(0))
            //     {
            //         fprintf(stderr, "[%s] Warning: Can not lock drop cargo\n", ENTITY_NAME);
            //     }
            //     else
            //     {
            //         fprintf(stderr, "[%s] Info: Succesfully lock drop cargo\n", ENTITY_NAME);
            //     }

            //     // try to pause flight
            //     if (!pauseFlight())
            //     {
            //         fprintf(stderr, "[%s] Warning: Can not pause flight\n", ENTITY_NAME);
            //     }
            //     else
            //     {
            //         fprintf(stderr, "[%s] Info: Succesfully pause flight\n", ENTITY_NAME);
            //     }
            // }

            if (currentHorizontalDroneSpeed > MAXIMUM_DRONE_SPEED)
            {
                fprintf(stderr, "[%s] Warning: The drone's flying too fast: %f(max: %f). Trying to slow down.\n", ENTITY_NAME, currentHorizontalDroneSpeed, MAXIMUM_DRONE_SPEED);
                currentMaximumDroneSpeed = currentHorizontalDroneSpeed;

                if (!changeSpeed(2))
                {
                    fprintf(stderr, "[%s] Warning: Speed change error\n", ENTITY_NAME);

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
                else
                {
                    fprintf(stderr, "[%s] Info: Current drone speed: %f\n", ENTITY_NAME, currentHorizontalDroneSpeed);
                }
            }

            // control altitude
            if (currentDroneCoordinates.altitude > MAX_DRONE_ALTITUDE + 30)
            {
                fprintf(stderr, "[%s] Warning: The drone is flying too high and landing: %f m. Trying to lower the altitude\n", ENTITY_NAME, currentDroneCoordinates.altitude);
                if (!changeAltitude(MAX_DRONE_ALTITUDE))
                {
                    fprintf(stderr, "[%s] Warning: Can not change altitude\n", ENTITY_NAME);

                    setKillSwitch(0);
                }
                else
                {
                    fprintf(stderr, "[%s] Info: Succesfully change drone altitude to %f.\n", ENTITY_NAME, MAX_DRONE_ALTITUDE);
                }
            }

            // control horizontal speed
            float dop;
            int32_t sats;
            if (!getGpsInfo(dop, sats))
            {
                fprintf(stderr, "[%s] Warning: Can not get gps info\n", ENTITY_NAME);
            }
            else
            {
                fprintf(stderr, "[%s] Info: dop: %.9f, sats: %d\n", ENTITY_NAME, dop, sats);
            }

            // control corridor
            getPointsBetween2Waypoints(previousWaypointCoordinates.latitude, previousWaypointCoordinates.longitude, nextWaypointCoordinates.latitude, nextWaypointCoordinates.longitude, latitudeCoordinates, longitudeCoordinates);
            if (!isInsideTheBorders(currentDroneCoordinates.latitude, currentDroneCoordinates.longitude, latitudeCoordinates, longitudeCoordinates))
            {
                fprintf(stderr, "[%s] Warning: the drone's out of the corridor and landing.\n", ENTITY_NAME);
                setKillSwitch(0);
            }

            float dToN = getDistanceToPoint(currentDroneCoordinates.latitude, currentDroneCoordinates.longitude, nextWaypointCoordinates.latitude, nextWaypointCoordinates.longitude);
            fprintf(stderr, "[%s] Info: dToN %f, prev coordinates: %f %f. Go to %d  waypoint.\n", ENTITY_NAME, dToN, previousWaypointCoordinates.latitude, previousWaypointCoordinates.longitude, currentWaypoint);
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
            altitudeDifference = altitudeDifference - currentDroneCoordinates.altitude;
            travelledDistancePerTick = getDistanceToPoint(previousDroneCoordinates.latitude, previousDroneCoordinates.longitude, currentDroneCoordinates.latitude, currentDroneCoordinates.longitude);
        }
        sleep(1);
        elapsedTime = stopwatch.getELapsedTime();
        stopwatch.restart();
    }

    return EXIT_SUCCESS;
}