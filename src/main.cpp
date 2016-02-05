#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include <shader.h> // Help to load shaders from files

// Include GLEW : Always include it before glfw.h et gl.h :)
#include <GL/glew.h>    // OpenGL Extension Wrangler Library : http://glew.sourceforge.net/ 
#include <GL/glfw.h>    // Window, keyboard, mouse : http://www.glfw.org/

#include <glm/glm.hpp>  // OpenGL Mathematics : http://glm.g-truc.net/0.9.5/index.html
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>

#include <GLFW_define.h>

// Dimensions de la fenêtre :
#define WIDTH 1000.0f
#define HEIGHT 800.0f

using namespace glm;
using namespace std;

void view_control(mat4 *view_matrix, double *v, vec3 axis){
    if(glfwGetKey(GLFW_KEY_DOWN) == GLFW_PRESS){
        *view_matrix = translate(*view_matrix, vec3(0.0, 0.01, 0.0));
    } else if(glfwGetKey(GLFW_KEY_UP) == GLFW_PRESS){
        *view_matrix = translate(*view_matrix, vec3(0.0, -0.01, 0.0));
    } else if(glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS){
        *view_matrix = translate(*view_matrix, vec3(0.01, 0.0, 0.0));
    } else if(glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS){
        *view_matrix = translate(*view_matrix, vec3(-0.01, 0.0, 0.0));
    } else if(glfwGetKey(GLFW_KEY_L) == GLFW_PRESS){
        *view_matrix = scale(*view_matrix, vec3(0.9, 0.9, 0.9));
    } else if(glfwGetKey(GLFW_KEY_M) == GLFW_PRESS){
        *view_matrix = scale(*view_matrix, vec3(1.1, 1.1, 1.1));
    } else if(glfwGetKey(GLFW_KEY_R) == GLFW_PRESS){
        *view_matrix = rotate(*view_matrix, 0.5f, axis);
    } else if(glfwGetKey(GLFW_KEY_A) == GLFW_PRESS){
        (*v)++;
    } else if(glfwGetKey(GLFW_KEY_Z) == GLFW_PRESS){
        (*v)--;
    }
}

void model_control(mat4 *model_matrix, double *v, vec3 axis){
    if(glfwGetKey(GLFW_KEY_UP) == GLFW_PRESS){
        *model_matrix = translate(*model_matrix, vec3(0.0, 0.01, 0.0));
    } else if(glfwGetKey(GLFW_KEY_DOWN) == GLFW_PRESS){
        *model_matrix = translate(*model_matrix, vec3(0.0, -0.01, 0.0));
    } else if(glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS){
        *model_matrix = translate(*model_matrix, vec3(0.01, 0.0, 0.0));
    } else if(glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS){
        *model_matrix = translate(*model_matrix, vec3(-0.01, 0.0, 0.0));
    } else if(glfwGetKey(GLFW_KEY_L) == GLFW_PRESS){
        *model_matrix = scale(*model_matrix, vec3(0.9, 0.9, 0.9));
    } else if(glfwGetKey(GLFW_KEY_M) == GLFW_PRESS){
        *model_matrix = scale(*model_matrix, vec3(1.1, 1.1, 1.1));
    } else if(glfwGetKey(GLFW_KEY_R) == GLFW_PRESS){
        *model_matrix = rotate(*model_matrix, 0.5f, axis);
    } else if(glfwGetKey(GLFW_KEY_A) == GLFW_PRESS){
        (*v)++;
    } else if(glfwGetKey(GLFW_KEY_Z) == GLFW_PRESS){
        (*v)--;
    }
}

void projection_control(mat4 *projection_matrix, double *v, vec3 axis){
    if(glfwGetKey(GLFW_KEY_UP) == GLFW_PRESS){
        *projection_matrix = translate(*projection_matrix, vec3(0.0, 0.01, 0.0));
    } else if(glfwGetKey(GLFW_KEY_DOWN) == GLFW_PRESS){
        *projection_matrix = translate(*projection_matrix, vec3(0.0, -0.01, 0.0));
    } else if(glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS){
        *projection_matrix = translate(*projection_matrix, vec3(0.01, 0.0, 0.0));
    } else if(glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS){
        *projection_matrix = translate(*projection_matrix, vec3(-0.01, 0.0, 0.0));
    } else if(glfwGetKey(GLFW_KEY_L) == GLFW_PRESS){
        *projection_matrix = scale(*projection_matrix, vec3(0.9, 0.9, 0.9));
    } else if(glfwGetKey(GLFW_KEY_M) == GLFW_PRESS){
        *projection_matrix = scale(*projection_matrix, vec3(1.1, 1.1, 1.1));
    } else if(glfwGetKey(GLFW_KEY_R) == GLFW_PRESS){
        *projection_matrix = rotate(*projection_matrix, 0.5f, axis);
    } else if(glfwGetKey(GLFW_KEY_A) == GLFW_PRESS){
        (*v)++;
    } else if(glfwGetKey(GLFW_KEY_Z) == GLFW_PRESS){
        (*v)--;
    }
}


int main()
{

    cout << "Debut du programme..." << endl;

    //==================================================
    //============= Creation de la fenetre =============
    //==================================================


    // Initialisation de GLFW
	if( !glfwInit() )
	{
		cout << "Echec de l'initialisation de GLFW" << endl;
		exit(EXIT_FAILURE);
	}

    glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4); // Anti Aliasing
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3); // OpenGL 3.1
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 1);

    // Ouverture d'une fenêtre en 1024x768
    // et creation d'un contexte OpenGL
    if( !glfwOpenWindow(WIDTH, HEIGHT, 0,0,0,0, 32,0, GLFW_WINDOW ) )
	{
		cout << "Echec de l'ouverture de fenetre OpenGL" << endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
    }

    // Definition du titre de la fenêtre
	glfwSetWindowTitle( "Polytech RICM 4 - TP2" );

    // Autorise GLFW a recevoir les appuis de touche
	glfwEnable( GLFW_STICKY_KEYS );

    // Initialisation de  GLEW
	if (glewInit() != GLEW_OK) {
		cout << "Echec de l'initialisation de GLEW" << endl;
		exit(EXIT_FAILURE);
	}

    // Verification des donnees du contexte OpenGL
    const GLubyte* renderer = glGetString (GL_RENDERER);
    cout << "Carte Graphique : " << renderer << endl;

    const GLubyte* version = glGetString (GL_VERSION);
    cout << "Driver OpenGL : " << version << endl;


    //==================================================
    //================= Initialisation =================
    //==================================================

    cout << "Initialisations..." << endl;

    // Definition de la couleur du fond
    glClearColor(0.1, 0.1, 0.1, 0.0);

    // Compilation du shader programm
	GLuint programID = LoadShaders( "../shader/vertex.glsl", "../shader/fragment.glsl" );
    cout << "programID = " << programID << endl;

    // Definition d'un tableau de vecteurs définissant la geometrie
    vec3 vertex[] = {
        vec3(-0.5, -0.5, -0.5),
        vec3( 0.5, -0.5, -0.5),
        vec3(-0.5,  0.5, -0.5),
        vec3(-0.5,  0.5, -0.5),
        vec3( 0.5, -0.5, -0.5),
        vec3( 0.5,  0.5, -0.5)
        };

    // Creation d'un buffer (VBO) avec vboID pour identifiant
    GLuint vboID;
    glGenBuffers(1, &vboID);
    cout << "vboID = " << vboID << endl;

    // Definition de vboID comme le buffer courant
    glBindBuffer(GL_ARRAY_BUFFER, vboID);

    // Copie des donnees sur la carte graphique (dans vboID)
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

	// Obtention de l'ID de l'attribut "vertex_position" dans programID
	GLuint vertexPositionID = glGetAttribLocation(programID, "in_position");
    cout << "vertexPositionID = " << vertexPositionID << endl;


    //==================================================
    // ToDo : Creer les matrices de transformation
    //==================================================

	// Creation des matrices
	mat4 model_matrix = mat4(1.0);
	mat4 view_matrix = lookAt(vec3(0.0, 0.0, 2.0),			// position
							  vec3(0.0),					// orientation
							  vec3(0.0, 1.0, 0.0));			// direction verticale
	mat4 projection_matrix = perspective(45.0f,				// angle de vue
										 WIDTH / HEIGHT,	// ratio de la fenetre
										 0.1f,				// limite de proximite
										 100.0f);			// limite d'eloignement
	
	// Changement de point de vue									 
    vec3 axis = vec3(0.0, 1.0, 0.0);
    vec3 axisX = vec3(1.0, 1.0, 1.0);
	// view_matrix = rotate(view_matrix, 45.0f, axis);
	// view_matrix = scale(view_matrix, vec3(0.5, 0.5, 0.5));
	// view_matrix = translate(view_matrix, vec3(0.5, 0.0, 0.0));

	// Recuperation des ID des matrices dans le shader program
	GLuint MmatrixID = glGetUniformLocation(programID, "ModelMatrix");
	GLuint VmatrixID = glGetUniformLocation(programID, "ViewMatrix");
	GLuint PmatrixID = glGetUniformLocation(programID, "ProjectionMatrix");

    cout << "Debut de la boucle principale..." << endl;
    // Boucle de dessin
    unsigned int i = 0;
    double time1 = glfwGetTime();
    double time2;
    double dt;
    float dx;
    double v = 1;
    float fps;
    int cptFrame = 0;
    bool modeView = true;
    bool modeModel = false;
    bool modeProjection = false;
	do{
        // Nettoyage de la zone de dessin
		glClear( GL_COLOR_BUFFER_BIT );

        time2 = glfwGetTime();
        dt = time2-time1;
        dx = v*dt;
        time1 = time2;
        if(cptFrame == 10){
            cptFrame = 0;
            fps = ((int)100.0/dt)/100.0;
            ostringstream os;
            os << fps;
            string fpsMessage = "Polytech RICM 4 - TP2 -- FR:" + os.str() + " FPS";

            glfwSetWindowTitle(fpsMessage.c_str());
        } else{
            cptFrame++;
        }

        //==================================================
        // ToDo : Modifier les matrices de transformation
        //==================================================

        // Animation de la caméra - rotation autour de l'axe y 

        if(glfwGetKey(GLFW_KEY_F1) == GLFW_PRESS){
            modeView = true;
            modeModel = false;
            modeProjection = false;
        } else if(glfwGetKey(GLFW_KEY_F2) == GLFW_PRESS){
            modeModel = true;
            modeView = false;
            modeProjection = false;
        } else if(glfwGetKey(GLFW_KEY_F3) == GLFW_PRESS){
            modeProjection = true;
            modeView = false;
            modeModel = false;
        }

        if(modeView){
            view_control(&view_matrix, &v, axis);
        } else if(modeModel) {
            model_control(&model_matrix, &v, axis);
        } else if(modeProjection){
            projection_control(&projection_matrix, &v, axis);
        }

        view_matrix = rotate(view_matrix, dx, axisX);

        //==================================================
        //===================== Dessin =====================
        //==================================================


        // Definition de programID comme le shader courant
        glUseProgram(programID);


        //==================================================
        // ToDo : Transmettre les matrices au vertex shader
        //==================================================
		glUniformMatrix4fv(MmatrixID, 1, GL_FALSE, value_ptr(model_matrix));
		glUniformMatrix4fv(VmatrixID, 1, GL_FALSE, value_ptr(view_matrix));
		glUniformMatrix4fv(PmatrixID, 1, GL_FALSE, value_ptr(projection_matrix));


        // Activation de l'attribut vertexPositionID
        glEnableVertexAttribArray(vertexPositionID);

        // Definition de vboID comme le buffer courant
        glBindBuffer(GL_ARRAY_BUFFER, vboID);

        // On lui indique comment lire les donnees
        glVertexAttribPointer(
            vertexPositionID,   // ID de l'attribut à configurer
            3,                  // nombre de composante par position (x, y, z)
            GL_FLOAT,           // type des composantes
            GL_FALSE,           // normalisation des composantes
            0,                  // decalage des composantes
            (void*)0            // offset des composantes
        );


        // On dit a OpenGL de dessiner le contenu du buffer courant
        glDrawArrays(GL_TRIANGLES, 0, 6); // 6 indices en commencant par 0

        // Desactivation de l'attribut d'identifiant 0
        glDisableVertexAttribArray(vertexPositionID);

		// Echange des zones de dessin buffers
		glfwSwapBuffers();

        cout << "Compteur : " << i++ << "\r";
        cout.flush();

    } // Execution de la boucle...
    while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&  // ... jusqu'a appui sur la touche ESC
           glfwGetWindowParam( GLFW_OPENED )        );  // ... ou fermeture de la fenetre

    cout << endl;

    // Ferme GLFW et OpenGL
	glfwTerminate();



    //==================================================
    //============== Nettoyage la memoire ==============
    //==================================================

    // Liberation des vboID
    glDeleteBuffers(1, &vboID);



    cout << "Fin du programme..." << endl;

	return EXIT_SUCCESS;
}


