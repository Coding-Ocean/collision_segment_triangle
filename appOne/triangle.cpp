#include"view_proj.h"
#include"graphic.h"
void triangle(const VECTOR* op, const COLOR& c) 
{
    VECTOR p[3];
    //そして座標変換
    for (int i = 0; i < 3; i++) {
        p[i] = gView * op[i];
        p[i] = gProj * p[i];
    }
    //描画
    triangle3D(p[0], p[1], p[2], c, c, c);
}
