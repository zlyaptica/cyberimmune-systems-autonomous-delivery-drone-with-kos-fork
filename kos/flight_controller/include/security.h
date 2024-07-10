#ifndef SECURITY_H
#define SECURITY_H

#include <stdio.h>

#include "constants.h"
#include "coordinates.h"
#include "mission.h"
#include "stopwatch.h"

#include "../../shared/include/initialization_interface.h"
#include "../../shared/include/ipc_messages_initialization.h"
#include "../../shared/include/ipc_messages_autopilot_connector.h"
#include "../../shared/include/ipc_messages_credential_manager.h"
#include "../../shared/include/ipc_messages_navigation_system.h"
#include "../../shared/include/ipc_messages_periphery_controller.h"
#include "../../shared/include/ipc_messages_server_connector.h"

#include "constants.h"

using namespace std;

class Security
{
private:
    uint32_t commandNum;
    MissionCommand *commands;
    uint32_t currentWaypoint;
    uint32_t currentDropCargoWaypoint; // номер вейпоинта со сброс груза

    pointCoordinates previousWaypointCoordinates; // координаты вейпоинта, который пролетел дрон. Первая точка - старт
    pointCoordinates nextWaypointCoordinates;     // координаты вейпоинта, на который должен прилететь дрон

    pointCoordinates previousDroneCoordinates;
    pointCoordinates currentDroneCoordinates;
    float currentMaximumDroneAltitude; // максимальная высота, с которой летел дрон
    float altitudeDifference;          // разница высота за тик для вычисления вертикальной скорости. Рассчитывается как разница между текущей высотой и значением данной переменной

    int32_t reachedWaypoint; // вейпонт, который пролетел дрон

    float currentHorizontalDroneSpeed;
    float currentMaximumHorizontalDroneSpeed; // максимальная скорость, с которой дрон летел горизонтально
    float currentMaximumVerticalDroneSpeed; // максимальная скорость, с которой дрон летел вертикально
    float currentVerticalDroneSpeed;

    float elapsedTime = 0;                         // время, затраченное дроном на один тик
    float travelledDistancePerTick = 0;            // пройденная дроном дистанция за один тик
    float latitudeCoordinates[POINTS_IN_BETWEEN];  // массив с промежуточными координатами широты между контрольными точками для идентификации середины коридора
    float longitudeCoordinates[POINTS_IN_BETWEEN]; // массив с промежуточными координатами долготы между контрольными точками для идентификации середины коридора

public:
    Security(uint32_t commandNum, MissionCommand *commands);
    bool isDroneFlying();
    // обновляет данные о следующем вейпоинте, если дрон в зоне радиуса вейпоинта. + обновление координат текущего и след вейпоинта
    void getNextWaypoint();
    void calculateSpeed();
    void secure();
    void controlVerticalSpeed();
    void controlHorizontalSpeed();
    void controlCargoLock();
    void controlAltitude();
    void controlCorridor();

    void lockServo();

    void printLog();
};

#endif