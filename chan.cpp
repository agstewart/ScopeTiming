#include "StdAfx.h"
#include "chan.h"

chan::chan(void)
{
	chanNum = 1; // default is channel one
}

chan::chan(int channel)
{
	chanNum = channel;
}

chan::~chan(void)
{
}
