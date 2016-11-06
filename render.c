#include "spatial.h"

/* Create the main camera. */
struct _camera spc = { 0, 0, -100, 0, 0, 0 };

struct _p3d *sp_cube(int l, int w, int h) {
	struct _p3d *cube = malloc(sizeof(struct _p3d) * 8);
	cube[0] = (struct _p3d){ 0, 0, h };
	cube[1] = (struct _p3d){ l, 0, h };
	cube[2] = (struct _p3d){ 0, w, h };
	cube[3] = (struct _p3d){ l, w, h };
	cube[4] = (struct _p3d){ 0, 0, 0 };
	cube[5] = (struct _p3d){ l, 0, 0 };
	cube[6] = (struct _p3d){ 0, w, 0 };
	cube[7] = (struct _p3d){ l, w, 0 };
	return cube;
}

void sp_draw(struct _p3d pos, struct _p3d *vertices, int number) {
	for (int i = 0; i < number; i ++) {
		/* The final 2-dimensional projection of the 3D point. */
		struct _p2d projection;
		/* Projection vector. */
		struct _p3d d;
		double x = vertices[i].x - spc.x,
			   y = vertices[i].y - spc.y,
			   z = vertices[i].z - spc.z;
		/* Cosines and sines of camera rotation. */
		double cx = cos(spc.tx), cy = cos(spc.ty), cz = cos(spc.tz);
		double sx = sin(spc.tx), sy = sin(spc.ty), sz = sin(spc.tz);
		/* Calculate projection vector. */
		d.x = cy * (sz * y + cz * x) - sy * z;
		d.y = sx * (cy * z + sy * (sz * y + cz * x)) + cx * (cz * y - sz * x);
		d.z = cx * (cy * z + sy * (sz * y + cz * x)) - sx * (cz * y - sz * x);
		/* Calculate 2D projection. */
		projection.x = (pos.z / d.z) * d.x - pos.x;
		projection.y = (pos.z / d.z) * d.y - pos.y;
		/* Draw a box to represent the point. */
		sp_line(projection.x, projection.y, projection.x + 2, projection.y, GREEN);
		sp_line(projection.x, projection.y + 2, projection.x, projection.y, GREEN);
		sp_line(projection.x + 2, projection.y + 2, projection.x + 2, projection.y, GREEN);
		sp_line(projection.x, projection.y + 2, projection.x + 2, projection.y + 2, GREEN);
	}
}

/* The main render loop of the engine. */
void sp_render() {

	struct _p3d *cube = sp_cube(100, 100, 100);
	struct _p3d cube_pos = { 100, 100, 100 };
	sp_draw(cube_pos, cube, 8);

}
