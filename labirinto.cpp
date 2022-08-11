//*******
// Gabriel Dias Oliveira
// Disciplina : Computação Gráfica - UNIVASF
// Base de criação : Jogo "Labirinto" 
/*1 - O objeto deve estar preenchido com uma cor de escolha da dupla;
2 - Os obstáculos podem ser definidos pela dupla (no mínimo 7 no tabuleiro) ;
3 - Utilizar as setas do teclado para movimento do objeto no trajeto.
4 - O botão esquerdo do mouse deve ser usado para mudar as cores da janela, 
dos obstáculos e do objeto.
5 - Outros requisitos para o funcionamento do jogo 
(contador de vidas, dimensões, cores, formato do labirinto etc..) 
podem ser definidos pela dupla.*/
//EXTRAS: 
// ver regra do circulo para talvez seg*2  {inverter de 180 para 360} 
// -> Tx: colocar para 20+  é a posição inicial do boneco 1 para a direita 
// mudar linha  para if ( tx < -win/16 ) 	tx = -win/16; caso queira limitar o boneco 1 para a metade 
//*******

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

// Declaração de variáveis globais
int cor = 0 , vidas = 3;
GLfloat rf = 0.0 , gf = 0 ,bf = 0 , plan1 = 0 ; // variaveis de cores
GLfloat tx = 0 , ty = -18; //posição inicial do boneco 
GLfloat ang1 = 0, ang2 = -90; //angulos
GLfloat win = 25; //janela

//Função para desenhar circulo
void drawCircleFill(float cx, float cy, float r, int num_segments)
{
    float theta = 3.1415926 * 2 / float(num_segments);
    float tangetial_factor = tanf(theta);// calcula fator tangencial
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    float radial_factor = cosf(theta);//calcula fator radial 
    float x = r;//iniciando angulo em 0 
    float y = 0;

    glBegin(GL_POLYGON);
    
    if (num_segments = 180) num_segments = num_segments/2; 
    for (int ii = 0; ii < num_segments; ii++)
    {
        glVertex2f(x + cx, y + cy);//vertex de saída

        float tx = -y;
        float ty = x;

        x += tx * tangetial_factor;
        y += ty * tangetial_factor;

        x *= radial_factor;
        y *= radial_factor;
    }
    glEnd();
}

// função vida
void Vida()
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);          //fundo branco
		glVertex2f(24,24);
		glVertex2f(24,20);
		glVertex2f(26,20);
		glVertex2f(26,24);
	glEnd();
	if(vidas==3){
		glColor3f(1.0f, 0.0f, 0.0f);          //cor vermelho
    	drawCircleFill(25, 23, 0.4, -180); // vida 1
	    drawCircleFill(25, 22, 0.4, -180); // vida 2
		drawCircleFill(25, 21, 0.4, -180); // vida 3
	}
	else{
	if(vidas==2){
		glColor3f(1.0f, 0.0f, 0.0f);
		drawCircleFill(25, 23, 0.4, -180); // vida 1
	    drawCircleFill(25, 22, 0.4, -180); // vida 2
		}
	if(vidas==1){
	glColor3f(1.0f, 0.0f, 0.0f); 
	drawCircleFill(25, 23, 0.4, -180); // vida 1
		}
	if( vidas == 0 ){
		printf("\n\n  DERROTA (YOU LOSE)");
		vidas=3;
		}
	}
	
	
		
}

//função de tratamento de colisões
void Colisoes()
{
	if(tx >= -15 && ty>= -14 && ty <= -10){ //linha de baixo
	vidas--;
	tx = 0 , ty = -20;
	}
	
	if(tx <= 15 && ty>= 5 && ty <= 9){ //linha meio
	vidas--;
	tx = 0 , ty = -20;
	}
	
	if(tx >= -2 && tx <= 1 && ty>= -1 && ty <= 4.5){ //bloco 1 vertical
	vidas--;
	tx = 0 , ty = -20;
	}
	
	if(tx >= 4 && tx <= 15 && ty>= -7 && ty <= -1){ //bloco 1 horizontal
	vidas--;
	tx = 0 , ty = -20;
	}
	
	if(tx >= 19 && tx <= 25 && ty>= -9.5 && ty <= -1){ //bloco 2 vertical
	vidas--;
	tx = 0 , ty = -20;
	}
	
	if(tx >= 19 && ty>= 0 && ty <= 9){ //bloco 2 horizontal
	vidas--;
	tx = 0 , ty = -20;
	}
	
	if(tx >= -16 && ty>= 14){ //linha topo
	vidas--;
	tx = 0 , ty = -20;
	}
	
	if(tx >= -24 && tx <=17 && ty>= 17){ //linha topo
	vidas=3;
	tx = 0 , ty = -20;
	printf("\n\n  VITORIA (YOU WIN)");}
	
}
// Função para desenhar a base do objeto {ave}          
void DesenhaBase()
{
	glLineWidth(2);
	glBegin(GL_POLYGON);
		glVertex2f(2,0);
		glVertex2f(2,-2);
		glVertex2f(0,-2);
		glVertex2f(0,0);
	glEnd();
}
           
// Função callback de redesenho da janela de visualização
void Desenha(void)
{
	// Muda para o sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa a matriz de transformação corrente
	glLoadIdentity();
	// Limpa a janela de visualização com a cor de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT);

	// Desenha o "topo"
	glColor3f(0.004f,0.364f,0.031f); glLineWidth(6); glBegin(GL_LINE_LOOP);	glVertex2f(-win,25); glVertex2f(win,25); glEnd();
	
	//desenha o prato de comida
	glColor3f(0.7, 0.5, 0.2);
	drawCircleFill(-20,20,3,90);
	glColor3f(1.0f,1.0f,0.0f);
    glPointSize(4);
	glBegin(GL_POINTS);
		glVertex2i(-20,20);  glVertex2i(-19,20); glVertex2i(-20,21.5);   glVertex2i(-19.86,21.12); glVertex2i(-20,18.7);   glVertex2i(-18.9,19); glVertex2i(-20,17.9);   glVertex2i(-19.86,22.12);           glEnd(); 
	
	//contador de vidas
	Vida();
	
	//OBSTACULOS:
	glColor3f(plan1, plan1, plan1+0.2); 
    glBegin(GL_POLYGON);      //retangulo longo
		glVertex2f(15,-5);
		glVertex2f(15,-7);
		glVertex2f(5.0,-7);
		glVertex2f(5.0,-5);
	glEnd();
	
	glBegin(GL_POLYGON);   //mais a direita  altura igual
		glVertex2f(30,5);
		glVertex2f(30,0);
		glVertex2f(20,0);
		glVertex2f(20,5);
	glEnd();
	
	glBegin(GL_POLYGON);    // mais a esquerda longo
		glVertex2f(25,-10);
		glVertex2f(25,-5);
		glVertex2f(20,-5);
		glVertex2f(20,-10);
	glEnd();
	
	glColor3f(plan1, plan1, plan1+0.2);
	glLineWidth(6);
	glBegin(GL_LINE_LOOP);
		glVertex2f(-win,5);
		glVertex2f(15,5);
	glEnd();
	
	glLineWidth(6);
	glBegin(GL_LINE_LOOP);    //linha top 1
		glVertex2f(-15,14);
		glVertex2f(-15,25);
	glEnd();
	
	glLineWidth(6);
	glBegin(GL_LINE_LOOP);    //linha top 1
		glVertex2f(win,14);
		glVertex2f(-15,14);
	glEnd();
	
	glLineWidth(6);
	glBegin(GL_LINE_LOOP);
		glVertex2f(win,-14);
		glVertex2f(-15,-14);
	glEnd();
	
	glBegin(GL_POLYGON);
		glVertex2f(1.0,4.6);
		glVertex2f(1.0,-0.8);
		glVertex2f(-1.0,-0.8);
		glVertex2f(-1.0,4.6);
	glEnd();
	
	glColor3f(1,0.0,0.0);
	glPointSize(2);
	glBegin(GL_POINTS);
		glVertex2i(0,0);              
	glEnd();
	
	                           
	// Desenha um objeto modelado com transformações hierárquicas                
	glTranslatef(tx,0.0f,0.0f); // poe no meio
    glTranslatef(0.0f, ty, 0.0f); // meio em y
	glPushMatrix();
	
	glScalef(0.5f,2.0f,1.0f);
	glColor3f(plan1+0.25,0.8,plan1+0.09f);       //azul escuro
	DesenhaBase();                      //corpo da ave
	glColor3f(1.0f, 0.5f, 0.0f);          //cor fogo
    drawCircleFill(0.6, -0.3, 0.4, -180); //bico
	glScalef(1.4f,1.4f,1.0f);
    
	glColor3f(0.0f,0.0f,0.0f); glPointSize(4); glBegin(GL_POINTS);
		glVertex2i(0,0);    //olhos
		glVertex2i(1.99,0);          
	glEnd();    
	
	Colisoes();             
	// Executa os comandos OpenGL 
	glFlush();
}

// Função callback chamada quando o tamanho da janela é alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	GLsizei largura, altura;
                   
	// Evita a divisao por zero
	if(h == 0) h = 1;

	// Atualiza as variáveis
	largura = w;
	altura = h;
                                              
	// Especifica as dimensões da Viewport
	glViewport(0, 0, largura, altura);

	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Estabelece a janela de seleção (esquerda, direita, inferior, 
	// superior) mantendo a proporção com a janela de visualização
	if (largura <= altura) 
	{ 
		gluOrtho2D (-25.0f, 25.0f, -25.0f*altura/largura, 25.0f*altura/largura);
		win = 25.0f;
	}              
	else 
	{ 
		gluOrtho2D (-25.0f*largura/altura, 25.0f*largura/altura, -25.0f, 25.0f);
		win = 25.0f*largura/altura;           
	}             
}

// Função callback chamada para gerenciar eventos de teclas especiais(F1,PgDn,...)
void TeclasEspeciais(int key, int x, int y)
{
	// Move  horizontalmente
	if(key == GLUT_KEY_LEFT)
	{
		tx-=0.5;
		//printf("\n(x,y) = %f  , %f", tx, ty);
		if ( tx < -win )
			tx = -win; 
	}
	if(key == GLUT_KEY_RIGHT)
	{
		tx+=0.5;
		if ( tx > win )
			tx = win; 
	}     

	// Move  verticalmente
	if(key == GLUT_KEY_UP)
	{
		ty+=0.5;
		if ( ty < -win )
			ty = -win; 
		if (ty > 26)
			ty = -17;
	}
	if(key == GLUT_KEY_DOWN)
	{
		ty-=0.5;
		if (ty > -26 && ty < -20)
			ty = -17;		 
	} 
	           
                                                
	glutPostRedisplay();
}

// Função callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
}

// Função callback chamada para gerenciar eventos do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
	
    if (button == GLUT_LEFT_BUTTON){
    
		switch (cor) {
            case 0: glClearColor(1.0f, 0.0f,0.0f, 0.5f); cor++; plan1= 0.1;
        				break;
            case 1:// muda a cor corrente para vermelho
                     glClearColor(1.0f, 0.0f,0.3f, 0.5f); cor++;plan1= 0.2;
        				break;
            case 2: glClearColor(1.0f, 0.3f,0.3f, 0.5f); cor++;plan1 = 0.3;
        				break;
            case 3:// muda a cor corrente para verde
                     glClearColor(1.0f, 0.3f,0.6f, 0.5f); cor++;plan1 = 0.4;
        				break;
            case 4: glClearColor(1.0f, 0.6f,0.6f, 0.5f); cor++;plan1 = 0.5;
        				break;
            case 5:// muda a cor corrente para azul
                     glClearColor(1.0f, 0.6f,0.9f, 0.5f); cor=0; plan1 = 0.0;
        				break;
    }
       
     }
    glutPostRedisplay();
}
          
// Função responsável por inicializar parâmetros e variáveis
void Inicializa (void)
{   
	// Define a cor de fundo da janela de visualização como marrom
	glClearColor(rf, gf,bf, 1.0f);
    
	// Exibe mensagem que avisa como interagir
	printf("Projeto Computacao Grafica - Averinto:");
	printf("\n-----------------------------------------------------------------");
	printf("\nCOMANDOS:");
	printf("\n\n* Clique com o botão esquerdo do mouse para trocar as cores ");
	printf("\n  *Setas para cima, baixo , direita e esquerda, movem o personagem ");
	printf("\n-----------------------------------------------------------------");
	printf("\n\nAperte esc para sair do jogo");    
}

// Programa Principal 
int main(void)
{
	system("color A");
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  
	glutInitWindowPosition(3,5);  //Define a posição inicial na tela, do canto superior esquerdo a janela   
	glutInitWindowSize(700,600);  //Define o tamanho inicial da janela GLUT que será criada
	glutCreateWindow("Gabriel Dias - Averinto"); 
    glutMouseFunc(GerenciaMouse);
	// Registra a função callback de redesenho da janela de visualização
	glutDisplayFunc(Desenha);  
	
	// Registra a função callback de redimensionamento da janela de visualização
	glutReshapeFunc(AlteraTamanhoJanela);    

	// Registra a função callback para tratamento das teclas especiais
	glutSpecialFunc(TeclasEspeciais);

	// Registra a função callback para tratamento das teclas ASCII
	glutKeyboardFunc (Teclado);

	// Chama a função responsável por fazer as inicializações 
	Inicializa(); 
    
	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop();
	
	return 0;
}
