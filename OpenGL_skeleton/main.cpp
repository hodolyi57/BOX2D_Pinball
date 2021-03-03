#include <iostream>
#include <stdio.h>
#include <glut.h>
#include <math.h>
#include <vector>


using namespace std;


// Window screen size
int scr_width = 1500;
int scr_height = 600;

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

void display()
{

    // Initialize glut
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluOrtho2D(0.0f, 150.0f, 0.0f, 60.0f);


    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);   // Translation
    glRotatef(0.0f, 0.0f, 0.0f, 1.0f);         // Rotation
    glColor3f(0.2f, 0.2f, 0.2f);            // Set color

    //Draw the edge shape with 2 vertices
    //glLineWidth(3.0f);

    // 바닥 그리기
    glBegin(GL_QUADS);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(150.0f, 0.0f, 0.0f);
    glVertex3f(150.0f, 8.0f, 0.0f);
    glVertex3f(0.0f, 8.0f, 0.0f);
    glEnd();
    glPopMatrix();


    glutSwapBuffers();
    // 원 그리기
    //position = ball->GetPosition();
    //angle = ball->GetAngle();
    //ball->
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(circle.coord[0], circle.coord[1], 0.0f);// Translation
    glRotatef(circle.angle, 0.0f, 0.0f, 1.0f);         // Rotation
    glColor3f(0.2f, 0.5f, 0.7f);            // Set color


    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++)
    {
        double angle = i * 3.141592 / 180;
        double x = circle.rad * cos(angle);
        double y = circle.rad * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();


    // 회전 운동 표시할 선 그리기
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(circle.coord[0], circle.coord[1], 0.0f);// Translation
    glRotatef(circle.angle, 0.0f, 0.0f, 1.0f);         // Rotation
    glColor3f(1.0f, 0.1f, 0.2f);            // Set color


    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, circle.rad, 0.0f);
    glEnd();
    glPopMatrix();

    glutSwapBuffers();


    // 경로 그리기
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    for (int i = 0; i < path.size(); i++)
    {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(path[i].coord[0], path[i].coord[1], 0.0f);// Translation
        glRotatef(circle.angle, 0.0f, 0.0f, 1.0f);         // Rotation
        glColor4f(0.1f, 0.1f, 0.1f, 0.5f);            // Set color

        glBegin(GL_POLYGON);
        for (int i = 0; i < 360; i++)
        {
            double angle = i * 3.141592 / 180;
            double x = 0.2f * cos(angle);
            double y = 0.2f * sin(angle);
            glVertex2f(x, y);
        }
        glEnd();
        glPopMatrix();
    }



    glFlush();

    glutSwapBuffers();

}
void Dokeyboard(unsigned char key, int x, int y)
{


    switch (key)
    {
        // 왼쪽으로 힘주기
    case 'a':
        ex_force[0] = -8.0f;
        break;
        // 오른쪽으로 힘주기
    case 'd':
        ex_force[0] = 8.0f;
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

void Upkeyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        // 왼쪽 힘 풀기
    case 'a':
        ex_force[0] = 0.0f;
        break;
        // 오른쪽 힘 풀기
    case 'd':
        ex_force[0] = 0.0f;
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

void Reshape(int _width, int _height)
{
    scr_width = _width;
    scr_height = _height;
    glViewport(0, 0, _width, _height);
}
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
int main(int argc, char** argv)
{
    // Initialize glut
    glutInitWindowSize(scr_width, scr_height);
    glutInit(&argc, argv);
    glutCreateWindow("Simulation");


    // Setting Box2D elements
    // Setup();

    glutDisplayFunc(display);      //If you want to render, Use it.
    glutReshapeFunc(Reshape);      //Reshape by window size
    glutTimerFunc(20, Update, 0);   //Update physics simulation

    glutKeyboardFunc(Dokeyboard);   //If you want to use keyborad event,
                            //Activate this!
    glutKeyboardUpFunc(Upkeyboard); // 키보드 뗐을 때
    glutMainLoop();

    return 0;
}