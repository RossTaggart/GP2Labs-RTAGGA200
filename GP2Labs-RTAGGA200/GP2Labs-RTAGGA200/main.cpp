//Header files
#include <iostream>
#include "Vertex.h"
#include "Shader.h"
//Maths headers
#include <glm/glm.hpp>
using glm::mat4;
using glm::vec3;

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//header for SDL2 functionality

#include<gl\glew.h>
#include<SDL.h>
#include<SDL_opengl.h>
#include<gl\GLU.h>

#ifdef _DEBUG && WIN32
const std::string ASSET_PATH = "../assets";
#else
const std::string ASSET_PATH = "assets";
#endif

const std::string SHADER_PATH = "/shaders";

//Global variables go here
//Pointer to our SDL Windows
SDL_Window*window;
SDL_GLContext glcontext;

bool running = true;
//Constraints to control window creation
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

Vertex triangleData[] = {
	//Front
		{ -0.5f, 0.5f, 0.5f,
		1.0f, 0.0f, 1.0f, 1.0f }, //Top Left

		{ -0.5f, -0.5f, 0.5f,
		1.0f, 1.0f, 0.0f, 1.0f }, //Bottom Left

		{ 0.5f, -0.5f, 0.5f,
		0.0f, 1.0f, 1.0f, 1.0f }, //Bottom Right

		{ 0.5f, 0.5f, 0.5f,
		1.0f, 0.0f, 1.0f, 1.0f }, //Top Right

	//Back
		{ -0.5f, 0.5f, -0.5f,
		1.0f, 0.0f, 1.0f, 1.0f }, //Top Left

		{ -0.5f, -0.5f, -0.5f,
		1.0f, 1.0f, 0.0f, 1.0f }, //Bottom Left

		{ 0.5f, -0.5f, -0.5f,
		0.0f, 1.0f, 1.0f, 1.0f }, //Bottom Right

		{ 0.5f, 0.5f, -0.5f,
		1.0f, 0.0f, 1.0f, 1.0f }, //Top Right
		
	//Right
		{ 0.5f, 0.5f, 0.5f,
		1.0f, 0.0f, 1.0f, 0.0f }, //Top Left

		{ 0.5f, -0.5f, 0.5f,
		0.0f, 1.0f, 1.0f, 1.0f }, //Bottom Left

		{ 0.5f, -0.5f, -0.5f,
		0.0f, 1.0f, 1.0f, 1.0f }, //Bottom Right

		{ 0.5f, 0.5f, -0.5f,
		1.0f, 0.0f, 1.0f, 1.0f }, //Top Right

	//Left
		{-0.5f, 0.5f, -0.5f,
		1.0f, 0.0f, 1.0f, 0.0f}, //Top left

		{-0.5f, -0.5f, -0.5f,
		1.0f, 1.0f, 0.0f, 1.0f}, //Bottom Left

		{ -0.5f, -0.5f, 0.5f,
		1.0f, 1.0f, 0.0f, 1.0f }, //Bottom Right

		{ -0.5f, 0.5f, 0.5f,
		1.0f, 0.0f, 1.0f, 1.0f }, //Top Right

	//Top
		{ -0.5f, 0.5f, -0.5f,
		1.0f, 0.0f, 1.0f, 1.0f }, //Top Left

		{ -0.5f, -0.5f, 0.5f,
		1.0f, 0.0f, 1.0f, 1.0f }, //Bottom Left

		{ 0.5f, 0.5f, 0.5f,
		1.0f, 0.0f, 1.0f, 1.0f }, //Bottom Right

		{ 0.5f, 0.5f, -0.5f,
		1.0f, 0.0f, 1.0f, 1.0f }, //Top Right

	//Bottom
		{ -0.5f, -0.5f, -0.5f,
		1.0f, 1.0f, 0.0f, 1.0f }, //Top Left

		{ -0.5f, -0.5f, -0.5f,
		1.0f, 1.0f, 0.0f, 1.0f }, //Bottom Left

		{ 0.5f, -0.5f, 0.5f,
		0.0f, 1.0f, 1.0f, 1.0f }, //Bottom Right

		{ 0.5f, -0.5f, -0.5f,
		0.0f, 1.0f, 1.0f, 1.0f }, //Top Right
};

GLuint indices[] = {
	//front
	0, 1, 2,
	0, 3, 2,

	//left
	4, 5, 1,
	4, 1, 0,

	//right
	3, 7, 2,
	7, 6, 2,

	//bottom
	1, 5, 2,
	6, 2, 1,

	//top
	5, 0, 7,
	5, 7, 3,

	//back
	4, 5, 6,
	4, 7, 6
};


double cameraPosX = 0.0;
double cameraPosY = 0.0;
double cameraPosZ = 0.0;

float cube1PosX = 1.0f;
float cube1PosY = 0.0f;
float cube1PosZ = -4.0f;

GLuint triangleVBO;
GLuint triangleEBO;
GLuint VAO;

GLuint shaderProgram = 0;

//matrices
mat4 viewMatrix;
mat4 projMatrix;
mat4 worldMatrix;


//Global functions
void InitWindow(int width, int height, bool fullscreen){

	//Create a window
	window = SDL_CreateWindow("Lab1",//window title
								SDL_WINDOWPOS_CENTERED, //x position, centered
								SDL_WINDOWPOS_CENTERED, //y position, centered
								width, //width, in pixels
								height, //height, in pixels
								SDL_WINDOW_OPENGL //flags
								);
}

//Used to cleanup once we exit
void CleanUp(){
	glDeleteVertexArrays(1, &VAO);
	glDeleteProgram(shaderProgram);
	glDeleteBuffers(1, &triangleEBO);
	glDeleteBuffers(1, &triangleVBO);
	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

//Function to initialise OpenGL
void initOpenGL(){

	//Ask for version 3.2 of OpenGL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	//Create OpenGL Context
	glcontext = SDL_GL_CreateContext(window);
	//Something went wrong in creating the context, if it is still NULL
	if (!glcontext){

		std::cout << "Error Creating OpenGL Context" << SDL_GetError() <<
		std::endl;
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
	if (GLEW_OK != err){
		/*Problem: glewInit failed, something is seriously wrong*/
		std::cout << "Error: " << glewGetErrorString(err) << std::endl;
	}

}

//Function to set/reset viewport
void setViewport(int width, int height){

	//screen ration
	GLfloat ratio;

	//make sure height is always above 0
	if (height == 0){
		height = 1;
	}

	//calculate screen ration
	ratio = (GLfloat)width / (GLfloat)height;

	//Setup viewport
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	
}

//Function to draw
void render(){
	//set the clear colour(background)
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//clear the colour and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Make the new VBO active. Repeat here as a sanity check (may have changed since init
	glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
		//Bind EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangleEBO);
	glBindVertexArray(VAO);

	glUseProgram(shaderProgram);

	GLint MVPLocation = glGetUniformLocation(shaderProgram, "MVP");
	mat4 MVP = projMatrix*viewMatrix*worldMatrix;
	glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, glm::value_ptr(MVP));

	//Tell the shader that 0 is the position element
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), NULL);



	//Actually draw the triangle, giving the number of vertices provided
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	//require to swap the back and front buffer
	SDL_GL_SwapWindow(window);

}

//Function to update game state
void update(){

	projMatrix = glm::perspective(45.0f, (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.f);
	viewMatrix = glm::lookAt(vec3(0.0f, 0.0f, 5.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	worldMatrix = glm::translate(mat4(1.0f), vec3(0.0f, 0.0f, 0.0f));
}

void initGeometry(){
	
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	//Tell the shader that 0 is the position element
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), NULL);

	//Create buffer
	glGenBuffers(1, &triangleVBO);
	//Make the new VBO active
	glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
	//Copy Vertext Data to VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleData), triangleData, GL_STATIC_DRAW);

	//Create buffer
	glGenBuffers(1, &triangleEBO);
	//Make the EBO active
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangleEBO);
	//Copy Index data to the EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

}

void createShader(){

	GLuint vertexShaderProgram = 0;
	std::string vsPath = ASSET_PATH + SHADER_PATH + "/simpleVS.glsl";
	vertexShaderProgram = loadShaderFromFile(vsPath, VERTEX_SHADER);

	GLuint fragmentShaderProgram = 0;
	std::string fsPath = ASSET_PATH + SHADER_PATH + "/simpleFS.glsl";
	fragmentShaderProgram = loadShaderFromFile(fsPath, FRAGMENT_SHADER);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShaderProgram);
	glAttachShader(shaderProgram, fragmentShaderProgram);
	glLinkProgram(shaderProgram);
	checkForLinkErrors(shaderProgram);

	glBindAttribLocation(shaderProgram, 0, "vertexPosition");

	//now we can delete the VS & FS Programs
	glDeleteShader(vertexShaderProgram);
	glDeleteShader(fragmentShaderProgram);
}

//Main Method - Entry Point
int main(int argc, char* arg[]){
	//init everything - SDL, if it is nonzero we have a problem
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "ERROR SDL_Init" << SDL_GetError() << std::endl;

		return-1;
	}
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, false);

	//Call our InitOpenGL Function
	initOpenGL();
	//Call our initGeometry function
	initGeometry();
	//set our viewport
	setViewport(WINDOW_WIDTH, WINDOW_HEIGHT);

	SDL_Event event;
	createShader();
	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			//Get event type
			if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE){
				//set our boolean which controls the game loop to false
				running = false;
			}
		
			
		}

		update();
		render();
	}

	CleanUp();
}