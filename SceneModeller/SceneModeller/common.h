#ifndef SM_COMMON_H
#define SM_COMMON_H



class Vector3;

Vector3 RotateVectorAroundVector(Vector3 trg_,Vector3 bse_,double angle);

enum SMEditingMode
{
	SINGLE_OBJECT_MODE = 0,
	OBJECT_TREE_MODE = 1,
	CAMERA_EDITING_MODE = 2,
	LIGHT_EDITING_MODE = 3,
	FACE_EDITING_MODE = 4,
	VERTEX_EDITING_MODE = 5
};

enum SMEditingType
{
	TRANSLATE_TYPE = 0,
	ROTATE_TYPE = 1,
	SCALE_TYPE = 2,
	DELETE_TYPE = 3,
	DUPLICATE_TYPE = 4,
	ADD_CHILD_TYPE = 5,
	REMOVE_CHILD_TYPE = 6,
	CONVERT_TO_MESH = 7,
	SPLIT_FACE = 8,
	EXTRUDE_FACE = 9,
	MOVE_TARGER = 10,
	MOVE_CAMERA = 11
};

class SMGlobalSettings
{
public:
	static SMEditingMode getEditingMode()
	{
		return m_editing_mode;
	}
	static void setEditingMode(SMEditingMode md_)
	{
		m_editing_mode = md_;
	}
	static SMEditingType getEditingType()
	{
		return m_editing_type;
	}
	static void setEditingType(SMEditingType type_)
	{
		m_editing_type = type_;
	}

	static SMEditingMode m_editing_mode;
	static SMEditingType m_editing_type;
};


#endif // SCENEMODELLER_H
