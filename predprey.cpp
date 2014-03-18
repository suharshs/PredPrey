/* Predator Prey cellular automaton
 * 
 * Author: Suharh Sivakumar
 * Date of creation : January 28, 2012
 * 
 */
 
#include "eco.h"
#include <iostream>


int cells_per_side = 100;
int delay = 1;

Eco ecosystem(cells_per_side);
 
void full(void) {
  ecosystem.initial();
  ecosystem.display();
  ecosystem.generations();
}

void Timer(int extra) {
  glutPostRedisplay();
  glutTimerFunc(delay,Timer,0);
}

void initFrustum(void) {
  glClearColor(0.0, 0.0, 0.0, 0.0);
  gluOrtho2D(0, ecosystem.getside(), 0, ecosystem.getside());
}

void speedUp(){
  if (delay > 10) {
    delay -= 10;
  }
}

void slowDown(){
  delay += 10;
}

void keyboard (unsigned char key, int x, int y) {
  // key variable has the key pressed
  switch (key) {
    case 27: exit(0); // exit program when [ESC] key presseed
             break;
    case 'f': speedUp();
             break;
    case 's': slowDown();
             std::cout << "oink";
             break;
    default: break;
  }
}

 
int main(int argc, char **argv)
{ 
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
  glutInitWindowSize(1000,1000);
  glutInitWindowPosition(5,5);
  glutCreateWindow("Predator, Prey, Plants Cellular Automaton");
  glutDisplayFunc(full);
  glutKeyboardFunc(keyboard);
  glutTimerFunc(0,Timer,0);
  initFrustum();
  glutMainLoop();
}
  