#include "point.h"

inline void 
set_position(int x, int y, struct point *buf)
{
	buf->x = x;
	buf->y = y;
}

inline int
get_x_coord(struct point pt)
{
	return pt.x;
}

inline int
get_y_coord(struct point pt)
{
	return pt.y;
}
