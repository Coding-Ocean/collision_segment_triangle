#include"view_proj.h"
#include"graphic.h"
void triangle(const VECTOR* op, const COLOR& c) 
{
    VECTOR p[3];
    //�����č��W�ϊ�
    for (int i = 0; i < 3; i++) {
        p[i] = gView * op[i];
        p[i] = gProj * p[i];
    }
    //�`��
    triangle3D(p[0], p[1], p[2], c, c, c);
}
