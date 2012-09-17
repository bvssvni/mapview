#include <stdlib.h>

#include "mapview.h"

mapview mapview_inside(const mapview *view)
{
	mapview m = *view;
	if (m.vx < m.x) m.vx = m.x;
	if (m.vy < m.y) m.vy = m.y;
	if (m.vx + m.vw > m.x + m.w) m.vx = m.x + m.w - m.vw;
	if (m.vy + m.vh > m.y + m.h) m.vy = m.y + m.h - m.vh;
	return m;
}

mapview mapview_center(const mapview *view)
{
	mapview m = *view;
	m.vx = m.x + m.w / 2 - m.vw / 2;
	m.vy = m.y + m.h / 2 - m.vh / 2;
	return m;
}

mapview mapview_corner(const mapview *view, mapview_direction d)
{
	mapview m = *view;
	if ((d&MAPVIEW_LEFT) == MAPVIEW_LEFT) m.vx = m.x;
	if ((d&MAPVIEW_TOP) == MAPVIEW_TOP) m.vy = m.y;
	if ((d&MAPVIEW_RIGHT) == MAPVIEW_RIGHT) m.vx = m.x+m.w-m.vw;
	if ((d&MAPVIEW_BOTTOM) == MAPVIEW_BOTTOM) m.vy = m.y+m.h-m.vh;
	return m;
}

mapview_direction mapview_check_direction(const mapview *m)
{
	mapview_direction d = 0;
	if (m->vx < m->x) d += MAPVIEW_LEFT;
	if (m->vy < m->y) d += MAPVIEW_TOP;
	if (m->vx + m->vw > m->x + m->w) d += MAPVIEW_RIGHT;
	if (m->vy + m->vh > m->y + m->h) d += MAPVIEW_BOTTOM;
	if (d == 0) d = MAPVIEW_CENTER;
	return d;
}

mapview mapview_split(const mapview *view, mapview_direction d)
{
	mapview m = *view;
	if ((d&MAPVIEW_LEFT) == MAPVIEW_LEFT ||
	(d&MAPVIEW_RIGHT) == MAPVIEW_RIGHT) m.vw /= 2;
	if ((d&MAPVIEW_RIGHT) == MAPVIEW_RIGHT) m.vx += m.vw;
	if ((d&MAPVIEW_TOP) == MAPVIEW_TOP || d == MAPVIEW_BOTTOM) m.vh /= 2;
	if ((d&MAPVIEW_BOTTOM) == MAPVIEW_BOTTOM) m.vy += m.vh;
	return m;
}

mapview mapview_swap(const mapview *m)
{
	return (mapview){.x = m->vx, .y = m->vy, .w = m->vw, .h = m->vh,
	.vx = m->x, .vy = m->y, .vw = m->w, .vh = m->h};
}

mapview mapview_goto(const mapview *view, int x, int y)
{
	mapview m = *view;
	m.vx = x - m.vw/2;
	m.vy = y - m.vh/2;
	return m;
}

mapview mapview_everything(const mapview *view)
{
	// Higher ratio means taller rectangle.
	mapview m = *view;
	double r = (double)m.h / m.w;
	double vr = (double)m.vh / m.vw;
	if (r >= vr) {m.vh = m.h; m.vw = (int)(m.h/vr);}
	else {m.vw = m.w; m.vh = (int)(vr*m.w);}
	return m;
}


