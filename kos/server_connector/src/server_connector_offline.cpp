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
        strcpy(response, "$FlightMission H46.6143906_142.8119694_73&T1.5&W0.0_46.6141188_142.8119172_1.5&W0.0_46.6141431_142.8117610_1.5&W0.0_46.6143290_142.8117956_1.5&W0.0_46.6143362_142.8116908_1.5&W0.0_46.6141587_142.8116570_1.5&W0.0_46.6141611_142.8115112_1.5&W0.0_46.6143632_142.8115542_0.7&W0.0_46.6144542_142.8115727_1.5&S5.0_1200.0&W0.0_46.6144484_142.8116072_1.5&L46.6143906_142.8119694_73#");
    else if ((strstr(query, "/api/arm?") != NULL) || (strstr(query, "/api/fly_accept?") != NULL))
        strcpy(response, "$Arm: 0#");
    else
        strcpy(response, "$#");

    return 1;
}