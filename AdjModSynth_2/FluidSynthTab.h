/**
* @file		FluidSynthTab.h
*	@author		Nahum Budin
*	@date		16-Jan-2021
*	@version	1.1 
*				1. Adding Control Widgets control through Knob and Slider
*	
*	Version	1.0		20-Oct-2019
*
*	@brief		Fluid Synthesizer ui handling.
*/

#ifndef _FLUID_SYNTH_TAB
#define _FLUID_SYNTH_TAB

#include <Ui_MainWindow.h>

#include "libAdjHeartModSynth_2.h"

#include "Dialog_FluidSynthSelectProgram.h"

#include "NQgridWidget.h"
#include "NQgridWidgetItem.h"


void onRowDoubleClickWraper(int *row, int *col);


class FluidSynthUiHandling : public QMainWindow
{

	Q_OBJECT

public:
	FluidSynthUiHandling(Ui_MainWindow *mainWind);

	static FluidSynthUiHandling *getInstance();

	void setTrigers();

	void setWidgetsInfoMap();

	void update();

protected slots:
	void FluidVolumeChanged(int vol);
	void ReverbRoomSizeChanged(int val);
	void ReverbDampChanged(int val);
	void ReverbWidthChanged(int val);
	void ReverbLevelChanged(int val);

	void ChorusNumberChanged(int val);
	void ChorusLevelChanged(int val);
	void ChorusSpeedChanged(int val);
	void ChorusDepthChanged(int val);
	void ChorusWaveformChanged(int val);

	void ReverbActivationChanged(bool val);
	void ChorusActivationChanged(bool val);

private:
	Ui_MainWindow *mainWindow;

	Dialog_FluidSynthSelectProgram *dialog_FluidSynthSelectProgram;

	static FluidSynthUiHandling *fluidSynthUiHandlingInstance;
	
	char mssg1[128] = { "" };

};



#endif


