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
#pragma warning(disable : 4996)

int timeDuration = 0;
int resolutionNodes = 0;
double startingTemp = 0;
double materialSpecificHeat = 0;
double materialHeatTransferCoef = 0.0;

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
	ofstream myfile;
	myfile.open("example.txt");

	// NOTE : this is for surface and is effectively 2 dimensional
	// get user input
	cout << "Heat Transfer Simulation (2d)" << endl;

	getUserInput();

	// setup graph
	HexGraph* material = new HexGraph(resolutionNodes, resolutionNodes);

	material->SetGraphConditions(startingTemp * materialSpecificHeat, materialHeatTransferCoef, materialSpecificHeat);

	// generate frames and export frames to file
	cout << "Baking frames\n" << endl;

	const long TICKS = (timeDuration * MILLIS_IN_SECOND) / TICKLENGTH;
	long tenPercentMarker = TICKS / 10;
	int percentCounter = 0;

	for (long i = 0; i < TICKS; i++)
	{
		material->updateConditions();
		// TODO -- append material state to file

		// loading marker
		if (i % tenPercentMarker == 0)
		{
			percentCounter += 10;
			cout << percentCounter << "%" << endl;
		}
			
	}

	cout << "\nDone baking" << endl;
	cout << "Frame count: " << TICKS << endl;

	myfile << "Writing this to a file.\n";
	myfile.close();

	cout << "Closing File" << endl;
	cout << "Opening sim" << endl;

	char filename[] = "Display.py";
	FILE* fp;

	Py_Initialize();

	fp = fopen(filename, "r");
	PyRun_SimpleFile(fp, filename);

	Py_Finalize();

	cout << "Sim playback complete" << endl;
	delete material;
}



