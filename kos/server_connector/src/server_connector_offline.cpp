#include "../include/server_connector.h"

#include <stdio.h>
#include <string.h>

int initServerConnector()
{
    return 1;
}

int sendRequest(char *query, char *response)
{
    if (strstr(query, "/api/kill_switch?") != NULL)
        strcpy(response, "$KillSwitch: 1#");
    else if (strstr(query, "/api/auth?") != NULL)
        strcpy(response, "$Success#");
    else if (strstr(query, "/api/fmission_kos?") != NULL)
        strcpy(response, "$FlightMission H46.6143906_142.8119694_73&T2.0&W0.0_46.6141140_142.8119172_2.0&W0.0_46.6141435_142.8117889_2.0&W0.0_46.6143143_142.8117929_2.0&W0.0_46.6143199_142.8116903_2.0&W0.0_46.6141587_142.8116570_2.0&W0.0_46.6141611_142.8115112_2.0&W0.0_46.6143217_142.8115462_0.8&W0.0_46.6144433_142.8115703_2.0&S5.0_1200.0&W0.0_46.6144415_142.8116059_2.0&L46.6143906_142.8119694_73#");
    else if ((strstr(query, "/api/arm?") != NULL) || (strstr(query, "/api/fly_accept?") != NULL))
        strcpy(response, "$Arm: 0#");
    else
        strcpy(response, "$#");

    return 1;
}