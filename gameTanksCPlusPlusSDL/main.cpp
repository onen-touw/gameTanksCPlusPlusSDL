#include "Gameplay.h"

int main(int argc, char* argv[]) {

	Gameplay gm;

	gm.loop();

	return gm.getErrorStatus();
}