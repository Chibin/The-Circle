#include <iostream>
#include "GameManager.h"

void GLFWCALL keyCallback(int key, int action){
	//will probably need switch case later on
	if(key == GLFW_KEY_UP && action == GLFW_PRESS)
		std::cout << "PRESSING UP" << std::endl;
	if(key == GLFW_KEY_ENTER && action == GLFW_PRESS)
		std::cout << "PRESSING ENTER" << std::endl;
	if(key == GLFW_KEY_ESC && action == GLFW_PRESS)
		glfwTerminate();
}
GameManager::GameManager(){
	if (!glfwInit())
        std::cout << "error" << std::endl;
    if (!glfwOpenWindow(640, 480, 8, 8, 8, 0, 24, 0, GLFW_WINDOW))
        std::cout << "error" << std::endl;
}
void GameManager::GameLoop(){
	while (glfwGetWindowParam(GLFW_OPENED))
	{
		//gameEngine Handle here
		//while loop to make sure the frame rate is right, 30 frames?
		{	//will only redraw ever 30 frames
			GameDisplay();
			//should handle inputs here
			glfwSetKeyCallback(keyCallback);
			glfwSetKeyCallback(keyCallback);
		}
		/* Swap front and back buffers and process events */
		glfwSwapBuffers();
	}
}

//will handle all the drawing
void GameManager::GameDisplay(){
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//call Scene draw here
	glfwSwapBuffers();
}
