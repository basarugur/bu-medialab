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

#define HALF_EYE_SEP_CM 5

// For with-mouse simulation purposes: 1024 Pixels = 40 cm
#define PX_2_CM 0.16

#define PX_WIN_WIDTH 1024
#define PX_WIN_HEIGHT 768

#define SERVER_IP "79.123.176.157"

class HeadTrackerClient;
class Scene;
class Camera;
class CanvasGrid;
class RenderController;
class Light;
class Shader;

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
    static bool use_stereo_camera,    /// whether stereo camera is used or not
                use_wiimote,   /// whether wiimote is used or not
                online_mode,   /// whether head tracking is applied in online mode
                use_shaders;   /// whether "blurring far objects" shading will be used

    static float half_eye_sep_x, /// half of eye separation in x axis
                 half_eye_sep_y; /// half of eye separation in y axis

    static GLfloat gl_light_position[4] = { 10.0f, 10.0f, -20.0f, 1.0f };
    static GLfloat gl_light_intensity[4] = { 0.8f, 0.8f, 0.8f, 1.0f };
    static GLfloat gl_ambient_intensity[4] = { 0.4f, 0.4f, 0.4f, 1.0f };

    static enum {
        TOGGLE_FULLSCREEN = 0,
        TOGGLE_WIIMOTE = 1,
        RENDER_SCENE = 2
    } options;

    static GLubyte frame_buf[PX_WIN_WIDTH][PX_WIN_HEIGHT][4];
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
    /// \brief Texture-related initializations
    static void InitTextures();

    //-------------------------------------------------------------------------------
    /// \brief Right click menu items preparation
    static void PrepareMenus();

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
    /// \brief	Called when a timer function period is passed
    //
    static void Timer(int timer_id);


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
    /// \brief Selects from several action options, such as "toggle fullscreen", etc
    static void SelectOption(int opt);

    //-------------------------------------------------------------------------------
    /// \brief Creates a drawable 3D scene
    static void CreateScene(string VRMLfile);

    //-------------------------------------------------------------------------------
    /// \brief GLUI interface control callback
    static void GLUIControl(int ui_item_id);

    //-------------------------------------------------------------------------------
    /// \brief Get a copy of frame buffer to textures[0]
    static void CopyFrameBufferToTexture();

    //-------------------------------------------------------------------------------
    /// \brief Draw fullscreen texture copy of frame buffer with simple shading
    static void DrawTextureWithShader(float cm_camera_tilt_x, float cm_camera_tilt_y);

    //-------------------------------------------------------------------------------
    /// \brief Off-axis frustum preparation for left / right stereo buffers and
    ///         drawing afterwards.
    /// For shading, drawing of 3D scene is done twice.
    /// At first pass, frame buffer is cleared so that a clear picture
    /// of the scene can be copied to the texture.
    /// At second pass, texture is drawn with shaders, and then
    /// the scene is drawn again.
    static void DrawToOneBuffer(float cm_camera_tilt_x, float cm_camera_tilt_y,
                                float frustum_z_start, float frustum_z_end,
                                bool first_pass);

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

/** ATTRIBUTES */

    static HeadTrackerClient* p_htc;

    static Scene* p_scene;
    static Camera* p_camera;
    static CanvasGrid* p_grid;
    static RenderController* p_rc;
    static Light* p_light;
    static Shader* p_shader;

    static int submenus[1];
    static GLuint textures[1];
};
