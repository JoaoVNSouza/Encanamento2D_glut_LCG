/*
 * Universidade Federal da Grande Dourados - UFGD.
 * Faculdade de Ci�ncias Exatas e Computa��o - FACET.
 * Curso Bacharelado em Engenharia de Computa��o.
 *
 * Disciplina: Laborat�rio de Computa��o Gr�fica - LCG.
 * Professor: Adailton Jos� Alves da Cruz.
 * Per�odo: semestre 2022.1 || ocorr�ncia no 2� semestre de 2022.]
 *
 * Programa: main.cpp
 * Desenvolvido por: Jo�o Vitor Nascimento de Souza.
 *
 * Objetivos: Desenhar um sistema de tubula��o com circuitos de canos
 * - Diversos formatos de canos.
 * - Anima��o de uma gota.
 * - Som representativo.
 * - Exibi��o em diversas telas.
 */

// Bibliotecas utilizadas.
#include <GL/gl.h>
#include <GL/glut.h>
#include <windows.h>
#include <math.h>
#include <time.h>
#include <MMsystem.h>
#include "cabecalho.h"
#include <stdio.h>

/*
 * Fun��o principal: respons�vel pela execu��o do programa do in�cio ao fim.
 * Entrada: argumentos passados pelos prompt de comando.
 * Sa�da:
 * - EXIT_SUCESS: finalizado corretamente.
 * - Outros valors: ocorr�ncia de erros na execu��o.
 */
int main(int argc, char *argv[])
{

    inicializa();                                // Inicializa vari�veis globais.
    glutInit(&argc, argv);                       // Inicicializa com os argumentos passados no prompt de comando.
    glutInitWindowSize(width, height);           // Define o tamanho da janela em pixels.
    glutInitWindowPosition(400, 10);             // Define a posi��o do canto superior esquerda da janela.
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // Descreve as configura��es da janela (cores suportadas e suas caracter�sticas).
    glutCreateWindow("Encanamento");             // Cria a janela e inseri um t�tulo.

    PlaySound(TEXT("pingo.wav"), NULL, SND_ASYNC);

    glClearColor(0.1, 0.1, 0.1, 1); // Seleciona a cor de fundo para limpeza da tela (R, G, B, A).

    /*
     * Rotinas callback:
     *  Se ocorrer um evento de sistema devido a intera��o com a janela criada
     *  aciona uma dessas rotinas, executando suas fun��es internas.
     */

    glutDisplayFunc(display);     // Executa o procedimento display.
    glutReshapeFunc(resize);      // Executa o procedimento resize.
    glutKeyboardFunc(key);        // Executa o procedimento key.
    glutTimerFunc(fps, timer, 0); // Executa o procedimento timer a cada per�odo de tempo t em (ms).

    glutMainLoop(); // Mant�m o programa executando em loop, aguardando a ocorr�ncia de novos eventos com a janela.

    return EXIT_SUCCESS;
}

/* Rotinas callback. */

/*
 * Fun��o respons�vel por adaptar a janela de visualiza��o (Viewport) e os elementos contidos na janela (Proje��o),
 * caso ocorra um evento de redimensionamento de janela.
 * Entrada:
 *  - w: nova largura.
 *  - h: nova altura.
 */
static void resize(int w, int h)
{
    width = w;
    height = h;

    glViewport(0, 0, width, height); // Porta de visualiza��o, onde ser� feitos os desenhos dos elementos.
    glMatrixMode(GL_PROJECTION);     // Inicializa os valores de visualiza��o.
    glLoadIdentity();                // Faz com que a matriz corrente seja inicializada com a matriz identidade.

    // Se altura for igual a 0, altera passa a ser 1.
    if (height == 0)
        height = 1;

    // Define o limites para as coordenadas da janela (RANGE em 2D).
    if (width <= height)
        gluOrtho2D(-win, win, -win * height / width, win * height / width);
    else
        gluOrtho2D(-win * width / height, win * width / height, -win, win);
}

/*
 * Procedimento respons�vel por executar instru��es caso ocorra o pressionamento de teclas na janela exibida.
 * Entrada: uma tecla digitada.
 * - "ESC": fecha o programa.
 * Sa�da: Executa uma instru��o.
 */
static void key(unsigned char letra, int x, int y)
{
    switch (letra)
    {
    case 27: // Fecha a janela.
        exit(0);
        break;
    default:
        break;
    }

    glutPostRedisplay(); // Atualiza o display a cada evento do teclado.
}

/*
 * Procedimento respons�vel por atualizar o display da janela.
 *  -> Mostra todos os desenhos.
 */
static void display()
{
    switch (cena)
    {
    case 1: // Exibi a tela 1.
        tela1();
        break;
    case 2: // Exibi a tela 2.
        tela2();
        break;
    case 3: // Exibi a tela 3.
        tela3();
        break;
    case 4: // Exibi a tela 4.
        tela4();
        break;
    default:
        break;
    }
}

/*
 * Procedimento que realiza as anima��es.
 */
static void timer(int valor)
{
    glutPostRedisplay();          // Redesenha os objetos com as novas coordenadas.
    glutTimerFunc(fps, timer, 0); // Isso garante que seja executa inumeras vezes, mais de uma.

    switch (cena)
    {
    case 1:
        animation1();
        break;
    case 2:
        animation2();
        break;
    case 3:
        animation3();
        break;
    default:
        break;
    }
}

/* Telas utilizadas. */

void tela1()
{
    glClear(GL_COLOR_BUFFER_BIT); // Limpa o buffer de cores atual da janela.

    glMatrixMode(GL_MODELVIEW); // Matriz corrente, contendo todas as transforma��es geom�tricas em um determinado momento.
    glLoadIdentity();           // Faz com que a matriz corrente seja inicializada com a matriz identidade.

    glLineWidth(4);     // Tamanho das bordas dos canos.
    glColor3f(1, 1, 0); // Cor dos canos Amarelo.

    /* Desenhar o circuito. */

    // Transforma��o 0.
    glTranslatef(x_InitPosition, y_InitPosition, 0);
    tam = 30; // Para padronizar o desenho, vai fazer todos os canos com tamanho relacionado a esse.
    canoReto(tam);

    // Transforma��o 1.
    glTranslatef(tam, 0, 0);
    canoJoelho(360);

    // Transforma��o 2 e 3.
    glTranslatef((diametro / 2) + diametro, (diametro / 2) + diametro, 0);
    glRotatef(90, 0, 0, 1); // Rotaciona 90� no sentido anti-hor�rio.
    canoReto(tam * 3);

    // Transforma��o 4.
    glTranslatef(tam * 3, 0, 0);
    canoJoelho(90);

    //  Transforma��o 5 e 6.
    glRotatef(-90, 0, 0, 1); // Rotaciona 90� no sentido hor�rio.
    glTranslatef((diametro / 2) + diametro, (diametro / 2) + diametro, 0);
    canoReto(tam / 2);

    // Transforma��o 7.
    glTranslatef(tam / 2, 0, 0);
    tamCruzeta = tam * 2;
    canoCruzeta(tamCruzeta);

    // Transforma��o 8.
    glTranslatef(tamCruzeta / 2, 0, 0);
    glPushMatrix(); // Salva a matriz corrente.

    // Transforma��o 9 e 10.
    glTranslatef(0, tamCruzeta / 2, 0);
    glRotatef(90, 0, 0, 1);
    canoJoelho(90);

    // Transforma��o 11 e 12.
    glRotatef(-90, 0, 0, 1);
    glTranslatef((diametro / 2) + diametro, (diametro / 2) + diametro, 0);
    canoReto(tam);

    // Transforma��o 13.
    glTranslatef(tam, 0, 0);
    canoJoelho(90);

    glPopMatrix(); // Baixa a matriz corrente da mem�ria.

    glPushMatrix(); // Salva a matriz corrente.

    // Transforma��o 14.
    glTranslatef(tamCruzeta / 2, 0, 0);
    canoReto(tam);

    // Transforma��o 15.
    glTranslatef(tam, 0, 0);
    canoCruzeta(tamCruzeta);

    glPopMatrix(); // Baixa a matriz corrente da mem�ria.

    glPushMatrix(); // Salva a matriz corrente.

    // Transforma��o 16 e 17.
    glTranslatef(0, -tamCruzeta / 2, 0);
    glRotatef(-90, 0, 0, 1);
    canoJoelho(360);

    // Transforma��o 18 e 19.
    glRotatef(90, 0, 0, 1);
    glTranslatef((diametro + diametro / 2), -(diametro + diametro / 2), 0);
    canoReto(tam);

    // Transforma��o 20.
    glTranslatef(tam, 0, 0);
    canoJoelho(360);

    glPopMatrix(); // Baixa a matriz corrente da mem�ria.

    // Transforma��o 21.
    glTranslatef(((tamCruzeta / 2) * 3) + tam, 0, 0);
    canoReto(tam * 3);

    /* Anima��o. */

    glLoadIdentity();
    glTranslatef(x_InitPosition, y_InitPosition, 0); // Translada para a posi��o inicial do circuito.
    glTranslatef(x_position, y_position, 0);         // Vai transladar a gota por todo o circuito.
    gota();                                          // Desenha a gota circular.

    glutSwapBuffers(); // Necess�rio para anima��o para fazer a troca entre buffers e continua executando fun��es que n�o foram executadas.
}

void tela2()
{
    glClear(GL_COLOR_BUFFER_BIT); // Limpa o buffer de cores atual da janela.

    glMatrixMode(GL_MODELVIEW); // Matriz corrente, contendo todas as transforma��es geom�tricas em um determinado momento.
    glLoadIdentity();           // Faz com que a matriz corrente seja inicializada com a matriz identidade.

    glLineWidth(4);     // Tamanho das bordas dos canos.
    glColor3f(0, 1, 1); // Cor dos canos Azul claro.

    /* Desenhar o circuito. */

    // Transforma��o 0.
    x_InitPosition = -win;
    y_InitPosition = 0;
    glTranslatef(x_InitPosition, y_InitPosition, 0);
    tam = 30; // Para padronizar o desenho, vai fazer todos os canos com tamanho relacionado a esse.
    canoReto(tam);

    // Transforma��o 1.
    glTranslatef(tam, 0, 0);
    canoJoelho(90);

    // Transforma��o 2 e 3.
    glTranslatef((diametro + diametro / 2), -(diametro + diametro / 2), 0);
    glRotatef(-90, 0, 0, 1);
    canoJoelho(360);

    // Transforma��o 4 e 5.
    glRotatef(90, 0, 0, 1);
    glTranslatef((diametro + diametro / 2), -(diametro + diametro / 2), 0);
    canoReto(tam * 3);

    // Transforma��o 6.
    glTranslatef(tam * 3, 0, 0);
    canoJoelho(360);

    // Transforma��o 7 e 8.
    glTranslatef((diametro + diametro / 2), (diametro + diametro / 2), 0);
    glRotatef(90, 0, 0, 1);
    canoReto(tam * 2);

    // Transforma��o 9.
    glTranslatef(tam * 2, 0, 0);
    tamCruzeta = tam * 2;
    canoCruzeta(tamCruzeta);

    // Transforma��o 10.
    glTranslatef((tamCruzeta / 2), 0, 0);
    glPushMatrix(); // Salva a matriz corrente no meio da Cruzeta.

    // Transforma��o 11 e 12.
    glRotatef(-90, 0, 0, 1);
    glTranslatef(-(diametro + diametro / 2), 0, 0);
    canoJoelho(270);

    // Transforma��o 13 e 14.
    glTranslatef(-(diametro + diametro / 2), (diametro + diametro / 2), 0);
    glRotatef(90, 0, 0, 1);
    canoJoelho(90);

    // Transforma��o 15 e 16.
    glRotatef(-90, 0, 0, 1);
    glTranslatef((diametro + diametro / 2), (diametro + diametro / 2), 0);
    canoJoelho(90);

    glPopMatrix(); // Baixa a matriz corrente da mem�ria.

    // Transforma��o 17 e 18.
    glRotatef(-90, 0, 0, 1);
    glTranslatef((tamCruzeta / 2), 0, 0);
    canoReto(tam * 2);

    /* Anima��o. */
    glLoadIdentity();
    glTranslatef(x_InitPosition, y_InitPosition, 0); // Translada para a posi��o inicial do circuito.
    glTranslatef(x_position, y_position, 0);         // Vai transladar a gota por todo o circuito.
    gota();                                          // Desenha a gota circular.

    glutSwapBuffers(); // Necess�rio para anima��o para fazer a troca entre buffers e continua executando fun��es que n�o foram executadas.
}

void tela3()
{
    glClear(GL_COLOR_BUFFER_BIT); // Limpa o buffer de cores atual da janela.

    glMatrixMode(GL_MODELVIEW); // Matriz corrente, contendo todas as transforma��es geom�tricas em um determinado momento.
    glLoadIdentity();           // Faz com que a matriz corrente seja inicializada com a matriz identidade.

    glLineWidth(4);     // Tamanho das bordas dos canos.
    glColor3f(0, 1, 0); // Cor dos canos Verde.

    /* Desenhar o circuito. */

    // Transforma��o 0.
    x_InitPosition = -win;
    y_InitPosition = 0;
    glTranslatef(x_InitPosition, y_InitPosition, 0);
    tam = 30;
    canoReto(tam);

    // Transforma��o 1.
    glTranslatef(tam, 0, 0);
    canoJoelho(360);

    // Transforma��o 2 e 3.
    glTranslatef((diametro + diametro / 2), (diametro + diametro / 2), 0);
    glRotatef(90, 0, 0, 1);
    canoReto(tam * 3);

    // Transforma��o 4.
    glTranslatef((tam * 3), 0, 0);
    canoJoelho(90);

    // Transforma��o 5 e 6.
    glRotatef(-90, 0, 0, 1);
    glTranslatef((diametro + diametro / 2), (diametro + diametro / 2), 0);
    canoJoelho(90);

    // Transforma��o 7 e 8.
    glTranslatef((diametro + diametro / 2), -(diametro + diametro / 2), 0);
    glRotatef(-90, 0, 0, 1);
    canoReto(tam * 3);

    // Transforma��o 9.
    glTranslatef((tam * 3), 0, 0);
    canoJoelho(360);

    // Transforma��o 10 e 11.
    glRotatef(90, 0, 0, 1);
    glTranslatef((diametro + diametro / 2), -(diametro + diametro / 2), 0);
    canoJoelho(360);

    // Transforma��o 12 e 13.
    glTranslatef((diametro + diametro / 2), (diametro + diametro / 2), 0);
    glRotatef(90, 0, 0, 1);
    canoReto(tam * 3);

    // Transforma��o 14.
    glTranslatef((tam * 3), 0, 0);
    canoJoelho(90);

    // Transforma��o 15 e 16.
    glRotatef(-90, 0, 0, 1);
    glTranslatef((diametro + diametro / 2), (diametro + diametro / 2), 0);
    canoJoelho(90);

    // Transforma�a� 17 e 18.
    glTranslatef((diametro + diametro / 2), -(diametro + diametro / 2), 0);
    glRotatef(-90, 0, 0, 1);
    canoReto(tam * 3);

    // Transforma��o 19.
    glTranslatef((tam * 3), 0, 0);
    canoJoelho(360);

    // Transforma��o 20 e 21.
    glRotatef(90, 0, 0, 1);
    glTranslatef((diametro + diametro / 2), -(diametro + diametro / 2), 0);
    canoReto(tam);

    /* Anima��o. */

    glLoadIdentity();
    glTranslatef(x_InitPosition, y_InitPosition, 0); // Translada para a posi��o inicial do circuito.
    glTranslatef(x_position, y_position, 0);         // Vai transladar a gota por todo o circuito.
    gota();                                          // Desenha a gota circular.

    glutSwapBuffers(); // Necess�rio para anima��o para fazer a troca entre buffers e continua executando fun��es que n�o foram executadas.
}

void tela4()
{
    glClear(GL_COLOR_BUFFER_BIT); // Limpa o buffer de cores atual da janela.

    glMatrixMode(GL_MODELVIEW); // Matriz corrente, contendo todas as transforma��es geom�tricas em um determinado momento.
    glLoadIdentity();           // Faz com que a matriz corrente seja inicializada com a matriz identidade.

    glColor3f(1, 1, 1); // Cor da msg VERDE.

    // Mostra mensagem de FINISH na tela.
    char texto[] = "FINISH - Pressione ESC";
    DesenhaTexto(texto);

    // Desliga o som.
    PlaySound(NULL, 0, 0);

    glutSwapBuffers();
}

/* Anima��es utilizadas. */

void animation1()
{
    switch (c)
    {
    case 0: // Move pelo setor 0.
        if (x_position < tam)
            x_position += 1;
        else
        {
            c++;
            x_position = max_x += tam;
            y_position = max_y += 0;
        }
        break;

    case 1: // Move pelo setor 1.
        if (x_position < max_x + (diametro + diametro / 2))
            rotaciona(270, 360);
        else
        {
            c++;
            aux++;
            x_position = max_x += (diametro + diametro / 2);
            y_position = max_y += (diametro + diametro / 2);
        }
        break;

    case 2: // Move pelo setor 2.
        if (y_position < max_y + (tam * 3))
            y_position += 1;
        else
        {
            c++;
            x_position = max_x += 0;
            y_position = max_y += (tam * 3);
        }
        break;

    case 3: // Move pelo setor 3.
        if (x_position < max_x + (diametro + diametro / 2))
            rotaciona(180, 90);
        else
        {
            c++;
            aux++;
            x_position = max_x += (diametro + diametro / 2);
            y_position = max_y += (diametro + diametro / 2);
        }

        break;

    case 4: // Move pelo setor 4.
        if (x_position < max_x + (tam / 2 + tamCruzeta / 2))
            x_position += 1;
        else
        {
            // Escolher qual dos 3 caminhos ir� seguir.
            srand(time(NULL));

            switch (rand() % 3)
            {
            case 0: // Para cima da cruzeta.
                c = 5;
                break;
            case 1: // Para direita da cruzeta.
                c = 11;
                break;
            case 2: // Para baixo da cruzeta.
                c = 12;
                break;
            }

            x_position = max_x += (tam / 2 + tamCruzeta / 2);
            y_position = max_y += 0;
        }
        break;

    case 5: // Move pelo setor 5.
        if (y_position < max_y + (tamCruzeta / 2))
            y_position += 1;
        else
        {
            c++;
            x_position = max_x += 0;
            y_position = max_y += (tamCruzeta / 2);
        }
        break;

    case 6: // Move pelo setor 6.
        if (x_position < max_x + (diametro + diametro / 2))

            rotaciona(180, 90);
        else
        {
            c++;
            aux++;
            x_position = max_x += (diametro + diametro / 2);
            y_position = max_y += (diametro + diametro / 2);
        }
        break;

    case 7: // Move pelo setor 7.
        if (x_position < max_x + tam)
            x_position += 1;
        else
        {
            c++;
            x_position = max_x += tam;
            y_position = max_y += 0;
        }
        break;

    case 8: // Move pelo setor 8.
        if (x_position < max_x + (diametro + diametro / 2))
            rotaciona(90, 0);
        else
        {
            c++;
            aux++;
            x_position = max_x += (diametro + diametro / 2);
            y_position = max_y -= (diametro + diametro / 2);
        }
        break;

    case 9: // Move pelo setor 9.
        if (y_position > max_y - (tamCruzeta / 2))
            y_position -= 1;
        else
        {
            c++;
            x_position = max_x += 0;
            y_position = max_y -= (tamCruzeta / 2);
        }
        break;

    case 10: // Move pelo setor 10.
        if (x_position < max_x + (tamCruzeta / 2) + (tam * 3))
            x_position += 1;
        else // Muda de cena.
            c = 100;
        break;

    case 11: // Move pelo setor 11.
        if (x_position < max_x + (tamCruzeta / 2) * 3 + (tam * 3))
            x_position += 1;
        else // Muda de cena.
            c = 100;
        break;

    case 12: // Move pelo setor 12.
        if (y_position > max_y - (tamCruzeta / 2))
            y_position -= 1;
        else
        {
            c++;
            x_position = max_x += 0;
            y_position = max_y -= (tamCruzeta / 2);
        }
        break;

    case 13: // Move pelo setor 13.
        if (x_position < max_x + (diametro + diametro / 2))
            rotaciona(180, 270);
        else
        {
            c++;
            aux++;
            x_position = max_x += (diametro + diametro / 2);
            y_position = max_y -= (diametro + diametro / 2);
        }
        break;

    case 14: // Move pelo setor 14.
        if (x_position < max_x + tam)
            x_position += 1;
        else
        {
            c++;
            x_position = max_x += tam;
            y_position = max_y += 0;
        }
        break;

    case 15: // Move pelo setor 15.
        if (x_position < max_x + (diametro + diametro / 2))
            rotaciona(270, 360);
        else
        {
            c++;
            aux++;
            x_position = max_x += (diametro + diametro / 2);
            y_position = max_y += (diametro + diametro / 2);
        }
        break;

    case 16: // Move pelo setor 16.
        if (y_position < max_y + tamCruzeta / 2)
            y_position += 1;
        else
        {
            c++;
            x_position = max_x += 0;
            y_position = max_y += (tamCruzeta / 2);
        }
        break;

    case 17: // Move pelo setor 17.
        if (x_position < max_x + (tamCruzeta / 2) + (tam * 3))
            x_position += 1;
        else // Muda de cena.
            c = 100;
        break;

    case 100: // Muda de cena.
        cena++;
        x_position = max_x = 0;
        y_position = max_y = 0;
        c = 0;
        break;
    }
}

void animation2()
{
    switch (c)
    {
    case 0: // Move pelo setor 0.
        if (x_position < tam)
            x_position += 1;
        else
        {
            c++;
            x_position = max_x += tam;
            y_position = max_y += 0;
        }
        break;

    case 1: // Move pelo setor 1.
        if (x_position < max_x + (diametro + diametro / 2))
            rotaciona(90, 0);
        else
        {
            c++;
            aux++;
            x_position = max_x += (diametro + diametro / 2);
            y_position = max_y -= (diametro + diametro / 2);
        }
        break;

    case 2: // Move pelo setor 2.
        if (x_position < max_x + (diametro + diametro / 2))
            rotaciona(180, 270);
        else
        {
            c++;
            aux++;
            x_position = max_x += (diametro + diametro / 2);
            y_position = max_y -= (diametro + diametro / 2);
        }
        break;

    case 3: // Move pelo setor 3.
        if (x_position < max_x + (tam * 3))
            x_position += 1;
        else
        {
            c++;
            x_position = max_x += (tam * 3);
            y_position = max_y += 0;
        }
        break;

    case 4: // Move pelo setor 4.
        if (x_position < max_x + (diametro + diametro / 2))
            rotaciona(270, 360);
        else
        {
            c++;
            aux++;
            x_position = max_x += (diametro + diametro / 2);
            y_position = max_y += (diametro + diametro / 2);
        }
        break;

    case 5: // Move pelo setor 5.
        if (y_position < max_y + (tam * 2) + (tamCruzeta / 2))
            y_position += 1;
        else
        {
            // Escolher qual dos 3 caminhos ir� seguir, ser� gerado um valor para isso.
            srand(time(NULL));
            switch (rand() % 2)
            {
            case 0: // Para cima da cruzeta.
                c = 6;
                break;
            case 1: // Para esquerda da cruzeta.
                c = 11;
                break;
            }

            x_position = max_x += 0;
            y_position = max_y += (tam * 2) + (tamCruzeta / 2);
        }
        break;

    case 6: // Move pelo setor 6.
        if (y_position < max_y + (tamCruzeta / 2))
            y_position += 1;
        else
        {
            c++;
            max_x += 0;
            max_y += (tamCruzeta / 2);
        }
        break;

    case 7: // Move pelo setor 7.
        if (x_position >= max_x - (diametro + diametro / 2))
            rotaciona(0, 90);
        else
        {
            c++;
            aux++;
            x_position = max_x -= (diametro + diametro / 2);
            y_position = max_y += (diametro + diametro / 2);
        }
        break;

    case 8: // Move pelo setor 8.
        if (y_position > max_y - (diametro + diametro / 2))
            rotaciona(90, 180);
        else
        {
            c++;
            aux++;
            x_position = max_x -= (diametro + diametro / 2);
            y_position = max_y -= (diametro + diametro / 2);
        }
        break;

    case 9: // Move pelo setor 9.
        if (x_position < max_x + (diametro + diametro / 2))
            rotaciona(180, 270);
        else
        {
            c++;
            aux++;
            x_position = max_x += (diametro + diametro / 2);
            y_position = max_y -= (diametro + diametro / 2);
        }
        break;

    case 10: // Move pelo setor 10.
        if (x_position < max_x + (tamCruzeta) + (tam * 2))
            x_position += 1;
        else // Muda de cena.
            c = 100;
        break;

    case 11: // Move pelo setor 11.
        if (x_position < max_x + (tamCruzeta / 2) + (tam * 2))
            x_position += 1;
        else // Muda de cena.
            c = 100;
        break;

    case 100: // Muda de cena
        cena++;
        x_position = max_x = 0;
        y_position = max_y = 0;
        c = 0;
        break;
    }
}

void animation3()
{
    switch (c)
    {
    case 0: // Move pelo setor 0.
        if (x_position < tam)
            x_position += 1;
        else
        {
            c++;
            x_position = max_x += tam;
            y_position = max_y += 0;
        }
        break;

    case 1: // Move pelo setor 1.
        if (x_position < max_x + (diametro + diametro / 2))
            rotaciona(270, 360);
        else
        {
            c++;
            aux++;
            x_position = max_x += (diametro + diametro / 2);
            y_position = max_y += (diametro + diametro / 2);
        }
        break;

    case 2: // Move pelo setor 2.
        if (y_position < max_y + (tam * 3))
            y_position += 1;
        else
        {
            c++;
            x_position = max_x += 0;
            y_position = max_y += (tam * 3);
        }
        break;

    case 3: // Move pelo setor 3.
        if (x_position < max_x + (diametro + diametro / 2))
            rotaciona(180, 90);
        else
        {
            c++;
            aux++;
            x_position = max_x += (diametro + diametro / 2);
            y_position = max_y += (diametro + diametro / 2);
        }
        break;

    case 4: // Move pelo setor 4.
        if (y_position > max_y - (diametro + diametro / 2))
            rotaciona(90, 0);
        else
        {
            c++;
            aux++;
            x_position = max_x += (diametro + diametro / 2);
            y_position = max_y -= (diametro + diametro / 2);
        }
        break;

    case 5: // Move pelo setor 5.
        if (y_position > max_y - (tam * 3))
            y_position -= 1;
        else
        {
            c++;
            x_position = max_x += 0;
            y_position = max_y -= (tam * 3);
        }
        break;

    case 6: // Move pelo setor 6.
        if (y_position > max_y - (diametro + diametro / 2))
            rotaciona(180, 270);
        else
        {
            c++;
            aux++;
            x_position = max_x += (diametro + diametro / 2);
            y_position = max_y -= (diametro + diametro / 2);
        }
        break;

    case 7: // Move pelo setor 7.
        if (x_position < max_x + (diametro + diametro / 2))
            rotaciona(270, 360);
        else
        {
            c++;
            aux++;
            x_position = max_x += (diametro + diametro / 2);
            y_position = max_y += (diametro + diametro / 2);
        }
        break;

    case 8: // Move pelo setor 8.
        if (y_position < max_y + (tam * 3))
            y_position += 1;
        else
        {
            c++;
            x_position = max_x += 0;
            y_position = max_y += (tam * 3);
        }
        break;

    case 9: // Move pelo setor 9.
        if (x_position < max_x + (diametro + diametro / 2))
            rotaciona(180, 90);
        else
        {
            c++;
            aux++;
            x_position = max_x += (diametro + diametro / 2);
            y_position = max_y += (diametro + diametro / 2);
        }
        break;

    case 10: // Move pelo setor 10.
        if (y_position > max_y - (diametro + diametro / 2))
            rotaciona(90, 0);
        else
        {
            c++;
            aux++;
            x_position = max_x += (diametro + diametro / 2);
            y_position = max_y -= (diametro + diametro / 2);
        }
        break;

    case 11: // Move pelo setor 11.
        if (y_position > max_y - (tam * 3))
            y_position -= 1;
        else
        {
            c++;
            x_position = max_x += 0;
            y_position = max_y -= (tam * 3);
        }
        break;

    case 12: // Move pelo setor 12.
        if (y_position > max_y - (diametro + diametro / 2))
            rotaciona(180, 270);
        else
        {
            c++;
            aux++;
            x_position = max_x += (diametro + diametro / 2);
            y_position = max_y -= (diametro + diametro / 2);
        }
        break;

    case 13: // Move pelo setor 13.
        if (x_position < max_x + (tam))
            x_position += 1;
        else // Muda cena.
            cena = 4;
        break;
    }
}

/* Primitivas. */

/*
 * Primitiva para desenhar cano no formato de cruzeta no eixo x.
 */
void canoCruzeta(int tamanho)
{
    GLfloat meioCruzeta = tamanho / 2;

    glBegin(GL_LINE_STRIP);
    glVertex2f(0, diametro / 2);
    glVertex2f(meioCruzeta - (diametro / 2), diametro / 2);
    glVertex2f(meioCruzeta - (diametro / 2), meioCruzeta);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2f(meioCruzeta + (diametro / 2), meioCruzeta);
    glVertex2f(meioCruzeta + (diametro / 2), diametro / 2);
    glVertex2f(tamanho, diametro / 2);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2f(0, -diametro / 2);
    glVertex2f(meioCruzeta - (diametro / 2), -diametro / 2);
    glVertex2f(meioCruzeta - (diametro / 2), -meioCruzeta);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2f(meioCruzeta + (diametro / 2), -meioCruzeta);
    glVertex2f(meioCruzeta + (diametro / 2), -diametro / 2);
    glVertex2f(tamanho, -diametro / 2);
    glEnd();
}

/*
 * Primitiva para desenhar retas paralelas no eixo x.
 */
void canoReto(int tamanho)
{
    glBegin(GL_LINES);
    // Reta superior.
    glVertex2f(0, diametro / 2);
    glVertex2f(tamanho, diametro / 2);
    // Reta inferior.
    glVertex2f(0, -diametro / 2);
    glVertex2f(tamanho, -diametro / 2);
    glEnd();
}

/*
 * Primitiva para desenhar a gota no centro do eixo de coordenadas.
 */
void gota()
{
    // Vari�veis.
    int i;
    angulo2 = 0;
    aumento2 = 360 / pts;

    glColor3f(0, 0.5, 1); // Cor Azul claro.

    // Desenha c�rculo com preenchimento.
    glBegin(GL_POLYGON);
    for (i = 0; i < pts; i++)
    {
        radiano2 = angulo2 * (PI / 180); // Convers�o de �ngulos para radianos.
        glVertex2f(diametro / 4 * cos(radiano2), diametro / 4 * sin(radiano2));
        angulo2 += aumento2;
    }
    glEnd();
}

/*
 * Primitiva para desenhar at� 4 formas do semicirculo de um cano, variando o Theta:
 * - 90�: desenha c�rculo de 0� at� 90�.
 * - 180�: desenha c�rculo de 90� at� 180�.
 * - 270�: desenha c�rculo de 180� at� 270�.
 * - 360�: desenha c�rculo de 270� at� 360�.
 */
void canoJoelho(int theta)
{
    // Vari�veis.
    int i;
    aumento2 = 91 / pts; // Vai aumentar at� 90�.

    glPushMatrix(); // Salva a matriz corrente.

    // Translada o canoJoelho para ser desenhado no centro do eixo.
    if (theta >= 270)
        glTranslatef(0, diametro + (diametro / 2), 0);
    else
        glTranslatef(0, -(diametro + (diametro / 2)), 0);

    // Semic�rculo interno.
    angulo2 = theta - 90;
    glBegin(GL_LINE_STRIP);
    for (i = 0; i < pts; i++)
    {
        radiano2 = angulo2 * (PI / 180); // Convers�o de �ngulos para radianos.
        glVertex2f(diametro * cos(radiano2), diametro * sin(radiano2));
        angulo2 += aumento2;
    }
    glEnd();

    // Semic�rculo externo.
    angulo2 = theta - 90;
    glBegin(GL_LINE_STRIP);
    for (i = 0; i < pts; i++)
    {
        radiano2 = angulo2 * (PI / 180); // Convers�o de �ngulos para radianos.
        glVertex2f(diametro * 2 * cos(radiano2), diametro * 2 * sin(radiano2));
        angulo2 += aumento2;
    }
    glEnd();

    glPopMatrix(); // Baixa a matriz armazenada na mem�ria.
}

/* Outras rotinas. */

/*
 * Desenha plano cartesiano.
 */
void planoCartesiano()
{

    // Desenha as linhas.
    glLineWidth(1); // Tamanho da linha padr�o.
    glBegin(GL_LINES);
    glColor3f(1, 1, 1); // Cor Branco.
    glVertex2f(-win, 0);
    glVertex2f(win, 0);
    glColor3f(1, 0, 0); // Cor Vermelho.
    glVertex2f(0, -win);
    glVertex2f(0, win);
    glEnd();

    // Desenha os pontos de m�x e min para cada eixo.
    glPointSize(8);
    glBegin(GL_POINTS);
    glColor3f(0, 1, 1);
    glVertex2f(-win, 0);
    glColor3f(0, 0, 1);
    glVertex2f(win, 0);
    glColor3f(1, 0, 0);
    glVertex2f(0, win);
    glColor3f(1, 0.5, 0);
    glVertex2f(0, -win);
    glEnd();
}

/*
 * Inicializa��o das vari�veis globais.
 */
void inicializa()
{
    width = 700;
    height = 800;
    diametro = 20;
    x_InitPosition = -win;
    y_InitPosition = -win + 20;
    x_position = 0;
    y_position = 0;
    max_x = 0;
    max_y = 0;
    c = 0;
    aux = 1;
    cena = 1;
    pts = 360;

    // SetConsoleTitle("Encanamento"); // Coloca um t�tulo na janela do prompt.
}

/*
 * Procedimento para rotacionar a gota pelas curvas.
 */
void rotaciona(int inicio, int fim)
{
    if (aux == 1)
    {
        angulo = inicio; // inicio� at� fim�.
        aumento = 90 / 25;
        aux = 0;

        switch (inicio)
        {
        case 0:
        case 360:
            x_atual = (diametro + diametro / 2);
            y_atual = 0;
            break;
        case 90:
            x_atual = 0;
            y_atual = (diametro + diametro / 2);
            break;
        case 180:
            x_atual = -(diametro + diametro / 2);
            y_atual = 0;
            break;
        case 270:
            x_atual = 0;
            y_atual = -(diametro + diametro / 2);
            break;
        default:
            break;
        }
    }

    radiano = angulo * (PI / 180); // Convers�o de �ngulos para radianos.

    // Calcula todos os pontos necess�rios e subtrai para ver qual deve ser o incremento.
    x_anterior = x_atual;
    x_atual = (diametro + diametro / 2) * cos(radiano);
    x_rotate = x_atual - x_anterior;

    y_anterior = y_atual;
    y_atual = (diametro + diametro / 2) * sin(radiano);
    y_rotate = y_atual - y_anterior;

    if (fim > inicio)
        angulo += aumento;
    else
        angulo -= aumento;

    x_position += x_rotate;
    y_position += y_rotate;
}

/*
 * Desenha um texto na janela GLUT
 */
void DesenhaTexto(char *string)
{
    glPushMatrix();

    // Posi��o no universo onde o texto ser� colocado
    glRasterPos2f(-40, 0);

    // Exibe caracter a caracter
    while (*string)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *string++);
    glPopMatrix();
}
