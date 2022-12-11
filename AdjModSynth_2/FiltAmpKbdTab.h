/**
*	@file		FiltAmpKbdTab.h
*	@author		Nahum Budin
*	@date		12-Nov-2019
*	@version	1.0
*
*	@brief		Filters, Amplifier and Keyboard Tab ui handling.
*/

#ifndef _TAB_FLTAMPKBD
#define _TAB_FLTAMPKBD

#include <ui_MainWindow.h>
#include "qcustomplot.h"

#include "Dialog_KbdControlMap.h"

class FiltAmpKbdTabUiHandling : public QMainWindow 
{
	Q_OBJECT
		
public :
	
	FiltAmpKbdTabUiHandling(Ui_MainWindow *mainWind);
	
	static FiltAmpKbdTabUiHandling *getInstance();

	void setTrigers();
	void setWidgetsInfoMap();

	void update();

protected slots:
	
	void filter1freqChanged(int val);
	void filter1Qchanged(int val);
	void filter1octChanged(int val);
	void filter1kbdTrackChanged(int val);
	void filter1bandChanged(int val);
	void filter1FreqModLfoChanged(int val);
	void filter1FreqModLevelLfoChanged(int val);
	void filter1FreqModEnvChanged(int val);
	void filter1FreqModLevelEnvChanged(int val);

	void filter2freqChanged(int val);
	void filter2Qchanged(int val);
	void filter2octChanged(int val);
	void filter2kbdTrackChanged(int val);
	void filter2bandChanged(int val);
	void filter2FreqModLfoChanged(int val);
	void filter2FreqModLevelLfoChanged(int val);
	void filter2FreqModEnvChanged(int val);
	void filter2FreqModLevelEnvChanged(int val);
	void filter2trackFilter1Changed(bool val);
	
	void amp1LevelChanged(int val);
	void amp1PanChanged(int val);
	void amp1SendChanged(int val);
	void amp1PanModLfoChanged(int val);
	void amp1PanModLevelLfoChanged(int val);

	void amp2LevelChanged(int val);
	void amp2PanChanged(int val);
	void amp2SendChanged(int val);
	void amp2PanModLfoChanged(int val);
	void amp2PanModLevelLfoChanged(int val);

	void fixedChanged(bool val);
	
	void kbdPortamentoLevelChanged(int val);
	void kbdPortamentoEnableChanged(bool val);
	void kbdSensitivityChanged(int val);
	void kbdLowSensitivityChanged(int val);
	void kbdSplitChanged(int Val);
	void kbdControlsMapCliked(bool Val);
	void polyFifoClicked(bool val);
	void polyLimitClicked(bool val);
	void polyReuseClicked(bool val);	
	
private:
	
	Ui_MainWindow *mainWindow;
	static FiltAmpKbdTabUiHandling *filtAmpKbdTabUiHandling;
	
	bool mapKbdControlDialogShown;
	Dialog_KbdControlMap *dialog_KbdControlMap;
	
	bool filter2FollowsFilter1;

	QList<QString> stringFilterBandsList;
	QList<QString> stringKeyboardSlipList;
	
	char mssg1[128] = { "" };
	
};

#endif
