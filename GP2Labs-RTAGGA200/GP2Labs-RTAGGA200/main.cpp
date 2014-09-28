//Header files
#include <iostream>
//header for SDL2 functionality
#include<SDL.h>
#include<SDL_opengl.h>
#include<gl\GLU.h>

//Global variables go here
//Pointer to our SDL Windows
SDL_Window*window;
SDL_GLContext glcontext;

bool running = true;

//Constraints to control window creation
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

//values of triangle 1
float triangle1Vertex1PosX = 0.0f;
float triangle1Vertex1PosY = 1.0f;
float triangle1Vertex2PosX = 0.0f;
float triangle1Vertex2PosY = -1.0f;
float triangle1Vertex3PosX = 1.0f;
float triangle1Vertex3PosY = -1.0f;

//values of triangle 2
float triangle2Vertex1PosX = -1.0f;
float triangle2Vertex1PosY = 1.0f;
float triangle2Vertex2PosX = -1.0f;
float triangle2Vertex2PosY = -1.0f;
float triangle2Vertex3PosX = -2.0f;
float triangle2Vertex3PosY = -1.0f;

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
	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

//Function to initialise OpenGL
void initOpenGL(){

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

	//Change to project matrix mode
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//Calculate perspective matrix, using glu library functions
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	//Switch to ModelView
	glMatrixMode(GL_MODELVIEW);

	//Reset using the Identity Matrix
	glLoadIdentity();
}

//Function to draw
void render(){
	//set the clear colour(background)
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//clear the colour and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Switch to ModelView
	glMatrixMode(GL_MODELVIEW);
	//Reset using the Identity Matrix
	glLoadIdentity();
	//Translate to -0.5f on Z-Axis
	glTranslatef(0.0f, 0.0f, -5.0f);
	//Begin drawing triangles
	glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.0f); //Colour of triangle one
		glVertex3f(triangle1Vertex1PosX, triangle1Vertex1PosY, 0.0f); //Top
		glVertex3f(triangle1Vertex2PosX, triangle1Vertex2PosY, 0.0f); //Bottom Left
		glVertex3f(triangle1Vertex3PosX, triangle1Vertex3PosY, 0.0f); //Bottom Right

		glColor3f(0.0f, 1.0f, 0.0f); //Colour of triangle 2
		glVertex3f(triangle2Vertex1PosX, triangle2Vertex1PosY, 0.0f);
		glVertex3f(triangle2Vertex2PosX, triangle2Vertex2PosY, 0.0f);
		glVertex3f(triangle2Vertex3PosX, triangle2Vertex3PosY, 0.0f);
	glEnd();


	//require to swap the back and front buffer
	SDL_GL_SwapWindow(window);

}

//Function to update game state
void update(){

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
	//set our viewport
	setViewport(WINDOW_WIDTH, WINDOW_HEIGHT);

	SDL_Event event;
	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			//Get event type
			if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE){
				//set our boolean which controls the game loop to false
				running = false;
			}
			else if (event.type == SDL_KEYDOWN){
				//checks for keypress
				switch (event.key.keysym.sym){
					//if left key pressed, x coords decreased by 0.1
					case SDLK_LEFT:
						triangle1Vertex1PosX -= 0.1f;
						triangle1Vertex2PosX -= 0.1f;
						triangle1Vertex3PosX -= 0.1f;

						triangle2Vertex1PosX -= 0.1f;
						triangle2Vertex2PosX -= 0.1f;
						triangle2Vertex3PosX -= 0.1f;
						break;
					//if right key pressed, x coords increased by 0.1
					case SDLK_RIGHT:
						triangle1Vertex1PosX += 0.1f;
						triangle1Vertex2PosX += 0.1f;
						triangle1Vertex3PosX += 0.1f;

						triangle2Vertex1PosX += 0.1f;
						triangle2Vertex2PosX += 0.1f;
						triangle2Vertex3PosX += 0.1f;
						break;
					//if up key pressed, y coords increased by 0.1
					case SDLK_UP:
						triangle1Vertex1PosY += 0.1f;
						triangle1Vertex2PosY += 0.1f;
						triangle1Vertex3PosY += 0.1f;

						triangle2Vertex1PosY += 0.1f;
						triangle2Vertex2PosY += 0.1f;
						triangle2Vertex3PosY += 0.1f;
						break;
					//if down key pressed, y coords decreased by 0.1
					case SDLK_DOWN:
						triangle1Vertex1PosY -= 0.1f;
						triangle1Vertex2PosY -= 0.1f;
						triangle1Vertex3PosY -= 0.1f;

						triangle2Vertex1PosY -= 0.1f;
						triangle2Vertex2PosY -= 0.1f;
						triangle2Vertex3PosY -= 0.1f;
						break;
					default:
						break;
				}
			}
		}

		update();
		render();
	}

	CleanUp();
}