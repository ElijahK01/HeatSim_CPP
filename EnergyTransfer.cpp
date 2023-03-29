#include "EnergyTransfer.h"
#include "Main.h"

double EnergyTransfer::transferConductionEnergy(Hex* parent, Hex* target)
{
	if (target == nullptr)
		return 0.0;

	double k = parent->getTransferCoef();
	double tHot = parent->getTemp();
	double tCold = target->getTemp();
	
	double q = (k * A * (tHot - tCold) * TICKLENGTH) / D;
	parent->addEnergy(q);
	target->subtractEnergy(q);

	return q;
}
