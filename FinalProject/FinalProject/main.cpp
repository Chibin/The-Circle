#include <iostream>
#include "GameManager.h"
using namespace std;

void GLFWCALL keyCallback(int key, int action){
	if(key == GLFW_KEY_UP && action == GLFW_PRESS)
		std::cout << "PRESSING UP" << std::endl;
	if(key == GLFW_KEY_ENTER && action == GLFW_PRESS)
		cout << "PRESSING ENTER" << endl;
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//draw everything here
	//call Scene draw here
	glfwSwapBuffers();
}
int main(){
	int counter = 0;

	GameManager singleton;
	
	/* Loop until the user closes the window */
	while (glfwGetWindowParam(GLFW_OPENED))
	{
		//while loop to make sure the frame rate is right, 30 frames?
		{	display();
			//should handle inputs here
			glfwSetKeyCallback(keyCallback);
			glfwSetKeyCallback(keyCallback);
		}
		/* Swap front and back buffers and process events */
		glfwSwapBuffers();
		if(counter > 3000)
			cout << counter++ << endl;
	}
	return 0;
}
