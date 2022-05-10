#include"view_proj.h"
#include"graphic.h"
#include"input.h"
#include"mathUtil.h"
//�s��
extern MATRIX gView={0}, gProj={0};
//�J�����̈ʒu���ߗp�ϐ�
float angleY = 0 * TO_RAD;
float angleX = 10 * TO_RAD;
float radius = 2;
int swCam = 0;
VECTOR camPos, lookat(0, 0, 0), up(0, 1, 0);

void createProj()
{
    gProj.pers(45 * TO_RAD, width / height, 0.1f, 5);
}

void updateView() 
{

    if (isTrigger(KEY_SPACE)) {
        ++swCam %= 4;
        if (swCam == 0) {
            angleY = 30 * TO_RAD;
            angleX = 30 * TO_RAD;
        }
    }

    if (swCam == 0) {
        if (isPress(KEY_L))angleY += 0.017f;
        if (isPress(KEY_J))angleY -= 0.017f;
        if (isPress(KEY_I))angleX += 0.017f;
        if (isPress(KEY_K))angleX -= 0.017f;
        if (angleX > 1.57f)angleX = 1.57f;
        if (angleX < -1.57f)angleX = -1.57f;
    }
    else if (swCam == 1) {
        angleY = 0;
        angleX = 0;
    }
    else if (swCam == 2) {
        angleY = 0;
        angleX = 1.57f;
    }
    else if (swCam == 3) {
        angleY = 1.57f;
        angleX = 0;
    }

    camPos.x = sin(angleY) * cos(angleX) * radius;
    camPos.y = sin(angleX) * radius;
    camPos.z = cos(angleY) * cos(angleX) * radius;
    gView.camera(camPos, lookat, up);
}
