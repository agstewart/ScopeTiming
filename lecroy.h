
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

// #pragma once

using std::cout;
using std::endl;

enum CHANNEL {C1, C2, C3, C4};
enum SLOPE {Pos, Neg, Window};

class lecroy
{
public:
	lecroy(void);
	lecroy(int channel);
	~lecroy(void);

	void get_idn();
	void initialise();
	void clearScope();
	void sendCommand(char *command);
	void getTrace(char T, int k); // Get Trace waveform
	void saveData(char * data, int j); // save data to text file
	void saveData(char * filename, char * data); // save data to text file with filename as argument
	void scopeWait(); // prevents instrument analysing new commands until acquisition is complete
	void scopeArm(); // Start a new data acquisition 
	void setCommHeader(); // sets scope response format, i.e. turn off the header
	void setMemorySize();
	void setFormat();
	// void genWaveform(char * wf); // take scope data and generate waveform
	void setNrows(int numrows); // set the value of n rows
	double getNrows(); // get the number of rows (nrows) written to arrays
	void grabData(); // pull data from scope


	void queryTrigSlope();
	void queryVolt();
	void queryTrigMode();
	void queryTimeBase();
	void queryMemorySize();
	void queryWaveform(); // query the waveform
	void queryTimeInterval(); // query the Time interval
	void queryTimeOffset(); // query Time Offset
	void queryFormat(); // query the format
	void queryMax(); // query the maximum recorded amplitude
	void queryTrigLev(); // query the trigger level
	void queryDesc(); // query the wave description
	void queryVerticalOffset(); // query vertical offset
	double queryAmplitude(); // query waveform amplitude
	double queryMinimum(); // query waveform minimum
	double queryMaximum(); // query waveform maximum
	double queryFalltime(); // query pulse falltime
	double queryFalltime82(); // query pulse fallltime 80% to 20%
	double queryRisetime82(); // query pulse risetime 20% to 80%
	
	// functions to set up oscilloscope
	void setTrigMode();
	void setTrigLev(double lev);
	void setTimeBase(double tdiv);
	void setVerticalOffset(double v_offset);
	void setVoltageDiv(double volt_div);
	void setTrigSlope(SLOPE t_slope);

	double getTimeInt() const; // get time interval member variable
	double getTimeOffset() const;
	double getSigInt() const;
	double getSigMin() const;
	double getVerticalOffset() const;
	double rtnData(char * resp); // return data value from scope response
	unsigned int getVectorSize();
	void clearVectors();
	double getAmpElement(int index);
	double getTimebaseElement(int index);
	
	void openFile(char filename); // open text file for writing
	void wf2Vector(char * wf); // write waveform data to vector
	bool vec2File(char * filename);

protected : 
	int m_device; // instrument identifier
	int chanNum; // Scope channel number
	int nrows; // number of rows written to data arrays
	double timeInt; // time interval
	double timeOffset; // time offset
	double verticalOffset; // Vertical offset
	double sigInt; // Integral of scope signal
	double sigMin; // Minimum of scope signal
	std::vector<double> timebase; // vector for timebase values 
	std::vector<double> amplitude; // vector for amplitude value
	std::vector<double>::iterator it;
};
