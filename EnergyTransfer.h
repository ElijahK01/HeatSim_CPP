#pragma once

#include "Hex.h"
#include "Main.h"

const int D = 1;				// thickness used in calculations
const double A = 1.0 / 6.0;		// Area of contact used in calculations

class EnergyTransfer
{
public:
	double transferConductionEnergy(Hex* parent, Hex* target);
};

