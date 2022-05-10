#include"view_proj.h"
#include"graphic.h"

void wall() 
{
    //�P�񃋁[�v���邲�ƂɈȉ��̒l�ŏ�����
    VECTOR p[4] = {
        VECTOR(0, 0, 0),
        VECTOR(1, 0, 0),
        VECTOR(0, 1, 0),
        VECTOR(0, 0, 1),
    };
    //�����č��W�ϊ�
    for (int i = 0; i < 4; i++) {
        p[i] = gView * p[i];
        p[i] = gProj * p[i];
    }
    //�`��
    COLOR c;
    c.set(192, 192, 192, 80);
    triangle3D(p[0], p[1], p[2], c, c, c);
    c.set(255, 255, 255, 80);
    triangle3D(p[0], p[1], p[3], c, c, c);
    c.set(128, 128, 128, 80);
    triangle3D(p[0], p[2], p[3], c, c, c);
}
