/**
* @file		Osciloscope.h
*	@author		Nahum Budin
*	@date		18-5-2020 (based on OsciloscopeDialog 20-Oct-2019)
*	@version	1.0
*
*	@brief		Displaying signal waveform.
*/

#ifndef _OSCILOSCOPE
#define _OSCILOSCOPE

#include "qcustomplot.h"

class Osciloscope
{
public:
	Osciloscope(QCustomPlot *plt = NULL);
	
	void setupPlot();
	void setSensitivity(int sens = 5.0);
	void updatePlotParams(float *sig = NULL, int size = -1);
	void redrawPlot();
	
private:
	int signalPlotDataSize = 0;
	float *sigData = NULL;
	float sensitivity = 1.0;
	
	QCustomPlot *plot;
};

#endif