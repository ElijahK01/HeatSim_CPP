#pragma once

#include <vector>

using namespace std;

class Hex
{
	public:
		Hex();
		Hex(double energy);
		Hex(double energy, double energyTransferCoef);
		Hex(double energy, double energyTransferCoef, double specificHeat);
		Hex(double energy, double energyTransferCoef, double specificHeat, double density);


		Hex* getSelfPtr();
		Hex* getPtr(int dir);
		void setPtr(int dir, Hex* ptr);
		void setConditions(double energy, double energyTransferCoef, double specificHeat);

		double getTransferCoef();
		double getTemp();

		void addEnergy(double q);
		void subtractEnergy(double q);

		void applyChanges();

	private:
		// direction pointers
		Hex* ptrI;
		Hex* ptrII;
		Hex* ptrIII;
		Hex* ptrIV;
		Hex* ptrV;
		Hex* ptrVI;

		double energy;
		double density;
		double specificHeat;
		double tempEnergyIn;
		double tempEnergyOut;
		double energyTransferCoef;

		vector<int> edgeLengths;
};

