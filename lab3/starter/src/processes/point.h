#ifndef POINT_H_
#define POINT_H_

struct point {
	int x;
	int y;
};

extern void set_position(int x, int y, struct point *buf);
extern int get_x_coord(struct point p);
extern int get_y_coord(struct point p);

#endif
