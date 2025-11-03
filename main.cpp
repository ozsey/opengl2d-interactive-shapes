#include <GL/glut.h>
#include <iostream>
#include <vector>

int windowWidth = 640;
int windowHeight = 480;

bool drawLines = false;
bool solidMode = true;

GLfloat mouseX = 0;
GLfloat mouseY = 0;

struct Point {
    GLfloat x;
    GLfloat y;
};

std::vector<Point> points;

GLfloat square1Color[3] = {1.0, 1.0, 1.0}; // Warna default untuk persegi 1 (putih)
GLfloat triangleColor[3] = {1.0, 1.0, 1.0}; // Warna default untuk segitiga (putih)
GLfloat square2Color[3] = {1.0, 1.0, 1.0}; // Warna default untuk persegi 2 (putih)

// Fungsi untuk menggambar persegi
void drawSquare(GLfloat color[]) {
    if (solidMode) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Mode penggambaran: solid
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Mode penggambaran: wireframe
    }
    glBegin(GL_QUADS);
    glColor3fv(color);
    glVertex2f(-25, -25);
    glVertex2f(25, -25);
    glVertex2f(25, 25);
    glVertex2f(-25, 25);
    glEnd();
}

// Fungsi untuk menggambar segitiga
void drawTriangle(GLfloat color[]) {
    if (solidMode) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Mode penggambaran: solid
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Mode penggambaran: wireframe
    }
    glBegin(GL_TRIANGLES);
    glColor3fv(color);
    glVertex2f(0, 25);
    glVertex2f(-25, -25);
    glVertex2f(25, -25);
    glEnd();
}

// Fungsi untuk menggambar titik
void drawPoint(GLfloat x, GLfloat y) {
    glPointSize(5.0); // Ukuran titik
    glBegin(GL_POINTS);
    glColor3f(1.0, 1.0, 1.0); // Warna titik (putih)
    glVertex2f(x, y);
    glEnd();
}

// Fungsi untuk menggambar titik-titik yang tetap
void drawPermanentPoints() {
    glPointSize(5.0); // Ukuran titik
    glBegin(GL_POINTS);
    glColor3f(1.0, 1.0, 1.0); // Warna titik (putih)
    for (const auto& point : points) {
        glVertex2f(point.x, point.y);
    }
    glEnd();
}

// Fungsi untuk menggambar semua objek
void draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glPushMatrix();
    glTranslatef(-100, 0, 0);
    drawSquare(square1Color); // Gambar persegi 1
    glPopMatrix();

    drawTriangle(triangleColor); // Gambar segitiga

    glPushMatrix();
    glTranslatef(100, 0, 0);
    drawSquare(square2Color); // Gambar persegi 2
    glPopMatrix();

    drawPermanentPoints(); // Gambar titik-titik yang tetap

    drawPoint(mouseX, mouseY); // Gambar titik pada posisi mouse

    glutSwapBuffers();
}

// Fungsi yang dipanggil saat tombol keyboard ditekan
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'a':
        case 'A':
            square1Color[0] = 0.0; // Merah
            square1Color[1] = 0.0;
            square1Color[2] = 1.0;

            triangleColor[0] = 1.0; // Hijau
            triangleColor[1] = 0.0;
            triangleColor[2] = 0.0;

            square2Color[0] = 0.0; // Biru
            square2Color[1] = 1.0;
            square2Color[2] = 0.0;
            solidMode = true;
            break;
        case 's':
        case 'S':
            square1Color[0] = 1.0; // Kembali ke warna default (putih)
            square1Color[1] = 1.0;
            square1Color[2] = 1.0;

            triangleColor[0] = 1.0;
            triangleColor[1] = 1.0;
            triangleColor[2] = 1.0;

            square2Color[0] = 1.0;
            square2Color[1] = 1.0;
            square2Color[2] = 1.0;
            solidMode = true;
            break;
        case 'd':
        case 'D':
            drawLines = !drawLines; // Toggle mode antara solid dan wireframe
            solidMode = false;
            square1Color[0] = 1.0; // Kembali ke warna default (putih)
            square1Color[1] = 1.0;
            square1Color[2] = 1.0;

            triangleColor[0] = 1.0;
            triangleColor[1] = 1.0;
            triangleColor[2] = 1.0;

            square2Color[0] = 1.0;
            square2Color[1] = 1.0;
            square2Color[2] = 1.0;
            break;
    }
    glutPostRedisplay();
}

// Fungsi yang dipanggil saat tombol mouse ditekan
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        mouseX = x - windowWidth / 2;
        mouseY = windowHeight / 2 - y;
        points.push_back({mouseX, mouseY});
    }
    glutPostRedisplay();
}

// Fungsi untuk mengatur ulang tampilan saat window diubah ukurannya
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-w / 2, w / 2, -h / 2, h / 2);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    windowWidth = w;
    windowHeight = h;
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Computer Graphics Assignment");

    glClearColor(0.0, 0.0, 0.0, 1.0); // Warna latar belakang (hitam)

    glutDisplayFunc(draw);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}
