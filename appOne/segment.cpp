#include"graphic.h"
#include"mathUtil.h"
#include"VECTOR.h"
#include"MATRIX.h"
#include"view_proj.h"
#include"segment.h"

//�\���Ɍ�������Q�̎l�p�|���S��
const int numVertices = 8;
float thickness = 0.002f;
VECTOR op[numVertices] = {
    VECTOR(1, 0, -thickness),
    VECTOR(0, 0, -thickness),
    VECTOR(0, 0, thickness),
    VECTOR(1, 0, thickness),
    VECTOR(1, -thickness, 0),
    VECTOR(0, -thickness, 0),
    VECTOR(0, thickness, 0),
    VECTOR(1, thickness, 0),
};
//���W�ϊ���̈ʒu
VECTOR p[numVertices];

void segment(const VECTOR& sp, const VECTOR& ep, const COLOR& col, float thickness)
{
    VECTOR v = ep - sp;
    float len = v.mag();
    float angleY = atan2(-v.z, v.x);
    v.normalize();
    float angleZ = acos(-v.y) - 1.57f;
    MATRIX world;
    world.identity();
    world.mulTranslate(sp.x, sp.y, sp.z);
    world.mulRotateY(angleY);
    world.mulRotateZ(angleZ);
    world.mulScaling(len, thickness, thickness);
    for (int i = 0; i < numVertices; i++) {
        //world���W�ϊ�
        p[i] = world * op[i];
        //gView���W�ϊ�
        p[i] = gView * p[i];
        //projection���W�ϊ�
        p[i] = gProj * p[i];
    }
    triangle3D(p[0], p[1], p[2], col, col, col);
    triangle3D(p[0], p[2], p[3], col, col, col);
    triangle3D(p[4], p[5], p[6], col, col, col);
    triangle3D(p[4], p[6], p[7], col, col, col);
}
