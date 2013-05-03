#include <iostream>
#include <SDL.h>
#include "Manager/GameManager.h"
using namespace std;

int main(int argc, char *argv[]){
	//start the static version of game manager
	GameManager::getInstance().GameLoop();
	return 0;
}
