#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>

#define SAME 0
#define BLUR 1

class Shader
{

public:
    Shader() { };
    ~Shader() { };

    /** Credits: http://www.lighthouse3d.com
    *   \brief interface for reading and writing text files
    */
    char *textFileRead(char *fn)
    {

        FILE *fp;
        char *content = NULL;

        int count=0;

        if (fn != NULL) {
            fp = fopen(fn,"rt");

            if (fp != NULL) {

          fseek(fp, 0, SEEK_END);
          count = ftell(fp);
          rewind(fp);

                if (count > 0) {
                    content = (char *)malloc(sizeof(char) * (count+1));
                    count = fread(content,sizeof(char),count,fp);
                    content[count] = '\0';
                }
                fclose(fp);
            }
        }
        return content;
    }

    void setShaderProgram(GLuint& vert, GLuint& frag, GLuint& prog,
                          char* vert_filename, char* frag_filename)
    {
        char *vs = NULL, *fs = NULL;

        vert = glCreateShader(GL_VERTEX_SHADER);
        frag = glCreateShader(GL_FRAGMENT_SHADER);

        vs = textFileRead( vert_filename );
        fs = textFileRead( frag_filename );

        const char * ff = fs;
        const char * vv = vs;

        glShaderSource(vert, 1, &vv, NULL);
        glShaderSource(frag, 1, &ff, NULL);

        free(vs);
        free(fs);

        glCompileShader(vert);
        glCompileShader(frag);

        prog = glCreateProgram();
        glAttachShader(prog, frag);
        glAttachShader(prog, vert);

        glLinkProgram(prog);

        glUseProgram(prog);
    }

    void setShaders()
    {
        glewInit();

        if (glewIsSupported("GL_VERSION_2_0"))
            printf("Ready for OpenGL 2.0\n");
        else
        {
            printf("OpenGL 2.0 not supported\n");

            exit(1);
        }

        setShaderProgram(sh_vert[SAME], sh_frag[SAME], sh_prog[SAME],
                         "shaders/sv_same.vert", "shaders/sv_same.frag");

        setShaderProgram(sh_vert[BLUR], sh_frag[BLUR], sh_prog[BLUR],
                         "shaders/sv_blur.vert", "shaders/sv_blur.frag");
    }

/// Attributes:

    GLuint sh_vert[2], sh_frag[2], sh_prog[2];

};
