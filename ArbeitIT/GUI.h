#pragma once
#include "Graph.h"
#include <vector>
#include <iostream>

using namespace std; 

struct Info
	{
	Node* m_ZielOrt;
	std::string m_kundenName;
	double m_fahrKost;
	double m_einnahme;
	double gesamtDistance; 
	string aktuelle_position; // um die aktuelle position zu speichern
	};

class GUI: public Graph
{
	
public:

	// GUI Konstruktor 
	// Das Objekt wird mit dieser Sachen initialisiert

	GUI()
	{
		aktuelle_position = "Mittenwalde"; 
	}
	int showMenu(); 
	void arbeitswegZeigen(); 
	void naechsterKunde();
	void markiereBaustellen(); 
	void arbeitstagBeenden();
	void set_position(string position) { aktuelle_position = position;  }
	
private: 
   vector<Info> Arbeitstag;
   string aktuelle_position; 
};

