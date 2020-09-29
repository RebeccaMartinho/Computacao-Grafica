#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <windows.h>

float speed = 0;
float barcoX = 0;
float gasolina = 0;
float barcoY = 0;
float heliX = 0;
float heliY = 0;
int opX = 1;
int opY = 1;

int janela_largura = 600;
int janela_altura = 800;

int element = 1;
int espera = 0;
int toRight = true;
int timer = 70;
int level = 0;
int life, totalLifes;

float bala = 0;
float rotacao = 1;
float zoom = 1;
float trans = 1;
float posX = 1;
float posY = 1;
float player1PositionX = 1;
float player1PositionY = 1;
float translateX = 0;
float translateY = 0;
float xStep = 4;
float yStep = 4;
float bulletSpeed = 0;
float combus = 137;

bool bulletTrigerred = false;
bool shouldShowbulled = false;
bool atirou = false;
bool aa = true;
bool ab = true;
bool ac = true;
bool ad = true;
bool ha = true;
bool hb = true;
bool hc = true;
bool pa = true;
bool pb = true;

GLboolean fueloff = false;
GLboolean bateu = false;


void specialKeyboard(int tecla, int x, int y) {
    int DEFAULT_FORCE = 8;

    if (tecla == GLUT_KEY_RIGHT) {
        posX = posX + DEFAULT_FORCE;
    }
    if (tecla == GLUT_KEY_LEFT) {
        posX = posX - DEFAULT_FORCE;
    }
    glutPostRedisplay();
}

void keyboard(unsigned char tecla, int x, int y) {
    int DEFAULT_FORCE = 10;

    if (tecla == 'w') {
        bulletSpeed = 10;
        bulletSpeed++;
        bala = posX;
        atirou = true;
    }
    if (tecla == 'W') {
        bulletSpeed = 10;
        bulletSpeed++;
        bala = posX;
        atirou = true;
    }
}

void resize(GLsizei w, GLsizei h) {
    if (h == 0) h = 1;  // Evita a divisao por zero

    glViewport(0, 0, w, h);  // Especifica as dimensões da Viewport
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (w <= h) {
        gluOrtho2D(0.0f, 600.0f, 0.0f, 600.0f * h / w);
    }
    else {
        gluOrtho2D(0.0f, 600.0f * w / h, 0.0f, 600.0f);
    }
    glMatrixMode(GL_MODELVIEW);

}

int rotatePropeller;
void heli2(int x, int y) {
    glBegin(GL_QUADS);
    glColor3f(0.8f, 0.6f, 0.0f);//cor
    glVertex2f(x - 9 - heliX, y + 105 - speed);
    glVertex2f(x + 20 - heliX, y + 105 - speed);
    glVertex2f(x + 20 - heliX, y + 82 - speed);
    glVertex2f(x - 9 - heliX, y + 82 - speed);
    glEnd();

    // segura o pe
    glBegin(GL_QUADS);
    glColor3f(0.8f, 0.6f, 0.0f);//cor
    glVertex2f(x + 6 - heliX, y + 82 - speed);
    glVertex2f(x + 9 - heliX, y + 82 - speed);
    glVertex2f(x + 9 - heliX, y + 77 - speed);
    glVertex2f(x + 6 - heliX, y + 77 - speed);
    glEnd();

    // pe
    glBegin(GL_QUADS);
    glColor3f(0.8f, 0.6f, 0.0f);//cor
    glVertex2f(x - 4 - heliX, y + 77 - speed);
    glVertex2f(x + 17 - heliX, y + 77 - speed);
    glVertex2f(x + 17 - heliX, y + 74 - speed);
    glVertex2f(x - 4 - heliX, y + 74 - speed);
    glEnd();

    //parte de tras
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f);//cor
    glVertex2f(x - 19 - heliX, y + 85 - speed);
    glVertex2f(x - 19 - heliX, y + 100 - speed);
    glVertex2f(x - 25 - heliX, y + 95 - speed);
    glVertex2f(x - 25 - heliX, y + 90 - speed);
    glEnd();

    //retangulo gigante
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 4.0f);//cor
    glVertex2f(x + 20 - heliX, y + 90 - speed);
    glVertex2f(x + 20 - heliX, y + 95 - speed);
    glVertex2f(x - 25 - heliX, y + 95 - speed);
    glVertex2f(x - 25 - heliX, y + 90 - speed);
    glEnd();

    if (rotatePropeller > 4) {
        // quadrado 
        glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 0.0f);//cor
        glVertex2f(x + 6 - heliX, y + 105 - speed);
        glVertex2f(x + 30 - heliX, y + 105 - speed);
        glVertex2f(x + 30 - heliX, y + 109 - speed);
        glVertex2f(x + 6 - heliX, y + 109 - speed);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 0.0f);//cor
        glVertex2f(x + 9 - heliX, y + 109 - speed);
        glVertex2f(x + 9 - heliX, y + 113 - speed);
        glVertex2f(x - 14 - heliX, y + 113 - speed);
        glVertex2f(x - 14 - heliX, y + 109 - speed);
        glEnd();

    }
    else {

        glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 0.0f);//cor
        glVertex2f(x + 6 - heliX, y + 109 - speed);
        glVertex2f(x + 30 - heliX, y + 109 - speed);
        glVertex2f(x + 30 - heliX, y + 113 - speed);
        glVertex2f(x + 6 - heliX, y + 113 - speed);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 0.0f);//cor
        glVertex2f(x + 9 - heliX, y + 105 - speed);
        glVertex2f(x + 9 - heliX, y + 109 - speed);
        glVertex2f(x - 14 - heliX, y + 109 - speed);
        glVertex2f(x - 14 - heliX, y + 105 - speed);
        glEnd();
    }
}

void Fuel(int x, int y) {
    glTranslatef(opX, opY, 0);

    //inteiro
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.5f, 0.8f);//cor
    glVertex2f(x - 170, y + 250 - speed);
    glVertex2f(x - 130, y + 250 - speed);
    glVertex2f(x - 130, y + 330 - speed);
    glVertex2f(x - 170, y + 330 - speed);
    glEnd();


    //branco em cima do cima
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);//cor
    glVertex2f(x - 170, y + 310 - speed);
    glVertex2f(x - 130, y + 310 - speed);
    glVertex2f(x - 130, y + 290 - speed);
    glVertex2f(x - 170, y + 290 - speed);
    glEnd();

    //branco em cima
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);//cor
    glVertex2f(x - 170, y + 250 - speed);
    glVertex2f(x - 130, y + 250 - speed);
    glVertex2f(x - 130, y + 270 - speed);
    glVertex2f(x - 170, y + 270 - speed);
    glEnd();

    //F Esquerda
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f);//cor
    glVertex2f(x - 160, y + 310 - speed);
    glVertex2f(x - 160, y + 325 - speed);
    glVertex2f(x - 157, y + 325 - speed);
    glVertex2f(x - 157, y + 310 - speed);
    glEnd();

    //F Cima
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f);//cor
    glVertex2f(x - 145, y + 323 - speed);
    glVertex2f(x - 145, y + 325 - speed);
    glVertex2f(x - 157, y + 325 - speed);
    glVertex2f(x - 157, y + 323 - speed);
    glEnd();

    // F Baixo
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f);//cor
    glVertex2f(x - 145, y + 318 - speed);
    glVertex2f(x - 145, y + 320 - speed);
    glVertex2f(x - 157, y + 320 - speed);
    glVertex2f(x - 157, y + 318 - speed);
    glEnd();

    //U Esquerda
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f);//cor
    glVertex2f(x - 160, y + 290 - speed);
    glVertex2f(x - 160, y + 305 - speed);
    glVertex2f(x - 157, y + 305 - speed);
    glVertex2f(x - 157, y + 290 - speed);
    glEnd();

    //U Meio
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f);//cor
    glVertex2f(x - 157, y + 290 - speed);
    glVertex2f(x - 157, y + 292 - speed);
    glVertex2f(x - 145, y + 292 - speed);
    glVertex2f(x - 145, y + 290 - speed);
    glEnd();

    //U  Direita
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f);//cor
    glVertex2f(x - 142, y + 290 - speed);
    glVertex2f(x - 142, y + 305 - speed);
    glVertex2f(x - 145, y + 305 - speed);
    glVertex2f(x - 145, y + 290 - speed);
    glEnd();


    //E Esquerda
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f);//cor
    glVertex2f(x - 160, y + 270 - speed);
    glVertex2f(x - 160, y + 285 - speed);//top
    glVertex2f(x - 157, y + 285 - speed);
    glVertex2f(x - 157, y + 270 - speed);
    glEnd();

    //E Cima
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f);//cor
    glVertex2f(x - 157, y + 283 - speed);
    glVertex2f(x - 157, y + 285 - speed);
    glVertex2f(x - 145, y + 285 - speed);
    glVertex2f(x - 145, y + 283 - speed);
    glEnd();

    //E Baixo
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f);//cor
    glVertex2f(x - 157, y + 270 - speed);
    glVertex2f(x - 157, y + 272 - speed);
    glVertex2f(x - 145, y + 272 - speed);
    glVertex2f(x - 145, y + 270 - speed);
    glEnd();

    //E Meio
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f);//cor
    glVertex2f(x - 157, y + 278 - speed);
    glVertex2f(x - 157, y + 276 - speed);
    glVertex2f(x - 145, y + 276 - speed);
    glVertex2f(x - 145, y + 278 - speed);
    glEnd();


    //L Esquerda
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f);//cor
    glVertex2f(x - 160, y + 250 - speed);
    glVertex2f(x - 160, y + 265 - speed);//top
    glVertex2f(x - 157, y + 265 - speed);
    glVertex2f(x - 157, y + 250 - speed);
    glEnd();

    //L Baixo
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f);//cor
    glVertex2f(x - 157, y + 251 - speed);
    glVertex2f(x - 157, y + 253 - speed);
    glVertex2f(x - 145, y + 253 - speed);
    glVertex2f(x - 145, y + 251 - speed);
    glEnd();
}

void arvore(int x, int y) {
    glTranslatef(opX, opY, 0);

    // madeira
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.5f, 0.0f);//cor
    glVertex2f((x - 235), (y - 260 - speed));
    glVertex2f((x - 215), (y - 260 - speed));
    glVertex2f((x - 215), (y - 270 - speed));
    glVertex2f((x - 235), (y - 270 - speed));
    glEnd();

    //quadrado grande
    glBegin(GL_QUADS);
    glColor3f(0.2f, 0.5f, 0.3f);//cor
    glVertex2f((x - 250), (y - 260 - speed));
    glVertex2f((x - 250), (y - 240 - speed));
    glVertex2f((x - 200), (y - 240 - speed));
    glVertex2f((x - 200), (y - 260 - speed));
    glEnd();

    //retangulo da arvore
    glBegin(GL_QUADS);
    glColor3f(0.2f, 0.5f, 0.3f);//cor
    glVertex2f((x - 260), (y - 245 - speed));
    glVertex2f((x - 260), (y - 255 - speed));
    glVertex2f((x - 190), (y - 255 - speed));
    glVertex2f((x - 190), (y - 245 - speed));
    glEnd();

    //copa da arvore
    glBegin(GL_QUADS);
    glColor3f(0.2f, 0.5f, 0.3f);//cor
    glVertex2f((x - 237), (y - 240 - speed));
    glVertex2f((x - 212), (y - 240 - speed));
    glVertex2f((x - 212), (y - 233 - speed));
    glVertex2f((x - 237), (y - 233 - speed));
    glEnd();
}

void Aeronave(int x, int y) {
    glPushMatrix();
    glRotated(rotacao, 0, 0, 1);
    glScaled(zoom, zoom, 0);
    glTranslatef(posX, posY, 0);

    //retangulo 
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.5f, 0.0f);//cor
    glVertex2f(x - 3, y - 345);
    glVertex2f(x - 3, y - 385);
    glVertex2f(x + 3, y - 385);
    glVertex2f(x + 3, y - 345);
    glEnd();

    //asas 
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.5f, 0.0f);//cor
    glVertex2f(x - 9, y - 360);
    glVertex2f(x - 3, y - 355);
    glVertex2f(x - 3, y - 365);
    glVertex2f(x - 9, y - 370);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.5f, 0.0f);//cor
    glVertex2f(x + 9, y - 360);
    glVertex2f(x + 3, y - 355);
    glVertex2f(x + 3, y - 365);
    glVertex2f(x + 9, y - 370);
    glEnd();

    //asas baixo

    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.5f, 0.0f);//cor
    glVertex2f(x - 7, y - 380);
    glVertex2f(x - 3, y - 378);
    glVertex2f(x - 3, y - 385);
    glVertex2f(x - 7, y - 390);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.5f, 0.0f);//cor
    glVertex2f(x + 7, y - 380);
    glVertex2f(x + 3, y - 378);
    glVertex2f(x + 3, y - 385);
    glVertex2f(x + 7, y - 390);
    glEnd();

    if ((bulletSpeed - 345) > (janela_altura / 2)) {
        atirou = false;
        bala = 0;
    }
    else {
        bulletSpeed = bulletSpeed + 15;
    }
    glPopMatrix();

    if (atirou) {
        glPushMatrix();
        glTranslatef(bala, 0, 0);
        glBegin(GL_QUADS); // bullet
        glColor3ub(233, 201, 122);
        glVertex2f(x - 3, y - 345 + bulletSpeed);
        glVertex2f(x - 3, y - 365 + bulletSpeed);
        glVertex2f(x + 3, y - 365 + bulletSpeed);
        glVertex2f(x + 3, y - 345 + bulletSpeed);
        glEnd();
        glPopMatrix();
    }
}

void Barco(int x, int y) {
    glTranslatef(opX, opY, 0);

    glBegin(GL_QUADS); //SHIP
    glColor3f(0.0f, 0.1f, 0.5f);
    glVertex2f(x + 100 - barcoX, y + 11 - speed);
    glVertex2f(x + 150 - barcoX, y + 11 - speed);
    glVertex2f(x + 150 - barcoX, y + 15 - speed);
    glVertex2f(x + 100 - barcoX, y + 15 - speed);
    glEnd();

    glBegin(GL_QUADS); //SHIP
    glColor3f(0.0f, 0.1f, 0.5f);
    glVertex2f(x + 100 - barcoX, y + 15 - speed);
    glVertex2f(x + 165 - barcoX, y + 15 - speed);
    glVertex2f(x + 165 - barcoX, y + 20 - speed);
    glVertex2f(x + 100 - barcoX, y + 20 - speed);
    glEnd();

    glBegin(GL_QUADS); //SHIP
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(x + 85 - barcoX, y + 20 - speed);
    glVertex2f(x + 165 - barcoX, y + 20 - speed);
    glVertex2f(x + 165 - barcoX, y + 24 - speed);
    glVertex2f(x + 85 - barcoX, y + 24 - speed);
    glEnd();

    glBegin(GL_QUADS); //SHIP
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(x + 70 - barcoX, y + 24 - speed);
    glVertex2f(x + 165 - barcoX, y + 24 - speed);
    glVertex2f(x + 165 - barcoX, y + 29 - speed);
    glVertex2f(x + 70 - barcoX, y + 29 - speed);
    glEnd();

    glBegin(GL_QUADS); //SHIP
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(x + 95 - barcoX, y + 29 - speed);
    glVertex2f(x + 150 - barcoX, y + 29 - speed);
    glVertex2f(x + 150 - barcoX, y + 33 - speed);
    glVertex2f(x + 95 - barcoX, y + 33 - speed);
    glEnd();

    glBegin(GL_QUADS); //SHIP
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(x + 115 - barcoX, y + 33 - speed);
    glVertex2f(x + 145 - barcoX, y + 33 - speed);
    glVertex2f(x + 145 - barcoX, y + 37 - speed);
    glVertex2f(x + 115 - barcoX, y + 37 - speed);
    glEnd();

    glBegin(GL_QUADS); //SHIP
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(x + 115 - barcoX, y + 33 - speed);
    glVertex2f(x + 130 - barcoX, y + 33 - speed);
    glVertex2f(x + 130 - barcoX, y + 42 - speed);
    glVertex2f(x + 115 - barcoX, y + 42 - speed);
    glEnd();
    glPopMatrix();
}

void BarcoParado(int x, int y) {

    if (aa) {
        glTranslatef(opX, opY, 0);
        glBegin(GL_QUADS); //SHIP
        glColor3f(0.0f, 0.1f, 0.5f);
        glVertex2f(x + 100, y + 11 - speed);
        glVertex2f(x + 150, y + 11 - speed);
        glVertex2f(x + 150, y + 15 - speed);
        glVertex2f(x + 100, y + 15 - speed);
        glEnd();

        glBegin(GL_QUADS); //SHIP
        glColor3f(0.0f, 0.1f, 0.5f);
        glVertex2f(x + 100, y + 15 - speed);
        glVertex2f(x + 165, y + 15 - speed);
        glVertex2f(x + 165, y + 20 - speed);
        glVertex2f(x + 100, y + 20 - speed);
        glEnd();

        glBegin(GL_QUADS); //SHIP
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(x + 85, y + 20 - speed);
        glVertex2f(x + 165, y + 20 - speed);
        glVertex2f(x + 165, y + 24 - speed);
        glVertex2f(x + 85, y + 24 - speed);
        glEnd();

        glBegin(GL_QUADS); //SHIP
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(x + 70, y + 24 - speed);
        glVertex2f(x + 165, y + 24 - speed);
        glVertex2f(x + 165, y + 29 - speed);
        glVertex2f(x + 70, y + 29 - speed);
        glEnd();

        glBegin(GL_QUADS); //SHIP
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(x + 95, y + 29 - speed);
        glVertex2f(x + 150, y + 29 - speed);
        glVertex2f(x + 150, y + 33 - speed);
        glVertex2f(x + 95, y + 33 - speed);
        glEnd();

        glBegin(GL_QUADS); //SHIP
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(x + 115, y + 33 - speed);
        glVertex2f(x + 145, y + 33 - speed);
        glVertex2f(x + 145, y + 37 - speed);
        glVertex2f(x + 115, y + 37 - speed);
        glEnd();

        glBegin(GL_QUADS); //SHIP
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(x + 115, y + 33 - speed);
        glVertex2f(x + 130, y + 33 - speed);
        glVertex2f(x + 130, y + 42 - speed);
        glVertex2f(x + 115, y + 42 - speed);
        glEnd();
        glPopMatrix();
    }
}

void PonteMapa1(int x, int y) {
    glTranslatef(opX, opY, 0);

    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f);//cor
    glVertex2f(x + 300, y - 330 - speed);
    glVertex2f(x + 300, y - 400 - speed);
    glVertex2f(x + 35, y - 400 - speed);
    glVertex2f(x + 35, y - 330 - speed);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.3f, 0.3f, 0.3f);//cor
    glVertex2f(x + 300, y - 341 - speed);
    glVertex2f(x + 300, y - 389 - speed);
    glVertex2f(x + 35, y - 389 - speed);
    glVertex2f(x + 35, y - 341 - speed);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 0.0f);//cor
    glVertex2f(x + 300, y - 363 - speed);
    glVertex2f(x + 300, y - 368 - speed);
    glVertex2f(x + 35, y - 368 - speed);
    glVertex2f(x + 35, y - 363 - speed);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f);//cor
    glVertex2f(x - 300, y - 330 - speed);
    glVertex2f(x - 300, y - 400 - speed);
    glVertex2f(x - 20, y - 400 - speed);
    glVertex2f(x - 20, y - 330 - speed);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.3f, 0.3f, 0.3f);//cor
    glVertex2f(x - 300, y - 341 - speed);
    glVertex2f(x - 300, y - 389 - speed);
    glVertex2f(x - 20, y - 389 - speed);
    glVertex2f(x - 20, y - 341 - speed);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 0.0f);//cor
    glVertex2f(x - 300, y - 363 - speed);
    glVertex2f(x - 300, y - 368 - speed);
    glVertex2f(x - 20, y - 368 - speed);
    glVertex2f(x - 20, y - 363 - speed);
    glEnd();
}

void MontanhasMapa1(int x, int y) {
    glTranslatef(opX, opY, 0);

    glBegin(GL_QUADS);
    glColor3f(0.5f, 5.0f, 0.0f);//cor // retangulo lado      //direito 
    glVertex2f(300, y + 3500 - speed);
    glVertex2f(250, y + 3500 - speed);
    glVertex2f(250, y - 1130 - speed);
    glVertex2f(300, y - 1130 - speed);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.5f, 5.0f, 0.0f);//cor // retangulo lado      //esquerda
    glVertex2f(-300, y + 3500 - speed);
    glVertex2f(-250, y + 3500 - speed);
    glVertex2f(-250, y - 1130 - speed);
    glVertex2f(-300, y - 1130 - speed);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.5f, 5.0f, 0.0f);//cor // quadrado da arvore    //esquerda
    glVertex2f(-300, y - 190 - speed);
    glVertex2f(-180, y - 190 - speed);
    glVertex2f(-180, y - 330 - speed);
    glVertex2f(-300, y - 330 - speed);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.5f, 5.0f, 0.0f);//cor // quadrado da arvore    //direito
    glVertex2f(300, y - 190 - speed);
    glVertex2f(180, y - 190 - speed);
    glVertex2f(180, y - 330 - speed);
    glVertex2f(300, y - 330 - speed);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.5f, 5.0f, 0.0f);//cor      //retangulo da arvore   // esquerda
    glVertex2f(-100, y + 150 - speed);
    glVertex2f(-180, y + 150 - speed);
    glVertex2f(-180, y - 140 - speed);
    glVertex2f(-100, y - 140 - speed);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.5f, 5.0f, 0.0f);//cor       // retangulo deitado    // direita 
    glVertex2f(300, y + 190 - speed);
    glVertex2f(300, y + 260 - speed);
    glVertex2f(50, y + 260 - speed);
    glVertex2f(50, y + 190 - speed);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.5f, 5.0f, 0.0f);//cor       // retangulo deitado    // esquerda
    glVertex2f(-300, y + 380 - speed);
    glVertex2f(-300, y + 450 - speed);
    glVertex2f(-50, y + 450 - speed);
    glVertex2f(-50, y + 380 - speed);
    glEnd();
    //colisao mapa 1 completo
}

void MontanhasMapa2(int x, int y) {
    glTranslatef(opX, opY, 0);

    glBegin(GL_QUADS);                      // quadrado q tem uma arvore lado direito
    glColor3f(0.5f, 5.0f, 0.0f);//cor
    glVertex2f(120, y + 700 - speed);
    glVertex2f(120, y + 500 - speed);
    glVertex2f(250, y + 500 - speed);
    glVertex2f(250, y + 700 - speed);
    glEnd();

    glBegin(GL_QUADS);                      //retangulo com as casas e as arvores 
    glColor3f(0.5f, 5.0f, 0.0f);//cor
    glVertex2f(-50, y + 950 - speed);
    glVertex2f(-150, y + 950 - speed);
    glVertex2f(-150, y + 620 - speed);
    glVertex2f(-50, y + 620 - speed);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.5f, 5.0f, 0.0f);//cor      // base do T
    glVertex2f(135, y + 900 - speed);
    glVertex2f(200, y + 900 - speed);
    glVertex2f(200, y + 1100 - speed);
    glVertex2f(135, y + 1100 - speed);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.5f, 5.0f, 0.0f);//cor    // topo do T
    glVertex2f(-25, y + 1050 - speed);
    glVertex2f(-25, y + 1100 - speed);
    glVertex2f(200, y + 1100 - speed);
    glVertex2f(200, y + 1050 - speed);
    glEnd();
}

void MontanhasMapa3(int x, int y) {
    glTranslatef(opX, opY, 0);

    glBegin(GL_QUADS);
    glColor3f(0.3f, 0.3f, 0.3f);//cor // ASFALTO MEIO CINZA
    glVertex2f(-110, y + 1380 - speed);
    glVertex2f(110, y + 1380 - speed);
    glVertex2f(110, y + 1420 - speed);
    glVertex2f(-110, y + 1420 - speed);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.3f, 0.3f, 0.3f);//cor // ASFALTO ESQUERDA CINZA
    glVertex2f(-300, y + 1380 - speed);
    glVertex2f(-250, y + 1380 - speed);
    glVertex2f(-250, y + 1420 - speed);
    glVertex2f(-300, y + 1420 - speed);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.3f, 0.3f, 0.3f);//cor // ASFALTO DIREITA CINZA
    glVertex2f(300, y + 1380 - speed);
    glVertex2f(250, y + 1380 - speed);
    glVertex2f(250, y + 1420 - speed);
    glVertex2f(300, y + 1420 - speed);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 0.0f);//cor // ASFALTO MEIO FAIXA AMARELA
    glVertex2f(-110, y + 1398 - speed);
    glVertex2f(110, y + 1398 - speed);
    glVertex2f(110, y + 1403 - speed);
    glVertex2f(-110, y + 1403 - speed);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 0.0f);//cor // ASFALTO ESQUERDA FAIXA AMARELA
    glVertex2f(-300, y + 1398 - speed);
    glVertex2f(-250, y + 1398 - speed);
    glVertex2f(-250, y + 1403 - speed);
    glVertex2f(-300, y + 1403 - speed);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 0.0f);//cor // ASFALTO DIREITA FAIXA AMARELA
    glVertex2f(300, y + 1398 - speed);
    glVertex2f(250, y + 1398 - speed);
    glVertex2f(250, y + 1403 - speed);
    glVertex2f(300, y + 1403 - speed);
    glEnd();

    glBegin(GL_QUADS);                          // base e topo do +
    glColor3f(0.5f, 5.0f, 0.0f);//cor 
    glVertex2f(100, y + 1500 - speed);
    glVertex2f(-100, y + 1500 - speed);
    glVertex2f(-100, y + 1900 - speed);
    glVertex2f(100, y + 1900 - speed);
    glEnd();

    glBegin(GL_QUADS);                           // largura do +          
    glColor3f(0.5f, 5.0f, 0.0f);//cor 
    glVertex2f(150, y + 1600 - speed);
    glVertex2f(-150, y + 1600 - speed);
    glVertex2f(-150, y + 1800 - speed);
    glVertex2f(150, y + 1800 - speed);
    glEnd();
}

void PonteMapa3(int x, int y) {
    glTranslatef(opX, opY, 0);

    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.3f, 0.1f);//cor // PONTO ESQUERDA PARTE DE BAIXO
    glVertex2f(-250, y + 1388 - speed);
    glVertex2f(-250, y + 1380 - speed);
    glVertex2f(-236, y + 1380 - speed);
    glVertex2f(-236, y + 1388 - speed);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.3f, 0.1f);//cor // PONTO ESQUERDA PARTE DE BAIXO
    glVertex2f(-250, y + 1396 - speed);
    glVertex2f(-250, y + 1388 - speed);
    glVertex2f(-222, y + 1388 - speed);
    glVertex2f(-222, y + 1396 - speed);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.3f, 0.1f);//cor // PONTO ESQUERDA PARTE DE BAIXO LADO DIREITO
    glVertex2f(-124, y + 1388 - speed);
    glVertex2f(-124, y + 1380 - speed);
    glVertex2f(-110, y + 1380 - speed);
    glVertex2f(-110, y + 1388 - speed);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.3f, 0.1f);//cor // PONTO ESQUERDA PARTE DE BAIXO LADO DIREITO
    glVertex2f(-110, y + 1396 - speed);
    glVertex2f(-110, y + 1388 - speed);
    glVertex2f(-138, y + 1388 - speed);
    glVertex2f(-138, y + 1396 - speed);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.3f, 0.1f);//cor // PONTO ESQUERDA PARTE DE CIMA
    glVertex2f(-250, y + 1428 - speed);
    glVertex2f(-250, y + 1396 - speed);
    glVertex2f(-110, y + 1396 - speed);
    glVertex2f(-110, y + 1428 - speed);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.3f, 0.1f);//cor // PONTO ESQUERDA PARTE DE CIMA
    glVertex2f(-236, y + 1436 - speed);
    glVertex2f(-236, y + 1428 - speed);
    glVertex2f(-124, y + 1428 - speed);
    glVertex2f(-124, y + 1436 - speed);
    glEnd();
}

void PonteMapa3Direita(int x, int y) {
    glTranslatef(opX, opY, 0);
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.3f, 0.1f);//cor // PONTO DIREITA PARTE DE BAIXO
    glVertex2f(250, y + 1388 - speed);
    glVertex2f(250, y + 1380 - speed);
    glVertex2f(236, y + 1380 - speed);
    glVertex2f(236, y + 1388 - speed);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.3f, 0.1f);//cor // PONTO DIREITA PARTE DE BAIXO
    glVertex2f(250, y + 1396 - speed);
    glVertex2f(250, y + 1388 - speed);
    glVertex2f(222, y + 1388 - speed);
    glVertex2f(222, y + 1396 - speed);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.3f, 0.1f);//cor // PONTO DIREITA PARTE DE BAIXO LADO DIREITO
    glVertex2f(124, y + 1388 - speed);
    glVertex2f(124, y + 1380 - speed);
    glVertex2f(110, y + 1380 - speed);
    glVertex2f(110, y + 1388 - speed);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.3f, 0.1f);//cor // PONTO DIREITA PARTE DE BAIXO LADO DIREITO
    glVertex2f(110, y + 1396 - speed);
    glVertex2f(110, y + 1388 - speed);
    glVertex2f(138, y + 1388 - speed);
    glVertex2f(138, y + 1396 - speed);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.3f, 0.1f);//cor // PONTO DIREITA PARTE DE CIMA
    glVertex2f(250, y + 1428 - speed);
    glVertex2f(250, y + 1396 - speed);
    glVertex2f(110, y + 1396 - speed);
    glVertex2f(110, y + 1428 - speed);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.3f, 0.1f);//cor // PONTO DIREITA PARTE DE CIMA
    glVertex2f(236, y + 1436 - speed);
    glVertex2f(236, y + 1428 - speed);
    glVertex2f(124, y + 1428 - speed);
    glVertex2f(124, y + 1436 - speed);
    glEnd();
}

void agua() {
    glBegin(GL_QUADS);
    glColor3f(0.1f, 0.5f, 5.0f);//cor
    glVertex2f(-300, -400 - speed);
    glVertex2f(300, -400 - speed);
    glVertex2f(300, 4300 - speed);
    glVertex2f(-300, 4300 - speed);
    glEnd();
}

void nomes(int x, int y) {
    glPushMatrix();

    char nome_str[80];
    strcpy_s(nome_str, "Mauricio e Rebecca");
    GLint nome_length = (GLint)strlen(nome_str);
    GLint nome_cont = 0;

    glScalef(0.1, 0.1, 1);
    glTranslatef(-1800, -2800, 1);

    glPushMatrix();

    glLineWidth(3);
    for (nome_cont = 0; nome_cont < nome_length; nome_cont++) {
        glPushMatrix();
        glColor3ub(255, 255, 255);
        glTranslatef((200 * nome_cont), 0, 0);
        glutStrokeCharacter(GLUT_STROKE_ROMAN, nome_str[nome_cont]);
        glPopMatrix();
    }
    glPopMatrix();

    glPopMatrix();
}

void casa(int x, int y) {
    glTranslatef(opX, opY, 0);

    glBegin(GL_QUADS); //parede 
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f((x + 100), (y - 168 - speed));
    glVertex2f((x + 170), (y - 168 - speed));
    glVertex2f((x + 170), (y - 178 - speed));
    glVertex2f((x + 100), (y - 178 - speed));
    glEnd();

    glBegin(GL_QUADS); //telhado1 
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f((x + 100), (y - 165 - speed));
    glVertex2f((x + 170), (y - 165 - speed));
    glVertex2f((x + 170), (y - 168 - speed));
    glVertex2f((x + 100), (y - 168 - speed));
    glEnd();

    glBegin(GL_QUADS); //telhado2  
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f((x + 110), (y - 163 - speed));
    glVertex2f((x + 160), (y - 163 - speed));
    glVertex2f((x + 160), (y - 165 - speed));
    glVertex2f(x + (110), (y - 165 - speed));
    glEnd();

    glBegin(GL_QUADS); //telhado3  
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f((x + 118), (y - 160 - speed));
    glVertex2f((x + 152), (y - 160 - speed));
    glVertex2f((x + 152), (y - 163 - speed));
    glVertex2f((x + 118), (y - 163 - speed));
    glEnd();

    glBegin(GL_QUADS); //janela1     
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f((x + 150), (y - 171 - speed));
    glVertex2f((x + 160), (y - 171 - speed));
    glVertex2f((x + 160), (y - 175 - speed));
    glVertex2f((x + 150), (y - 175 - speed));
    glEnd();

    glBegin(GL_QUADS); //janela2
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f((x + 129), (y - 171 - speed));
    glVertex2f((x + 139), (y - 171 - speed));
    glVertex2f((x + 139), (y - 175 - speed));
    glVertex2f((x + 129), (y - 175 - speed));
    glEnd();

    glBegin(GL_QUADS); //janela3  
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f((x + 110), (y - 171 - speed));
    glVertex2f((x + 120), (y - 171 - speed));
    glVertex2f((x + 120), (y - 175 - speed));
    glVertex2f((x + 110), (y - 175 - speed));
    glEnd();
}

void painel() {
    glBegin(GL_QUADS);// CINZA TOTAL  
    glColor3f(0.5f, 0.5f, 0.5f);
    glVertex2f(-350, -450);
    glVertex2f(300, -450);
    glVertex2f(300, -320);
    glVertex2f(-350, -320);
    glEnd();

    glBegin(GL_QUADS); // PRETO EM CIMA DO CINZA  
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-350, -320);
    glVertex2f(300, -320);
    glVertex2f(300, -315);
    glVertex2f(-350, -315);
    glEnd();

    glBegin(GL_QUADS); // PRETO BAIXO
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-120, -405);
    glVertex2f(70, -405);
    glVertex2f(70, -400);
    glVertex2f(-120, -400);
    glEnd();

    glBegin(GL_QUADS); // PRETO CIMA
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-120, -340);
    glVertex2f(70, -340);
    glVertex2f(70, -335);
    glVertex2f(-120, -335);
    glEnd();

    glBegin(GL_QUADS); // PRETO ESQUERDA
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-120, -405);
    glVertex2f(-117, -405);
    glVertex2f(-117, -335);
    glVertex2f(-120, -335);
    glEnd();

    glBegin(GL_QUADS); // PRETO DIREITA
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(67, -405);
    glVertex2f(70, -405);
    glVertex2f(70, -335);
    glVertex2f(67, -335);
    glEnd();

    glBegin(GL_QUADS); // BARRA AMARELA DA GASOLINA
    glColor3f(1.0f, 2.0f, 0.0f);
    glVertex2f(35 - gasolina, -400);
    glVertex2f(55 - gasolina, -400);
    glVertex2f(55 - gasolina, -365);
    glVertex2f(35 - gasolina, -365);
    glEnd();

    if (gasolina >= 110) {
        glBegin(GL_QUADS); // BARRA AMARELA DA GASOLINA
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(35 - gasolina, -400);
        glVertex2f(55 - gasolina, -400);
        glVertex2f(55 - gasolina, -365);
        glVertex2f(35 - gasolina, -365);
        glEnd();
    }

    glBegin(GL_QUADS); // E DIREITA
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-105, -395);
    glVertex2f(-100, -395);
    glVertex2f(-100, -360);
    glVertex2f(-105, -360);
    glEnd();

    glBegin(GL_QUADS); // E CIMA
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-105, -357);
    glVertex2f(-83, -357);
    glVertex2f(-83, -360);
    glVertex2f(-105, -360);
    glEnd();

    glBegin(GL_QUADS); // E BAIXO
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-105, -395);
    glVertex2f(-83, -395);
    glVertex2f(-83, -392);
    glVertex2f(-105, -392);
    glEnd();

    glBegin(GL_QUADS); // E meio
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-105, -374);
    glVertex2f(-83, -374);
    glVertex2f(-83, -377);
    glVertex2f(-105, -377);
    glEnd();

    glBegin(GL_QUADS); // E bagulho em cima do E
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-100, -340);
    glVertex2f(-92, -340);
    glVertex2f(-92, -352);
    glVertex2f(-100, -352);
    glEnd();

    glBegin(GL_QUADS); // F DIREITA
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(25, -395);
    glVertex2f(30, -395);
    glVertex2f(30, -360);
    glVertex2f(25, -360);
    glEnd();

    glBegin(GL_QUADS); // F CIMA
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(25, -357);
    glVertex2f(47, -357);
    glVertex2f(47, -360);
    glVertex2f(25, -360);
    glEnd();

    glBegin(GL_QUADS); // F CIMA
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(25, -374);
    glVertex2f(47, -374);
    glVertex2f(47, -377);
    glVertex2f(25, -377);
    glEnd();

    glBegin(GL_QUADS); // F bagulho em cima do F 
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(40, -340);
    glVertex2f(48, -340);
    glVertex2f(48, -352);
    glVertex2f(40, -352);
    glEnd();

    glBegin(GL_QUADS); // 1/2 bagulho em cima do 1/2 
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-24, -340);
    glVertex2f(-16, -340);
    glVertex2f(-16, -352);
    glVertex2f(-24, -352);
    glEnd();

    glBegin(GL_QUADS); // 1/2  ///////////////////////
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-40, -390);
    glVertex2f(-45, -390);
    glVertex2f(-5, -352);
    glVertex2f(0, -352);
    glEnd();

    glBegin(GL_QUADS); // 1/2 111111111
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-40, -352);
    glVertex2f(-36, -352);
    glVertex2f(-36, -375);
    glVertex2f(-40, -375);
    glEnd();

    glBegin(GL_QUADS); // 1/2 111111111
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-36, -352);
    glVertex2f(-45, -352);
    glVertex2f(-45, -356);
    glVertex2f(-36, -356);
    glEnd();

    glBegin(GL_QUADS); // 1/2 22222222222
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-10, -380);
    glVertex2f(-14, -380);
    glVertex2f(-14, -395);
    glVertex2f(-10, -395);
    glEnd();

    glBegin(GL_QUADS); // 1/2 22222222222
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-14, -370);
    glVertex2f(-0, -370);
    glVertex2f(-0, -374);
    glVertex2f(-14, -374);
    glEnd();

    glBegin(GL_QUADS); // 1/2 22222222222
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-4, -374);
    glVertex2f(-0, -374);
    glVertex2f(-0, -380);
    glVertex2f(-4, -380);
    glEnd();

    glBegin(GL_QUADS); // 1/2 22222222222
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-14, -380);
    glVertex2f(-0, -380);
    glVertex2f(-0, -383);
    glVertex2f(-14, -383);
    glEnd();

    glBegin(GL_QUADS); // 1/2 22222222222
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-14, -391);
    glVertex2f(-0, -391);
    glVertex2f(-0, -395);
    glVertex2f(-14, -395);
    glEnd();
}

void colisao(int x1, int x2, int y1, int y2) {
    int AeronaveX1 = -21 - posX;
    int AeronaveX2 = -39 - posX;
    int  AeronaveY1 = -210 - posY;
    int  AeronaveY2 = -250 - posY;

    if (AeronaveX1 < x1 && AeronaveX2 >  x2) {
        if (AeronaveY1 < y1 && AeronaveY1 > y2) {
            printf("- - - Bateu - - -");
            bateu = true;
        }
    }
    else {
    }
}

void colisaobala(int x1, int x2, int y1, int y2, bool* verifi) {

    if (atirou) {
        int  bulletx1 = 3 - 30 - posX;
        int  bulletx2 = -3 - 30 - posX;
        int  bullety1 = -345 + 100 + 30 + 13 + bulletSpeed;
        int  bullety2 = -365 + 100 + 30 + 13 + bulletSpeed;

        if (bulletx1 < x1 && bulletx2 >  x2) {
            if (bullety1 < y1 && bullety1 > y2) {
                printf("- - - Tiro Certeiro - - -");
                *verifi = false;
                atirou = false;
            }
        }
    }
    else {
    }
}

void fuelon(int x1, int x2, int y1, int y2) {
    int AeronaveX1 = -21 - posX;
    int AeronaveX2 = -39 - posX;
    int  AeronaveY1 = -210 - posY;
    int  AeronaveY2 = -250 - posY;

    if (AeronaveX1 < x1 && AeronaveX2 >  x2) {
        if (AeronaveY1 < y1 && AeronaveY1 > y2) {
            printf("- - - Gasolina - - -");
            gasolina = 0;
        }
    }
}

void animate(int value) {
    /////////////////////////////////////////   
    if (gasolina >= combus) {
        bateu = true;
    }
    //////////////////////////////////////////
    if (bateu) {
        espera += timer;
        if (espera >= 3500) {
            speed = 0;
            bateu = false;
            gasolina = 0;
            espera = 0;
            fueloff = false;
            aa = true;
            ab = true;
            ac = true;
            ad = true;
            ha = true;
            hb = true;
            hc = true;
            pa = true;
            pb = true;
        }
    }
    else {
        if (translateX > 300 || translateX < -100) {
            xStep = -xStep;
        }
        if (translateY > 2000 || translateY < 1) {
            yStep = -yStep;
        }
        if (translateY <= (player1PositionX + 400 && translateY >= (player1PositionX - 400))) {
            xStep = -xStep;
        }

        translateX -= xStep;
        translateY -= yStep;
        barcoX = translateX;
        heliX = -translateX;

        barcoX += 3;
        gasolina += 0.55;
        heliX -= 3;
        speed += 6;

        /////////////////////////////////////////////////////////// MAPA 1
        int barcoooX1 = -108; //Barcoooo que fica parado
        int barcoooX2 = -248;
        int barcoooY1 = 11 + 100 + 80 - speed;
        int barcoooY2 = 42 + 100 - speed;

        int ponte1x1 = -25;//mapa 1 pont lado direito
        int ponte1x2 = 300;
        int ponte1y1 = 470 - speed;
        int ponte1y2 = 400 - speed;

        int ponte2x1 = -50; //mapa 1 pont lado direito
        int ponte2x2 = -350;
        int ponte2y1 = 470 - speed;
        int ponte2y2 = 400 - speed;

        int gramaEx1 = -268; // mapa 1 grama p nao sair do mapa
        int gramaEx2 = -350;
        int gramaEy1 = 3500;
        int gramaEy2 = -1130;

        int gramaDx1 = 200;// mapa 1 grama p nao sair do mapa
        int gramaDx2 = 350;
        int gramaDy1 = 3500;
        int gramaDy2 = -1130;

        int quadradoVx1 = -200; //mapa 1 quadrado q tem uma arvore
        int quadradoVx2 = -300;
        int quadradoVy1 = -190 + 800 - speed;
        int quadradoVy2 = -330 + 800 - speed;

        int quadradoDx1 = 130;// mapa 1quadrado q tem uma arvore
        int quadradoDx2 = 300;
        int quadradoDy1 = -190 + 800 - speed;
        int quadradoDy2 = -330 + 800 - speed;

        int retanguloPx1 = 48;  // mapa 1 retangulo de pe 
        int retanguloPx2 = 163;
        int retanguloPy1 = -140 + 800 - speed;
        int retanguloPy2 = 150 + 800 - speed;

        int retanguloDx1 = -65; // mapa 1 retangulo de pe 
        int retanguloDx2 = -300;
        int retanguloDy1 = 190 + 800 - speed;
        int retanguloDy2 = 260 + 800 - speed;

        int retanguloEx1 = 2; // mapa 1 retangulo lado esquerdo
        int retanguloEx2 = 300;
        int retanguloEy1 = 380 + 800 - speed;
        int retanguloEy2 = 450 + 800 - speed;
        ////////////////////////////////////////////////////////////// MAPA 2 

        int quadradaoDx1 = -137; //mapa 2
        int quadradaoDx2 = -300;
        int quadradaoDy1 = 500 + 800 - speed;
        int quadradaoDy2 = 700 + 800 - speed;

        int quadradoCEx1 = 0; //mapa 2
        int quadradoCEx2 = 133;
        int quadradoCEy1 = 620 + 800 - speed;
        int quadradoCEy2 = 950 + 800 - speed;

        int baseTx1 = -150; //mapa 2
        int baseTx2 = -245;
        int baseTy1 = 900 + 800 - speed;
        int baseTy2 = 1100 + 800 - speed;

        int topoTx1 = 3; //mapa 2
        int topoTx2 = -245;
        int topoTy1 = 1050 + 800 - speed;
        int topoTy2 = 1100 + 800 - speed;
        ////////////////////////////////////////////////////////////// MAPA 3

        int ponteCx1 = 91; //mapa 3
        int ponteCx2 = -158;
        int ponteCy1 = 1380 + 800 - speed;
        int ponteCy2 = 1420 + 800 - speed;

        int ponteC1x1 = 61; //PONTE QUEBRAVEL MAPA3
        int ponteC1x2 = 227;
        int ponteC1y1 = 1380 + 800 - speed;
        int ponteC1y2 = 1420 + 800 - speed;

        int ponteC2x1 = -140; //mapa PQUEBRAVEL2 MAPA3
        int ponteC2x2 = -300;
        int ponteC2y1 = 1380 + 800 - speed;
        int ponteC2y2 = 1420 + 800 - speed;

        int basedoMaisx1 = 82; //mapa 3
        int basedoMaisx2 = -152;
        int basedoMaisy1 = 1500 + 800 - speed;
        int basedoMaisy2 = 1900 + 800 - speed;

        int larguraMaisx1 = 130;//mapa 3
        int larguraMaisx2 = -199;
        int larguraMaisy1 = 1600 + 800 - speed;
        int larguraMaisy2 = 1800 + 800 - speed;

        ////////////////////////////////////////////////////////////// HELICOP BARCO

        int HeliMx1 = -15 - 110 + 165 + heliX; // helicopt que se move 1
        int HeliMx2 = 25 - 110 + 160 + heliX;
        int HeliMy1 = +109 + 230 - speed;
        int HeliMy2 = +75 + 230 - speed;

        int HeliM1x1 = 150 + 10 + heliX; // helicopt que se move 2
        int HeliM1x2 = 185 + 10 + heliX;
        int HeliM1y1 = +109 + 1200 + 25 - speed;
        int HeliM1y2 = +75 + 1200 + 25 - speed;

        int HeliM2x1 = -15 - 110 + 165 + heliX; // helicopt que se move 3
        int HeliM2x2 = 25 - 110 + 160 + heliX;
        int HeliM2y1 = +109 + 3100 - speed;
        int HeliM2y2 = +75 + 3100 - speed;

        int barcoM1x1 = 70 - 30 - 165 - 60 + barcoX; // barco que se move 1
        int barcoM1x2 = 165 - 30 - 160 - 60 + barcoX;
        int barcoM1y1 = 11 + 600 - speed;
        int barcoM1y2 = 42 + 600 - speed;

        int barcoM2x1 = 70 - 30 - 165 - 60 + barcoX; // barco que se move 1
        int barcoM2x2 = 165 - 20 - 160 - 60 + barcoX;
        int barcoM2y1 = 11 + 2000 + 10 - speed;
        int barcoM2y2 = 42 + 2000 + 10 - speed;

        int barcoM3x1 = 70 - 30 - 165 - 60 + barcoX; // barco que se move 3
        int barcoM3x2 = 165 - 20 - 160 - 60 + barcoX;
        int barcoM3y1 = 11 + 2800 + 10 - speed;
        int barcoM3y2 = 42 + 2800 + 10 - speed;

        //////////////////////   MAPA 1    ////////////////////  

        colisao(ponte1x2, ponte1x1, ponte1y1, ponte1y2);                 //ponte lado esquerdo
        colisao(ponte2x1, ponte2x2, ponte2y1, ponte2y2);                 //ponto lado direito
        colisao(gramaDx2, gramaDx1, gramaDy1, gramaDy2);                 //grama p nao sair do mapa
        colisao(gramaEx1, gramaEx2, gramaEy1, gramaEy2);                 //grama p nao sair do mapa
        colisao(quadradoVx1, quadradoVx2, quadradoVy1, quadradoVy2);     //quadrado verde direito
        colisao(quadradoDx2, quadradoDx1, quadradoDy1, quadradoDy2);     //quadrado verde esquerdo
        colisao(retanguloPx2, retanguloPx1, retanguloPy2, retanguloPy1); //retangulo
        colisao(retanguloDx1, retanguloDx2, retanguloDy2, retanguloDy1); //retangulo
        colisao(retanguloEx2, retanguloEx1, retanguloEy2, retanguloEy1); //retangulo
           //////////////////////   MAPA 2    ////////////////////
        colisao(topoTx1, topoTx2, topoTy2, topoTy1);
        colisao(baseTx1, baseTx2, baseTy2, baseTy1);
        colisao(quadradoCEx2, quadradoCEx1, quadradoCEy2, quadradoCEy1);
        colisao(quadradaoDx1, quadradaoDx2, quadradaoDy2, quadradaoDy1);
        //////////////////////   MAPA 3    ////////////////////
        colisao(ponteCx1, ponteCx2, ponteCy2, ponteCy1);
        if (pa) {
            colisao(ponteC1x2, ponteC1x1, ponteC1y2, ponteC1y1);
        }
        if (pb) {
            colisao(ponteC2x1, ponteC2x2, ponteC2y2, ponteC2y1);
        }
        colisao(basedoMaisx1, basedoMaisx2, basedoMaisy2, basedoMaisy1);
        colisao(larguraMaisx1, larguraMaisx2, larguraMaisy2, larguraMaisy1);
        //////////////////////   MOVIMENTOS HELI BARCO    ////////////////////
        if (aa) {
            colisao(barcoooX1, barcoooX2, barcoooY1, barcoooY2);             // barco parado
        }
        if (ha) {
            colisao(HeliMx2, HeliMx1, HeliMy1, HeliMy2);
        }
        if (hb) {
            colisao(HeliM1x2, HeliM1x1, HeliM1y1, HeliM1y2);
        }
        if (hc) {
            colisao(HeliM2x2, HeliM2x1, HeliM2y1, HeliM2y2);
        }
        if (ab) {
            colisao(barcoM1x2, barcoM1x1, barcoM1y2, barcoM1y1);
        }
        if (ac) {
            colisao(barcoM2x2, barcoM2x1, barcoM2y2, barcoM2y1);
        }
        if (ad) {
            colisao(barcoM3x2, barcoM3x1, barcoM3y2, barcoM3y1);
        }

        ////////////////////  BALAS   //////////////////////////////////////
        colisaobala(barcoooX1, barcoooX2, barcoooY1, barcoooY2, &aa);             // barco parado
        colisaobala(HeliMx2, HeliMx1, HeliMy1, HeliMy2, &ha);
        colisaobala(HeliM1x2, HeliM1x1, HeliM1y1, HeliM1y2, &hb);
        colisaobala(HeliM2x2, HeliM2x1, HeliM2y1, HeliM2y2, &hc);
        colisaobala(barcoM2x2, barcoM2x1, barcoM2y2, barcoM2y1, &ac);
        colisaobala(barcoM1x2, barcoM1x1, barcoM1y2, barcoM1y1, &ab);
        colisaobala(barcoM3x2, barcoM3x1, barcoM3y2, barcoM3y1, &ad);
        colisaobala(ponteC1x2, ponteC1x1, ponteC1y2, ponteC1y1, &pa); //dieira
        colisaobala(ponteC2x1, ponteC2x2, ponteC2y2, ponteC2y1, &pb);
        ///////////////////// fuelon /////////////////////
        int fuel1x1 = 65;
        int fuel1x2 = 138;
        int fuel1y1 = 250 + 800 - speed;
        int fuel1y2 = 330 + 800 - speed;

        int fuel2x1 = -68;
        int fuel2x2 = -132;
        int fuel2y1 = 250 + 1300 - speed;
        int fuel2y2 = 330 + 1300 - speed;

        int fuel3x1 = -15;
        int fuel3x2 = -100;
        int fuel3y1 = 250 + 2700 - speed;
        int fuel3y2 = 330 + 2700 - speed;

        fuelon(fuel1x2, fuel1x1, fuel1y2, fuel1y1);
        fuelon(fuel2x1, fuel2x2, fuel2y2, fuel2y1);
        fuelon(fuel3x1, fuel3x2, fuel3y2, fuel3y1);
    }
    glutPostRedisplay();
    glutTimerFunc(timer, animate, 1);
}//////////////////////////////////////////////////////////////////////////////////////////////////////

void display() {
    glMatrixMode(GL_MODELVIEW);//cordenadas
    glLoadIdentity();//limpar a matriz

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);  // cor do fundo
    glClear(GL_COLOR_BUFFER_BIT);  // limpa a tela com a cor do fundo

    glTranslatef(janela_largura / 2, janela_altura / 2, 0.0f);
    glViewport(0, 0, janela_largura, janela_altura);

    agua();
    nomes(-500, 400);
    MontanhasMapa2(0, 800);
    MontanhasMapa1(0, 800);
    PonteMapa1(0, 800);
    MontanhasMapa3(0, 795);
    if (pa) {
        PonteMapa3(0, 800);
    }
    if (pb) {
        PonteMapa3Direita(0, 800);
    }
    if (ab) {
        Barco(-30, 600);
    }
    if (ac) {
        Barco(-30, 2000);
    }
    if (ad) {
        Barco(-30, 2800);
    }
    arvore(0, 800); // 1
    arvore(450, 800); // 2
    arvore(80, 1070); //3
    arvore(350, 1280); //4
    arvore(60, 1460); //5
    arvore(420, 1660); //6
    arvore(-60, 1700); //7
    arvore(370, 2110); //8
    arvore(115, 1750); //9
    arvore(115, 1920); //9
    Fuel(0, 800);//1
    Fuel(200, 1300);//2
    Fuel(150, 2700);//3
    if (ha) {
        heli2(-110, 200);//2
    }
    if (hb) {
        heli2(-250, 1200);//3
    }
    if (hc) {
        heli2(-110, 3100);//3
    }
    casa(-249, 1620);//2
    casa(-249, 1880);//3
    BarcoParado(0, 100);

    Aeronave(-30, 100);
    painel();

    barcoX = barcoX + 0;
    heliX = heliX + 0;
    gasolina = gasolina + 0;

    rotatePropeller++;
    if (rotatePropeller == 8) {
        rotatePropeller = 0;
    }
    glFlush(); // executa o desenho
}

int main(int argc, char** argv)
{

    glutInit(&argc, argv);  // controla se o sistema operacional tem suporte a janelas.

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  // quantidade de buffer de cores e que o padrao de cores é RGB ou RGBA

    glutInitWindowSize(600, 800);  // tamanho da janela
    glutInitWindowPosition(500, 100); // posicao inicial da janela
    glutCreateWindow("GLUT Test wagner---- exercicio de glut");

    glutKeyboardFunc(&keyboard); //chama teclado
    glutSpecialFunc(&specialKeyboard);

    glutReshapeFunc(&resize);
    glutTimerFunc(150, animate, 1);//chamada dda animate

    glutDisplayFunc(display);

    glutMainLoop(); //redesenhar
    return EXIT_SUCCESS;

}