#include "Main.h"
#include "Hex.h"
#include "HexGraph.h"
#include "EnergyTransfer.h"
#include <iostream>

using namespace std;

#define MILLIS_IN_SECOND 1000

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
	// NOTE : this is for surface and is effectively 2 dimensional
	// get user input
	cout << "Heat Transfer Simulation (2d)" << endl;

	getUserInput();

	// setup graph
	HexGraph* material = new HexGraph(resolutionNodes, resolutionNodes);

	material->SetGraphConditions(startingTemp * materialSpecificHeat, materialHeatTransferCoef, materialSpecificHeat);

	// generate frames and export frames to file
	cout << "Baking frames\n..." << endl;
	long fCount = 0;

	const long TICKS = (timeDuration * MILLIS_IN_SECOND) / TICKLENGTH;

	for (long i = 0; i < TICKS; i++)
	{
		material->updateConditions();
		// TODO -- append material state to file
	}

	cout << "Done baking" << endl;
	cout << "Frame count: " << fCount << endl;
	cout << "Opening sim" << endl;

	// run frames in python script

	cout << "Sim playback complete" << endl;
	delete material;
}



