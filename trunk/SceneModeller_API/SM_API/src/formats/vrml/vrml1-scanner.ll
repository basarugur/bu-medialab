%{                                            /* -*- C++ -*- */
#include <cstdlib>
#include <errno.h>
#include <limits.h>
#include <string>
#include "convert.hh"
#include "Driver.hh"
#include "vrml1-parser.hh"
     
/* Work around an incompatibility in flex (at least versions
   2.5.31 through 2.5.33): it generates code that does
   not conform to C89.  See Debian bug 333231
   <http://bugs.debian.org/cgi-bin/bugreport.cgi?bug=333231>.  */

#undef yywrap
#define yywrap() 1
     
/* By default yylex returns int, we use token_type.
   Unfortunately yyterminate by default returns 0, which is
   not of token_type.  */

#define yyterminate() return token::END
%}


%option noyywrap nounput batch debug


D			[0-9]
L			[a-zA-Z]
C			[a-zA-Z']
H			[a-fA-F0-9]
E			[Ee][+-]?{D}+


%%

%{
  typedef vrml1::vrml1_parser::token token;
%}


0			{
					return token::KW_ZERO;
			}

1			{
					return token::KW_ONE;
			}
			
0[xX]{H}+	{
					from_string<int>(yylval->ival, std::string(yytext), std::hex);
					return token::TYPE_INTEGER;
			}


{D}+|-{D}+	{
					from_string<int>(yylval->ival, std::string(yytext), std::dec);
					return token::TYPE_INTEGER;
			}


{D}+{E}|-{D}+{E}|{D}*"."{D}+({E})?|-{D}*"."{D}+({E})?|{D}+"."{D}*({E})?|-{D}+"."{D}*({E})? {
					from_string<float>(yylval->fval, std::string(yytext), std::dec);
					return token::TYPE_FLOAT;
			}


ALL			{
					return token::KW_ALL;
			}
			
AUTO		{	
					return token::KW_AUTO;
			}
			
AsciiText	{
					return token::KW_AsciiText;
			}
			
BOLD		{	
					return token::KW_BOLD;
			}
			
BOTTOM		{	
					return token::KW_BOTTOM;
			}
			
CENTER		{	
					return token::KW_CENTER;
			}
			
CLAMP		{	
					return token::KW_CLAMP;
			}

CLOCKWISE	{	
					return token::KW_CLOCKWISE;
			}
			
CONVEX		{	
					return token::KW_CONVEX;
			}
			
COUNTERCLOCKWISE	{	
					return token::KW_COUNTERCLOCKWISE;
			}
			
Cone		{	
					return token::KW_Cone;
			}
			
Coordinate3		{	
					return token::KW_Coordinate3;
			}
			
Cube		{	
					return token::KW_Cube;
			}
			
Cylinder	{	
					return token::KW_Cylinder;
			}
			
DEF			{	
					return token::KW_DEF;
			}
			
DEFAULT		{	
					return token::KW_DEFAULT;
			}
			
DirectionalLight	{	
					return token::KW_DirectionalLight;
			}
			
FALSE		{	
					return token::KW_FALSE;
			}
			
FontStyle	{	
					return token::KW_FontStyle;
			}
			
ITALIC		{	
					return token::KW_ITALIC;
			}
			
IndexedFaceSet		{	
					return token::KW_IndexedFaceSet;
			}
			
IndexedLineSet		{	
					return token::KW_IndexedLineSet;
			}
			
LEFT		{	
					return token::KW_LEFT;
			}
			
LOD			{	
					return token::KW_LOD;
			}
			
Material	{	
					return token::KW_Material;
			}
						
MaterialBinding		{	
					return token::KW_MaterialBinding;
			}
			
MatrixTransform		{	
					return token::KW_MatrixTransform;
			}
			
NONE		{	
					return token::KW_NONE;
			}
			
Normal		{	
					return token::KW_Normal;
			}
			
NormalBinding		{	
					return token::KW_NormalBinding;
			}
			
OFF			{	
					return token::KW_OFF;
			}
			
ON			{	
					return token::KW_ON;
			}
			
OVERALL		{	
					return token::KW_OVERALL;
			}
			
OrthographicCamera	{	
					return token::KW_OrthographicCamera;
			}
			
PER_FACE	{	
					return token::KW_PER_FACE;
			}
			
PER_FACE_INDEXED	{	
					return token::KW_PER_FACE_INDEXED;
			}
			
PER_PART	{	
					return token::KW_PER_PART;
			}
			
PER_PART_INDEXED	{	
					return token::KW_PER_PART_INDEXED;
			}
			
PER_VERTEX		{	
					return token::KW_PER_VERTEX;
			}
			
PER_VERTEX_INDEXED	{	
					return token::KW_PER_VERTEX_INDEXED;
			}
			
POINT		{	
					return token::KW_POINT;
			}
			
PerspectiveCamera	{	
					return token::KW_PerspectiveCamera;
			}
			
PointLight	{	
					return token::KW_PointLight;
			}
			
PointSet	{	
					return token::KW_PointSet;
			}
			
REPEAT		{	
					return token::KW_REPEAT;
			}
			
RIGHT		{	
					return token::KW_RIGHT;
			}
			
Rotation	{	
					return token::KW_Rotation;
			}
			
SANS		{	
					return token::KW_SANS;
			}
			
SERIF		{	
					return token::KW_SERIF;
			}
			
SIDES		{	
					return token::KW_SIDES;
			}
			
SOLID		{	
					return token::KW_SOLID;
			}
			
Scale		{	
					return token::KW_Scale;
			}
			
Separator	{	
					return token::KW_Separator;
			}
			
ShapeHints	{	
					return token::KW_ShapeHints;
			}
			
Sphere		{	
					return token::KW_Sphere;
			}
			
SpotLight	{	
					return token::KW_SpotLight;
			}
			
			
Switch		{	
					return token::KW_Switch;
			}
			
TOP			{	
					return token::KW_TOP;
			}
			
TRUE		{	
					return token::KW_TRUE;
			}
			
TYPEWRITER	{	
					return token::KW_TYPEWRITER;
			}
			
Texture2	{	
					return token::KW_Texture2;
			}
			
Texture2Transform	{	
					return token::KW_Texture2Transform;
			}
			
TextureCoordinate2	{	
					return token::KW_TextureCoordinate2;
			}
			
Transform	{	
					return token::KW_Transform;
			}
			
Translation		{	
					return token::KW_Translation;
			}
			
UNKNOWN_FACE_TYPE	{	
					return token::KW_UNKNOWN_FACE_TYPE;
			}
			
UNKNOWN_ORDERING	{	
					return token::KW_UNKNOWN_ORDERING;
			}
			
UNKNWON_SHAPE_TYPE	{	
					return token::KW_UNKNOWN_SHAPE_TYPE;
			}
			
USE			{	
					return token::KW_USE;
			}
			
WWWAnchor	{	
					return token::KW_WWWAnchor;
			}
			
WWWInline	{	
					return token::KW_WWWInline;
			}
			
ambientColor	{	
					return token::KW_ambientColor;
			}
			
bboxCenter	{	
					return token::KW_bboxCenter;
			}
			
bboxSize		{	
				return token::KW_bboxSize;
			}
			
bottomRadius	{	
					return token::KW_bottomRadius;
			}
			
center		{	
					return token::KW_center;
			}
			
color		{	
					return token::KW_color;
			}
			
coordIndex	{	
					return token::KW_coordIndex;
			}
			
creaseAngle 	{	
					return token::KW_creaseAngle;
			}
			
cutOffAngle		{	
					return token::KW_cutOffAngle;
			}
			
depth		{	
					return token::KW_depth;
			}
			
description		{	
					return token::KW_description;
			}
			
diffuseColor	{	
					return token::KW_diffuseColor;
			}
			
direction		{	
					return token::KW_direction;
			}
			
dropOffRate		{	
					return token::KW_dropOffRate;
			}
			
emissiveColor	{	
					return token::KW_emissiveColor;
			}
			
faceType	{	
					return token::KW_faceType;
			}
			
family		{	
					return token::KW_family;
			}
			
filename	{	
					return token::KW_filename;
			}
			
focalDistance		{	
					return token::KW_focalDistance;
			}
			
height		{	
					return token::KW_height;
			}
			
heightAngle		{	
					return token::KW_heightAngle;
			}
			
image		{	
					return token::KW_image;
			}
			
intensity	{	
					return token::KW_intensity;
			}
			
justification	{	
					return token::KW_justification;
			}
			
location	{	
					return token::KW_location;
			}
			
map 		{	
					return token::KW_map;
			}
			
materialIndex	{	
					return token::KW_materialIndex;
			}
			
matrix		{	
					return token::KW_matrix;
			}
			
name		{	
					return token::KW_name;
			}
			
normalIndex		{	
					return token::KW_normalIndex;
			}
			
numPoints	{	
					return token::KW_numPoints;
			}
			
on			{	
				return token::KW_on;
			}
			
orientation		{	
					return token::KW_orientation;	
			}
			
parts		{	
					return token::KW_parts;
			}
			
point		{	
					return token::KW_point;
			}
			
position	{	
					return token::KW_position;
			}
			
radius		{	
					return token::KW_radius;
			}
			
range 		{	
					return token::KW_range;
			}
			
renderCulling	{	
					return token::KW_renderCulling;
			}
			
rotation	{	
					return token::KW_rotation;
			}
			
scaleFactor		{	
					return token::KW_scaleFactor;
			}
			
scaleOrientation	{	
					return token::KW_scaleOrientation;
			}

shapeType	{					
					return token::KW_shapeType;
			}
			
shininess	{	
					return token::KW_shininess;
			}
			
size		{	
					return token::KW_size;
			}
			
spacing		{	
					return token::KW_spacing;
			}
			
specularColor	{	
					return token::KW_specularColor;
			}
			
startIndex	{	
					return token::KW_startIndex;
			}
			
string		{	
					return token::KW_string;
			}
			
style		{	
					return token::KW_style;
			}
			
textureCoordIndex	{	
					return token::KW_textureCoordIndex;
			}
			
translation	{	
					return token::KW_translation;
			}
			
transparency	{	
					return token::KW_transparency;
			}
			
value 		{	
					return token::KW_value;
			}
			
vector		{	
					return token::KW_vector;
			}
			
vertexOrdering	{	
					return token::KW_vertexOrdering;
			}
			
whichChild	{	
					return token::KW_whichChild;
			}
			
width		{	
					return token::KW_width;
			}
			
wrapS		{	
					return token::KW_wrapS;
			}
			
wrapT		{	
					return token::KW_wrapT;
			}

{L}+({L}|{D})*	{	
				yylval->sval = new string(yytext);
				return token::TYPE_STRING;
			}

\"[^\"\\\r\n]*(\\.[^\"\\\r\n]*)*\" 	{
				yylval->sval = new string(yytext);
				return token::TYPE_STRING;
			}
			

"{"			{
				return token::KW_BRACKETOPEN;
			}

"}"			{
				return token::KW_BRACKETCLOSE;
			}

"["			{
				return token::KW_SQUAREDBRACKETOPEN;
			}

"]"			{
				return token::KW_SQUAREDBRACKETCLOSE;
			}
			
"("			{
				return token::KW_LEFTPARENTHESIS;
			}

")"			{
				return token::KW_RIGHTPARENTHESIS;
			}

"|"			{
				return token::KW_BAR;
			}			

","			{
					return token::KW_COMMA;
			}			


"#VRML V1.0 ascii" {
				return token::KW_VRML_ID;
			}	

#[^\n]*		{
			}		

			
[ ]			{
				/* eat up */
			}
			
\t			{
				/* eat up */
			}			
			
			
\n			{
			}			

.			{
			}

%%

namespace vrml1 {

void Driver::scan_begin () {

	yy_flex_debug = trace_scanning;
	
	if (!(yyin = fopen (file.c_str (), "r")))
		error (std::string ("cannot open ") + file);
}
     
void Driver::scan_end ()  {
	fclose (yyin);
}

}
