#include "spatial.h"

/* Called when the arrow keys are pressed. */

void sp_w(void) {
	spc.y += 5;
}

void sp_a(void) {
	spc.x -= 5;
}

void sp_s(void) {
	spc.y -= 5;
}

void sp_d(void) {
	spc.x += 5;
}

void sp_up(void) {
	spc.ty += SP_WALK_AMOUNT;
}

void sp_down(void) {
	spc.ty -= SP_WALK_AMOUNT;
}

void sp_left(void) {
	spc.tx -= SP_WALK_AMOUNT;
}

void sp_right(void) {
	spc.tx += SP_WALK_AMOUNT;
}
