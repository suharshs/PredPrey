/* Ecosystem class (cellular automaton) header file
 *
 * Author : Suharsh Sivakumar
 * Date of creation : January 27, 2012
 *
 */

#ifndef _ECO_H_
#define _ECO_H_
 
 
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

using namespace std;

class Eco {
	private:
		int side_pix; // the number of pixels on each side of the window
		int side; // the number of columns on each side of the window
		int cells; // the total number of cells in the window
		int generation;
		enum species {empty = 0, plant = 1, prey = 2, predator = 3}; //how we differentiate from each square
		species * current; // pointer to the array of cells for the current generation
		species * next; // pointer to the array of cells for the next generation
		void init_current(); // initializes the current[] array using heap memory
		void init_next(); // initializes the next[] array using heap memory
		int * counts; // Stored as [Predator, prey, plants]
		void count(int curcell); // counts the number of the inputted species in the neighborhood of each cell
		
		
	public:
		Eco();
		Eco(int input);
		int getside(void);
		void display(); // displays each generation for OpenGL
		void generations(); //computes the next generation into next[] and transfers them into current[] 
		void initial(); // puts a random number of pred, prey, plants, and empty on the gridto start the system
};		

#endif