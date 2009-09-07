///-----------------------------------------------------------------------------
///
/// \file	main.cpp
/// \author	Basar Ugur
/// \brief	Moved on from Rob Bateman's simple viewer for GLUT,
///         an enhanced Stereo VRML2.0 viewer
/// \note
///-----------------------------------------------------------------------------

#include "IGlut.h"

//-------------------------------------------------------------------------------
/// \brief Main program loop.

int main(int argc, char** argv)
{
    /**
    if (strstr(argv[0], "-r") != NULL)//******************
        //showgrid = 1;//**********************
    //g = new Geometry("bunny.wrl", "Whole_Bunny");
	o1 = new SceneObject("res/chapel_97.wrl","OB_Ground_Ground_M");
	o1->children[0].scale(20, 20, 20);

	//o2  = new SceneObject("res/chapel_97.wrl", "OB_Thumbstone_Chapel");
    o2  = new SceneObject("res/box.wrl", "OB_rsvd_Box");

	// Write example:
	vrml_io writer;
	writer.write(g, "new.wrl", "New-Name");
	*/

    IGlut _iGlut(argc, argv);

    _iGlut.Init();
}
