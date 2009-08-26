///-----------------------------------------------------------------------------
///
/// \file	IGlut.h
/// \author	Basar Ugur
/// \brief	GLUT Window interface header file.
/// \note
///-----------------------------------------------------------------------------

#include <GL/glut.h>
#include <iostream>

#define PI 3.141592654
#define PI_HALF 1.570796327

#define HALF_EYE_SEP_CM 3

// For simulation purposes: 1024 Pixels = 40 cm
#define PX_2_CM 0.16

#define SERVER_IP "79.123.176.157"

class HeadTrackerClient;
class SceneDrawer;
class Scene;
class Camera;
class CanvasGrid;

using namespace std;

///-----------------------------------------------------------------------------
/// \brief Namespace for global GLUT environment variables
namespace glut_env
{
    static bool full_screen;

    static int cm_win_width,
               cm_win_height,
               px_win_width,
               px_win_height;

    /// Distance between User's Head and Screen Plane
    static int cm_user_height;

    /// Distance between User and Center of the Screen in CM
    static int cm_user_to_screen_center;

    /// Yaw of User relative to Screen
    static float deg_user_yaw;

    /// Viewing Frustum near clipping coefficient:
    static float K;

    // camera position (obsolete)
    // Point3 cam_pos;

    static int last_x, last_y;

    /// Glut mouse buttons:
    static unsigned char Buttons[3];

    /// Delta_t value, for assigning stereo calibrated data smoothly, not directly with noise
    static float delta_t;

    // Different modes of the program:
    static bool use_camera,    /// whether camera is used or not
                use_wiimote,   /// whether wiimote is used or not
                online_mode;   /// whether head tracking is applied in online mode

    static float half_eye_sep_x, /// half of eye separation in x axis
                 half_eye_sep_y; /// half of eye separation in y axis
}

class IGlut
{
public:
/** METHODS */
    IGlut(int argc, char** argv);
    ~IGlut();

    //-------------------------------------------------------------------------------
    /// \brief Initialization, registering GLUT related callbacks
    static void Init();

    //-------------------------------------------------------------------------------
    /// \brief Starting main loop for GLUT
    void StartMainLoop();

    //-------------------------------------------------------------------------------
    /// \brief	Called when a mouse motion occurs
    //
    static void Motion(int x, int y);


    //-------------------------------------------------------------------------------
    /// \brief	Called when a keyboard action occurs
    //
    static void Keyboard(unsigned char key, int x, int y);


    //-------------------------------------------------------------------------------
    /// \brief	Called when a mouse button action occurs
    //
    static void Mouse(int button, int state, int x, int y);


    //-------------------------------------------------------------------------------
    /// \brief	Called when the screen gets resized
    /// \param	w	-	the new width
    /// \param	h	-	the new height
    ///
    static void Reshape(int w, int h);

    //-------------------------------------------------------------------------------
    /// \brief Called when a glut window update occurs
    static void Display(void);

    //-------------------------------------------------------------------------------
    /// \brief Creates a drawable 3D scene
    void CreateScene(Scene* scn_, string VRMLfile);

    //-------------------------------------------------------------------------------
    /// \brief Draw the current 3D scene with GL functions (obsolete)
    // void DrawScene();

    //-------------------------------------------------------------------------------
    /// \brief Drawing a reference grid at base, i.e. "y=0" plane.
    static void DrawBaseGrid();

    //-------------------------------------------------------------------------------
    /// \brief Disparity preparation for left / right stereo buffers and
    ///         drawing afterwards.
    static void DrawToOneBuffer(float cm_camera_tilt_x, float cm_camera_tilt_y);

    //-------------------------------------------------------------------------------
    /// \brief Updating user / camera position by mouse position
    ///        relative to monitor center
    static void UpdateUserPositionByMouse(int mouse_x, int mouse_y);

    //-------------------------------------------------------------------------------
    /// \brief Updating user / camera position by head tracking
    static void UpdateUserPositionByTracking();

    //-------------------------------------------------------------------------------
    /// \brief OpenGL Fog Effect, added by Ozan Cetinaslan
    static void FogEffect(float fogKey);

    //-------------------------------------------------------------------------------
    /// \brief Initializing Head Tracker (+ Network Client) module
    static void InitHeadTracker();

    //-------------------------------------------------------------------------------
    /// \brief Closing Head Tracker module
    static void CloseHeadTracker();

/** VARIABLES */

    static HeadTrackerClient* p_htc;

    static Scene* p_scene;
    static Camera* p_camera;
    static SceneDrawer* p_drawer;
    static CanvasGrid* p_grid;
};
