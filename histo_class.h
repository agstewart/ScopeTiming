
#include <vector>
#pragma once

class histo
{
public:
	// Constructor
	histo(void);
	histo(double min, double max, int nBins);
	histo(double min, double max, double binWidth);

	// Destructor
	~histo(void);

	// Member functions
	void record(double val);					// Bin data value
	int getNumBins() const;						// Get the number of bins
	double getWidth() const;					// Get Bin width
	int getCount(int bin);						// Get the frequency of some bin
	double getLowCentre() const;				// Get Lower Outlier Centre
	double getUpperCentre() const;				// Get Upper Outlier Centre
	int countLowerOutliers() const;				// Get number of values below the minimum 
	int countUpperOutliers() const;				// Get number of values at or above the maximum
	double lowerBound(int bin);					// Get the inclusive lower bound of a bin
	double upperBound(int bin);					// Get the exclusive upper bound of a bin
	double binCentre(int bin);					// Get the centre value of a bin

	// Memeber variables

	double minimum;						// Data set minimum
	double maximum;						// Data set maximum
	double binWidth;					// Width of bin
	int numBins;						// Number of bins
	int lowerOutlier, upperOutlier;		// Number of values below and above min/max
	double lowCentre;
	double upperCentre;					// Not real outlier bin centres
	std::vector<int> counts;			// create vector for histogram counts
	std::vector<double> centres;		// create a vector of bin centres
};

