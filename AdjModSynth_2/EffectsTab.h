/**
*	@file		EffectsTab.h
*	@author		Nahum Budin
*	@date		15-Nov-2019
*	@version	1.0
*
*	@brief		Effects (Reverb, Distortion and Band Equilizer) Tab ui handling.
*/

#ifndef _TAB_EFFECTS
#define _TAB_EFFECTS

#include <ui_MainWindow.h>


class EffectsTabUiHandling : public QMainWindow 
{
	Q_OBJECT
		
public :
	
	EffectsTabUiHandling(Ui_MainWindow *mainWind);
	
	static EffectsTabUiHandling *getInstance();

	void setTrigers();

	void update();

protected slots:	
	// Freeverb 3 modified
	void reverb3MenableChanged(bool val);
	void reverbTypeSelected(int val);

	// Freverb
	void reverbEnableChanged(bool val);
	void reverbRoomSizeChanged(int val);
	void reverbDampChanged(int val);
	void reverbWetChanged(int val);
	void reverbDryChanged(int val);
	void reverbWidthChanged(int val);
	void reverbModeChanged(int val);
	
	// Distortion
	void distortionEnableChanged(bool val);
	void distortionAutoGainChanged(bool val);
	void distortion1driveChanged(int val);
	void distortion1rangeChanged(int val);
	void distortion1blendChanged(int val);
	void distortion2driveChanged(int val);
	void distortion2rangeChanged(int val);
	void distortion2blendChanged(int val);	
	
	// Band Equilizer
	void bandEquilizerBand31Changed(int val);
	void bandEquilizerBand62Changed(int val);
	void bandEquilizerBand125Changed(int val);
	void bandEquilizerBand250Changed(int val);
	void bandEquilizerBand500Changed(int val);
	void bandEquilizerBand1KChanged(int val);
	void bandEquilizerBand2KChanged(int val);
	void bandEquilizerBand4KChanged(int val);
	void bandEquilizerBand8KChanged(int val);
	void bandEquilizerBand16KChanged(int val);
	
	void bandEquilizerBandPresetChanged(int val);
	void bandEquilizerSetAllZeroClicked(bool val);	
	
private:	
	Ui_MainWindow *mainWindow;
	static EffectsTabUiHandling *effectsTabUiHandling;
	
	QList<QString> stringReverbModeList;
	
	char mssg1[128] = { "" };	
};

#endif