using namespace std;

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
#include "FBXLoader.h"
#include "Light.h"

//header for SDL2 functionality
#include <gl\glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <gl\GLU.h>
#include <SDL_ttf.h>

//maths headers
#include <glm/glm.hpp>
using glm::mat4;
using glm::vec4;
using glm::vec3;

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifdef _DEBUG && WIN32
const string ASSET_PATH = "../assets/";
#else
const string ASSET_PATH = "assets/";
#endif
const string SHADER_PATH = "shaders/";
const string TEXTURE_PATH = "textures/";
const string FONT_PATH = "fonts/";
const string MODEL_PATH = "models/";

//Global variables go here
//Pointer to our SDL Windows
SDL_Window * window;
//SDL GL Context
SDL_GLContext glcontext = NULL;

//Constants to control window creation
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

bool running = true;

//Vertex triangleData[] = 
//{
//	//Front
//		{ vec3(-0.5f, 0.5f, 0.5f), vec2(0.0f, 0.0f), vec4(1.0f, 0.0f, 1.0f, 1.0f) }, //Top Left
//		{ vec3(-0.5f, -0.5f, 0.5f), vec2(0.0f, 1.0f), vec4(1.0f, 1.0f, 0.0f, 1.0f) }, //Bottom Left
//		{ vec3(0.5f, -0.5f, 0.5f), vec2(1.0f, 1.0f), vec4(0.0f, 1.0f, 1.0f, 1.0f) }, //Bottom Right
//		{ vec3(0.5f, 0.5f, 0.5f), vec2(1.0f, 0.0f), vec4(1.0f, 0.0f, 1.0f, 1.0f) }, //Top Right
//
//		//Back
//		{ vec3(-0.5f, 0.5f, -0.5f), vec2(0.0f, 0.0f), vec4(1.0f, 0.0f, 1.0f, 1.0f) }, //Top Left
//		{ vec3(-0.5f, -0.5f, -0.5f), vec2(0.0f, 1.0f), vec4(1.0f, 1.0f, 0.0f, 1.0f) }, //Bottom Left
//		{ vec3(0.5f, -0.5f, -0.5f), vec2(1.0f, 1.0f), vec4(0.0f, 1.0f, 1.0f, 1.0f) }, //Bottom Right
//		{ vec3(0.5f, 0.5f, -0.5f), vec2(1.0f, 0.0f), vec4(1.0f, 0.0f, 1.0f, 1.0f) } //Top Right
//
//};
//
//GLuint indices[] = 
//{
//	//Front
//	0, 1, 2,
//	0, 3, 2,
//	//Left
//	4, 5, 1,
//	4, 1, 0,
//	//Right
//	3, 7, 2,
//	7, 6, 2,
//	//Bottom
//	1, 5, 2,
//	6, 2, 1,
//	//Top
//	5, 0, 7,
//	5, 7, 3,
//	//Back
//	4, 5, 6,
//	4, 7, 6
//};

vector<GameObject*> displayList;
GameObject * mainCamera;
GameObject * mainLight;

vec4 ambientLightColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);

//Global functions
void InitWindow(int width, int height, bool fullscreen)
{
	//Create a window
	window = SDL_CreateWindow("Lab 7",	//window title
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
	t->setPosition(0.0f, 0.0f, 10.0f);
	mainCamera->setTransform(t);

	Camera *c = new Camera();
	c->setFOV(45.0f);
	c->setAspectRatio((float)WINDOW_WIDTH / WINDOW_HEIGHT);
	c->setNearClip(0.1f);
	c->setFarClip(100.0f);

	mainCamera->setCamera(c);
	displayList.push_back(mainCamera);

	mainLight = new GameObject();
	mainLight->setName("MainLight");

	t = new Transform();
	t->setPosition(0.0f, 0.0f, 0.0f);
	mainLight->setTransform(t);

	Light *l = new Light();
	mainLight->setLight(l);
	displayList.push_back(mainLight);

	for (auto iter = displayList.begin(); iter != displayList.end(); iter++)
	{
		(*iter)->init();

	}
	
	string ModelPath = ASSET_PATH + MODEL_PATH + "armoredrecon.fbx";
	GameObject* go = loadFBXFromFile(ModelPath);
	for (int i = 0; i < go->getChildCount(); i++)
	{
		Material* material = new Material();
		material->init();
		string vsPath = ASSET_PATH + SHADER_PATH + "diffuseVS.glsl";
		string fsPath = ASSET_PATH + SHADER_PATH + "diffuseFS.glsl";
		material->loadShader(vsPath, fsPath);

		go->getChild(i)->setMaterial(material);
	}
	displayList.push_back(go);


	/*GameObject *cube = new GameObject();
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

	displayList.push_back(cube);*/

	/*mesh->copyVertexData(8, sizeof(Vertex), (void**)(triangleData));
	mesh->copyIndexData(36, sizeof(int), (void**)(indices));*/


}


//Used to cleanup once we exit
void CleanUp()
{
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
	displayList.clear();

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

//draws game object
void renderGameObject(GameObject* pObject)
{
	if (!pObject){
		return;
	}
	
	pObject->render();

	Mesh * currentMesh = pObject->getMesh();
	Transform * currentTransform = pObject->getTransform();
	Material * currentMaterial = pObject->getMaterial();

	if (currentMesh && currentTransform && currentMaterial)
	{
		currentMesh->Bind();
		currentMaterial->Bind();

		GLint MVPLocation = currentMaterial->getUniformLocation("MVP");
		GLint ModelLocation = currentMaterial->getUniformLocation("Model");

		GLint ambientMaterialLocation = currentMaterial->getUniformLocation("ambientMaterialColor");
		GLint ambientLightLocation = currentMaterial->getUniformLocation("ambientLightColor");

		GLint lightDirectionLocation = currentMaterial->getUniformLocation("lightDirection");
		GLint diffuseMatLocation = currentMaterial->getUniformLocation("diffuseMaterialColor");
		GLint diffuseLightLocation = currentMaterial->getUniformLocation("diffuseLightColor");

		Camera *cam = mainCamera->getCamera();
		Light *light = mainLight->getLight();

		mat4 MVP = cam->getProjectionMatrix()*cam->getViewMatrix()*currentTransform->getModelMatrix();
		mat4 Model = currentTransform->getModelMatrix();
		
		vec4 ambientMaterialColor = currentMaterial->getAmbientColor();
		vec4 diffuseMaterialColor = currentMaterial->getDiffuseColor();
		vec4 diffuseLightColor = light->getLightDiffuse();
		vec3 lightDirection = light->getLightDirection();

		glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, glm::value_ptr(MVP));
		glUniformMatrix4fv(ModelLocation, 1, GL_FALSE, glm::value_ptr(Model));

		glUniform4fv(ambientMaterialLocation, 1, glm::value_ptr(ambientMaterialColor));
		glUniform4fv(ambientLightLocation, 1, glm::value_ptr(ambientLightColor));

		glUniform4fv(diffuseMatLocation, 1, glm::value_ptr(diffuseMaterialColor));
		glUniform4fv(diffuseLightLocation, 1, glm::value_ptr(diffuseLightColor));
		glUniform3fv(lightDirectionLocation, 1, glm::value_ptr(lightDirection));

		glDrawElements(GL_TRIANGLES, currentMesh->getIndex(), GL_UNSIGNED_INT, 0);
	}

	for (int i = 0; i < pObject->getChildCount(); i++)
	{
		renderGameObject(pObject->getChild(i));
	}
	
}

//Function to draw
void render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto iter = displayList.begin(); iter != displayList.end(); iter++)
	{
		(*iter)->render();
		renderGameObject((*iter));
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
