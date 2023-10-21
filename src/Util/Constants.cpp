#include "Constants.h"

namespace magica_rogue
{
	namespace constants
	{
		int operator*(MRAttribute lhs, int rhs) {
			return static_cast<int>(lhs) * rhs;
		}
	}
}