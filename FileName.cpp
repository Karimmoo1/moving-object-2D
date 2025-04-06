#include <Windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

float lanternX = 0.0f;
float lanternY = 0.0f;
float dx = 0.1f;
float dy = 0.1f;

float screenWidth = 800;
float screenHeight = 600;

float worldLeft = -10, worldRight = 10, worldTop = 10, worldBottom = -10;
bool colorToggle = false;

void drawLantern() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Change background color when lantern hits wall
    if (colorToggle)
        glClearColor(0.8, 0.5, 0.2, 1.0);
    else
        glClearColor(0.5, 0.4, 1, 0);

    glTranslatef(lanternX, lanternY, 0);

    glColor3f(1.0, 0.8, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(-2, -5);
    glVertex2f(2, -5);
    glVertex2f(3, 3);
    glVertex2f(-3, 3);
    glEnd();

    glColor3f(1.0, 0.5, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(-1.5, -4);
    glVertex2f(1.5, -4);
    glVertex2f(2, 2);
    glVertex2f(-2, 2);
    glEnd();

    glColor3f(0.6, 0.3, 0.0);
    glBegin(GL_QUADS);
    glVertex2f(-2.5, -5.5);
    glVertex2f(2.5, -5.5);
    glVertex2f(2, -5);
    glVertex2f(-2, -5);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(1, 0, 0);
    glVertex2f(-3, 3);
    glColor3f(1, 1, 0);
    glVertex2f(3, 3);
    glVertex2f(0.0, 5);
    glEnd();

    glColor3f(0, 0, 0);
    glLineWidth(5);
    glBegin(GL_LINES);
    glVertex2f(0.0, 5);
    glVertex2f(0.0, 6);
    glEnd();

    glEnable(GL_POINT_SMOOTH);
    glPointSize(40);
    glBegin(GL_POINTS);
    glColor3f(1, 0.3, 0);
    glVertex2f(0, 6);
    glEnd();

    glFlush();
}

void update(int value) {
    lanternX += dx;
    lanternY += dy;

    // Check for collision with borders
    if (lanternX + 3 >= worldRight || lanternX - 3 <= worldLeft) {
        dx *= -1;
        colorToggle = !colorToggle;
    }

    if (lanternY + 6 >= worldTop || lanternY - 6 <= worldBottom) {
        dy *= -1;
        colorToggle = !colorToggle;
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // ~60 FPS
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float ratio = (float)w / h;
    if (w >= h) {
        gluOrtho2D(-10.0 * ratio, 10.0 * ratio, -10.0, 10.0);
        worldLeft = -10.0f * ratio;
        worldRight = 10.0f * ratio;
        worldTop = 10.0f;
        worldBottom = -10.0f;
    }
    else {
        gluOrtho2D(-10.0, 10.0, -10.0 / ratio, 10.0 / ratio);
        worldLeft = -10.0f;
        worldRight = 10.0f;
        worldTop = 10.0f / ratio;
        worldBottom = -10.0f / ratio;
    }

    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    screenWidth = GetSystemMetrics(SM_CXSCREEN);
    screenHeight = GetSystemMetrics(SM_CYSCREEN);
    glutInitWindowSize(screenWidth, screenHeight);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Moving Lantern");

    glutDisplayFunc(drawLantern);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, update, 0);

    glClearColor(0.5, 0.4, 1, 0);
    glutMainLoop();
    return 0;
}
