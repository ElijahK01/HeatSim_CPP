#pragma once
#include "Hex.h"
#include <string>

using namespace std;

class HexGraph
{
public:
	HexGraph();
	HexGraph(int width, int height);
	void GenerateGraph();
	void SetDimensions(int width, int height);
	void SetGraphConditions(double energy, double energyTransferCoef, double specificHeat);
	void updateConditions();

	Hex* returnHexRelative(Hex* base, vector<int> path);	// returns hex from base following path
	Hex* returnHexAbsolute(vector<int> path);				// returns hax from parent hex following path

	Hex* getParentHex();
	Hex* getHexAt(int i);
	Hex* getHexAt(int x, int y);
	int getSize();
	int getWidth();
	int getHeight();

private:
	int width;
	int height;
	int size;

	Hex* parentHex;
	vector<Hex*> hexList;
	void makeConnections(Hex* h, int n);

	// checks position attributes of hex
	bool isNodeOnLeftmostColumn(int pos, int h);
	bool isNodeOnRightmostColumn(int pos, int h, int w);
	bool isNodeOnTopOfColumn(int pos, int h);
	bool isNodeOnBottomOfColumn(int pos, int h);
	bool isNodeInEvenColumn(int pos, int h);
};

