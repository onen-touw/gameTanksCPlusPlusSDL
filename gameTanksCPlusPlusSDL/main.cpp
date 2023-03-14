#include "Gameplay.h"

int main(int argc, char* argv[]) {

	Gameplay gm;

	gm.handlingHelloWin();
	gm.loop();

	return gm.getErrorStatus();
}