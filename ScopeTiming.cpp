// ScopeTiming.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
// #include "chan.h"
#include "lecroy.h"
#include <iostream>
#include <fstream>

using std::cout;
using std::endl;
using std::ofstream;


int _tmain(int argc, _TCHAR* argv[])
{
	int chan1 = 1;
	int chan2 = 2;

	CHANNEL ch = C1;

	lecroy chanOne(chan1);

	lecroy chanTwo(chan2);

	chanOne.initialise();
	chanTwo.initialise();

	// cout << "Get Time offset : " << chanOne.getTimeOffset() << endl; 

	
	// Set up Trigger
	chanOne.setTrigMode(); // Sets trigger mode to single
	double trig_lev = 0.4;
	chanOne.setTrigLev(trig_lev);
	SLOPE t_slope = Pos;
	chanOne.setTrigSlope(t_slope);

	// Set voltage per division
	double voltsetting = 0.50; 
	chanOne.setVoltageDiv(voltsetting);
	chanTwo.setVoltageDiv(voltsetting); 

	// Set vertical offset 
	double v_offset = voltsetting*-3; //voltsetting*3;
	chanOne.setVerticalOffset(v_offset);
	chanTwo.setVerticalOffset(v_offset);
	double offset = chanOne.getVerticalOffset();
	// cout << "Offset is " << offset << endl;

	
	int runs = 3000;
	double max_values[3000][2];

	for (int i = 0; i < runs; i++)
	{
		// Arm channel one for trigger
		chanOne.scopeArm();
		chanOne.scopeWait();

		// Check channel 2 for pulse
		double max_chan1 = chanOne.queryMaximum();
		double max_chan2 = chanTwo.queryMaximum();

		max_values[i][1] = max_chan1;
		max_values[i][2] = max_chan2;

		if (max_chan2 > 0.4)
		{
			// Create some file
			cout << i << " : " << "Chan 1 Min : Chan 2 Min " << max_chan1 << " : " << max_chan2 << endl;
			char fstart[] = "C:/Users/astewart/Documents/Data/Coincidence/020315_30V_";
			char fend[] = ".txt";
			char filename[255];
			sprintf_s(filename, "%s%d%s", fstart, i, fend);

			ofstream fout (filename); // open file
	
			// Transfer data and save to file
			chanOne.grabData(); // Transfer channel 1 data
			chanTwo.grabData(); // Transfer channel 2 data
				
			for (unsigned int b = 0; b < chanOne.getVectorSize(); b++)
			{
				fout << chanTwo.getTimebaseElement(b) << '\t' 
					<< chanOne.getAmpElement(b) << '\t' 
					<< chanTwo.getAmpElement(b) << '\n'; // write data to text file
			}
			
			fout.close();
		
			chanOne.clearVectors(); // clear channel one vectors
			chanTwo.clearVectors(); // clear channel two vectors
		}
		else 
		{
			i--;
		}
	}

	ofstream fout2 ("C:/Users/astewart/Documents/Data/Coincidence/020315_amplitudes.txt"); // open file for amplitude values
	
	for (int j = 0; j < 3000; j++)
	{
		fout2 << max_values[j][1] << '\t' << max_values[j][2] << '\n'; // write amplitudes to file
	}

	fout2.close();

	return 0;
}

