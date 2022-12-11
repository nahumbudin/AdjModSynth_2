/**
* @file		Osciloscope.cpp
*	@author		Nahum Budin
*	@date		18-5-2020 (based on OsciloscopeDialog 20-Oct-2019)
*	@version	1.0
*
*	@brief		Displaying signal waveform.
*/

#include "Osciloscope.h"

Osciloscope::Osciloscope(QCustomPlot *plt)
{
	if (plt != NULL)
	{
		plot = plt;
		
		QPen pen;
		pen.setStyle(Qt::SolidLine);
		pen.setWidth(2);
		pen.setColor(QColor("#0080FF"));
		plot->addGraph();
		plot->graph(0)->setPen(pen);
		plot->addGraph();
		
		plot->xAxis->setVisible(false);
		plot->xAxis->setTickLabels(true);
		plot->yAxis->setVisible(false);
		plot->yAxis->setTickLabels(true);
		
		plot->yAxis->setRange(-1.0 , 1.0);	
		
		plot->setBackground(QBrush(QColor("#929292")));
		
		sensitivity = 0.5f + 50.0/4.0; // mid range
	}
}

void Osciloscope::setupPlot()
{
	if ((signalPlotDataSize > 0) && (sigData != NULL) && (plot != NULL))
	{
		QVector<double> x(signalPlotDataSize + 1), y0(signalPlotDataSize + 1);
		for (int i = 0; i < signalPlotDataSize; ++i)
		{
			x[i] = i;
			y0[i] = *(sigData + i) * sensitivity;
		}
		// pass data points to graphs:
		plot->graph(0)->setData(x, y0);
		plot->xAxis->setRange(0, signalPlotDataSize);
	}
}

void Osciloscope::setSensitivity(int sens)
{
	if ((sens >= 0) && (sens <= 100))
	{
		// 0.5 - 25.5
		sensitivity = 0.5f + sens / 4.0f;
	}
}

void Osciloscope::updatePlotParams(float *sig, int size)
{
	if ((sig != NULL) && (size >= 0))
	{
		sigData = sig;
		signalPlotDataSize = size;
	}
}

void Osciloscope::redrawPlot()
{
	setupPlot();

	if (plot != NULL)
	{
		plot->replot();
	}
}
