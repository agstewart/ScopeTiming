#include "StdAfx.h"
#include "histo_class.h"

#include "StdAfx.h"
#include "histo_class.h"
#include <iostream>


// Constructors
histo::histo(double min, double max, int nBins)
{
	minimum = min;
	maximum = max;
	lowerOutlier = 0;
	upperOutlier = 0;
	numBins = nBins;
	binWidth = (maximum - minimum)/numBins;
	// resize vector to the correct number of bins
	counts.resize(numBins,0);
	centres.resize(numBins);
	for (int i = 0; i < numBins; i++)
	{
		centres[i] = (minimum + binWidth*(i + 0.5));
		// std::cout << "Bin " << i << " Centre: " << centres[i] << std::endl;
	}
	lowCentre = centres[0] - binWidth/2;
	upperCentre = centres[numBins-1] + binWidth/2;
}

histo::histo(double min, double max, double binwidth)
{
	binWidth = binwidth;
	minimum = min;
	maximum = max;
	lowerOutlier = 0;
	upperOutlier = 0;
	numBins = int ((maximum - minimum)/binWidth);
	// resize vector to correct number of bins
	counts.resize(numBins,0);
	centres.resize(numBins);
	for (int i = 0; i < numBins; i++)
	{
		centres[i] = (minimum + binWidth*(i + 0.5));
		// std::cout << "Bin " << i << " Centre: " << centres[i] << std::endl;
	}
	lowCentre = centres[0] - binWidth/2;
	upperCentre = centres[numBins-1] + binWidth/2;
}

// Destructors

histo::~histo(void)
{
}

void histo::record(double val)
{
	int bin = (int)((val - minimum)/binWidth);
	if (bin < 0)
	{
		lowerOutlier++;
	}
	else if (bin >= numBins)
	{
		upperOutlier++;
	}
	else
	{
		counts[bin] = counts[bin]++;
	} 
}

int histo::getNumBins() const
{
	return numBins;
}

double histo::getWidth() const
{
	return binWidth;
}

int histo::getCount(int bin)
{
	return counts[bin];
}

double histo::getLowCentre() const
{
	return lowCentre;
}

double histo::getUpperCentre() const
{
	return upperCentre;
}

int histo::countLowerOutliers() const
{
	return lowerOutlier;
}

int histo::countUpperOutliers() const
{
	return upperOutlier;
}

double histo::lowerBound(int bin)
{
		return (minimum + binWidth*bin);
}

double histo::upperBound(int bin)
{
		return (minimum + binWidth*(bin+1));
}

double histo::binCentre(int bin)
{
	return centres[bin];
}

