#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#define janela_altura 480
#define janela_largura 640
int on = 1;
int cobree = 1;
float x = 0.0, y = 0.0, z = 0.0;

float padrao[] = { 0.0, 0.0, 0.0, 1.0 };
float mat_ambientee[] = { 0.23125f, 0.23125f, 0.23125f, 1.0f };
float mat_diffuse[] = { 0.2775f, 0.2775f, 0.2775f, 1.0f };
float mat_specular[] = { 0.773911f, 0.773911f, 0.773911f, 1.0f };
float alto_brilho[] = { 25.0 };

void reshape(GLsizei largura, GLsizei altura);
void display();
void keyboard(unsigned char key, int a, int b);
void conf_luz();
int main(int argc, char** argv)
{
	printf("Press 'C' to change colors");
	glutInit(&argc, argv); // Ligar GLUT
	glutInitDisplayMode(GLUT_DOUBLE); // Display com Duplo Buffer
	glutInitWindowSize(janela_largura, janela_altura); // tamanho da janela
	glutInitWindowPosition(50, 50); // Pos. onde surge a janela
	glutCreateWindow("iluminacao"); // Criar Janela
	conf_luz(); // configuração de luz
	glutDisplayFunc(display); // imagem
	glutReshapeFunc(reshape); // config telas
	glutKeyboardFunc(keyboard); // funcoes de teclado
	glutMainLoop(); // loop
	return 0;
}
void conf_luz(void)
{
	if (cobree == 1) {

		float ambiente[] = { 0.0, 0.0, 0.0, 1.0 };
		float diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
		float specular[] = { 1.0, 1.0, 1.0, 1.0 };
		float posicao[] = { 1.5, 0.0 };
		float lmodel_ambiente[] = { 0.4, 0.4, 0.4, 1.0 };
		float local_view[] = { 8.0 };
		glClearColor(0.0, 0.1, 0.1, 0.0);
		glEnable(GL_DEPTH_TEST);
		glShadeModel(GL_SMOOTH);
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
		glLightfv(GL_LIGHT0, GL_POSITION, posicao);
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambiente);
		glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
	}
	else{
	float ambiente[] = { 0.19125f, 0.0735f, 0.0225f, 1.0f };
	float diffuse[] = { 0.7038f, 0.27048f, 0.0828f, 1.0f };
	float specular[] = { 0.256777f, 0.137622f, 0.086014f, 1.0f };

	float posicao[] = { 1.5, 0.0 };
	float lmodel_ambiente[] = { 0.4, 0.4, 0.4, 1.0 };
	float local_view[] = { 0.0 };
	glClearColor(0.0, 0.1, 0.1, 0.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, posicao);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambiente);
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);	
				
	}
	
}

void reshape(GLsizei largura, GLsizei altura)
{
	if (altura == 0) altura = 1; // previne a divisão por zero
	GLfloat aspecto = (GLfloat)largura / (GLfloat)altura;
	glViewport(0, 0, largura, altura);
	glMatrixMode(GL_PROJECTION); // manipulando matriz de projeção
	glLoadIdentity(); // zerando a matriz
	gluPerspective(45.0f, aspecto, 0.1f, 100.0f);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // configura fundo sem transparencia
	glEnable(GL_DEPTH_TEST); // alunos devem testar
	glShadeModel(GL_SMOOTH); // acabamento com suavização
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // correcao de perspectiva
}

void display()
{

	float padrao[] = { 0.0, 0.0, 0.0, 1.0 };

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // executa a limpeza
	glMatrixMode(GL_MODELVIEW); // operando com a camera de modelos


	glLoadIdentity();
	glPushMatrix();
	
	glTranslatef(-1.5f, 0.0f, -6.0f); // posiciona 
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambientee);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, alto_brilho);
	glMaterialfv(GL_FRONT, GL_EMISSION, padrao);
	glutSolidSphere(1.0, 60, 60);
	glPopMatrix();

	//glutSwapBuffers(); // trocar a matriz da tela por esta aqui.
	glPushMatrix();
	glTranslatef(1.5f, 0.0f, -6.0f); // posiciona
	glRotatef(15.0f, 1.0f, 0.0f, 0.0f);

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambientee);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, alto_brilho);
	glMaterialfv(GL_FRONT, GL_EMISSION, padrao);
	glutSolidCube(1.5f);
	glPopMatrix();
	glutSwapBuffers(); // trocar a matriz da tela por esta aqui.


}
void keyboard(unsigned char key, int a, int b)
{
	switch (key)
	{
	case 'o':
	{
		if (on)
		{
			glDisable(GL_LIGHT0);
			on = 0;
		}
		else
		{
			glEnable(GL_LIGHT0);
			on = 1;
		}
		glutPostRedisplay();
	} break;
	case 'c':
	{
		if (cobree) {
			
			conf_luz();
			cobree = 0;
		}
		else
		{
			
			conf_luz();
			cobree = 1;
		}
		glutPostRedisplay();
		
	}
	break;
	}
}