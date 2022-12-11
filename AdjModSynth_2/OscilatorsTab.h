/**
* @file		OscilatorsTab.h
*	@author		Nahum Budin
*	@date		16-Jan-2021
*	@version	1.1 
*				1. Adding Control Widgets control through Knob and Slider
*	
*	Version	1.0		9-Nov-2019
*
*	@brief		Oscilators Tab ui handling.
*/

#ifndef _TAB_OSCILATORS
#define _TAB_OSCILATORS

#include <ui_MainWindow.h>


class OscilatorsTabUiHandling : public QMainWindow 
{
	Q_OBJECT
		
public :
	
	OscilatorsTabUiHandling(Ui_MainWindow *mainWind);
	
	static OscilatorsTabUiHandling *getInstance();

	void setTrigers();

	void setWidgetsInfoMap();

	void update();
	
	void osc1enDisSliders(uint16_t mask);
	void osc1SetUnisonMode(int mode);
	void osc1setUnisonLabales(QList<QString> str, uint16_t mask);
	void osc1setUnisonLabales(int mode);

	
public slots :
	void osc1unisonModeSelected(int val);

protected slots :
	void osc1waveformSelected(int val);
	void osc1symmetryChanged(int val);
	void osc1detuneOctaveChanged(int val);
	void osc1detuneSeminotesChanged(int val);
	void osc1detuneCentsChanged(int val);
	void osc1SendFilter1Changed(int val);
	void osc1SendFilter2Changed(int val);
	void osc1FreqModLfoChanged(int val);
	void osc1FreqModLevelLfoChanged(int val);
	void osc1FreqModEnvChanged(int val);
	void osc1FreqModLevelEnvChanged(int val);
	void osc1PwmModLfoChanged(int val);
	void osc1PwmModLevelLfoChanged(int val);
	void osc1PwmModEnvChanged(int val);
	void osc1PwmModLevelEnvChanged(int val);
	void osc1AmpModLfoChanged(int val);
	void osc1AmpModLevelLfoChanged(int val);
	void osc1AmpModEnvChanged(int val);
	void osc1AmpModLevelEnvChanged(int val);
	void osc1hammondModeSelected(int val);
	void osc1unisonDistortionChanged(int val);
	void osc1unisonLev1Changed(int val);
	void osc1unisonLev2Changed(int val);
	void osc1unisonLev3Changed(int val);
	void osc1unisonLev4Changed(int val);
	void osc1unisonLev5Changed(int val);
	void osc1unisonLev6Changed(int val);
	void osc1unisonLev7Changed(int val);
	void osc1unisonLev8Changed(int val);
	void osc1unisonLev9Changed(int val);
	void osc1unisonDetuneChanged(int val);
	void osc1unisonSquareChanges(bool val);
	void osc1EnableChanged(bool val);
	
	void osc2waveformSelected(int val);
	void osc2symmetryChanged(int val);
	void osc2detuneOctaveChanged(int val);
	void osc2detuneSeminotesChanged(int val);
	void osc2detuneCentsChanged(int val);
	void osc2SendFilter1Changed(int val);
	void osc2SendFilter2Changed(int val);
	void osc2FreqModLfoChanged(int val);
	void osc2FreqModLevelLfoChanged(int val);
	void osc2FreqModEnvChanged(int val);
	void osc2FreqModLevelEnvChanged(int val);
	void osc2PwmModLfoChanged(int val);
	void osc2PwmModLevelLfoChanged(int val);
	void osc2PwmModEnvChanged(int val);
	void osc2PwmModLevelEnvChanged(int val);
	void osc2AmpModLfoChanged(int val);
	void osc2AmpModLevelLfoChanged(int val);
	void osc2AmpModEnvChanged(int val);
	void osc2AmpModLevelEnvChanged(int val);
	void osc2syncOsc1Changed(bool val);
	void osc2EnableChanged(bool val);
	
	
private :
	Ui_MainWindow *mainWindow;
	static OscilatorsTabUiHandling *oscilatorsTabUiHandling;
	
	bool osc1enabled;
	bool osc2enabled;
	
	QSlider **unisonLevelSliders;

	QList<QString> stringWaveformsList;
	QList<QString> stringUnisonModesList;
	QList<QString> stringHammondModesList;

	QList<QString> stringUnisonLabelsHarmonized;
	QList<QString> stringUnisonLabelsHammond;
	QList<QString> stringUnisonLabelsOctaves;
	QList<QString> stringUnisonLabelsCchord;
	QList<QString> stringUnisonLabelsCmChord;
	QList<QString> stringUnisonLabelsC7chord;
	QList<QString> stringUnisonLabelsCm7chord;

	char mssg1[128] = { "" };
		
};


#endif

