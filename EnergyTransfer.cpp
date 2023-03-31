#include "EnergyTransfer.h"
#include "Main.h"

double EnergyTransfer::transferConductionEnergy(Hex* parent, Hex* target)
{
	if (target == nullptr)
		return 0.0;

	double k = parent->getTransferCoef();
	double tHot = parent->getTemp();
	double tCold = target->getTemp();
	
	double q = (k * (double)A * (tHot - tCold) * (TICKLENGTH));

	parent->addEnergy(q * -1);
	target->addEnergy(q);
	

	return q;
}
