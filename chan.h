#pragma once
#include "lecroy.h"

class chan : public lecroy
{
public:
	chan(void);
	chan(int channel);
	~chan(void);
};
