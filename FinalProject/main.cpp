#include <iostream>
#include <SDL.h>
#include "GameManager.h"
using namespace std;

int main(int argc, char *argv[]){
	//start the static version of game manager
	GameManager::getInstance().GameLoop();
	//singleton.GameLoop();
	return 0;
}
