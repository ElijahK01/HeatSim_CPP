#include "Hex.h"
#include <vector>

using namespace std;

Hex* ptrI   = nullptr;  // up
Hex* ptrII  = nullptr;  // up right
Hex* ptrIII = nullptr;  // down right
Hex* ptrIV  = nullptr;  // down
Hex* ptrV   = nullptr;  // down left
Hex* ptrVI  = nullptr;  // up left

double energy;
double density;
double specificHeat;
double tempEnergyIn  = 0.0;
double tempEnergyOut = 0.0;
double energyTransferCoef;

vector<int> edgeLengths;

// constructors
Hex::Hex()																				: energy(1.0),    energyTransferCoef(1.0),				  specificHeat(1.0),		  density(1.0),     tempEnergyIn(0.0), tempEnergyOut(0.0){}
Hex::Hex(double energy)																	: energy(energy), energyTransferCoef(1.0),				  specificHeat(1.0),		  density(1.0),     tempEnergyIn(0.0), tempEnergyOut(0.0){}
Hex::Hex(double energy, double energyTransferCoef)										: energy(energy), energyTransferCoef(energyTransferCoef), specificHeat(1.0),		  density(1.0),     tempEnergyIn(0.0), tempEnergyOut(0.0){}
Hex::Hex(double energy, double energyTransferCoef, double specificHeat)					: energy(energy), energyTransferCoef(energyTransferCoef), specificHeat(specificHeat), density(1.0),     tempEnergyIn(0.0), tempEnergyOut(0.0){}
Hex::Hex(double energy, double energyTransferCoef, double specificHeat, double density) : energy(energy), energyTransferCoef(energyTransferCoef), specificHeat(specificHeat), density(density), tempEnergyIn(0.0), tempEnergyOut(0.0){}

Hex* Hex::getSelfPtr()
{
	return this;
}

Hex* Hex::getPtr(int dir)
{
	switch (dir)
	{
	case 1:
		return ptrI;
	case 2:
		return ptrII;
	case 3:
		return ptrIII;
	case 4:
		return ptrIV;
	case 5:
		return ptrV;
	case 6:
		return ptrVI;
	default:
		return nullptr;
	}
}

void Hex::setPtr(int dir, Hex* ptr)
{
	switch (dir)
	{
	case 1:
		ptrI = ptr;
		break;
	case 2:
		ptrII = ptr;
		break;
	case 3:
		ptrIII = ptr;
		break;
	case 4:
		ptrIV = ptr;
		break;
	case 5:
		ptrV = ptr;
		break;
	case 6:
		ptrVI = ptr;
		break;
	}
}

double Hex::getTransferCoef()
{
	return this->energyTransferCoef;
}

double Hex::getTemp()
{
	return this->energy / (this->specificHeat * this->density);
}

void Hex::addEnergy(double q)
{
	this->tempEnergyIn = q;
}

void Hex::subtractEnergy(double q)
{
	this->tempEnergyOut = q;
}

void Hex::setConditions(double energy, double energyTransferCoef, double specificHeat)
{
	this->energy = energy;
	this->energyTransferCoef = energyTransferCoef;
	this->specificHeat = specificHeat;
}

void Hex::applyChanges()
{
	this->energy = this->tempEnergyIn - this->tempEnergyOut;
}
