#include "Tools.h"



String Tools::ValueToString(float value)
{
	static char tmpValue[7];
	dtostrf(value, 6, 2, tmpValue);
	return String(tmpValue);
}


