#include "GUI.h"
#include"Graph.h"
#include "Node.h"
#include "Edge.h"
#include "Connection.h"
#include <iostream>

extern double globalfaktor = 2; 


// Funktion to make tow way Edge.
void makeReversedConnection(Graph *ptrG, Node& rSrc, Node& rDes, double distance, double geschwendigkeit)
{
	ptrG->addEdge(new Connection(rSrc, rDes, distance, geschwendigkeit));
	ptrG->addEdge(new Connection(rDes, rSrc, distance, geschwendigkeit));
}
using namespace std; 

int main()

{
	GUI gui; 
	// Orte Bauen

	Node& rLudwigsfelde = gui.addNode(new Node("Ludwigsfelde"));
	Node& rTrebbin = gui.addNode(new Node("Trebbin"));
	Node& rZossen = gui.addNode(new Node("Zossen"));
	Node& rMittenwalde = gui.addNode(new Node("Mittenwalde"));
	Node& rLuckenwalde = gui.addNode(new Node("Luckenwalde"));
	Node& rTeupitz = gui.addNode(new Node("Teupitz"));

	makeReversedConnection(&gui, rLudwigsfelde, rTrebbin, 12, 65);
	makeReversedConnection(&gui, rTrebbin, rZossen, 40, 80);
	makeReversedConnection(&gui, rZossen, rMittenwalde, 10, 60);
	makeReversedConnection(&gui, rTrebbin, rLuckenwalde, 18, 85);
	makeReversedConnection(&gui, rLuckenwalde, rTeupitz, 45, 90);
	makeReversedConnection(&gui, rTeupitz, rZossen, 20, 80);





	bool bRunning = true; 

	while (bRunning)
	{
		int menuEntry = gui.showMenu(); 

		switch (menuEntry)
		{
		case 1:
			gui.arbeitswegZeigen();
			break; 
			
		case 2: 
			gui.naechsterKunde(); 
			break; 
		case 3: 
			gui.markiereBaustellen(); 
			break; 
		case 4: 
			gui.arbeitstagBeenden(); 
			break;

		case 5:
			bRunning = false;
			break;

		default:
			break;
		}

	}
	system("pause"); 
	return 0; 

}