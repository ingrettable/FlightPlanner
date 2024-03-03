// C++ LIBRARIES FOR I/O AND TEXT
#include <sstream>
#include <string>
#include <iostream>

// OUR TYPES
#include <cppTPS.h>
#include <cppTPS_Transaction.h>
#include "WeightedGraph.h"
#include "Airport.h"

class AddStopTransaction : public cppTPS_Transaction {
private:
	wstring stop;
	vector<wstring>* stops;
	cppTPS tps;
	
public: 
	AddStopTransaction(vector<wstring>* initStops, wstring initStop) {
		this->stop = initStop;
		this->stops = initStops;
	}
	void doTransaction() {
		stops->push_back(stop);
	}
	void undoTransaction() {
		stops->pop_back();
	}
	std::wstring toString() {
		return L"";
	}
};

// OUR APP'S GLOBAL VARIABLES
vector<wstring> stops;
WeightedGraph<Airport> graph;
cppTPS tps;

// FUNCTION DECLARATIONS, ALL DEFINED UNDER main
void initAllAirports();
void initEdge(wstring node1, wstring node2);
void displayAirports();
void displayCurrentTrip();
void displayMenu();
bool processUserInput();

int main() {
	initAllAirports();

	// LOOP FLAG VARIABLE
	bool keepGoing = true;
	while (keepGoing) {
		displayAirports();
		displayCurrentTrip();
		displayMenu();
		keepGoing = processUserInput();
	}
	wcout << L"GOODBYE";
    return 0;
}

void displayAirports() {
	// LIST OF AIRPORTS
	wcout << L"\n\nAIRPORTS YOU CAN TRAVEL TO AND FROM:" << endl;
	vector<wstring> codes;
	graph.getKeys(&codes);
	for (int i = 0; i < codes.size(); i++) {
		if ((i % 10) == 0) {
			wcout << "\t";
		}
		wcout << codes[i];
		if (i < (codes.size() - 1))
			wcout << ", ";
		if ((i % 10) == 9) {
			wcout << endl;
		}
	}
	wcout << endl << endl;
}

void displayCurrentTrip() {
	wcout << "Current Trip Stops: " << endl;
	for (size_t i = 0; i < stops.size(); i++) {
		std::wcout << "\t" << i + 1 << ". " << stops[i] << std::endl;
	} //part a
	wcout << "Current Trip Legs: " << endl;
	if (stops.size() > 1) {
		for (size_t i = 0; i < stops.size()-1; i++) {
			if (i == stops.size()) {
				break;
			}
			std::wstring out = stops[i] + L"-" + stops[i];
			wstring start = stops[i];
			wstring end = stops[i + 1];
			vector<wstring> path;
			graph.findPath(&path, start, end);
			wcout << "\t" << i + 1 << ". ";
			Airport* a1 = graph.getNodeData(stops[i]);
			Airport* a2 = graph.getNodeData(stops[i + 1]);
			float distance = Airport::calculateDistance(a1, a2);
			for (const wstring& node : path) {
				if (node != path.back()) {
					wcout << node << L"-> ";
				}
				else {
					wcout << node;
				}

			}
			wcout << L" (" << distance << L" Miles)" << endl;
		}
	}
	float totalDistance = 0.0f;
	for (size_t i = 0; i < stops.size() - 1; i++) {
		if (i == stops.size()) {
			break;
		}
		Airport* a1 = graph.getNodeData(stops[i]);
		Airport* a2 = graph.getNodeData(stops[i + 1]);
		totalDistance += Airport::calculateDistance(a1, a2);
	} //partc
	std::wcout << L"\nTotal Trip Distance: " << totalDistance << L" Miles" << std::endl;
	// ADD CODE HERE - FOR THIS YOU NEED TO DISPLAY THREE THINGS:
	// A) THE TRIP STOPS
	// B) EACH TRIP LEG, i.e. ROUTE TAKEN FROM STOP TO STOP (including mileage)
	// C) THE TOTAL TRIP MILEAGE

	// A) DISPLAY YOUR CURRENT TRIP STOPS IN THE FORM:
	/* Trip Stops :
	      1. BOS
	      2. LGA
		  3. LAX
	      ...
	*/

	// B) DISPLAY EACH TRIP LEG IN THE FORM:
	/*
		Trip Legs:
			1. BOS-LGA (X Miles)
			2. LGA-CHI-LAX (X Miles)
			...

		Note, in the above trip legs display, "LGA-CHI-LAX" would represent a valid
		found route produced by your graph walking algorithm and "X" Miles would have
		been computed by you using the calcluateDistance method you should find inside
		the Airport class. Note, if there are two stops, there is 1 leg. If there are 3
		stops, there would be 2 legs. Note, the first and last airport code count as
		stops. So, if you have 5 stops, you'll need to calculate 4 routes, one for each
		leg of the trip. Note that a single airport can occur twice in the trip, but not
		consecutively.
	*/

	// C) DISPLAY YOUR TOTAL TRIP DISTANCE:
	/*
		Total Trip Distance: X Miles

		Note, X would be calculated by you by combining the mileage of all the legs.
	*/
}

void displayMenu() {
	// DISPLAY THE MENU
	wcout << "ENTER A SELECTION" << endl;
	wcout << "S) Add a Stop to your Trip" << endl;
	wcout << "U) Undo" << endl;
	wcout << "R) Redo" << endl;
	wcout << "E) Empty Trip" << endl;
	wcout << "Q) Quit" << endl;
	wcout << "-";
}

bool processUserInput() {
	// GET THE USER SELECTION
	wstring entry;
	wcin >> entry;

	if (entry.compare(L"S") == 0) {
		wstring airportCode;
		wcout << "Enter the Airport Code: ";
		wcin >> airportCode;
		if (graph.nodeExists(airportCode)) {
			AddStopTransaction* transaction = new AddStopTransaction(&stops, airportCode);
			tps.addTransaction(transaction);
		}
		// ADD CODE HERE - MAKE SURE YOU GET USER INPUT REGARDING WHICH Airport TO
		// ADD TO THE TRIP AND MAKE SURE YOU ADD A TRANSACTION SO IT CAN BE ADDED
		// AND UNDONE AND REDONE
	}
	// UNDO A TRANSACTION
	else if (entry.compare(L"U") == 0) {
		tps.undoTransaction();
	}
	// REDO A TRANSACTION
	else if (entry.compare(L"R") == 0) {
		tps.doTransaction();
	}
	// CLEAR ALL TRANSACTIONS
	else if (entry.compare(L"E") == 0) {
		tps.clearAllTransactions();
		stops.clear();
	}
	// QUIT
	else if (entry.compare(L"Q") == 0) {
		return false;
	}
	return true;
}

void initAllAirports() {
	// FIRST ADD ALL THE AIRPORTS
	graph.addNode(L"AUS", new Airport(L"AUS", 30, 18, 97, 42));
	graph.addNode(L"AVL", new Airport(L"AVL", 36, 00, 82, 32));
	graph.addNode(L"BGR", new Airport(L"BGR", 44, 48, 68, 40));
	graph.addNode(L"BOS", new Airport(L"BOS", 42, 22, 71, 2));
	graph.addNode(L"BUF", new Airport(L"BUF", 42, 56, 78, 44));
	graph.addNode(L"BVT", new Airport(L"BVT", 44, 28, 73, 9));
	graph.addNode(L"CLE", new Airport(L"CLE", 41, 24, 81, 81));
	graph.addNode(L"COD", new Airport(L"COD", 44, 33, 109, 4));
	graph.addNode(L"DCA", new Airport(L"DCA", 38, 51, 77, 2));
	graph.addNode(L"DEN", new Airport(L"DEN", 39, 45, 104, 52));
	graph.addNode(L"DFW", new Airport(L"DFW", 32, 51, 96, 51));
	graph.addNode(L"ELP", new Airport(L"ELP", 31, 48, 106, 24));
	graph.addNode(L"HOU", new Airport(L"HOU", 29, 59, 95, 22));
	graph.addNode(L"IND", new Airport(L"IND", 39, 44, 86, 17));
	graph.addNode(L"JAX", new Airport(L"JAX", 30, 30, 81, 42));
	graph.addNode(L"LAX", new Airport(L"LAX", 33, 56, 118, 24));
	graph.addNode(L"LGA", new Airport(L"LGA", 40, 47, 73, 58));
	graph.addNode(L"LIT", new Airport(L"LIT", 34, 44, 92, 14));
	graph.addNode(L"MCI", new Airport(L"MCI", 39, 7, 94, 35));
	graph.addNode(L"MIA", new Airport(L"MIA", 25, 48, 80, 16));
	graph.addNode(L"MKE", new Airport(L"MKE", 42, 87, 87, 74));
	graph.addNode(L"MOT", new Airport(L"MOT", 48, 25, 101, 21));
	graph.addNode(L"MSY", new Airport(L"MSY", 29, 59, 90, 15));
	graph.addNode(L"OMA", new Airport(L"OMA", 41, 30, 95, 80));
	graph.addNode(L"PHX", new Airport(L"PHX", 33, 26, 112, 1));
	graph.addNode(L"PWM", new Airport(L"PWM", 43, 39, 70, 19));
	graph.addNode(L"SFO", new Airport(L"SFO", 37, 46, 122, 26));
	graph.addNode(L"SEA", new Airport(L"SEA", 47, 39, 122, 18));
	graph.addNode(L"SLC", new Airport(L"SLC", 40, 46, 111, 58));
	graph.addNode(L"VGT", new Airport(L"VGT", 36, 5, 115, 10));

	// NOW CONNECT THE AIRPORTS
	initEdge(L"AUS", L"DFW");
	initEdge(L"AVL", L"IND");
	initEdge(L"BOS", L"BUF");
	initEdge(L"BOS", L"CLE");
	initEdge(L"BOS", L"PWM");
	initEdge(L"BUF", L"CLE");
	initEdge(L"BVT", L"BGR");
	initEdge(L"CLE", L"IND");
	initEdge(L"CLE", L"MKE");
	initEdge(L"COD", L"MOT");
	initEdge(L"COD", L"SEA");
	initEdge(L"COD", L"DEN");
	initEdge(L"DCA", L"AVL");
	initEdge(L"DCA", L"JAX");
	initEdge(L"DEN", L"DFW");
	initEdge(L"DEN", L"ELP");
	initEdge(L"DFW", L"HOU");
	initEdge(L"ELP", L"PHX");
	initEdge(L"HOU", L"LIT");
	initEdge(L"IND", L"MKE");
	initEdge(L"JAX", L"AVL");
	initEdge(L"LAX", L"MIA");
	initEdge(L"LAX", L"SFO");
	initEdge(L"LAX", L"VGT");
	initEdge(L"LGA", L"IND");
	initEdge(L"LGA", L"DCA");
	initEdge(L"LGA", L"BOS");
	initEdge(L"LGA", L"MIA");
	initEdge(L"MCI", L"DEN");
	initEdge(L"MCI", L"DFW");
	initEdge(L"MCI", L"IND");
	initEdge(L"MCI", L"OMA");
	initEdge(L"MIA", L"BOS");
	initEdge(L"MIA", L"JAX");
	initEdge(L"MIA", L"MSY");
	initEdge(L"MKE", L"MOT");
	initEdge(L"MOT", L"SEA");
	initEdge(L"MOT", L"DEN");
	initEdge(L"MOT", L"IND");
	initEdge(L"MSY", L"JAX");
	initEdge(L"MSY", L"IND");
	initEdge(L"OMA", L"DEN");
	initEdge(L"OMA", L"MOT");
	initEdge(L"OMA", L"IND");
	initEdge(L"PHX", L"LAX");
	initEdge(L"PWM", L"BVT");
	initEdge(L"PWM", L"BGR");
	initEdge(L"SFO", L"VGT");
	initEdge(L"SFO", L"DEN");
	initEdge(L"SFO", L"SEA");
	initEdge(L"SLC", L"SFO");
	initEdge(L"SLC", L"DEN");
	initEdge(L"SLC", L"SEA");
	initEdge(L"VGT", L"PHX");
}

void initEdge(wstring node1, wstring node2) {
	Airport* a1 = graph.getNodeData(node1);
	Airport* a2 = graph.getNodeData(node2);
	float distance = Airport::calculateDistance(a1, a2);
	graph.addEdge(node1, node2, distance);
}