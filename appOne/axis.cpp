#include"view_proj.h"
#include"VECTOR.h"
#include"COLOR.h"
#include"segment.h"

VECTOR axisX(1, 0, 0);
VECTOR axisY(0, 1, 0);
VECTOR axisZ(0, 0, 1);
VECTOR o(0, 0, 0);
COLOR color(255,255,255);
float thick = 0.1f;

void axis() 
{
	segment(o, axisX, color, thick);
	segment(o, axisY, color, thick);
	segment(o, axisZ, color, thick);
}