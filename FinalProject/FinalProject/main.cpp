#include <glfw.h>
#include <iostream>
int main(){
	if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    if (!glfwOpenWindow(640, 480, 8, 8, 8, 0, 24, 0, GLFW_WINDOW))
        return -1;

    /* Loop until the user closes the window */
    while (glfwGetWindowParam(GLFW_OPENED))
    {
        
		std::cout << "testing! " <<std::endl;
        /* Swap front and back buffers and process events */
        glfwSwapBuffers();
    }
	return 0;
}