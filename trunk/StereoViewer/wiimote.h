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

const static float delta_acc = .005f;
static float delta_tr = .1f;//.05f;
const static float rad2deg = 180.f / PI;

static char wii_msg[255] = "";

/**
 * GLUT function to display \a string at position (\a x,\a y,\a z).
 */
void renderString(float x, float y, float z, char *string)
{
    char * c;

   glDisable(GL_LIGHTING);

    glRasterPos3f(x, y, z);

    for(c=string; *c!='\0'; c++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }

    glEnable(GL_LIGHTING);
}

void disconnect_wiimote();

/**
 * This function sets up the connection to the wiimote.
 */
bool setup_wiimote_connection()
{
    bool result = false;

    printf(wii_msg);
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

bool check_wiimote()
{
    if ( !g_wiimote )
    {
        if ( g_connect_attempts < g_max_connect_attempts )
        {
            sprintf(wii_msg, "Press button 1+2 on your Wiimote! (%d of %d)", g_connect_attempts+1, g_max_connect_attempts);

            glutPostRedisplay(); /* Inform GLUT to constantly update the screen */
            glutSwapBuffers(); /* High-end-machines may need this */

            /**
            *   Wiimote will NOT be connected at first attempt,
            *   OpenGL text message should be prompted previously
            *   so that bluetooth connection attempt does not block.
            */
            if (g_connect_attempts == 0)
            {
                g_connect_attempts++;
                return false;
            }

            setup_wiimote_connection();
            g_connect_attempts++;
        }
        else
        {
            sprintf(wii_msg, "Unable to connect to Wiimote! Press <Esc> to quit.");

            //renderString(-2, -2, 10, "Unable to connect to Wiimote! Press <Esc> to quit.");
            glutPostRedisplay(); /* Inform GLUT to constantly update the screen */
            glutSwapBuffers(); /* High-end-machines may need this */
        }
        return false;
    }
    else
	{
        sprintf(wii_msg, "");

		cwiid_get_state(g_wiimote, &g_wii_state); /* Capture the current wiimote-state. */

		return true;
	}
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

    g_connect_attempts = 0;
}

/**
 * Checking wiimote connection and setting up if not exists
 */
void update_object_by_wiimote(Rotation* ch_r, Point* ch_pos, bool object_mode, int last_x, int last_y)
{
	static double ir_positions[2][2] = { { 0, 0 }, { 0, 0 } };
    static int ir_sizes[2] = { 3, 3 }; /* Expect it to be around 2-8 in wiimote state struct */

    if ( check_wiimote() )
    {
        int diffx, diffy;
		if (last_x > 0) // Valid data
		{
			diffx = g_wii_state.acc[0] - last_x,
			diffy = g_wii_state.acc[2] - last_y;
		}
		else
			diffx = diffy = 0;

		last_x = g_wii_state.acc[0];
		last_y = g_wii_state.acc[2];

		uint8_t leds = 0x00;
		for (int i=0; i < 4; i++)
        {
        	if (g_wii_state.ir_src[i].valid)
	        	leds |= 0x01 * (i+1);

        	//printf("%2d %4d %4d %4d | ", g_wii_state.ir_src[i].valid, g_wii_state.ir_src[i].pos[CWIID_X], g_wii_state.ir_src[i].pos[CWIID_Y], g_wii_state.ir_src[i].size);
            /*
            double x, y;

            if (g_wii_state.ir_src[i].valid)
            {
            	x = g_wii_state.ir_src[i].pos[CWIID_X] * 64 / ((double) CWIID_IR_X_MAX);
                y = 64 - g_wii_state.ir_src[i].pos[CWIID_Y] * 64 / (double) CWIID_IR_Y_MAX;

                ir_positions[i][0] = x;
                ir_positions[i][1] = y;

                if (g_wii_state.ir_src[i].size != -1)
                {
                    ir_sizes[i] = g_wii_state.ir_src[i].size+1;
                }
            }
            else
            {
                x = ir_positions[i][0];
                y = ir_positions[i][1];
            }*/


        }
		//printf(" LEDS: %d\n", leds);

        /* Check if the home button is pressed, then exit */
		if ( g_wii_state.buttons & CWIID_BTN_HOME )
		{
			disconnect_wiimote();
		    exit(EXIT_SUCCESS);
		}

		if ( g_wii_state.buttons & CWIID_BTN_A && g_wii_state.buttons & CWIID_BTN_B )
			object_mode = !object_mode;
		else if ( g_wii_state.buttons & CWIID_BTN_LEFT )
			ch_pos->x -= delta_tr;
		else if ( g_wii_state.buttons & CWIID_BTN_RIGHT )
			ch_pos->x += delta_tr;
		else if ( g_wii_state.buttons & CWIID_BTN_UP )
			ch_pos->y += delta_tr;
		else if ( g_wii_state.buttons & CWIID_BTN_DOWN )
			ch_pos->y -= delta_tr;
		else if ( g_wii_state.buttons & CWIID_BTN_A )
			ch_pos->z += delta_tr;
		else if ( g_wii_state.buttons & CWIID_BTN_B )
			ch_pos->z -= delta_tr;

        float a_x = ((float)g_wii_state.acc[CWIID_X] - wm_cal.zero[CWIID_X]) /
        	          (wm_cal.one[CWIID_X] - wm_cal.zero[CWIID_X]);
        float a_y = ((float)g_wii_state.acc[CWIID_Y] - wm_cal.zero[CWIID_Y]) /
        	      (wm_cal.one[CWIID_Y] - wm_cal.zero[CWIID_Y]);
        float a_z = ((float)g_wii_state.acc[CWIID_Z] - wm_cal.zero[CWIID_Z]) /
        	      (wm_cal.one[CWIID_Z] - wm_cal.zero[CWIID_Z]);
        //float a = sqrt(pow(a_x,2)+pow(a_y,2)+pow(a_z,2));

		float a_t = atan(a_x/a_z);
		if (a_z == 0.f || cos(a_t) < .000001f)
			return;

        if (a_z <= 0.f)
        	a_t += PI * ((a_x > 0.f) ? 1 : -1);

        a_t *= -1;

		//printf("%d %d %d\n",g_wii_state.acc[CWIID_X] - wm_cal.zero[CWIID_X], g_wii_state.acc[CWIID_Y] - wm_cal.zero[CWIID_Y], g_wii_state.acc[CWIID_Z] - wm_cal.zero[CWIID_Z]);

        ch_r->pitch = ch_r->pitch + (atan(a_y/a_z*cos(a_t)) * rad2deg - ch_r->pitch) * delta_acc;
        ch_r->roll = ch_r->roll + (a_t*rad2deg - ch_r->roll) * delta_acc;

        //printf("accelerator data\n");
		/*for (int i = 0; i < 3; i++)
			printf("%d ", g_wii_state.acc[i]);
		printf("\n");
		if (abs(diffx) > 1 || abs(diffy) > 1)
			printf("%d %d - %d %d - %d %d\n", g_wii_state.acc[0], g_wii_state.acc[2], last_x, last_y, diffx, diffy);

		printf("%d %d - %d %d - %d %d\n", g_wii_state.acc[0], g_wii_state.acc[2], last_x, last_y, diffx, diffy);
		tx += (float) 0.05f * diffx;
		ty -= (float) 0.05f * diffy;
		*/

		return;
	}
}

