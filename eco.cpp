/* Ecosystem class (cellular automaton) source code
*
* Author : Suharsh Sivakumar
* Date of creation : January 27, 2012
*
*/
 
#include "eco.h"
 
// Helper functions in private section
void Eco::init_current() // initializes current
{
	current = new species[cells];
}
	
void Eco::init_next()
{
	next = new species[cells]; // initializes next
}

void Eco::initial()
{
	if (generation < 1) 
	{
		srand(time(NULL));
		for (int i = 0; i < cells; i++)
		{
			int v = rand() % 100;
			if (v < 20)
				current[i] = predator;
			else if (20 <= v && v <= 45)
				current[i] = prey;
			else if (45 < v && v < 75)
				current[i] = plant;
			else
				current[i] = empty;
		}
		printf("Generation 0\n");
	}
}

void Eco::count(int curcell)
{
	//Define variables
	int rightcell, leftcell, bottomcell, topcell, toprightcell, topleftcell, bottomrightcell, bottomleftcell;
	
	//First count will identify the neighbors
	//The first part of this step is to account for the edge cases where the window will wrap around.
    if (curcell+1 == cells)
		rightcell = 0;
    else
		rightcell = (curcell+1);
    if (curcell-1 < 0)
		leftcell = (cells-1);
    else
		leftcell = (curcell-1);
    if (curcell + side >= cells)
		bottomcell = (curcell-cells+side);
    else
		bottomcell = (curcell + side);
    if (curcell - side < 0)
		topcell = (cells - side +curcell);
    else
		topcell = (curcell - side);
    if (curcell+side+1 >= cells)
		bottomrightcell = (curcell-cells+side+1);
    else
		bottomrightcell = (curcell + side +1);
    if (curcell - side + 1 < 0)
		toprightcell = (cells - side + curcell + 1);
    else
		toprightcell = (curcell - side +1);
    if (curcell+side-1 >= cells)
		bottomleftcell = (curcell-cells+side-1);
    else
		bottomleftcell = (curcell + side -1);
    if (curcell - side - 1 < 0)
		topleftcell = (cells - side + curcell - 1);
    else
		topleftcell = (curcell - side -1);
      //calculate prey, pred, and plant count
    int predcount = 0;
    int preycount = 0;
    int plantcount = 0;
    switch (current[rightcell]) // Count the right cell
	{
	case predator : predcount++;
					break;
    case prey : preycount++;
					break;
    case plant : plantcount++;
					break;
	default : break;
	}
    switch (current[leftcell])  // Count the left cell
	{
	case predator : predcount++;
					break;
    case prey : preycount++;
					break;
    case plant : plantcount++;
					break;
	default : break;
	}
    switch (current[topcell])  // Count the top cell
	{
	case predator : predcount++;
					break;
    case prey : preycount++;
					break;
    case plant : plantcount++;
					break;
	default : break;
	}
    switch (current[bottomcell])  // Count the bottom cell
	{
	case predator : predcount++;
					break;
    case prey : preycount++;
					break;
    case plant : plantcount++;
					break;
	default : break;
	}
    switch (current[bottomrightcell]) // Count the bottom right cell
	{
	case predator : predcount++;
					break;
    case prey : preycount++;
					break;
    case plant : plantcount++;
					break;
	default : break;
	}
    switch (current[bottomleftcell]) // Count the bottom left cell
	{
	case predator : predcount++;
					break;
    case prey : preycount++;
					break;
    case plant : plantcount++;
					break;
	default : break;
	}
    switch (current[topleftcell]) // Count the top left cell
	{
	case predator : predcount++;
					break;
    case prey : preycount++;
					break;
    case plant : plantcount++;
					break;
	default : break;
	}
    switch (current[toprightcell]) // Count the top right cell
	{
	case predator : predcount++;
					break;
    case prey : preycount++;
					break;
    case plant : plantcount++;
					break;
	default : break;
	}
	counts[0] = predcount;
	counts[1] = preycount;
	counts[2] = plantcount;
}
    



// Member functions in public section
// Constructor
Eco::Eco(int input)
{
	generation = 0;
	side_pix = 750;
	side = input;
	counts = new int[3];
	cells = side*side;
	init_current();
	init_next();
}

Eco::Eco()
{
	generation = 0;
	side_pix = 750;
	side = 100;
	counts = new int[3];
	cells = side*side;
	init_current();
	init_next();
}

// the display() function displays each individual generation
void Eco::display()
{
	generation++;
	printf("generation %i\n", generation);
	glClear(GL_COLOR_BUFFER_BIT);
	if ((side_pix/side -1 )> 1)
		glPointSize(side_pix / side);
	else
		glPointSize(1);
	glBegin(GL_POINTS);
	for (int i = 0; i < cells; i++)
	{
		switch (current[i])
		{
			case predator : glColor3f(1.0, 0.0, 0.0);
							break;
			case prey : glColor3f(0.0, 0.0 ,1.0);
							break;
			case plant : glColor3f(0.0, 1.0, 0.0);
							break;
			default : glColor3f(0.0, 0.0, 0.0);
		}
		int rowindex = i/side;
		int colindex = i - rowindex*side;
		glVertex2f(colindex + 0.5, rowindex + 0.5);
	}
	glEnd();
	glFlush();
}


// This function is the program where the actual generations are determined.
void Eco::generations()
{
	// The automaton rules
	for (int i = 0; i < cells; i++)
	{
		count(i);
		switch (current[i])
		{
			case predator : if (counts[1] > 0) next[i] = predator;
							else next[i] = empty;
							break;
			case prey : if ((3 > counts[0]) && (counts[0] > 0)) next[i] = empty;
						else if (counts[0] > 2) next[i] = predator;
						else if (counts[2] > 0) next[i] = prey;
						else next[i] = empty;
						break;
			case plant : if ((2 > counts[1]) && (counts[1] > 0)) next[i] = empty;
						else if (counts[1] > 1) next[i] = prey;
						else next[i] = plant;
						break;
			default : if ((counts[1] > counts[0]) && (counts[1] > counts[2] -1) && (counts[2] > 0))
							next[i] = prey;
					else if ((counts[0] > counts[1] - 1) && (counts[0] > counts[2] - 1) && (counts[1]>0))
						next[i] = predator;
					else if ((counts[2] > counts[1]) && (counts[2] > counts[0]))
						next[i] = plant;
					else next[i] = empty;
		}
	}
	for (int j = 0; j < cells; j++)
	{
		//printf("blah\n%i", j);
		current[j] = next[j];
	}
}

// This function returns the side
int Eco::getside(void)
{
	return side;
}












