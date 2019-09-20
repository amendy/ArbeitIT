#include "GUI.h"
#include "Graph.h"
#include "Connection.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

extern double globalFaktor = 2;

using namespace std;


int GUI:: showMenu()
{
	cout << " Bitte waehlen Sie eine Aktion aus" << endl
		<< "1- Arbeitsweg zeigen : " << endl
		<< "2- Naechster Kunde: " << endl
		<< "3- Baustelle markieren: " << endl
		<< "4- Arbeitstag beenden: " << endl
		<< "5- Programm beenden" << endl;


	cout << "Eingabe: ";
	int eingabe;
	cin >> eingabe;
	return eingabe;
}

void GUI::arbeitswegZeigen()
{
	for (auto i : this->getNodes())
	{
		cout << i->getID() << endl;
	}
	for (auto i : this->getEdges())
	{
		Connection* temp = dynamic_cast <Connection*>(i);
		cout << temp->getSrcNode().getID() << " is connected to " << temp->getDstNode().getID() << " Distance is " << temp->getdistance() << endl;

		cout << i->getSrcNode().getID() << " is connected to " << i->getDstNode().getID() << endl;

	}
}


void GUI::naechsterKunde()
{
	
	string kundenName; 
	cout << " Geben Sie den Namen des Kunden ein "; 
	cin >> kundenName; 
	cout << endl; 
	
	string ZielOrt;
	cout << " Ort angeben: ";
	cin >> ZielOrt;
	cout << endl;
	while (this->findNode(ZielOrt) == NULL)
	{
		cout << "Ort nicht gefunden. " << endl;
		cin >> ZielOrt;
	}

	double gesamtKost = 0;
	double gesamtZeit = 0;
	double kostNachHause = 0;
	
	
	
	
	//Node* StartOrt = this->findNode("Mittenwalde");

	
	
	globalFaktor = 2; // globalFaktor =2
	deque<Edge*> path;
	findShortestPathDijkstra(path, *this->findNode(aktuelle_position), *this->findNode(ZielOrt));
	
	double gesamtDistance = 0; 
	//for (std::deque<Edge*>::iterator it = path.begin(); it != path.end(); it++)
	for( auto i : path)
	{
		Connection* temp = dynamic_cast<Connection*>(i);

		cout << "Teilroute: " << temp->toString() <<
			"\n Teilzeit: " << temp->getWeight() <<
			 "\n Kost: " << ((temp->getdistance() * 30)) << " Cent" << endl;

		gesamtKost += (temp->getdistance()) * 30;
		gesamtZeit += temp->getWeight();
		gesamtDistance += temp->getdistance(); 
	}
	cout << " Gesamt Einnahme: " << (gesamtKost / 100) + 50 << " Euro" << endl;
	cout << "Gesamt Zeit: " << gesamtZeit << endl;
	 
	// Das ist nur eine FahrtInformation. Also nur eine Fahrt
	Info fahrtenListe;
	fahrtenListe.m_kundenName = kundenName;
	fahrtenListe.m_fahrKost = gesamtKost / 100;
	fahrtenListe.m_einnahme = (gesamtKost / 100) + 50;
	fahrtenListe.m_ZielOrt = this->findNode(ZielOrt);   // find node
	fahrtenListe.gesamtDistance = gesamtDistance; 
	this->set_position(ZielOrt);  // merkt er sich die jetzige position
	this->Arbeitstag.push_back(fahrtenListe);
}


// Edges veraendern wie geht es denn? 

void GUI::markiereBaustellen()
{
	// Gehst Du in die Liste von Edges rein
    // erstelle eine neue Liste von Edges
	list<Edge*> EdgeList;
	//for (auto edgeIt = this->getEdges().begin(); edgeIt != this->getEdges().end(); edgeIt++)
	// Zeige alle Edges
	for(auto i: this->getEdges())
	{
		
		string hatbaustelle;
		Connection *tmpConnection = dynamic_cast<Connection*>(i);
		/*cout << "StartNode ist : " << tmpConnection->getSrcNode().getID() << 
			"---->  EndNode ist" << tmpConnection->getDstNode().getID() << endl;*/
		// besser es gibt eine Funktion dafuer

		cout << tmpConnection->toString() <<endl; 
		cout << " hat baustelle ja/nein" << endl;
		cin >> hatbaustelle;
		if (hatbaustelle == "ja")
		{
			tmpConnection->setGeschwendigkeit(40);
		}
		EdgeList.push_back((tmpConnection));
		this->m_edges = EdgeList; // Hier ist die neue Liste von Edges
	}
}
void GUI::arbeitstagBeenden()
{
	
	double gesamtZeit = 0;
	double kostNachHause = 0;

	
	Node* ZielOrt = this->findNode("Mittenwalde");
	// Zielort Mittenwalde wie mache ich das, dass ein Standort festbleibt??
	// ZielOrt bekannt aber der letzter Arbeitsort muss man man automatisch auswaehlen koennen. 
	// also dies ist der letzter Node im Vector

	Node* StartOrt = this->Arbeitstag.at(this->Arbeitstag.size() - 1).m_ZielOrt;
	deque<Edge*> path;
	findShortestPathDijkstra(path, *StartOrt, *ZielOrt);

	//for (std::deque<Edge*>::iterator it = path.begin(); it != path.end(); it++)
		for(auto i : path)
	{
		Connection* temp = dynamic_cast<Connection*>(i);

		std::cout << "Teilroute: " << temp->toString() <<

			"\n Kost: " << ((temp->getdistance() * 30)) << " Cent" << endl;

		kostNachHause += (temp->getdistance()) * 30;

	}
	cout << " Kost: " << (kostNachHause / 100) << " Euro" << endl;
	double gesamtKost = 0;
	double tagesKilometer = 0; 
	double gesamtEinnahme = 0; 

	for (auto it = Arbeitstag.begin(); it != Arbeitstag.end(); it++)
		//for (auto i : Arbeitstag)
	{
		cout << "Name der Kunde: " << it->m_kundenName << 
			" \n Ort: "	<< it->m_ZielOrt->getID() << 
			" \n Einnahme: " << it->m_einnahme <<
			 " \n Kost: " << it->m_fahrKost << endl;

		gesamtKost += it->m_fahrKost; 
		tagesKilometer += it->gesamtDistance;
		gesamtEinnahme += it->m_einnahme;
	}
	

	cout << " Kost des Tages: " << gesamtKost << 
        "\n Kilometer des Tages: " << tagesKilometer <<
		" \n Gesamt Einnahme: " << gesamtEinnahme<< endl;
}