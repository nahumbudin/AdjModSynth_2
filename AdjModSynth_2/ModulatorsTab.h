/**
*	@file		ModulatorsTab.h
*	@author		Nahum Budin
*	@date		14-Nov-2019
*	@version	1.0
*
*	@brief		Modulators (LFOs Envelope (ADSR) generators) Tab ui handling.
*/

#ifndef _TAB_MODULATORS
#define _TAB_MODULATORS

#include <ui_MainWindow.h>

#define _ADSR_CURVE_START_POINT					10
#define _ADSR_CURVE_TIME_MULTIPLIER				10		// 10 pixels per second
#define _ADSR_CURVE_SUSTAIN_SEGMENT_LENGTH		40
#define _ADSR_CURVE_HEIGHT						100

#define _ADSR_CURVE_VIEW_WIDGET_SHOW_TIME_SEC	5


class ModulatorsTabUiHandling : public QMainWindow 
{
	Q_OBJECT
		
public :
	
	ModulatorsTabUiHandling(Ui_MainWindow *mainWind);
	
	static ModulatorsTabUiHandling *getInstance();

	void setTrigers();
	void setWidgetsInfoMap();

	void update();
	void timerUpdate();

protected slots:
	
	void mod1AttackLevelChanged(int val);
	void mod1DecayLevelChanged(int val);
	void mod1ReleaseLevelChanged(int val);
	void mod1SustainLevelChanged(int val);

	void mod2AttackLevelChanged(int val);
	void mod2DecayLevelChanged(int val);
	void mod2ReleaseLevelChanged(int val);
	void mod2SustainLevelChanged(int val);

	void mod3AttackLevelChanged(int val);
	void mod3DecayLevelChanged(int val);
	void mod3ReleaseLevelChanged(int val);
	void mod3SustainLevelChanged(int val);
	
	void mod4AttackLevelChanged(int val);
	void mod4DecayLevelChanged(int val);
	void mod4ReleaseLevelChanged(int val);
	void mod4SustainLevelChanged(int val);
	
	void mod5AttackLevelChanged(int val);
	void mod5DecayLevelChanged(int val);
	void mod5ReleaseLevelChanged(int val);
	void mod5SustainLevelChanged(int val);
	
	void mod1LfoWaveformChanged(int val);
	void mod1LfoSymmetryChanged(int val);
	void mod1LfoRateChanged(int val);

	void mod2LfoWaveformChanged(int val);
	void mod2LfoSymmetryChanged(int val);
	void mod2LfoRateChanged(int val);

	void mod3LfoWaveformChanged(int val);
	void mod3LfoSymmetryChanged(int val);
	void mod3LfoRateChanged(int val);
	
	void mod4LfoWaveformChanged(int val);
	void mod4LfoSymmetryChanged(int val);
	void mod4LfoRateChanged(int val);
	
	void mod5LfoWaveformChanged(int val);
	void mod5LfoSymmetryChanged(int val);
	void mod5LfoRateChanged(int val);	
	
private:	
	
	void setAdsrViewWidgetPoints();
	void refreshAdsrCurveView();
	
	
	Ui_MainWindow *mainWindow;
	static ModulatorsTabUiHandling *modulatorsTabUiHandling;
	
	QList<QString> stringLfosWaveformsList;
	
	QCustomPlot *plot;
	
	int plotLength;
	
	char mssg1[128] = { "" };
	
	int lastModifiedAdsr = _ENV_NONE;
	
	int adsrViewWidgetAttack;
	int adsrViewWidgetDecay;
	int adsrViewWidgetSustain;
	int adsrViewWidgetRelease;
	
	int adsrCurveAttackEndPoint;
	int adsrCurveDecayEndPoint;
	int adsrCurveSustainEndPoint;
	int adsrCurveReleaseEndPoint;
	
	int adsrCurveMaxAttack;
	int adsrCurveMaxDecay;
	int adsrCurveMaxSustain;
	int adsrCurveMaxRelease;
	
	int adsrViewGadgetTimer;
	
};

#endif

