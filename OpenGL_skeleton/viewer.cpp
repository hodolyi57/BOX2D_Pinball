#include "simulator.cpp"

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