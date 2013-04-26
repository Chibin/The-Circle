#include <iostream>
#include "GameManager.h"
using namespace std;

int main(){
	GameManager singleton;
	singleton.GameLoop();
	return 0;
}
