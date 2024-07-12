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
        strcpy(response, "$FlightMission H46.6143906_142.8119694_73&T1.4&W0.0_46.6141204_142.8119177_1.4&W0.0_46.6141435_142.8117889_1.4&W0.0_46.6143208_142.8117950_1.4&W0.0_46.6143328_142.8116897_1.4&W0.0_46.46.6141605_142.8116407_1.4&W0.0_46.6141651_142.8115234_1.4&W0.0_46.6143632_142.8115542_1.0&W0.0_46.6144433_142.8115703_1.0&S5.0_1200.0&W0.0_46.6144410_142.8115800_1.4&S5.0_1800.0&W0.0_46.6143906_142.8119694_1.4&L46.6143906_142.8119694_74#");
    else if ((strstr(query, "/api/arm?") != NULL) || (strstr(query, "/api/fly_accept?") != NULL))
        strcpy(response, "$Arm: 0#");
    else
        strcpy(response, "$#");

    return 1;
}