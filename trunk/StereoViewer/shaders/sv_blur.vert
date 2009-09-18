// simple toon vertex shader
// www.lighthouse3d.com

void main()
{
    gl_TexCoord[0] = gl_MultiTexCoord0;

	gl_Position = ftransform();
}
