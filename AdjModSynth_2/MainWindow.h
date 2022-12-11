/**
*	@file		MainWindow.h
*	@author		Nahum Budin
*	@date		16-Jan-2021
*	@version	1.1 
*				1. Adding Control Widgets control through Knob and Slider
*				2. Adding JACK parameters selection options |(Auto/Manual).
*	
*	Version	1.0		16-Oct-2018
*
*	@brief		Application Main Windowg.
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStatusBar>
#include <Qcheckbox>
#include <QSlider>
#include <QLayout>

#include "spreadsheet.h"

#include <string.h>

#include "NQgridWidget.h"

#include "MainMenue.h"
#include "MainTab.h"
#include "FluidSynthTab.h"
#include "OscilatorsTab.h"
#include "NoiseMsoTab.h"
#include "KpsPadTab.h"
#include "FiltAmpKbdTab.h"
#include "ModulatorsTab.h"
#include "EffectsTab.h"
#include "MidiMixerTab.h"
#include "WebTab.h"
#include "Osciloscope.h"


//#include "Dialog_FluidSynthSelectProgram.h"

#define _UPDATE_TIMER_MS	200

namespace Ui {
class MainWindow;
}


// Used for calling _MAIN_WINDOW methods as callbacks
void
updateUiWrapper();
void updateStatusDisplayTextWraper(std::string msg);
void setUtilizationWrapper(int ut);
void setLeftLevelWrapper(int lev);
void setRightLevelWrapper(int lev);
void updatePlotsWrapper(float *sigL, float *sigR, int size);

void updateModuleGuiWrapper(int moduleId);

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
	
	void setTrigers();
	void setWidgetsInfoMap();

	static MainWindow *getInstance();
	
	void startUpdateTimer(int interval);

	void setBTindication_set();
	void setBTindication_reset();
	
	void setSketchRadiobuttonsEnable(bool en);

	void setJackIndication_set();
	void setJackIndication_reset();

	void updateStatusDisplayText(std::string msg);
	void updateFluidSynthSettingsNameText(std::string msg);

	void update();
	
	void updateModuleGui(int moduleId);
	
	void setUtilization(int utl);
	int getUtilization();
	void setUtilizationBar(int ut);
	void setUtilizationBar();
	void setLeftLevel(int lev);
	void setRightLevel(int lev);
	void setLeftLevelMeter(int lev);
	void setRightLevelMeter(int lev);
	int getLeftLevel();
	int getRightLevel();
	
	void setCpuUtilization(int util);
	
	std::string getFileName(std::string fullpath);
	std::string removeFileExtention(std::string file_name);

	MainMenuHandling *mainMenu;
	MainTabUiHandling *main_tab;
	FluidSynthUiHandling *fluid_synth_tab;
	OscilatorsTabUiHandling *oscilators_tab;
	NoiseMsoTabUiHandling *noise_mso_tab;
	KspPadTabUiHandling *ksp_pad_tab;
	FiltAmpKbdTabUiHandling *filter_amp_kbd_tab;
	ModulatorsTabUiHandling *modulatorsTab;
	EffectsTabUiHandling *effectsTab;
	MidiMixerTabUiHandling *midiMixerTab;
	WebTabUiHandling *webTabUiHandling;
	
	Osciloscope *scopeL, *scopeR;
	
	// Common string to many tabs
	QList<QString> stringLfosList;
	QList<QString> stringEnvsList;

	// Holds all GUI controls widgets and Ids
	QMap<QWidget *, int> m_widgetsIdsMap;
	// Holds all GUI controls widgets and Types (Dial, Slider....)
	QMap<QWidget *, int> m_widgetsTypesMap;

	bool updateMSOwaveformPlot;

  public slots:
	virtual void updateGUI();  		// Called by a Timer
	
protected slots:	
	void MainVolumeChanged(int vol);	
	void PanicClicked(bool val);
	void Sketch1clicked(bool val);
	void Sketch2clicked(bool val);
	void Sketch3clicked(bool val);
	void ScopeSensitivityChanged(int sens);

	void focusChanged(QWidget *, QWidget *now);

  protected:
	void timerEvent(QTimerEvent *event);

private:
    Ui::MainWindow *ui;
	static MainWindow *mwind;

	volatile static int utilization, leftLevel, rightLevel;

	

//	std::vector<std::string> horizontalHeaders, verticalHeaders;
};

#endif // MAINWINDOW_H
