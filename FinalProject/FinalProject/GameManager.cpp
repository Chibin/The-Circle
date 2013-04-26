#include <iostream>
#include "GameManager.h"

GameManager::GameManager(){
	if (!glfwInit())
        std::cout << "error" << std::endl;
    if (!glfwOpenWindow(640, 480, 8, 8, 8, 0, 24, 0, GLFW_WINDOW))
        std::cout << "error" << std::endl;

}
void GameManager::GameLoop(){
	

}
void GameManager::GameDisplay(){
}
