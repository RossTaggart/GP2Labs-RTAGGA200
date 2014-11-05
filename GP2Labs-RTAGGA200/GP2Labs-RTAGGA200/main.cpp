//Header files
#include <iostream>
#include <vector>
#include "Vertex.h"
#include "Shader.h"
#include "Texture.h"
#include "GameObject.h"
#include "Mesh.h"
#include "Transform.h"
#include "Camera.h"
#include "Material.h"

//header for SDL2 functionality
#include <gl\glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <gl\GLU.h>
#include <SDL_ttf.h>

//maths headers
#include <glm/glm.hpp>
using glm::mat4;
using glm::vec3;

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifdef _DEBUG && WIN32
const std::string ASSET_PATH = "../assets";
#else
const std::string ASSET_PATH = "assets";
#endif
const std::string SHADER_PATH = "/shaders";
const std::string TEXTURE_PATH = "/textures";
const std::string FONT_PATH = "/fonts";

//Global variables go here
//Pointer to our SDL Windows
SDL_Window * window;
//SDL GL Context
SDL_GLContext glcontext = NULL;

//Shader Programs
GLuint shaderProgram2d = 0;
GLuint shaderProgram3d = 0;

//matrices
mat4 viewMatrix;

//2D matrices
mat4 projMatrix2d;
mat4 worldMatrix2d;

//3D matrices
mat4 projMatrix3d;
mat4 worldMatrix3d;

//Constants to control window creation
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

bool running = true;


Vertex triangleData[] = 
{
	//Front
		{ vec3(-0.5f, 0.5f, 0.5f), vec2(0.0f, 0.0f), vec4(1.0f, 0.0f, 1.0f, 1.0f) }, //Top Left
		{ vec3(-0.5f, -0.5f, 0.5f), vec2(0.0f, 1.0f), vec4(1.0f, 1.0f, 0.0f, 1.0f) }, //Bottom Left
		{ vec3(0.5f, -0.5f, 0.5f), vec2(1.0f, 1.0f), vec4(0.0f, 1.0f, 1.0f, 1.0f) }, //Bottom Right
		{ vec3(0.5f, 0.5f, 0.5f), vec2(1.0f, 0.0f), vec4(1.0f, 0.0f, 1.0f, 1.0f) }, //Top Right

		//Back
		{ vec3(-0.5f, 0.5f, -0.5f), vec2(0.0f, 0.0f), vec4(1.0f, 0.0f, 1.0f, 1.0f) }, //Top Left
		{ vec3(-0.5f, -0.5f, -0.5f), vec2(0.0f, 1.0f), vec4(1.0f, 1.0f, 0.0f, 1.0f) }, //Bottom Left
		{ vec3(0.5f, -0.5f, -0.5f), vec2(1.0f, 1.0f), vec4(0.0f, 1.0f, 1.0f, 1.0f) }, //Bottom Right
		{ vec3(0.5f, 0.5f, -0.5f), vec2(1.0f, 0.0f), vec4(1.0f, 0.0f, 1.0f, 1.0f) }, //Top Right

		//Left
		{ vec3(-0.5f, 0.5f, -0.5f), vec2(0.0f, 0.0f), vec4(1.0f, 0.0f, 1.0f, 1.0f) }, //Top Left
		{ vec3(-0.5f, -0.5f, -0.5f), vec2(0.0f, 1.0f), vec4(1.0f, 1.0f, 0.0f, 1.0f) }, //Bottom Left
		{ vec3(-0.5f, -0.5f, 0.5f), vec2(1.0f, 1.0f), vec4(0.0f, 1.0f, 1.0f, 1.0f) }, //Bottom Right
		{ vec3(-0.5f, 0.5f, 0.5f), vec2(1.0f, 0.0f), vec4(1.0f, 0.0f, 1.0f, 1.0f) }, //Top Right

		//Right
		{ vec3(0.5f, 0.5f, 0.5f), vec2(0.0f, 0.0f), vec4(1.0f, 0.0f, 1.0f, 1.0f) }, //Top Left
		{ vec3(0.5f, -0.5f, 0.5f), vec2(0.0f, 1.0f), vec4(1.0f, 1.0f, 0.0f, 1.0f) }, //Bottom Left
		{ vec3(0.5f, -0.5f, -0.5f), vec2(1.0f, 1.0f), vec4(0.0f, 1.0f, 1.0f, 1.0f) }, //Bottom Right
		{ vec3(0.5f, 0.5f, -0.5f), vec2(1.0f, 0.0f), vec4(1.0f, 0.0f, 1.0f, 1.0f) }, //Top Right

		//Top
		{ vec3(-0.5f, 0.5f, -0.5f), vec2(0.0f, 0.0f), vec4(1.0f, 0.0f, 1.0f, 1.0f) }, //Top Left
		{ vec3(-0.5f, 0.5f, 0.5f), vec2(0.0f, 1.0f), vec4(1.0f, 1.0f, 0.0f, 1.0f) }, //Bottom Left
		{ vec3(0.5f, 0.5f, 0.5f), vec2(1.0f, 1.0f), vec4(0.0f, 1.0f, 1.0f, 1.0f) }, //Bottom Right
		{ vec3(0.5f, 0.5f, -0.5f), vec2(1.0f, 0.0f), vec4(1.0f, 0.0f, 1.0f, 1.0f) }, //Top Right

		//Bottom
		{ vec3(-0.5f, -0.5f, 0.5f), vec2(0.0f, 0.0f), vec4(1.0f, 0.0f, 1.0f, 1.0f) }, //Top Left
		{ vec3(-0.5f, -0.5f, -0.5f), vec2(0.0f, 1.0f), vec4(1.0f, 1.0f, 0.0f, 1.0f) }, //Bottom Left
		{ vec3(0.5f, -0.5f, -0.5f), vec2(1.0f, 1.0f), vec4(0.0f, 1.0f, 1.0f, 1.0f) }, //Bottom Right
		{ vec3(0.5f, -0.5f, 0.5f), vec2(1.0f, 0.0f), vec4(1.0f, 0.0f, 1.0f, 1.0f) }, //Top Right

};

GLuint indices[] = 
{
	//Front
	0, 1, 2,
	0, 3, 2,
	//Left
	4, 5, 1,
	4, 1, 0,
	//Right
	3, 7, 2,
	7, 6, 2,
	//Bottom
	1, 5, 2,
	6, 2, 1,
	//Top
	5, 0, 7,
	5, 7, 3,
	//Back
	4, 5, 6,
	4, 7, 6
};

//2D
GLuint VBO2d;
GLuint EBO2d;
GLuint VAO2d;

//3D
GLuint VBO3d;
GLuint EBO3d;
GLuint VAO3d;

//Textures
GLuint texture = 0;
GLuint fontTexture = 0;

vector<GameObject*> displayList;
GameObject * mainCamera;

//Global functions
void InitWindow(int width, int height, bool fullscreen)
{
	//Create a window
	window = SDL_CreateWindow("Lab 1",	//window title
		SDL_WINDOWPOS_CENTERED,	//x position, centered
		SDL_WINDOWPOS_CENTERED,	//y position, centered
		width,	//width, in pixels
		height,	//height, in pixels
		SDL_WINDOW_OPENGL	//flags
		);
}

void initialise()
{
	mainCamera = new GameObject();
	mainCamera->setName("Camera");

	Transform *t = new Transform();
	t->setPosition(0.0f,0.0f,10.0f);
	mainCamera->setTransform(t);

	Camera *c = new Camera();
	c->setLookAt(0.0f,0.0f,0.0f);
	c->setUp(0.0f,1.0f,0.0f);
	c->setFOV(45.0f);
	c->setAspectRatio(16.0f / 9.0f);
	c->setNearClip(0.1f);
	c->setFarClip(100.0f);
	mainCamera->setCamera(c);
	displayList.push_back(mainCamera);

	GameObject *cube = new GameObject();
	cube->setName("Cube");

	t = new Transform();
	t->setPosition(0.0f,0.0f,0.0f);
	cube->setTransform(t);

	Material *material = new Material();
	string vsPath = ASSET_PATH + SHADER_PATH + "/simpleVS.glsl";
	string fsPath = ASSET_PATH + SHADER_PATH + "/simpleFS.glsl";
	material->loadShader(vsPath, fsPath);
	cube->setMaterial(material);

	Mesh *mesh = new Mesh();
	cube->setMesh(mesh);

	displayList.push_back(cube);
	
	for (auto iter = displayList.begin(); iter != displayList.end(); iter++)
	{
		(*iter)->init();

	}

	mesh->copyVertexData(8, sizeof(Vertex), (void**)(triangleData));
	mesh->copyIndexData(36, sizeof(int), (void**)(indices));


}


//Used to cleanup once we exit
void CleanUp()
{
	/*CleanUp2D();
	CleanUp3D();*/
	auto iter = displayList.begin();
	while (iter != displayList.end())
	{
		(*iter)->destroy();
		if ((*iter))
		{
			delete(*iter);
			(*iter) = NULL;
			iter = displayList.erase(iter);
		}
		else
		{
			iter++;
		}
	}
	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

//Function to initialise OpenGL
void initOpenGL()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	//Create OpenGL Context
	glcontext = SDL_GL_CreateContext(window);
	//Something went wrong in creating the context, if it is still NULL
	if (!glcontext)
	{
		std::cout << "Error Creating OpenGL Context" << SDL_GetError() << std::endl;
	}

	//Smooth shading
	glShadeModel(GL_SMOOTH);
	//clear the background to black
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//Clear the depth buffer to 1.0
	glClearDepth(1.0f);
	//Enable depth testing
	glEnable(GL_DEPTH_TEST);
	//The depth test to use
	glDepthFunc(GL_LEQUAL);
	//Turn on best perspective correction
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glewExperimental = GL_TRUE;

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/*Problem: glewInit failed, something is seriously wrong*/
		std::cout << "Error: " << glewGetErrorString(err) << std::endl;
	}
}

//Function to set/reset viewport
void setViewport(int width, int height)
{
	//screen ration
	GLfloat ratio;
	//make sure height is always above 0
	if (height == 0)
	{
		height = 1;
	}
	//calculate screen ration
	ratio = (GLfloat)width / (GLfloat)height;
	//Setup viewport
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}



//Function to draw
void render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	for (auto iter = displayList.begin(); iter != displayList.end(); iter++)
	{
		(*iter)->render();
		Mesh * currentMesh = (*iter)->getMesh();
		Transform * currentTransform = (*iter)->getTransform();
		Material * currentMaterial = (*iter)->getMaterial();

		if (currentMesh && currentTransform && currentMaterial)
		{
			currentMesh->Bind();
			currentMaterial->Bind();

			GLint MVPLocation = currentMaterial->getUniformLocation("MVP");
			Camera *cam = mainCamera->getCamera();
			mat4 MVP = cam->getProjectionMatrix()*cam->getViewMatrix()*currentTransform->getModelMatrix();
			glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, glm::value_ptr(MVP));

			//glDrawElements(GL_TRIANGLES, currentMesh->getIndex(), GL_UNSIGNED_INT, 0);
		}

	}


	SDL_GL_SwapWindow(window);
}


//Function to update game state
void update()
{

	for (auto iter = displayList.begin(); iter != displayList.end(); iter++)
	{
		(*iter)->update();

	}
}

//Main Method - Entry Point
int main(int argc, char * arg[])
{
	// init everything - SDL, if it is nonzero we have a problem
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "ERROR SDL_Init" << SDL_GetError() << std::endl;
		return -1;
	}
	if (TTF_Init() == -1)
	{
		std::cout << "ERROR TFF_Init: " << TTF_GetError();
	}

	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, false);
	
	//Call our InitOpenGL Function
	initOpenGL();

	setViewport(WINDOW_WIDTH, WINDOW_HEIGHT);


	initialise();

	SDL_Event event;
	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			//Get event type
			if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE)
			{
				//set our boolean which controls the game loop to false
				running = false;
			}
		}
		
		update();
		render();
	}

	CleanUp();
	return 0;
}
