#include <iostream>
#include <vector>
#include <string>

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







    cout << "Debut de la boucle principale..." << endl;
    // Boucle de dessin
    unsigned int i = 0;
	do{
        // Nettoyage de la zone de dessin
		glClear( GL_COLOR_BUFFER_BIT );

        //==================================================
        // ToDo : Modifier les matrices de transformation
        //==================================================





        //==================================================
        //===================== Dessin =====================
        //==================================================


        // Definition de programID comme le shader courant
        glUseProgram(programID);


        //==================================================
        // ToDo : Transmettre les matrices au vertex shader
        //==================================================




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


