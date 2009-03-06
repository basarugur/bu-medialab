/**
 * Cwiid includes
 */
#include <cwiid.h>

/**
 * Global variables
 */
int g_connect_attempts = 0; /* How many times did we try to connect? */
const int g_max_connect_attempts = 10; /* How many times we will try to connect */
bdaddr_t g_bluetooth_address = *BDADDR_ANY; /* Bluetooth address-structure */
cwiid_wiimote_t * g_wiimote = NULL; /* Handles our wiimote connection */
struct cwiid_state g_wii_state; /* We capture this state on every frame */
struct acc_cal wm_cal;

void disconnect_wiimote();

/**
 * This function sets up the connection to the wiimote.
 */
bool setup_wiimote_connection()
{
    bool result = false;

    printf("Press buttons 1 and 2 on the Wiimote to connect... ");
    fflush(stdout);

    /* Establish a continous and non-blocking connection */
    g_wiimote = cwiid_connect(&g_bluetooth_address, CWIID_FLAG_CONTINUOUS|CWIID_FLAG_NONBLOCK);

    if (g_wiimote==0)
    {
        printf("failed\n");
    }
    else
    {
        printf("done\n");

        /* Power on LED 2 + 3 */
        printf("Power up LED 2+3... ");
        if (cwiid_command(g_wiimote, CWIID_CMD_LED, CWIID_LED2_ON|CWIID_LED3_ON)!=0)
        {
            printf("failed\n");
            disconnect_wiimote();
            exit(EXIT_FAILURE);
        }
        printf("done\n");

        /* Enable host-features: Infrared light sensor, buttons sensor */
        printf("Enable IR, accelerometer and buttons... ");
        if (cwiid_command(g_wiimote, CWIID_CMD_RPT_MODE, CWIID_RPT_IR|CWIID_RPT_ACC|CWIID_RPT_BTN)!=0)
        {
            printf("failed\n");
            disconnect_wiimote();
            exit(EXIT_FAILURE);
        }
        printf("done\n");

        /* Get and dump state */
        printf("Query state... ");
        if (cwiid_get_state(g_wiimote, &g_wii_state)!=0)
        {
            printf("failed\n");
            disconnect_wiimote();
            exit(EXIT_FAILURE);
        }
        printf("done\n");

        printf("Get accelerometer calibration... ");
        /* Get accelerometer calibration */
        if (cwiid_get_acc_cal(g_wiimote, CWIID_EXT_NONE, &wm_cal))
        {
        	printf("failed\n");
        	disconnect_wiimote();
            exit(EXIT_FAILURE);
        }
        else
        {
        	printf("x0:%d - x1:%d\n", wm_cal.zero[CWIID_X], wm_cal.one[CWIID_X]);
        	printf("y0:%d - y1:%d\n", wm_cal.zero[CWIID_Y], wm_cal.one[CWIID_Y]);
        	printf("z0:%d - z1:%d\n", wm_cal.zero[CWIID_Z], wm_cal.one[CWIID_Z]);
        }
        printf("done\n");

        printf("\nSome state information:\n");
        printf("-----------------------\n");
        printf("- Battery: %d%%\n\n", (int)(100.0 * g_wii_state.battery / CWIID_BATTERY_MAX));

        result = true;
    }

    return result;
}

/**
 * Disconnects the wiimote.
 */
void disconnect_wiimote()
{
    printf("\n========\n");
    printf("SHUTDOWN\n");
    printf("========\n\n");

    if (g_wiimote)
    {
        printf("Disconnecting wiimote... ");
        if (cwiid_disconnect(g_wiimote) != 0)
        {
            printf("failed\n");
        }
        printf("done\n");
    }
    fflush(stdout);
}

