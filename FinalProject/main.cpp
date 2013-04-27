#include <iostream>
#include <SDL.h>
#include "GameManager.h"
using namespace std;

int main(int argc, char *argv[]){
	GameManager singleton;
	singleton.GameLoop();
	return 0;
}
