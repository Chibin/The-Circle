#include <iostream>
#include <SDL.h>
#include <Windows.h>
#include "Manager/GameManager.h"
using namespace std;

int main(int argc, char *argv[]){
	//start the static version of game manager
	//FreeConsole();
	GameManager::getInstance().GameLoop();
	
	std::cout << "Game exited..." << std::endl;
	return 0;
}
