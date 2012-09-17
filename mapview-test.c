
#include <stdio.h>
#include <stdlib.h>

#include "mapview.h"
#include "mapview.c"

#define Err() do {printf("%i Error\n", __LINE__); exit(1);} while (0);

void test(void)
{
	{
		mapview a = {.w = 100, .h = 200, .vw = 10, .vh = 20};
		a.vx = -10;
		mapview b = mapview_inside(&a);
		if (b.x != a.x) Err();
		if (b.y != a.y) Err();
		if (b.w != a.w) Err();
		if (b.h != a.h) Err();
		if (b.vx != a.x) Err();
		if (b.vy != a.vy) Err();
		if (b.vw != a.vw) Err();
		if (b.vh != a.vh) Err();
	}
	{
		mapview a = {.w = 100, .h = 200, .vw = 10, .vh = 20};
		a.vx = -10;
		a.vy = 0;
		mapview_direction d;
		d = mapview_check_direction(&a);
		if (d != MAPVIEW_LEFT) Err();
		a.vx = 0;
		a.vy = -5;
		d = mapview_check_direction(&a);
		if (d != MAPVIEW_TOP) Err();
		a.vx = 0;
		a.vy = 0;
		d = mapview_check_direction(&a);
		if (d != MAPVIEW_CENTER) Err();
		a.vx = 100;
		a.vy = 0;
		d = mapview_check_direction(&a);
		if (d != MAPVIEW_RIGHT) Err();
		a.vx = 0;
		a.vy = 200;
		d = mapview_check_direction(&a);
		if (d != MAPVIEW_BOTTOM) Err();
	}
	{
		mapview a = {.w = 100, .h = 200, .vw = 10, .vh = 20};
		mapview b = mapview_center(&a);
		if (b.vx != 45) Err();
		if (b.vy != 90) Err();
	}
	{
		mapview a = {.w = 100, .h = 200, .vw = 10, .vh = 20};
		mapview b = mapview_split(&a, MAPVIEW_LEFT);
		if (b.vw != 5) Err();
		if (b.vx != 0) Err();
		b = mapview_split(&a, MAPVIEW_RIGHT);
		if (b.vw != 5) Err();
		if (b.vx != 5) Err();
		b = mapview_split(&a, MAPVIEW_TOP);
		if (b.vh != 10) Err();
		if (b.vx != 0) Err();
		b = mapview_split(&a, MAPVIEW_BOTTOM);
		if (b.vh != 10) Err();
		if (b.vy != 10) Err();
	}
	{
		mapview a = {.w = 100, .h = 200, .vw = 10, .vh = 20};
		mapview b = mapview_swap(&a);
		if (b.x != a.vx) Err();
		if (b.y != a.vy) Err();
		if (b.w != a.vw) Err();
		if (b.h != a.vh) Err();
		if (b.vx != a.x) Err();
		if (b.vy != a.y) Err();
		if (b.vw != a.w) Err();
		if (b.vh != a.h) Err();
	}
	{
		mapview a = {.w = 100, .h = 200, .vw = 10, .vh = 20};
		mapview b = mapview_goto(&a, 7, 7);
		if (b.vx != 2) Err();
		if (b.vy != -3) Err();	
	}
	{
		mapview a = {.w = 100, .h = 200, .vw = 8, .vh = 4};
		mapview b = mapview_everything(&a);
		if (b.vw != 400) Err();
		if (b.vh != 200) Err();
	}
	{
		mapview a = {.w = 200, .h = 100, .vw = 4, .vh = 8};
		mapview b = mapview_everything(&a);
		if (b.vw != 200) Err();
		if (b.vh != 400) Err();
	}
}

int main(int argc, char *argv[])
{
	test();
	printf("Unit tests succeeded\n");
	return 0;
}
