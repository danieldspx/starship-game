/*********************************************************************
// Canvas para desenho, criada sobre a API OpenGL. Nao eh necessario conhecimentos de OpenGL para usar.
//  Autor: Cesar Tadeu Pozzer
//         05/2020
//
//  Pode ser utilizada para fazer desenhos, animacoes, e jogos simples.
//  Tem tratamento de mouse e teclado
//  Estude o OpenGL antes de tentar compreender o arquivo gl_canvas.cpp
//
//  Versao 2.0
//
//  Instru��es:
//	  Para alterar a animacao, digite numeros entre 1 e 3
// *********************************************************************/

#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <thread>

#include "gl_canvas2d.h"
#include "base/vectors/Vector2D.h"
#include "SceneManager.h"

#define FPS 60

float worldWidth = 500, worldHeight = 5000;
int screenWidth = 500, screenHeight = 500; //largura e altura inicial da tela . Alteram com o redimensionamento de tela.
int mouseX, mouseY; //variaveis globais do mouse para poder exibir dentro da render().
SceneManager* sceneManager = new SceneManager(worldWidth, worldHeight, screenWidth, screenHeight);
auto previousTime = std::chrono::high_resolution_clock::now();

//funcao chamada continuamente. Deve-se controlar o que desenhar por meio de variaveis globais
//Todos os comandos para desenho na canvas devem ser chamados dentro da render().
//Deve-se manter essa fun��o com poucas linhas de codigo.
void render()
{
    auto now = std::chrono::high_resolution_clock::now();

    auto elapsed = std::chrono::duration<float>(now - previousTime).count();
    previousTime = now;
    sceneManager->render(screenWidth, screenHeight, elapsed);
}

//funcao chamada toda vez que uma tecla for pressionada.
void keyboard(int key)
{
//    printf("\nKey Down: %d\n", key);
    sceneManager->keyboardDown(key);
}

//funcao chamada toda vez que uma tecla for liberada
void keyboardUp(int key)
{
//    printf("\nKey Up: %d\n", key);
    sceneManager->keyboardUp(key);
}

//funcao para tratamento de mouse: cliques, movimentos e arrastos
void mouse(int button, int state, int wheel, int direction, int x, int y)
{}

int main(void)
{
    CV::init(&screenWidth, &screenHeight, "Starship Game");
    CV::run();
}
