#include "Dictionary.h"

std::ostream& operator<<(std::ostream& os,const  Dictionary& di)
{
	di.view();
	return os;
}