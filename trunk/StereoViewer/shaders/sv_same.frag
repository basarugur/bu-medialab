// simple fragment shader

varying vec3 normal, lightDir;
varying vec4 cl;

void main()
{
	float intensity;
	vec3 n;
	vec4 color;

	n = normalize( normal );

	intensity = max( dot(lightDir, n), 0.0 ) + gl_LightSource[0].ambient.r;

	color = cl * intensity;

	color.a = 1;

	gl_FragColor = color;
}
