#pragma once
#include "Graph.h"
#include "Edge.h"
#include <string>

extern double globalfaktor; 

using namespace std; 

class Connection : public Edge
{
public: 

	Connection(Node& rSrc, Node& rDst, double distance, double geschwendigkeit) : Edge(rSrc, rDst), m_distance(distance), m_geschwendigkeit(geschwendigkeit){}
	 virtual double getWeight()
	 {
		 if ( globalfaktor = 1)
		 {
			 return m_distance;
		 }
		 if (globalfaktor = 2)
		 {
			 return (m_distance / m_geschwendigkeit); 
		 }
		 return 0; 
	 }

	double getdistance() { return m_distance; }; 
	void setGeschwendigkeit(double geschwendigkeit) { m_geschwendigkeit= geschwendigkeit; }; 
	
private:
	double m_distance; 
	double m_geschwendigkeit; 
	
}; 
