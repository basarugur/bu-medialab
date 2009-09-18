// simple toon fragment shader
// www.lighthouse3d.com

uniform sampler2D tex;

#define PI 3.141592654

int hk = 9; // half kernel dimension

float gauss_5x5[5][5] = { { 0.003f, 0.012f, 0.021f, 0.012f, 0.003f },
                          { 0.012f, 0.06f, 0.099f, 0.06f, 0.012f },
                          { 0.021f, 0.099f, 0.166f, 0.099f, 0.021f },
                          { 0.012f, 0.06f, 0.099f, 0.06f, 0.012f },
                          { 0.003f, 0.012f, 0.021f, 0.012f, 0.003f } };

float horz[19] = { .01f, .02f, .03f, .04f, .05f, .06f, .07f, .08f, .09f, .1f, .09f, .08f, .07f, .06f, .05f, .04f, .03f, .02f, .01f };

float screen_width = 1024.f,
      screen_height = 768.f;

void main()
{
	float px = 1.f / screen_width, py = 1.f / screen_height;
	vec4 color;

    for (int i = -hk; i <= hk; i++)
        color = color + texture2D( tex, vec2(gl_TexCoord[0] + vec4(i*px, 0, 0, 0)) ) * horz[i+hk];

            /* * 4 +
                    texture2D( tex, vec2(gl_TexCoord[0] + vec4(-px, 0, 0, 0)) ) +
                    texture2D( tex, vec2(gl_TexCoord[0] + vec4(px, 0, 0, 0)) ) +
                    texture2D( tex, vec2(gl_TexCoord[0] + vec4(0, -px, 0, 0)) ) +
                    texture2D( tex, vec2(gl_TexCoord[0] + vec4(0, px, 0, 0)) );*/

    //color = texture2D( tex, vec2(gl_TexCoord[0]) );

    color.a = 1;

  	/*if (intensity > 0.98)
		color = vec4(0.8,0.8,1.0,1.0);
	else if (intensity > 0.5)
		color = vec4(0.4,0.4,0.8,1.0);
	else if (intensity > 0.25)
		color = vec4(0.2,0.2,0.4,1.0);
	else
		color = vec4(0.1,0.1,0.1,1.0);*/

	gl_FragColor = color;
}
