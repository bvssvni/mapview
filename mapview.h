/*
	Mapview - C library for dealing with 2D views of map coordinates.
	BSD license.
	by Sven Nilsen, 2012
	http://www.cutoutpro.com

	Version: 0.000 in angular degrees version notation
	http://isprogrammingeasy.blogspot.no/2012/08/angular-degrees-versioning-notation.html
*/
/*
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
1. Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies,
either expressed or implied, of the FreeBSD Project.
*/

#ifndef MAPVIEW_GUARD
#define MAPVIEW_GUARD

typedef struct mapview
{
	int x, y, w, h;
	int vx, vy, vw, vh;
} mapview;

/*
A combination of directions can be set by adding them together.

	// Top left direction.
	mapview_direction d = MAPVIEW_TOP + MAPVIEW_LEFT;

	// Alternative notion.
	mapview_direction d = MAPVIEW_TOP | MAPVIEW_LEFT;
*/
typedef enum mapview_direction
{
	MAPVIEW_CENTER = 1,
	MAPVIEW_TOP = 2,
	MAPVIEW_RIGHT = 4,
	MAPVIEW_BOTTOM = 8,
	MAPVIEW_LEFT = 16
} mapview_direction;

/*
Returns a view that is inside the map.
This function returns a copy because it can be used for animated camera movement.
*/
mapview mapview_inside(const mapview *mapview);

/*
Returns a view that is centered on the map.
*/
mapview mapview_center(const mapview *mapview);

/*
Returns a view that moves by setting a combination of directions.
*/
mapview mapview_corner(const mapview *view, mapview_direction d);

/*
Swaps the view with the map coordinates.
*/
mapview mapview_swap(const mapview *m);

/*
This splits the view into the wanted direction and returns that view.
For example, if you want to split a view into one upper half and lower half
for two player game, you call this function twice with direction 'top' and 'bottom'.
*/
mapview mapview_split(const mapview *mapview, mapview_direction d);

/*
Finds the relation between the view and the map.
If the view is out of bounds to the left, then the left direction is returned.
The same goes for all the others.

This function can be used to divide a level into smaller maps,
load a new piece when the camera moves in that direction.

If the view is not outside, the 'center' flag is set to true.
*/
mapview_direction mapview_check_direction(const mapview *mapview);

/*
Returns a view centered at a coordinate.
If you need to collide with bounds, use 'inside' afterwards.
*/
mapview mapview_goto(const mapview *m, int x, int y);

/*
Returns a view that contains the whole map but constraining the existing ratio.
This is particular useful for displaying thumbnails or similar.
The x and y are untouched, use 'center' aftwards to adjust to the center.
*/
mapview mapview_everything(const mapview *view);

#endif
