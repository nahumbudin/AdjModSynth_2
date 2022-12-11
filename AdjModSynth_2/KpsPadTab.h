/**
*	@file		KpsPadTab.h
*	@author		Nahum Budin
*	@date		12-Nov-2019
*	@version	1.0
*
*	@brief		Karplus Strong string and PAD synthesizers Tab ui handling.
*/

#ifndef _TAB_KSPPAD
#define _TAB_KSPPAD

#include <ui_MainWindow.h>
#include "qcustomplot.h"

class KspPadTabUiHandling : public QMainWindow 
{
	Q_OBJECT
		
public :
	
	KspPadTabUiHandling(Ui_MainWindow *mainWind);
	
	static KspPadTabUiHandling *getInstance();

	void setTrigers();
	void setWidgetsInfoMap();

	void setupMsoPlot(QCustomPlot *customPlot);

	void update_kps();
	void update_pad();

	void replotProfile();
	void replotSpectrum();

	// When set, main window update timer will update the plots
	bool update_plots;

  protected slots:

	void karplusExcitationWaveformChanged(int val);
	void karplusExcitationWaveformVariationsChanged(int val);
	void karplusStringDampingChanged(int val);
	void karplusStringDampingVariationChanged(int val);
	void karplusStringDampingCalcModeChanged(int val);
	void karplusPluckDampingChanged(int val);
	void karplusPluckDampingVariationChanged(int val);
	void karplusOnDecayChanged(int val);
	void karplusOffDecayChanged(int val);
	void karplusSendFilter1Changed(int val);
	void karplusSendFilter2Changed(int val);
	
	void karplusEnableChanged(bool val);
	
	void padEnableChanged(bool val);

	void padDetuneOctaveChanged(int val);
	void padDetuneSeminotesChanged(int val);
	void padDetuneCentsChanged(int val);
	void padSendFilter1Changed(int val);
	void padSendFilter2Changed(int val);
	void padFreqModLfoChanged(int val);
	void padFreqModLevelLfoChanged(int val);
	void padFreqModEnvChanged(int val);
	void padFreqModLevelEnvChanged(int val);
	void padAmpModLfoChanged(int val);
	void padAmpModLevelLfoChanged(int val);
	void padAmpModEnvChanged(int val);
	void padAmpModLevelEnvChanged(int val);

	void padQualityChanged(int val);
	void padBaseNoteChanged(int val);
	void padBaseWidthChanged(int val);
	void padShapeChanged(int val);
	void padShapeCutoffChanged(int val);
	void padGenerateClicked(bool val);

	void padHarmony1levelChanged(int val);
	void padHarmony2levelChanged(int val);
	void padHarmony3levelChanged(int val);
	void padHarmony4levelChanged(int val);
	void padHarmony5levelChanged(int val);
	void padHarmony6levelChanged(int val);
	void padHarmony7levelChanged(int val);
	void padHarmony8levelChanged(int val);
	void padHarmony9levelChanged(int val);
	void padHarmony10levelChanged(int val);

	void padHarmoniesDetuneChanged(int val);
	
private:
	
	void setupProfilePlot(QCustomPlot *profilePlot);
	void setupSpectrumPlot(QCustomPlot *spectrumPlot);
	
	Ui_MainWindow *mainWindow;
	static KspPadTabUiHandling *kspPadTabUiHandling;
	
	bool karplus_enabled;
	bool pad_enabled;
	bool update_profile_plot;
	bool update_spectrum_plot;
	
	QList<QString> stringKarplusExcitationWaveformList;
	QList<QString> stringKarplusStringDampingCalcModeList; 
	
	QList<QString> stringQualitiesList;
	QList<QString> stringBaseNotesList;
	QList<QString> stringShapesList;
	QList<QString> stringShapeCutoffsList;
	
	char mssg1[128] = { "" };
};

#endif
