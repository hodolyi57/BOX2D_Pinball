#include <iostream>
#include <stdio.h>
#include <glut.h>
#include <math.h>
#include <vector>
using namespace std;

struct Circle
{

    Circle()
    {
        rad = 1.0f;
        coord[0] = 0.0f;
        coord[1] = 30.0f;
        vel[0] = 10.0f;
        vel[1] = 0.0f;
        acc[0] = 0.0f;
        acc[1] = 0.0f;
        mass = 1.0f;
        angle = 0.0f;

    }

    float rad;
    float coord[2];
    float vel[2];
    float acc[2];
    float mass;
    float angle;

};

vector<Circle> path;


// �⺻ ������

float Ground_y = 8.0f;
float gravity[2] = { 0.0f,-10.0f };
float time;
float ex_force[2] = { 0.0f, 0.0f };
Circle circle;

void Update(int value)
{
    time = 0.05f; // ��Ÿ t

    // update the simulation
    // world->Step(timeStep, velocityIterations, positionIterations);

    // �ٴڿ� �浹 �� �ùķ��̼�
    if (circle.coord[1] > Ground_y + circle.rad)
    {
        // ���ӵ�
        circle.acc[1] = gravity[1] / circle.mass;

        // �ӵ�
        circle.vel[0] += circle.acc[0] * time;
        circle.vel[1] += circle.acc[1] * time;

        // ��ġ
        circle.coord[0] += circle.vel[0] * time;
        circle.coord[1] += circle.vel[1] * time;


    }
    // ������� ��ȣ�ۿ� , ������������ X
    else if (circle.coord[1] <= Ground_y + circle.rad)
    {
        // ��ź�� �浹
        if (circle.vel[1] > 0.05f || circle.vel[1] < -0.05f) // ��Ȱ�� �ùķ��̼��� ���� ������
        {
            // ���ӵ�
            circle.acc[1] = gravity[1] / circle.mass;
            // �ӵ�
            circle.vel[0] += circle.acc[0] * time;
            // ��ź�� �浹
            circle.vel[1] = -circle.vel[1] * 0.7 + circle.acc[1] * time;

            // ��ġ
            circle.coord[0] += circle.vel[0] * time;
            circle.coord[1] += circle.vel[1] * time;
        }
        // y�� ���� ��� ���� �� Rolling
        else
        {
            // x�� ���� ��� ���� ����, �ƴϸ� �ܷ��� �� ������ ����
            if (!(circle.vel[0] >= -0.01f && circle.vel[0] <= 0.01f) || ex_force[0] != 0.0f)
            {
                float n = abs(gravity[1]); // �����׷�
                float m = 0.1f; // �������
                float friction;
                // + ������ ��
                if (circle.vel[0] > 0.0f)
                {
                    friction = -n * m;
                }
                // - ������ ��
                else if (circle.vel[0] < 0.0f)
                {
                    friction = n * m;
                }
                else
                {
                    friction = 0.0f;
                }

                // ���ӵ�
                circle.acc[0] = (friction + ex_force[0]) / circle.mass;
                circle.acc[1] = 0.0f;

                // �ӵ�
                circle.vel[0] += circle.acc[0] * time;
                circle.vel[1] = 0.0f;

                // ȸ���� ����� ��ġ ��ȭ�� ����
                float dist = circle.vel[0] * time;
                circle.coord[0] += dist;

                // ȸ��
                circle.angle += -dist / circle.rad * 360.0f / (2.0f * 3.141592f);  // ���ְ�




            }


        }


    }
    // ��� ����
    path.push_back(circle);


    glutPostRedisplay();
    glutTimerFunc(20, Update, 0);   //Recursive function
}