/**
*	@file		NoiseMsoTab.h
*	@author		Nahum Budin
*	@date		16-Jan-2021
*	@version	1.1 
*				1. Adding Control Widgets control through Knob and Slider
*	
*	Version	1.0		11-Nov-2019
*
*	@brief		Noise and MSO Tab ui handling.
*/

#ifndef _TAB_NOISEMSO
#define _TAB_NOISEMSO

#include <ui_MainWindow.h>
#include "qcustomplot.h"

class NoiseMsoTabUiHandling : public QMainWindow 
{
	Q_OBJECT
		
public :
	
	NoiseMsoTabUiHandling(Ui_MainWindow *mainWind);
	
	static NoiseMsoTabUiHandling *getInstance();

	void setTrigers();

	void setWidgetsInfoMap();
	
	void setupMsoPlot(QCustomPlot *customPlot);

	void update();

	void updateMSOwaveformPlot();

	Ui_MainWindow *mainWindow;

  protected slots:
	void noiseColorChanged(int val);
	void noiseSendFilter1Changed(int val);
	void noiseSendFilter2Changed(int val);
	void noiseAmpModLfoChanged(int val);
	void noiseAmpModLevelLfoChanged(int val);
	void noiseAmpModEnvChanged(int val);
	void noiseAmpModLevelEnvChanged(int val);
	void noiseEnableChanged(bool val);
	
	void point_a_moved(int val);
	void point_b_moved(int val);
	void point_c_moved(int val);
	void point_d_moved(int val);
	void point_e_moved(int val);
	void point_f_moved(int val);

	void symetryChanged(int val);

	void msoDetuneOctaveChanged(int val);
	void msoDetuneSeminotesChanged(int val);
	void msoDetuneCentsChanged(int val);
	void msoSendFilter1Changed(int val);
	void msoSendFilter2Changed(int val);
	void msoFreqModLfoChanged(int val);
	void msoFreqModLevelLfoChanged(int val);
	void msoFreqModEnvChanged(int val);
	void msoFreqModLevelEnvChanged(int val);
	void msoPwmModLfoChanged(int val);
	void msoPwmModLevelLfoChanged(int val);
	void msoPwmModEnvChanged(int val);
	void msoPwmModLevelEnvChanged(int val);
	void msoAmpModLfoChanged(int val);
	void msoAmpModLevelLfoChanged(int val);
	void msoAmpModEnvChanged(int val);
	void msoAmpModLevelEnvChanged(int val);

	void msoPresetChanged(int val);
	
	void msoEnableChanged(bool val);

private:
	
	void handlePresetChange(int newPres);
	void setPositions(const int pos[]);
	
	static NoiseMsoTabUiHandling *noiseMsoTabUiHandling;
	
	bool noise_enabled;
	bool mso_enabled;
	bool updateMsoPlot;
	
	QList<QString> stringNoiseColorsList;
	QList<QString> stringMsoPresetList;
	char mssg1[128] = { "" };
};

#endif