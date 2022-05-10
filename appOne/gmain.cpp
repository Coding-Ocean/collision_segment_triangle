#include"libOne.h"
#include"view_proj.h"
#include"segment.h"
#include"triangle.h"
#include"axis.h"

#define _COLLISION_SEGMENT_TRIANGLE
#ifdef _COLLISION_SEGMENT_TRIANGLE
void gmain() {
    window(1000, 1000);
    //segment position
    VECTOR osp(0,  0.2f, 0);
    VECTOR oep(0, -0.2f, 0);
    //
    VECTOR sp, ep;
    VECTOR st;//�Z�O�����g�̈ړ��p
    VECTOR sr;//�Z�O�����g�̉�]�p

    //triangle original positions and normal
    VECTOR op[3];
    angleMode(DEGREES);
    op[0].set(sin(   0)*0.5f, 0.0f, -cos(   0)*0.5f);
    op[1].set(sin(-120)*0.5f, 0.0f, -cos(-120)*0.5f);
    op[2].set(sin(-240)*0.5f, 0.0f, -cos(-240)*0.5f);
    angleMode(RADIANS);
    VECTOR on = cross(op[1] - op[0], op[2] - op[0]);
    on.normalize();
    //triangle transposed positions and normal
    VECTOR p[3];
    VECTOR n;
    VECTOR tt;//�O�p�`�̈ړ��p
    VECTOR tr;//�O�p�`�̉�]�p
    
    //colors
    COLOR red(255, 0, 0, 190);
    COLOR pink(255, 200, 200,190);
    COLOR blue(0, 0, 255, 190);
    COLOR white(255, 255, 255);
    COLOR yellow(255, 255, 0);
    
    //�O�σx�N�g���\���X�C�b�`
    int sw = 0;
    
    createProj();

    //main loop
    while (notQuit) {
        clear(50);
        updateView();
        float speed = 0.005f;
        
        //�����𓮂���---------------------------------------------------------
        if (isPress(KEY_SHIFT)) {
            if (isPress(KEY_R)) { sr.z += speed; }
            if (isPress(KEY_Y)) { sr.z -= speed; }
        }
        else {
            if (isPress(KEY_H)) { st.x += speed; }
            if (isPress(KEY_F)) { st.x -= speed; }
            if (isPress(KEY_T)) { st.z -= speed; }
            if (isPress(KEY_G)) { st.z += speed; }
            if (isPress(KEY_R)) { st.y += speed; }
            if (isPress(KEY_Y)) { st.y -= speed; }
        }
        MATRIX mat;
        mat.identity();
        mat.mulTranslate(st.x, st.y, st.z);
        mat.mulRotateZ(sr.z);
        sp = mat * osp;
        ep = mat * oep;

        //�O�p�`�̒��_�𓮂���-------------------------------------------------
        if (isPress(KEY_SHIFT)) {
            if (isPress(KEY_D)) { tr.y += speed; }
            if (isPress(KEY_A)) { tr.y -= speed; }
            if (isPress(KEY_W)) { tr.x -= speed; }
            if (isPress(KEY_S)) { tr.x += speed; }
        }
        else {
            if (isPress(KEY_D)) { tt.x += speed; }
            if (isPress(KEY_A)) { tt.x -= speed; }
            if (isPress(KEY_W)) { tt.z -= speed; }
            if (isPress(KEY_S)) { tt.z += speed; }
            if (isPress(KEY_Q)) { tt.y += speed; }
            if (isPress(KEY_E)) { tt.y -= speed; }
        }
        mat.identity();
        mat.mulTranslate(tt.x,tt.y,tt.z);
        mat.mulRotateY(tr.y);
        mat.mulRotateX(tr.x);
        for (int i = 0; i < 3; i++) {
            p[i] = mat * op[i];
        }
        //�O�p�`�̖@������]������
        mat.identity();
        mat.mulRotateY(tr.y);
        mat.mulRotateX(tr.x);
        n = mat * on;

        //�����蔻��-----------------------------------------------------------
        if (isTrigger(KEY_C))++sw %= 2;//�O�σx�N�g���\�� On Off
        COLOR color = blue;//�������Ă��Ȃ��Ƃ���
        //�u�O�p�`���܂ޕ��ʁv�Ɓu�����v���������Ă��邩
        VECTOR v1 = sp - p[0];
        VECTOR v2 = ep - p[0];
        float d1 = dot(v1, n);
        float d2 = dot(v2, n);
        if (d1 * d2 <= 0) {//�����ʂƌ������Ă���
            //���ʂƐ������������Ă���_�̍��Wip
            d1 = absolute(d1);
            d2 = absolute(d2);
            float m = d1 / (d1 + d2);
            VECTOR ip = sp * (1 - m) + ep * m;
            //ip���O�p�`�Ɋ܂܂�Ă��邩
            int containFlag = 1;//�Ƃ肠�����܂܂�Ă��邱�Ƃɂ���
            for (int i = 0; i < 3; i++) {
                VECTOR side = p[(i + 1) % 3] - p[i];//�O�p�`�̈�ӂ̃x�N�g��
                VECTOR vip = ip - p[i];//�O�p�`�̂P�̒��_��������_�܂ł̃x�N�g��
                VECTOR c = cross(side, vip);
                if(sw)segment(p[i], p[i] + c, yellow);
                float d = dot(n, c);
                if (d < 0) {
                    containFlag = 0;//�܂܂�Ă��Ȃ�
                }
            }
            if (containFlag == 1) {
                color = red;//�O�p�`�ƌ������Ă���
            }
        }
        //draw
        axis();
        segment(sp, ep, white, 1.5f);
        triangle(p, color);

        printSize(20);
        print((let)"n:" + n.x + " " + n.y + " " + n.z);
    }
}
#endif
