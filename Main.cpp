#include "Main.h"
#include "Hex.h"
#include "HexGraph.h"
#include "EnergyTransfer.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <conio.h>
#include <Python.h>

using namespace std;

#define MILLIS_IN_SECOND 1000
//#define TESTING
#pragma warning(disable : 4996)

int timeDuration = 10;
int resolutionNodes = 40;
double startingTemp = 100;
double materialSpecificHeat = 10;
double materialHeatTransferCoef = 0.7;

void getUserInput()
{
	cout << "How long to run simulation (s): ";
	cin >> timeDuration;

	cout << "Resolution points per side: ";
	cin >> resolutionNodes;

	cout << "Starting tempurature (Deg. k): ";
	cin >> startingTemp;

	cout << "Material heat transfer coef: ";
	cin >> materialHeatTransferCoef;

	cout << "Material specific heat: ";
	cin >> materialSpecificHeat;
}

int main()
{
	ofstream simOutput;
	simOutput.open("SimulationOutput.txt");

	// NOTE : this is for surface and is effectively 2 dimensional
	// get user input
	cout << "Heat Transfer Simulation (2d)" << endl;

#ifndef TESTING
	getUserInput();
#endif // !1

	
	simOutput << "DIM " << resolutionNodes << "\n";
	// setup graph
	HexGraph* material = new HexGraph(resolutionNodes, resolutionNodes);

	material->SetGraphConditions(startingTemp * materialSpecificHeat, materialHeatTransferCoef, materialSpecificHeat);
	
	// generate frames and export frames to file
	cout << "Baking frames\n" << endl;

	const long TICKS = (timeDuration * MILLIS_IN_SECOND) / TICKLENGTH;
	long tenPercentMarker = TICKS / 10;
	int percentCounter = 0;
	int midIndex = (material->getSize() / 2) + (material->getHeight() / 2);

	for (long i = 0; i < TICKS; i++)
	{
		// heat source
		material->getHexAt(midIndex)->addEnergy(100);
		material->getHexAt(0)->applyChanges();

		material->updateConditions();
		
		for (int j = 0; j < material->getSize(); j++)
		{
			simOutput << material->getHexAt(j)->getTemp() << ",";
		}

		simOutput << "N\n";

		// loading marker
		if (i % tenPercentMarker == 0)
		{
			percentCounter += 10;
			cout << percentCounter << "%" << endl;
		}
			
	}

	cout << "\nDone baking" << endl;
	cout << "Frame count: " << TICKS << endl;

	simOutput << "\nEOF";
	simOutput.close();

	cout << "Closing File" << endl;
	cout << "Enter to display sim" << endl;
	char c;
	cin >> c;
	cout << "Opening sim" << endl;

	char filename[] = "Display.py";
	FILE* fp;

	/*
	* PYTHON PORTION
	*/

	Py_Initialize();

	fp = fopen(filename, "r");
	PyRun_SimpleFile(fp, filename);

	Py_Finalize();

	cout << "Sim playback complete" << endl;
	delete material;
}



