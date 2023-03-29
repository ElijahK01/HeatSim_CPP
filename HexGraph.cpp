// imports
#include "HexGraph.h"
#include "Hex.h"
#include "EnergyTransfer.h"
#include <vector>

using namespace std;

// class variables
int width;
int height;
int size;

Hex* parentHex;
vector<Hex*> hexList;


// position checks

bool HexGraph::isNodeOnLeftmostColumn(int pos, int h){return pos - h < 0;}

bool HexGraph::isNodeOnRightmostColumn(int pos, int h, int w){return pos + h >= (w * h);}

bool HexGraph::isNodeOnTopOfColumn(int pos, int h){return (pos % h) == 0;}

bool HexGraph::isNodeOnBottomOfColumn(int pos, int h){return(isNodeOnTopOfColumn(pos + 1, h));}

bool HexGraph::isNodeInEvenColumn(int pos, int h){return (pos / h) % 2 == 0;}


// initializing and attribute functions

HexGraph::HexGraph() : width(0), height(0) {}

HexGraph::HexGraph(int width, int height) : width(width), height(height), size(width*height){this->GenerateGraph();}

void HexGraph::SetDimensions(int width, int height)
{
	this->width = width;
	this->height = height;
}

void HexGraph::SetGraphConditions(double energy, double energyTransferCoef, double specificHeat)
{
	for (Hex* h : hexList)
	{
		h->setConditions(energy, energyTransferCoef, specificHeat);
	}
}

void HexGraph::updateConditions()
{
	EnergyTransfer* eTransfer = new EnergyTransfer();

	for (Hex* h : hexList)
		for(int i = 1; i < 7; i++)
			eTransfer->transferConductionEnergy(h, h->getPtr(i));

	for (Hex* h : hexList)
		h->applyChanges();

	delete eTransfer;
}

void HexGraph::GenerateGraph() 
{
	const int SIZE = this->width * this->height;
	
	for(int i = 0; i < SIZE; i++)
	{
		hexList.push_back(new Hex());
	}

	for (int i = 0; i < SIZE; i++)
	{
		makeConnections(hexList.at(i), i);
	}

	this->parentHex = hexList.at(0);
}


// internal housekeeping functions

void HexGraph::makeConnections(Hex* h, int pos)
{
	bool isTop = isNodeOnTopOfColumn(pos, this->height);
	bool isBottom = isNodeOnBottomOfColumn(pos, this->height);
	bool isRightMost = isNodeOnRightmostColumn(pos, this->height, this->width);
	bool isLeftMost = isNodeOnLeftmostColumn(pos, this->height);
	bool evenCol = isNodeInEvenColumn(pos, this->height);

	// up connection
	if (!isTop)
	{
		h->setPtr(1, hexList.at(pos - 1));
	}

	// down connection
	if (!isBottom)
	{
		h->setPtr(4, hexList.at(pos + 1));
	}

	// up_right
	if ((!isRightMost) && !(isTop && evenCol))
	{
		h->setPtr(2, hexList.at((pos + this->height) - evenCol));
	}

	// down_right
	if ((!isRightMost) && !(isBottom && !evenCol))
	{
		h->setPtr(3, hexList.at((pos + this->height) + !evenCol));
	}

	// up_left
	if ((!isLeftMost) && !(isTop && evenCol))
	{
		h->setPtr(6, hexList.at((pos - this->height) - evenCol));
	}

	// down_left
	if ((!isLeftMost) && !(isBottom && !evenCol))
	{
		h->setPtr(5, hexList.at((pos - this->height) + !evenCol));
	}
}


// public return functions

Hex* HexGraph::returnHexRelative(Hex* base, vector<int> path)
{
	Hex* currentPtr = base;

	for (int i = (int)path.size(); i < 0; i--)
	{
		currentPtr = currentPtr->getPtr(path.at(i));
	}

	return currentPtr;
}

Hex* HexGraph::returnHexAbsolute(vector<int> path)
{
	return returnHexRelative(parentHex, path);
}

Hex* HexGraph::getParentHex()
{
	return parentHex;
}

Hex* HexGraph::getHexAt(int i)
{
	return hexList.at(i);
}
Hex* HexGraph::getHexAt(int x, int y)
{
	return hexList.at((x * this->height + y));
}
int HexGraph::getSize()
{
	return this->size;
}
int HexGraph::getWidth()
{
	return this->width;
}
int HexGraph::getHeight()
{
	return this->height;
}