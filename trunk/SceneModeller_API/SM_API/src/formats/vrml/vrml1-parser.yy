%skeleton "lalr1.cc"                          /*  -*- C++ -*- */
%require "2.3"
%defines
%define "parser_class_name" "vrml1_parser"
%name-prefix="vrml1"

%{
#include <string>


namespace vrml1 {
	class Driver;
}
%}

// The parsing context.
%parse-param { vrml1::Driver& driver }
%lex-param   { vrml1::Driver& driver }

%locations
%initial-action
{
	// Initialize the initial location.
	@$.begin.filename = @$.end.filename = &driver.file;
};

%debug
%error-verbose

// Symbols.
%union
{
	int ival;
	float fval;
	std::string *sval;
};

%{
#include "Driver.hh"
%}

     
/* declarations */
%token 		END 0 "end of file"
%token KW_Separator
%token KW_BRACKETOPEN
%token KW_BRACKETCLOSE
%token KW_Cube
%token KW_width
%token KW_height
%token KW_depth
%token KW_SIDES
%token KW_parts
%token KW_bottomRadius
%token KW_BOTTOM
%token KW_Cone
%token KW_ALL
%token KW_Sphere
%token KW_radius
%token KW_Cylinder
%token KW_TOP
%token KW_DirectionalLight
%token KW_intensity
%token KW_color
%token KW_on
%token KW_direction
%token KW_FALSE
%token KW_TRUE
%token KW_transparency
%token KW_Material
%token KW_emissiveColor
%token KW_ambientColor
%token KW_specularColor
%token KW_shininess
%token KW_diffuseColor
%token KW_OVERALL
%token KW_MaterialBinding
%token KW_PER_FACE
%token KW_value
%token KW_PER_VERTEX_INDEXED
%token KW_PER_PART
%token KW_PER_FACE_INDEXED
%token KW_DEFAULT
%token KW_PER_PART_INDEXED
%token KW_PER_VERTEX
%token KW_Translation
%token KW_translation
%token KW_Rotation
%token KW_rotation
%token KW_Scale
%token KW_scaleFactor
%token KW_MatrixTransform
%token KW_matrix
%token KW_scaleOrientation
%token KW_Transform
%token KW_center
%token KW_OrthographicCamera
%token KW_position
%token KW_orientation
%token KW_focalDistance
%token KW_heightAngle
%token KW_PerspectiveCamera
%token KW_PointLight
%token KW_SpotLight
%token KW_cutOffAngle
%token KW_dropOffRate
%token KW_location
%token KW_Texture2Transform
%token KW_creaseAngle
%token KW_CLOCKWISE
%token KW_CONVEX
%token KW_vertexOrdering
%token KW_SOLID
%token KW_COUNTERCLOCKWISE
%token KW_shapeType
%token KW_UNKNOWN_FACE_TYPE
%token KW_UNKNOWN_ORDERING
%token KW_faceType
%token KW_UNKNOWN_SHAPE_TYPE
%token KW_ShapeHints
%token KW_NormalBinding
%token KW_SANS
%token KW_TYPEWRITER
%token KW_LOD
%token KW_style
%token KW_SERIF
%token KW_size
%token KW_range
%token KW_family
%token KW_FontStyle
%token KW_ITALIC
%token KW_NONE
%token KW_BOLD
%token KW_LEFTPARENTHESIS
%token KW_RIGHTPARENTHESIS
%token KW_BAR
%token KW_COMMA
%token KW_SQUAREDBRACKETOPEN
%token KW_SQUAREDBRACKETCLOSE
%token KW_vector
%token KW_Normal
%token KW_point
%token KW_Coordinate3
%token KW_TextureCoordinate2
%token KW_startIndex
%token KW_numPoints
%token KW_PointSet
%token KW_textureCoordIndex
%token KW_normalIndex
%token KW_coordIndex
%token KW_IndexedLineSet
%token KW_materialIndex
%token KW_IndexedFaceSet
%token KW_renderCulling
%token KW_OFF
%token KW_AUTO
%token KW_ON
%token KW_whichChild
%token KW_Switch
%token KW_filename
%token KW_wrapT
%token KW_CLAMP
%token KW_Texture2
%token KW_image
%token KW_REPEAT
%token KW_wrapS
%token KW_WWWInline
%token KW_bboxCenter
%token KW_bboxSize
%token KW_name
%token KW_map
%token KW_POINT
%token KW_description
%token KW_WWWAnchor
%token KW_justification
%token KW_CENTER
%token KW_spacing
%token KW_string
%token KW_RIGHT
%token KW_AsciiText
%token KW_LEFT
%token KW_ZERO
%token KW_ONE
%token KW_DEF
%token KW_USE
%token KW_VRML_ID
%token <fval> TYPE_FLOAT "float"
%token <ival> TYPE_INTEGER "integer"
%token <sval> TYPE_STRING "string"

%destructor { delete $$; } "string" 
%printer    { debug_stream () << $$; } "string" "float" "integer" 


%% /* the grammar */
start:	KW_VRML_ID Body { driver.pushVRMLDoc(); }
	;
	
Body: Separator
	| Separator Body 
	;
     
Separator: KW_Separator BracketOpen Separator_Body BracketClose  { driver.pushNodeSeparator(); }
	;
	
Separator_Body:	 /* empty */
	| renderCulling Separator_Childs
	| Separator_Childs
	;
	
renderCulling: KW_renderCulling renderCulling_Enums { driver.pushAttributeSFLong("renderCulling"); }
	;
	
renderCulling_Enums: KW_OFF { driver.pushInteger(0x00); }
	| KW_ON { driver.pushInteger(0x01); }
	| KW_AUTO { driver.pushInteger(0x02); }
	;



Separator_Childs: Separator_DEF
	| Separator_USE 
	| Separator_DEF Separator_Childs
	| Separator_USE Separator_Childs
	;

Separator_DEF: KW_DEF Identifier Separator_Tokens { if (!driver.pushDEF()) { YYERROR; }  }
	| Separator_Tokens
	;

Separator_USE: KW_USE Identifier { if (!driver.pushUSE()) { YYERROR; }  }
	;	

Separator_Tokens: Cube
	| Cone
	| Sphere
	| Cylinder
	| Material
	| MaterialBinding
	| Translation
	| Rotation
	| Scale
	| MatrixTransform
	| Transform
	| OrthographicCamera
	| PerspectiveCamera
	| PointLight
	| SpotLight
	| DirectionalLight
	| Texture2Transform
	| ShapeHints
	| NormalBinding 
	| Normal
	| Coordinate3
	| TextureCoordinate2
	| PointSet
	| IndexedLineSet
	| IndexedFaceSet
	| FontStyle
	| LOD
	| Texture2
	| WWWInline
	| WWWAnchor
	| AsciiText
	| Separator
	| Switch
	| MFColor
	| MFString
	;
	
	
	
Switch: KW_Switch BracketOpen Switch_Body BracketClose { driver.pushNodeSwitch(); }
	;
	
Switch_Body: /* empty */
	| whichChild Separator_Childs
	| Separator_Childs
	;
	
	
whichChild: KW_whichChild SFLong { driver.pushAttributeSFLong("whichChild"); }
	;



Cube:	KW_Cube BracketOpen Cube_Body BracketClose { driver.pushNodeCube(); }
	;

Cube_Body: /* empty */ 
	| Cube_Attributes
	;

Cube_Attributes:  Cube_Attribute
	| Cube_Attributes  Cube_Attribute
	;
	
Cube_Attribute:	KW_width SFFloat { driver.pushAttributeSFFloat("width"); }
	| KW_height SFFloat { driver.pushAttributeSFFloat("height"); }
	| KW_depth SFFloat { driver.pushAttributeSFFloat("depth"); }
	;
	
	
	
Cone: KW_Cone BracketOpen Cone_Body BracketClose { driver.pushNodeCone(); }
	;	
	
Cone_Body: /* empty */
	| Cone_Attributes
	;

Cone_Attributes: Cone_Attribute
	| Cone_Attributes Cone_Attribute
	;
	
Cone_Attribute: KW_parts Cone_Parts { driver.pushAttributeSFBitmask("parts"); }
	| KW_bottomRadius SFFloat { driver.pushAttributeSFFloat("bottomRadius"); }
	| KW_height SFFloat { driver.pushAttributeSFFloat("height"); }
	;
	
Cone_Parts: Cone_Part
	| KW_LEFTPARENTHESIS Cone_Part_Mask KW_RIGHTPARENTHESIS
	;
	
Cone_Part_Mask: Cone_Part
	| Cone_Part KW_BAR Cone_Part_Mask
	;	
	
Cone_Part: KW_SIDES { driver.pushInteger(0x01); }
	| KW_BOTTOM { driver.pushInteger(0x02); }
	| KW_ALL { driver.pushInteger(0x03); }
	;
	
	
	
Sphere: KW_Sphere BracketOpen Sphere_Body BracketClose {  driver.pushNodeSphere(); }	
	;
	
Sphere_Body: /* empty */
	| KW_radius SFFloat { driver.pushAttributeSFFloat("radius"); }
	;	



Cylinder: KW_Cylinder BracketOpen Cylinder_Body BracketClose { driver.pushNodeCylinder(); }
	;
	
Cylinder_Body: /* empty */
	| Cylinder_Attributes
	;
	
Cylinder_Attributes: Cylinder_Attribute
	| Cylinder_Attributes Cylinder_Attribute
	;
	
Cylinder_Attribute: KW_parts Cylinder_Parts { driver.pushAttributeSFBitmask("parts"); }
	| KW_radius SFFloat { driver.pushAttributeSFFloat("radius"); }
	| KW_height SFFloat { driver.pushAttributeSFFloat("height"); }
	;
	
Cylinder_Parts: KW_SIDES
	| KW_LEFTPARENTHESIS Cylinder_Part_Mask KW_RIGHTPARENTHESIS
	;

Cylinder_Part_Mask: Cylinder_Part
	| Cylinder_Part KW_BAR Cylinder_Part_Mask
	;	
	
Cylinder_Part: KW_SIDES { driver.pushInteger(0x01); }
	| KW_TOP  { driver.pushInteger(0x02); }
	| KW_BOTTOM  { driver.pushInteger(0x04); }
	| KW_ALL  { driver.pushInteger(0x07); }
	;



Material: KW_Material BracketOpen Material_Body BracketClose { driver.pushNodeMaterial(); }
	;
	
Material_Body: /* empty */
	| Material_Attributes
	;
	
Material_Attributes: Material_Attribute
	| Material_Attributes Material_Attribute
	;
	
Material_Attribute: KW_ambientColor MFColor { driver.pushAttributeMFColor("ambientColor"); }
	| KW_diffuseColor MFColor { driver.pushAttributeMFColor("diffuseColor"); }
	| KW_specularColor MFColor { driver.pushAttributeMFColor("specularColor"); }
	| KW_emissiveColor MFColor { driver.pushAttributeMFColor("emissiveColor"); }
	| KW_shininess MFFloat { driver.pushAttributeMFFloat("shininess"); }
	| KW_transparency MFFloat { driver.pushAttributeMFFloat("transparency"); }
	;



MaterialBinding: KW_MaterialBinding BracketOpen MaterialBinding_Body KW_MaterialBinding { driver.pushNodeMaterialBinding(); }
	;
	
MaterialBinding_Body: /* empty */
	| KW_value MaterialBinding_value { driver.pushAttributeSFLong("value"); }
	;

MaterialBinding_value: KW_DEFAULT { driver.pushInteger(0); }
	| KW_OVERALL  { driver.pushInteger(1); }
	| KW_PER_PART { driver.pushInteger(2); }
	| KW_PER_PART_INDEXED { driver.pushInteger(3); }
	| KW_PER_FACE { driver.pushInteger(4); }
	| KW_PER_FACE_INDEXED { driver.pushInteger(5); }
	| KW_PER_VERTEX { driver.pushInteger(6); }
	| KW_PER_VERTEX_INDEXED { driver.pushInteger(7); }
	;



Translation: KW_Translation BracketOpen Translation_Body BracketClose { driver.pushNodeTranslation(); }
	;
	
Translation_Body: /* empty */
	| KW_translation SFVec3f { driver.pushAttributeSFVec3f("translation"); }
	;



Rotation: KW_Rotation BracketOpen Rotation_Body BracketClose { driver.pushNodeRotation(); } 
	;
	
Rotation_Body: /* empty */
	| KW_rotation SFRotation { driver.pushAttributeSFRotation("rotation"); }
	;


	
Scale: KW_Scale BracketOpen Scale_Body BracketClose { driver.pushNodeScale(); }

Scale_Body: /* empty */
	| KW_scaleFactor SFVec3f { driver.pushAttributeSFVec3f("scaleFactor"); }
	;



MatrixTransform: KW_MatrixTransform BracketOpen MatrixTransform_Body BracketClose { driver.pushNodeMatrixTransform(); }
	;
	
MatrixTransform_Body: /* empty */
	| KW_matrix SFMatrix { driver.pushAttributeSFMatrix("matrix"); }
	;



Transform: KW_Transform BracketOpen Transform_Body BracketClose { driver.pushNodeTransform(); } 
	;

Transform_Body: /* empty */
	| Transform_Attributes
	;
	
Transform_Attributes: Transform_Attribute
	| Transform_Attributes Transform_Attribute
	;
	
Transform_Attribute: KW_translation SFVec3f { driver.pushAttributeSFVec3f("translation"); }
	| KW_rotation SFRotation { driver.pushAttributeSFRotation("rotation"); }
	| KW_scaleFactor SFVec3f { driver.pushAttributeSFVec3f("scaleFactor"); }
	| KW_scaleOrientation SFRotation { driver.pushAttributeSFRotation("scaleOrientation"); }
	| KW_center SFVec3f { driver.pushAttributeSFVec3f("center"); }
	;



OrthographicCamera: KW_OrthographicCamera BracketOpen OrthographicCamera_Body BracketClose { driver.pushNodeOrthographicCamera(); }
	;
	
OrthographicCamera_Body: /* empty */
	| OrthographicCamera_Attributes
	;
	
OrthographicCamera_Attributes: OrthographicCamera_Attribute
	| OrthographicCamera_Attributes OrthographicCamera_Attribute
	;
	
OrthographicCamera_Attribute: KW_position SFVec3f { driver.pushAttributeSFVec3f("position"); }
	| KW_orientation SFRotation { driver.pushAttributeSFVec3f("orientation"); }
	| KW_focalDistance SFFloat { driver.pushAttributeSFFloat("focalDistance"); }
	;
	
	
	
PerspectiveCamera: KW_PerspectiveCamera BracketOpen PerspectiveCamera_Body BracketClose { driver.pushNodePerspectiveCamera(); }
	;
	
PerspectiveCamera_Body: /* empty */
	| PerspectiveCamera_Attributes
	;
	
PerspectiveCamera_Attributes: PerspectiveCamera_Attribute
	| PerspectiveCamera_Attributes PerspectiveCamera_Attribute
	;
	
PerspectiveCamera_Attribute: KW_position SFVec3f { driver.pushAttributeSFVec3f("position"); }
	| KW_orientation SFRotation { driver.pushAttributeSFRotation("orientation"); }
	| KW_focalDistance SFFloat { driver.pushAttributeSFFloat("focalDistance"); }
	| KW_heightAngle SFFloat { driver.pushAttributeSFFloat("heightAngle"); }
	;
	


PointLight: KW_PointLight BracketOpen PointLight_Body BracketClose { driver.pushNodePointLight(); }

PointLight_Body: /* empty */
	| PointLight_Attributes
	;
	
PointLight_Attributes: PointLight_Attribute
	| PointLight_Attributes PointLight_Attribute
	;
	
PointLight_Attribute: KW_on SFBool { driver.pushAttributeSFBool("on"); }
	| KW_intensity SFFloat { driver.pushAttributeSFFloat("intensity"); }
	| KW_color SFColor { driver.pushAttributeSFColor("color"); }
	| KW_location SFVec3f { driver.pushAttributeSFVec3f("location"); }
	;
	
	
	
SpotLight: KW_SpotLight BracketOpen SpotLight_Body BracketClose { driver.pushNodeSpotLight(); }
	;
	
SpotLight_Body: /* empty */
	| SpotLight_Attributes
	;
	
SpotLight_Attributes: SpotLight_Attribute
	| SpotLight_Attributes SpotLight_Attribute
	;
	
SpotLight_Attribute: KW_on SFBool { driver.pushAttributeSFBool("on"); }
	| KW_intensity SFFloat { driver.pushAttributeSFFloat("intensity"); }
	| KW_color SFColor { driver.pushAttributeSFColor("color"); }
	| KW_location SFVec3f { driver.pushAttributeSFVec3f("location"); }
	| KW_direction SFVec3f { driver.pushAttributeSFVec3f("direction"); }
	| KW_dropOffRate SFFloat { driver.pushAttributeSFFloat("dropOffRate"); }
	| KW_cutOffAngle SFFloat { driver.pushAttributeSFFloat("cutOffAngle"); }
	;
	
	
	
DirectionalLight: KW_DirectionalLight BracketOpen DirectionalLight_Body BracketClose { driver.pushNodeDirectionalLight(); }
	;
	
DirectionalLight_Body: /* empty */
	| DirectionalLight_Attributes
	;
	
DirectionalLight_Attributes: DirectionalLight_Attribute
	| DirectionalLight_Attributes DirectionalLight_Attribute
	;
	
DirectionalLight_Attribute: KW_on SFBool { driver.pushAttributeSFBool("on"); }
	| KW_intensity  SFFloat { driver.pushAttributeSFFloat("intensity"); }
	| KW_color SFColor { driver.pushAttributeSFColor("color"); }
	| KW_direction SFVec3f { driver.pushAttributeSFVec3f("direction"); }
	;
    


Texture2Transform: KW_Texture2Transform BracketOpen Texture2Transform_Body BracketClose { driver.pushNodeTexture2Transform(); }
	;
	
Texture2Transform_Body: /* empty */
	| Texture2Transform_Attributes
	;	

Texture2Transform_Attributes: Texture2Transform_Attribute
	| Texture2Transform_Attributes Texture2Transform_Attribute
	;
	
Texture2Transform_Attribute: KW_translation SFVec2f { driver.pushAttributeSFVec2f("translation"); }
	| KW_rotation  SFFloat { driver.pushAttributeSFFloat("rotation"); }
	| KW_scaleFactor  SFVec2f { driver.pushAttributeSFVec2f("scaleFactor"); }
	| KW_center SFVec2f { driver.pushAttributeSFVec2f("center"); }
	;



ShapeHints: KW_ShapeHints BracketOpen ShapeHints_Body BracketClose { driver.pushNodeShapeHints(); }
	;
	
ShapeHints_Body: /* empty */
	| ShapeHints_Attributes	
	;
	
ShapeHints_Attributes: ShapeHints_Attribute
	| ShapeHints_Attributes ShapeHints_Attribute
	;
	
ShapeHints_Attribute: KW_vertexOrdering vertexOrdering_value { driver.pushAttributeSFLong("vertexOrdering"); }
	| KW_shapeType shapeType_value { driver.pushAttributeSFLong("shapeType"); }
	| KW_faceType faceType_value { driver.pushAttributeSFLong("faceType"); }
	| KW_creaseAngle SFFloat { driver.pushAttributeSFFloat("creaseAngle"); }
	;

vertexOrdering_value: KW_UNKNOWN_ORDERING { driver.pushInteger(0x00); }
	| KW_CLOCKWISE { driver.pushInteger(0x01); }
	| KW_COUNTERCLOCKWISE { driver.pushInteger(0x02); }
	;

shapeType_value: KW_UNKNOWN_SHAPE_TYPE { driver.pushInteger(0x00); }
	| KW_SOLID { driver.pushInteger(0x01); }
	;

faceType_value: KW_UNKNOWN_FACE_TYPE { driver.pushInteger(0x00); }
	| KW_CONVEX { driver.pushInteger(0x01); }
	;



NormalBinding: KW_NormalBinding BracketOpen NormalBinding_Body BracketClose { driver.pushNodeNormalBinding(); }
	;
	
NormalBinding_Body: /* empty */
	| KW_value NormalBinding_value { driver.pushAttributeSFLong("value"); }
	;
	
NormalBinding_value: KW_DEFAULT { driver.pushInteger(0x00); }
	| KW_OVERALL  { driver.pushInteger(0x01); }
	| KW_PER_PART  { driver.pushInteger(0x02); }
	| KW_PER_PART_INDEXED  { driver.pushInteger(0x03); }
	| KW_PER_FACE  { driver.pushInteger(0x04); }
	| KW_PER_FACE_INDEXED  { driver.pushInteger(0x05); }
	| KW_PER_VERTEX  { driver.pushInteger(0x06); }
	| KW_PER_VERTEX_INDEXED  { driver.pushInteger(0x07); }
	;



FontStyle: KW_FontStyle BracketOpen FontStyle_Body BracketClose { driver.pushNodeFontStyle(); }
	;
	
FontStyle_Body: /* empty */
	| FontStyle_Attributes
	;
	
FontStyle_Attributes: FontStyle_Attribute
	| FontStyle_Attributes FontStyle_Attribute
	;
	
FontStyle_Attribute: KW_size SFFloat { driver.pushAttributeSFFloat("size"); }
	| KW_family family_value { driver.pushAttributeSFLong("family"); }
	| KW_style style_bitmask { driver.pushAttributeSFBitmask("style"); }
	;
	
style_bitmask: style_values
	| KW_LEFTPARENTHESIS style_bits KW_RIGHTPARENTHESIS
	;
	
style_bits: style_values
	| style_bits KW_BAR style_values
	;

style_values: KW_NONE { driver.pushInteger(0x00); }
	| KW_BOLD { driver.pushInteger(0x01); }
	| KW_ITALIC { driver.pushInteger(0x02); }
	;

family_value: KW_SERIF { driver.pushInteger(0x00); }
	| KW_SANS { driver.pushInteger(0x01); }
	| KW_TYPEWRITER { driver.pushInteger(0x02); }
	;
	
	
	
LOD: KW_LOD BracketOpen LOD_Body BracketClose { driver.pushNodeLOD(); }
	;
	
LOD_Body: /* empty */
	| LOD_Attributes
	;
	
LOD_Attributes: LOD_Attribute
	| LOD_Attributes LOD_Attribute
	;
	
LOD_Attribute: KW_range MFFloat { driver.pushAttributeMFFloat("range"); }
	| KW_center SFVec3f { driver.pushAttributeSFVec3f("center"); }
	;
		


Normal: KW_Normal BracketOpen Normal_Body BracketClose { driver.pushNodeNormal(); }
	;
	
Normal_Body: KW_vector MFVec3f { driver.pushAttributeMFVec3f("vector"); }
	;
		
		
		
Coordinate3: KW_Coordinate3 BracketOpen Coordinate3_Body BracketClose { driver.pushNodeCoordinate3(); }
	;
	
Coordinate3_Body: KW_point MFVec3f { driver.pushAttributeMFVec3f("point"); }
	;



TextureCoordinate2: KW_TextureCoordinate2 BracketOpen TextureCoordinate2_Body BracketClose { driver.pushNodeTextureCoordinate2(); }
	;
	
TextureCoordinate2_Body: KW_point MFVec2f { driver.pushAttributeMFVec2f("point"); }
	;

		
		
PointSet: KW_PointSet BracketOpen PointSet_Body BracketClose { driver.pushNodePointSet(); }
	;
	
PointSet_Body: PointSet_Arguments
	;
	
PointSet_Arguments: PointSet_Argument
	| PointSet_Arguments PointSet_Argument
	;
	
PointSet_Argument: KW_startIndex SFLong { driver.pushAttributeSFLong("startIndex"); }
	| KW_numPoints SFLong { driver.pushAttributeSFLong("numPoints"); }
	;
		
		
		
IndexedLineSet: KW_IndexedLineSet BracketOpen IndexedLineSet_Body BracketClose { driver.pushNodeIndexedLineSet(); }
	;
	
IndexedLineSet_Body: IndexedLineSet_Arguments
	;
	
IndexedLineSet_Arguments: IndexedLineSet_Argument
	| IndexedLineSet_Arguments IndexedLineSet_Argument
	;
	
IndexedLineSet_Argument: KW_coordIndex MFLong { driver.pushAttributeMFLong("coordIndex"); }
	| KW_materialIndex MFLong { driver.pushAttributeMFLong("coordIndex"); }
	| KW_normalIndex MFLong { driver.pushAttributeMFLong("normalIndex"); }
	| KW_textureCoordIndex MFLong { driver.pushAttributeMFLong("textureCoordIndex"); }
	;


		
IndexedFaceSet: KW_IndexedFaceSet BracketOpen IndexedFaceSet_Body BracketClose { driver.pushNodeIndexedFaceSet(); }
	;
	
IndexedFaceSet_Body: IndexedFaceSet_Arguments
	;
	
IndexedFaceSet_Arguments: IndexedFaceSet_Argument
	| IndexedFaceSet_Arguments IndexedFaceSet_Argument
	;
	
IndexedFaceSet_Argument: KW_coordIndex MFLong { driver.pushAttributeMFLong("coordIndex"); }
	| KW_materialIndex MFLong { driver.pushAttributeMFLong("materialIndex"); }
	| KW_normalIndex MFLong { driver.pushAttributeMFLong("normalIndex"); }
	| KW_textureCoordIndex MFLong { driver.pushAttributeMFLong("textureCoordIndex"); }
	;



			
Texture2: KW_Texture2 BracketOpen Texture2_Body BracketClose { driver.pushNodeTexture2(); }
	;
	
Texture2_Body: Texture2_Arguments
	;
	
Texture2_Arguments: Texture2_Argument
	| Texture2_Argument Texture2_Arguments
	;
	
Texture2_Argument: KW_filename SFString { driver.pushAttributeSFString("filename"); }
	| KW_image SFImage { driver.pushAttributeSFImage("image"); }
	| KW_wrapS Texture2_wrap { driver.pushAttributeSFLong("wrapS"); }
	| KW_wrapT Texture2_wrap { driver.pushAttributeSFLong("wrapT"); }
	;
		
Texture2_wrap: KW_REPEAT { driver.pushInteger(0x00); }
	| KW_CLAMP { driver.pushInteger(0x01); }
	;
	


WWWInline: KW_WWWInline BracketOpen WWWInline_Body BracketClose { driver.pushNodeWWWInline(); }
	;
	
WWWInline_Body: WWWInline_Arguments;
	;
	
WWWInline_Arguments: WWWInline_Argument
	| WWWInline_Arguments WWWInline_Argument
	;
	
WWWInline_Argument: KW_name SFString { driver.pushAttributeSFString("name"); }
	| KW_bboxSize SFVec3f { driver.pushAttributeSFVec3f("bboxSize"); }
	| KW_bboxCenter SFVec3f { driver.pushAttributeSFVec3f("bboxCenter"); }
	;



WWWAnchor: KW_WWWAnchor BracketOpen WWWAnchor_Body BracketClose { driver.pushNodeWWWAnchor(); }
	;
	
WWWAnchor_Body: WWWAnchor_Arguments
	;
	
WWWAnchor_Arguments: WWWAnchor_Argument
	| WWWAnchor_Arguments WWWAnchor_Argument
	;
	
WWWAnchor_Argument: KW_name SFString { driver.pushAttributeSFString("name"); }
	| KW_description SFString { driver.pushAttributeSFString("description"); }
	| KW_map WWWAnchor_map { driver.pushAttributeSFLong("map"); }
	;
	
WWWAnchor_map: KW_NONE { driver.pushInteger(0x00); }
	| KW_POINT { driver.pushInteger(0x01); }
	;
		
	
		
AsciiText: KW_AsciiText BracketOpen AsciiText_Body BracketClose { driver.pushNodeAsciiText(); }
	;
	
AsciiText_Body: AsciiText_Arguments
	;
	
AsciiText_Arguments: AsciiText_Argument
	| AsciiText_Arguments AsciiText_Argument
	;
	
AsciiText_Argument: KW_string SFString { driver.pushAttributeSFString("string"); }
	| KW_spacing SFFloat { driver.pushAttributeSFFloat("spacing"); }
	| KW_justification AsciiText_justification { driver.pushAttributeSFLong("justification"); }
	| KW_width MFFloat { driver.pushAttributeMFFloat("width"); }
	;
	
AsciiText_justification: KW_LEFT { driver.pushInteger(0x00); }
	| KW_CENTER { driver.pushInteger(0x01); }
	| KW_RIGHT { driver.pushInteger(0x02); }
	;






BracketOpen: KW_BRACKETOPEN { driver.StackDown(); }
	;
	
BracketClose: KW_BRACKETCLOSE { driver.StackUp(); }
	;

		
		
SFBool: KW_FALSE { driver.pushBool(false); }
	| KW_TRUE { driver.pushBool(true); }
	| KW_ZERO { driver.pushBool(false); }
	| KW_ONE { driver.pushBool(true); }
	;
	
SFLong: KW_ZERO { driver.pushInteger(0); }
	| KW_ONE { driver.pushInteger(1); }
	| TYPE_INTEGER { driver.pushInteger($1); }
	;
	
MFLong: SFLong
	| KW_SQUAREDBRACKETOPEN MFLongs KW_SQUAREDBRACKETCLOSE
	;
	
MFLongs: SFLong
	| MFLongs KW_COMMA SFLong
	| MFLongs KW_COMMA 
	;
	
SFFloat: TYPE_FLOAT { driver.pushFloat($1); }
	| TYPE_INTEGER { driver.pushFloat($1); }
	| KW_ZERO { driver.pushFloat(0.0); }
	| KW_ONE { driver.pushFloat(1.0); }
	;
	
MFFloat: SFFloat
	| KW_SQUAREDBRACKETOPEN MFFloats KW_SQUAREDBRACKETCLOSE
	;
	
MFFloats: SFFloat
	| MFFloats KW_COMMA SFFloat
	| MFFloats KW_COMMA
	;
	
SFVec2f: SFFloat SFFloat
	;

MFVec2f: SFVec2f
	| KW_SQUAREDBRACKETOPEN MFVec2fs KW_SQUAREDBRACKETCLOSE
	;
	
MFVec2fs: SFVec2f
	| MFVec2fs KW_COMMA SFVec2f
	| MFVec2fs KW_COMMA 
	;

	
SFVec3f: SFFloat SFFloat SFFloat
	;
	
	
MFVec3f: SFVec3f
	| KW_SQUAREDBRACKETOPEN MFVec3fs KW_SQUAREDBRACKETCLOSE
	;
	
MFVec3fs: SFVec3f
	| MFVec3fs KW_COMMA SFVec3f
	| MFVec3fs KW_COMMA
	;
	
SFColor: SFFloat SFFloat SFFloat
	;
	
MFColor: SFColor
	| KW_SQUAREDBRACKETOPEN MFColors KW_SQUAREDBRACKETCLOSE
	;
	
MFColors: SFColor
	| MFColors KW_COMMA SFColor 
	| MFColors KW_COMMA 
	;
	
SFRotation: SFFloat SFFloat SFFloat SFFloat
	;
	
SFMatrix: SFFloat SFFloat SFFloat SFFloat SFFloat SFFloat SFFloat SFFloat SFFloat SFFloat SFFloat SFFloat SFFloat SFFloat SFFloat SFFloat 
	;  

SFString: TYPE_STRING  { driver.pushString(*$1); }
	;
	
MFString: SFString
	| KW_SQUAREDBRACKETOPEN MFStrings KW_SQUAREDBRACKETCLOSE
	;
	
MFStrings: SFString
	| MFStrings KW_COMMA SFString 
	| MFStrings KW_COMMA
	;
	
SFImage: SFLong SFLong SFLong Image_Body
	;
	
Image_Body: TYPE_INTEGER
	| Image_Body TYPE_INTEGER
	;

Identifier: TYPE_STRING  { driver.pushString(*$1); }
	| Keywords
	;
	
Keywords: KW_Separator { driver.pushString("Separator"); }
	| KW_BRACKETOPEN { driver.pushString("{"); }
	| KW_BRACKETCLOSE { driver.pushString("}"); }
	| KW_Cube { driver.pushString("Cube"); }
	| KW_width { driver.pushString("width"); }
	| KW_height { driver.pushString("height"); }
	| KW_depth { driver.pushString("depth"); }
	| KW_SIDES { driver.pushString("SIDES"); }
	| KW_parts { driver.pushString("parts"); }
	| KW_bottomRadius { driver.pushString("bottomRadius"); }
	| KW_BOTTOM { driver.pushString("BOTTOM"); }
	| KW_Cone { driver.pushString("Cone"); }
	| KW_ALL { driver.pushString("ALL"); }
	| KW_Sphere { driver.pushString("Sphere"); }
	| KW_radius { driver.pushString("radius"); }
	| KW_Cylinder { driver.pushString("Cylinder"); }
	| KW_TOP { driver.pushString("TOP"); }
	| KW_DirectionalLight { driver.pushString("DirectionalLight"); }
	| KW_intensity { driver.pushString("intensity"); }
	| KW_color { driver.pushString("color"); }
	| KW_on { driver.pushString("on"); }
	| KW_direction { driver.pushString("direction"); }
	| KW_FALSE { driver.pushString("FALSE"); }
	| KW_TRUE { driver.pushString("TRUE"); }
	| KW_transparency { driver.pushString("transparency"); }
	| KW_Material { driver.pushString("Material"); }
	| KW_emissiveColor { driver.pushString("emissiveColor"); }
	| KW_ambientColor { driver.pushString("ambientColor"); }
	| KW_specularColor { driver.pushString("specularColor"); }
	| KW_shininess { driver.pushString("shininess"); }
	| KW_diffuseColor { driver.pushString("diffuseColor"); }
	| KW_OVERALL { driver.pushString("OVERALL"); }
	| KW_MaterialBinding { driver.pushString("MaterialBinding"); }
	| KW_PER_FACE { driver.pushString("PER_FACE"); }
	| KW_value { driver.pushString("value"); }
	| KW_PER_VERTEX_INDEXED { driver.pushString("PER_VERTEX_INDEXED"); }
	| KW_PER_PART { driver.pushString("PER_PART"); }
	| KW_PER_FACE_INDEXED { driver.pushString("PER_FACE_INDEXED"); }
	| KW_DEFAULT { driver.pushString("DEFAULT"); }
	| KW_PER_PART_INDEXED { driver.pushString("PER_PART_INDEXED"); }
	| KW_PER_VERTEX { driver.pushString("PER_VERTEX"); }
	| KW_Translation { driver.pushString("Translation"); }
	| KW_translation { driver.pushString("translation"); }
	| KW_Rotation { driver.pushString("Rotation"); }
	| KW_rotation { driver.pushString("rotation"); }
	| KW_Scale { driver.pushString("Scale"); }
	| KW_scaleFactor { driver.pushString("scaleFactor"); }
	| KW_MatrixTransform { driver.pushString("MatrixTransform"); }
	| KW_matrix { driver.pushString("matrix"); }
	| KW_scaleOrientation { driver.pushString("scaleOrientation"); }
	| KW_Transform { driver.pushString("Transform"); }
	| KW_center { driver.pushString("center"); }
	| KW_OrthographicCamera { driver.pushString("OrthographicCamera"); }
	| KW_position { driver.pushString("position"); }
	| KW_orientation { driver.pushString("orientation"); }
	| KW_focalDistance { driver.pushString("focalDistance"); }
	| KW_heightAngle { driver.pushString("heightAngle"); }
	| KW_PerspectiveCamera { driver.pushString("PerspectiveCamera"); }
	| KW_PointLight { driver.pushString("PointLight"); }
	| KW_SpotLight { driver.pushString("SpotLight"); }
	| KW_cutOffAngle { driver.pushString("cutOffAngle"); }
	| KW_dropOffRate { driver.pushString("dropOffRate"); }
	| KW_location { driver.pushString("location"); }
	| KW_Texture2Transform { driver.pushString("Texture2Transform"); }
	| KW_creaseAngle { driver.pushString("creaseAngle"); }
	| KW_CLOCKWISE { driver.pushString("CLOCKWISE"); }
	| KW_CONVEX { driver.pushString("CONVEX"); }
	| KW_vertexOrdering { driver.pushString("vertexOrdering"); }
	| KW_SOLID { driver.pushString("SOLID"); }
	| KW_COUNTERCLOCKWISE { driver.pushString("COUNTERCLOCKWISE"); }
	| KW_shapeType { driver.pushString("shapeType"); }
	| KW_UNKNOWN_FACE_TYPE { driver.pushString("UNKNOWN_FACE_TYPE"); }
	| KW_UNKNOWN_ORDERING { driver.pushString("UNKNOWN_ORDERING"); }
	| KW_faceType { driver.pushString("faceType"); }
	| KW_UNKNOWN_SHAPE_TYPE { driver.pushString("UNKNOWN_SHAPE_TYPE"); }
	| KW_ShapeHints { driver.pushString("ShapeHints"); }
	| KW_NormalBinding { driver.pushString("NormalBindings"); }
	| KW_SANS { driver.pushString("SANS"); }
	| KW_FontStyle { driver.pushString("FontStyle"); }
	| KW_TYPEWRITER { driver.pushString("TYPEWRITER"); }
	| KW_LOD { driver.pushString("LOD"); }
	| KW_style { driver.pushString("style"); }
	| KW_SERIF { driver.pushString("SERIF"); }
	| KW_size { driver.pushString("size"); }
	| KW_range { driver.pushString("range"); }
	| KW_family { driver.pushString("family"); }
	| KW_ITALIC { driver.pushString("ITALIC"); }
	| KW_NONE { driver.pushString("NONE"); }
	| KW_BOLD { driver.pushString("BOLD"); }
	| KW_LEFTPARENTHESIS { driver.pushString("("); }
	| KW_RIGHTPARENTHESIS { driver.pushString(")"); }
	| KW_BAR { driver.pushString("|"); }
	| KW_COMMA { driver.pushString("COMMA"); }
	| KW_SQUAREDBRACKETOPEN { driver.pushString("["); }
	| KW_SQUAREDBRACKETCLOSE { driver.pushString("]"); }
	| KW_vector { driver.pushString("vector"); }
	| KW_Normal { driver.pushString("Normal"); }
	| KW_point { driver.pushString("point"); }
	| KW_Coordinate3 { driver.pushString("Coordinate3"); }
	| KW_TextureCoordinate2 { driver.pushString("TextrueCoordinate2"); }
	| KW_startIndex { driver.pushString("startIndex"); }
	| KW_numPoints { driver.pushString("numPoints"); }
	| KW_PointSet { driver.pushString("PointSet"); }
	| KW_textureCoordIndex { driver.pushString("textureCoordIndex"); }
	| KW_normalIndex { driver.pushString("normalIndex"); }
	| KW_coordIndex { driver.pushString("coordIndex"); }
	| KW_IndexedLineSet { driver.pushString("IndexedLineSet"); }
	| KW_materialIndex { driver.pushString("materialIndex"); }
	| KW_IndexedFaceSet { driver.pushString("IndexedFaceSet"); }
	| KW_renderCulling { driver.pushString("renderCulling"); }
	| KW_OFF { driver.pushString("OFF"); }
	| KW_AUTO { driver.pushString("AUTO"); }
	| KW_ON { driver.pushString("ON"); }
	| KW_whichChild { driver.pushString("whichChild"); }
	| KW_Switch { driver.pushString("Switch"); }
	| KW_filename { driver.pushString("filename"); }
	| KW_wrapT { driver.pushString("wrapT"); }
	| KW_CLAMP { driver.pushString("CLAMP"); }
	| KW_Texture2 { driver.pushString("Texture2"); }
	| KW_image { driver.pushString("image"); }
	| KW_REPEAT { driver.pushString("REPEAT"); }
	| KW_wrapS { driver.pushString("wrapS"); }
	| KW_WWWInline { driver.pushString("WWWInline"); }
	| KW_bboxCenter { driver.pushString("bboxCenter"); }
	| KW_bboxSize { driver.pushString("bboxSize"); }
	| KW_name { driver.pushString("name"); }
	| KW_map { driver.pushString("map"); }
	| KW_POINT { driver.pushString("POINT"); }
	| KW_description { driver.pushString("description"); }
	| KW_WWWAnchor { driver.pushString("WWWAnchor"); }
	| KW_justification { driver.pushString("justification"); }
	| KW_CENTER { driver.pushString("CENTER"); }
	| KW_spacing { driver.pushString("spacing"); }
	| KW_string { driver.pushString("string"); }
	| KW_RIGHT { driver.pushString("RIGHT"); }
	| KW_AsciiText { driver.pushString("AsciiText"); }
	| KW_LEFT { driver.pushString("LEFT"); }
	| KW_ZERO { driver.pushString("ZERO"); }
	| KW_ONE { driver.pushString("ONE"); }
	| KW_DEF { driver.pushString("DEF"); }
	| KW_USE { driver.pushString("USE"); }
	| KW_VRML_ID { driver.pushString("VRML_ID"); }
	;
	
%%

void vrml1::vrml1_parser::error (const vrml1::vrml1_parser::location_type& l,
                               const std::string& m) {
	driver.error (l, m);
}

