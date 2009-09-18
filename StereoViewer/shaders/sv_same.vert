// simple vertex shader

varying vec3 normal, lightDir;
varying vec4 cl;

void main()
{
    lightDir = normalize(vec3(gl_LightSource[0].position));
	normal = normalize(gl_NormalMatrix * gl_Normal);

    cl = gl_Color;

	gl_Position = ftransform();
}
