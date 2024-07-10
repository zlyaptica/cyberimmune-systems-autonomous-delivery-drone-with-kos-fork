#ifndef COORDINATES_H
#define COORDINATES_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "constants.h"

#include "../../shared/include/ipc_messages_navigation_system.h"

// const int POINTS_IN_BETWEEN = 22; // количество точек между вейпоинтами с учетом самих вейпоинтов
// const double WAYPOINT_RADIUS = 2.0;
// const float MAXIMUM_DRONE_SPEED = 5.5;
// const float MAX_DRONE_ALTITUDE = 500;

struct pointCoordinates // координаты точки float типа
{
    float latitude;
    float longitude;
    float altitude;
};

// создает массив с промежуточными точками между вейпоинтами
void getPointsBetween2Waypoints(float x1, float y1, float x2, float y2, float *latitudeCoordinates, float *longitudeCoordinates);
// вычисляет расстояние между двумя точками
float getDistanceToPoint(float x1, float y1, float x2, float y2);
// проверяет, не ушел ли дрон за пределы коридора
bool isInsideTheBorders(float currentLatitude, float currentLongitude, float *latitudeCoordinates, float *longitudeCoordinates);
// возвращает истонное значение координаты типа float умноженное на  10^-7
float convertCoordinatesToFloat(int32_t value);
// возвращает массив текущих координат дрона с типом float, где [0] - результат, возвращенный getCoords(), [1]-[3] - координаты
float *getFormattedCoordinates();


#endif