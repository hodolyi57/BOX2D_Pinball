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


// 기본 변수들

float Ground_y = 8.0f;
float gravity[2] = { 0.0f,-10.0f };
float time;
float ex_force[2] = { 0.0f, 0.0f };
Circle circle;

void Update(int value)
{
    time = 0.05f; // 델타 t

    // update the simulation
    // world->Step(timeStep, velocityIterations, positionIterations);

    // 바닥에 충돌 전 시뮬레이션
    if (circle.coord[1] > Ground_y + circle.rad)
    {
        // 가속도
        circle.acc[1] = gravity[1] / circle.mass;

        // 속도
        circle.vel[0] += circle.acc[0] * time;
        circle.vel[1] += circle.acc[1] * time;

        // 위치
        circle.coord[0] += circle.vel[0] * time;
        circle.coord[1] += circle.vel[1] * time;


    }
    // 지면과의 상호작용 , 정지해있으면 X
    else if (circle.coord[1] <= Ground_y + circle.rad)
    {
        // 비탄성 충돌
        if (circle.vel[1] > 0.05f || circle.vel[1] < -0.05f) // 원활한 시뮬레이션을 위한 보정값
        {
            // 가속도
            circle.acc[1] = gravity[1] / circle.mass;
            // 속도
            circle.vel[0] += circle.acc[0] * time;
            // 비탄성 충돌
            circle.vel[1] = -circle.vel[1] * 0.7 + circle.acc[1] * time;

            // 위치
            circle.coord[0] += circle.vel[0] * time;
            circle.coord[1] += circle.vel[1] * time;
        }
        // y축 방향 운동량 없을 때 Rolling
        else
        {
            // x축 방향 운동량 있을 때만, 아니면 외력을 준 상태일 때만
            if (!(circle.vel[0] >= -0.01f && circle.vel[0] <= 0.01f) || ex_force[0] != 0.0f)
            {
                float n = abs(gravity[1]); // 수직항력
                float m = 0.1f; // 마찰계수
                float friction;
                // + 방향일 때
                if (circle.vel[0] > 0.0f)
                {
                    friction = -n * m;
                }
                // - 방향일 때
                else if (circle.vel[0] < 0.0f)
                {
                    friction = n * m;
                }
                else
                {
                    friction = 0.0f;
                }

                // 가속도
                circle.acc[0] = (friction + ex_force[0]) / circle.mass;
                circle.acc[1] = 0.0f;

                // 속도
                circle.vel[0] += circle.acc[0] * time;
                circle.vel[1] = 0.0f;

                // 회전각 계산을 위치 변화량 저장
                float dist = circle.vel[0] * time;
                circle.coord[0] += dist;

                // 회전
                circle.angle += -dist / circle.rad * 360.0f / (2.0f * 3.141592f);  // 원주각




            }


        }


    }
    // 경로 저장
    path.push_back(circle);


    glutPostRedisplay();
    glutTimerFunc(20, Update, 0);   //Recursive function
}