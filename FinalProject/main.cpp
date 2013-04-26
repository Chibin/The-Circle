#include <iostream>
#include <SDL.h>
#include "GameManager.h"
using namespace std;

int main(int argc, char *argv[]){
	GameManager singleton;
	singleton.GameLoop();
	std::cout<< "TESTING" << std::endl;
	while(1);
	return 0;
}
