/**
*	@file		MainWindow.cpp
*	@author		Nahum Budin
*	@date		16-Jan-2021
*	@version	1.1 
*				1. Adding Control Widgets control through Knob and Slider
*	
*	Version	1.0		16-Oct-2018
*
*	@brief		Application Main Windowg.
*/

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QMessageBox>
#include <qlabel.h>
#include <QThread>
#include <QFileDialog>
#include <QLayout>
#include <QPalette>
#include <time.h>

#include "spreadsheet.h"

#include "libAdjHeartModSynth_2.h"

// Used for calling _MAIN_WINDOW methods as callbacks
void updateUiWrapper() { MainWindow::getInstance()->update(); }
void updateFluidSynthSettingsNameTextWrapper(std::string msg) { MainWindow::getInstance()->updateFluidSynthSettingsNameText(msg); }
void updateStatusDisplayTextWraper(std::string msg) { MainWindow::getInstance()->updateStatusDisplayText(msg); }
void refreshChannelsTableWidgetWrapper(int chan, int prog) { MainWindow::getInstance()->main_tab->refreshChannelsTableWidget(); }
void setUtilizationWrapper(int ut) { MainWindow::getInstance()->setUtilization(ut); }
void setLeftLevelWrapper(int lev) { MainWindow::getInstance()->setLeftLevel(lev); }
void setRightLevelWrapper(int lev) { MainWindow::getInstance()->setRightLevel(lev); }
void updateModuleGuiWrapper(int moduleId) { MainWindow::getInstance()->updateModuleGui(moduleId); }


void updatePlotsWrapper(float *sigL, float *sigR, int size)
{
	MainWindow::getInstance()->scopeL->updatePlotParams(sigL, size);	
	MainWindow::getInstance()->scopeR->updatePlotParams(sigR, size);
}


MainWindow *MainWindow::mwind = NULL;
volatile int MainWindow::utilization, MainWindow::leftLevel, MainWindow::rightLevel;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	mwind = this;
	mwind->move(10, 10);

	QPixmap pixmap("./musical-keyboard.png");
	QIcon icon(pixmap);

	QApplication::setWindowIcon(icon);

	mainMenu = new MainMenuHandling(ui);	
	main_tab = new MainTabUiHandling(ui);
	fluid_synth_tab = new FluidSynthUiHandling(ui);
	oscilators_tab = new OscilatorsTabUiHandling(ui);
	noise_mso_tab = new NoiseMsoTabUiHandling(ui);
	ksp_pad_tab = new KspPadTabUiHandling(ui);
	filter_amp_kbd_tab = new FiltAmpKbdTabUiHandling(ui);
	modulatorsTab = new ModulatorsTabUiHandling(ui);
	effectsTab = new EffectsTabUiHandling(ui);
	midiMixerTab = new MidiMixerTabUiHandling(ui);
	webTabUiHandling = new WebTabUiHandling(ui);

	ui->tabWidgetMain->setCurrentIndex(0);

	scopeL = new Osciloscope(ui->widget_signalLeft);
	scopeR = new Osciloscope(ui->widget_signalRight);
	
	ui->widget_signalLeft->setStyleSheet("border: 10px solid black");
	ui->widget_signalRight->setStyleSheet("border: 10px solid black");
	
	utilization = 0;

	updateMSOwaveformPlot = false;

	setTrigers();
	setWidgetsInfoMap();

	// Connect other signals (triggers) and slots
	mainMenu->setTrigers();
	main_tab->setTrigers();
	fluid_synth_tab->setTrigers();
	oscilators_tab->setTrigers();
	noise_mso_tab->setTrigers();
	ksp_pad_tab->setTrigers();
	filter_amp_kbd_tab->setTrigers();
	modulatorsTab->setTrigers();
	effectsTab->setTrigers();
	midiMixerTab->setTrigers();
	
	// Map dial and sliders widgets to enable Knob and Slider control.	
	oscilators_tab->setWidgetsInfoMap();
	midiMixerTab->setWidgetsInfoMap();
	fluid_synth_tab->setWidgetsInfoMap();
	noise_mso_tab->setWidgetsInfoMap();
	filter_amp_kbd_tab->setWidgetsInfoMap();
	ksp_pad_tab->setWidgetsInfoMap();
	modulatorsTab->setWidgetsInfoMap();

	// Init common strings
	stringLfosList.append("-----");
	stringLfosList.append("LFO 1");
	stringLfosList.append("LFO 2");
	stringLfosList.append("LFO 3");
	stringLfosList.append("LFO 4");
	stringLfosList.append("LFO 5");
	stringLfosList.append("LFO 1 0.5s");
	stringLfosList.append("LFO 2 0.5s");
	stringLfosList.append("LFO 3 0.5s");
	stringLfosList.append("LFO 4 0.5s");
	stringLfosList.append("LFO 5 0.5s");
	stringLfosList.append("LFO 1 1.0s");
	stringLfosList.append("LFO 2 1.0s");
	stringLfosList.append("LFO 3 1.0s");
	stringLfosList.append("LFO 4 1.0s");
	stringLfosList.append("LFO 5 1.0s");
	stringLfosList.append("LFO 1 1.5s");
	stringLfosList.append("LFO 2 1.5s");
	stringLfosList.append("LFO 3 1.5s");
	stringLfosList.append("LFO 4 1.5s");
	stringLfosList.append("LFO 5 1.5s");
	stringLfosList.append("LFO 1 2.0s");
	stringLfosList.append("LFO 2 2.0s");
	stringLfosList.append("LFO 3 2.0s");
	stringLfosList.append("LFO 4 2.0s");
	stringLfosList.append("LFO 5 2.0s");
		
	stringEnvsList.append("-----");
	stringEnvsList.append("ENV 1");
	stringEnvsList.append("ENV 2");
	stringEnvsList.append("ENV 3");
	stringEnvsList.append("ENV 4");
	stringEnvsList.append("ENV 5");

	/// Callback Functions Registration
	register_callback_update_ui(&updateUiWrapper);
	register_callback_update_fluid_synth_settings_text(&updateFluidSynthSettingsNameTextWrapper);
	register_callback_midi_program_change_event(&refreshChannelsTableWidgetWrapper);
	register_callback_update_utilization_bar(&setUtilizationWrapper);
	register_callback_update_left_level(&setLeftLevelWrapper);
	register_callback_update_right_level(&setRightLevelWrapper);
	register_callback_update_signal_display(&updatePlotsWrapper);
	register_initiate_update_gui_callback(&updateModuleGuiWrapper);

	update();
	
	ui->actionOpen_AdjSyntPatch->setEnabled(true);
	ui->actionSave_AdjSynthPatch->setEnabled(true);
	ui->actionOpen_AdjSynthSettings->setEnabled(true);
	ui->actionSave_AdjSynthSettings->setEnabled(true);
	
	// start a periodic timer after this timeout - 
	startTimer(2000);
	
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setTrigers()
{
	// Connect main window signals (triggers) and slots
	connect(ui->horizontalSlider_masterVolume,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(MainVolumeChanged(int)));
	
	connect(ui->pushButton_panic,
		SIGNAL(toggled(bool)),
		this,
		SLOT(PanicClicked(bool)));
	
	connect(ui->radioButton_sketch_1,
		SIGNAL(clicked(bool)),
		this,
		SLOT(Sketch1clicked(bool)));
	
	connect(ui->radioButton_sketch_2,
		SIGNAL(clicked(bool)),
		this,
		SLOT(Sketch2clicked(bool)));
	
	connect(ui->radioButton_sketch_3,
		SIGNAL(clicked(bool)),
		this,
		SLOT(Sketch3clicked(bool)));
	
	connect(ui->verticalSlider_scope_sensitivity,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(ScopeSensitivityChanged(int)));

	connect(qApp, 
		SIGNAL(focusChanged(QWidget *, QWidget *)),
		this, 
		SLOT(focusChanged(QWidget *, QWidget *)));
}

void MainWindow::setWidgetsInfoMap()
{
	// Widgets Ids
	MainWindow::getInstance()->m_widgetsIdsMap.insert(ui->horizontalSlider_masterVolume, _MOD_SYNTH_EVENT * 10000 + _MASTER_VOLUME);

	// Widgets types
	MainWindow::getInstance()->m_widgetsTypesMap.insert(ui->horizontalSlider_masterVolume, _CONTROL_TYPE_SLIDER);
}

MainWindow *MainWindow::getInstance() {

	if (!mwind)
		mwind = new MainWindow();

	return mwind;
}

void MainWindow::focusChanged(QWidget *, QWidget *now)
{
	int module = -1, control = -1, type = -1;

	if (m_widgetsIdsMap.contains(now))
	{
		module = m_widgetsIdsMap.value(now) / 10000;
		control = m_widgetsIdsMap.value(now) - module * 10000;
	}

	if (m_widgetsTypesMap.contains(now))
	{
		type = m_widgetsTypesMap.value(now);
	}

	mod_synth_set_in_focus_module_control(module, control, type);
}

void MainWindow::startUpdateTimer(int interval)
{
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(updateGUI()));
	timer->start(interval);
}

void MainWindow::setCpuUtilization(int util)
{
	ui->label_cpuUtilization->setText(QString::number(util) + "%");
}

void MainWindow::setLeftLevel(int lev)
{
	leftLevel = lev;
	if (leftLevel < 0)
		leftLevel = 0;
	else if (leftLevel > 100)
		leftLevel = 100;
}

void MainWindow::setRightLevel(int lev)
{
	rightLevel = lev;
	if (rightLevel < 0)
		rightLevel = 0;
	else if (rightLevel > 100)
		rightLevel = 100;
}

int MainWindow::getLeftLevel() { return leftLevel; }
int MainWindow::getRightLevel() { return rightLevel; }

void MainWindow::setLeftLevelMeter(int lev)
{
	
	ui->progressBar_outSignalLeft->setValue(lev);
	
	QPalette p = ui->progressBar_outSignalLeft->palette();
	if (lev > 80)
	{
		p.setColor(QPalette::Highlight, QColor(Qt::red));
	}
	else
	{
		p.setColor(QPalette::Highlight, QColor(Qt::green));
	}
	ui->progressBar_outSignalLeft->setPalette(p);
}

void MainWindow::setRightLevelMeter(int lev)
{
	ui->progressBar_outSignalRight->setValue(lev);
	
	QPalette p = ui->progressBar_outSignalRight->palette();
	if (lev > 80)
	{
		p.setColor(QPalette::Highlight, QColor(Qt::red));
	}
	else
	{
		p.setColor(QPalette::Highlight, QColor(Qt::green));
	}
	ui->progressBar_outSignalRight->setPalette(p);
}

void MainWindow::updateGUI()
{
	static int prevCpuUtilization = 0, prevUtilization = 0;	
	static int prevLeftLevel = 0, prevRightLevel = 0;
	int util;
	
	util = getUtilization();
	
	if (util != prevUtilization)
	{
		setUtilizationBar();
		prevUtilization = util;
	}

	if (mod_synth_get_cpu_utilization() != prevCpuUtilization)
	{
		setCpuUtilization(mod_synth_get_cpu_utilization());
		prevCpuUtilization = mod_synth_get_cpu_utilization();
	}
	
	if (getLeftLevel() != prevLeftLevel)
	{
		setLeftLevelMeter(getLeftLevel());
		prevLeftLevel = getLeftLevel();
	}
	
	if (getRightLevel() != prevRightLevel)
	{
		setRightLevelMeter(getRightLevel());
		prevRightLevel = getRightLevel();
	}
	
	if (mod_synth_get_midi_control_sequences_training_enabled())
	{
		Dialog_KbdControlMap::getInstance()->updateMappingDisplay();
	}

	if (updateMSOwaveformPlot)
	{
		// Update MSO waveform plot
		ui->customPlotMSOwaveform->replot();		
		updateMSOwaveformPlot = false;
	}

	if (ksp_pad_tab->update_plots)
	{
		ksp_pad_tab->update_plots = false;

		ksp_pad_tab->replotProfile();
		ksp_pad_tab->replotSpectrum();
	}

	

	scopeL->redrawPlot();
	scopeR->redrawPlot();
	
	modulatorsTab->timerUpdate();
}


/**
 * Set the BT ststus ui indication to active.
 * @param none
 * @return none
 */
void MainWindow::setBTindication_set() { ui->checkBox_BT_status->setChecked(true);  }

/**
 * Set the BT ststus ui indication to not active.
 * @param none
 * @return none
 */
void MainWindow::setBTindication_reset() { ui->checkBox_BT_status->setChecked(false); }

void MainWindow::setSketchRadiobuttonsEnable(bool en)
{
	ui->radioButton_sketch_1->setEnabled(en);
	ui->radioButton_sketch_2->setEnabled(en);
	ui->radioButton_sketch_3->setEnabled(en);
}

/**
 * Set the Jack connection ststus ui indication to active.
 * @param none
 * @return none
 */
void MainWindow::setJackIndication_set() { ui->checkBox_jack_status->setChecked(true); }

/**
 * Set the Jack connection ststus ui indication to not active.
 * @param none
 * @return none
 */
void MainWindow::setJackIndication_reset() { ui->checkBox_jack_status->setChecked(false); }

/**
 * Set a text message on the ststus bar. Message disappers after 20sec unless updated.
 * @param message string
 * @return none
 */
void MainWindow::updateStatusDisplayText(std::string mssg)
{
	ui->statusBar->showMessage(QString::fromStdString(mssg), 20000);
}

/**
 * Set the FluidSynth settings name text.
 * @param message string
 * @return none
 */
void MainWindow::updateFluidSynthSettingsNameText(std::string msg)
{
	std::string mssg = "Settings " + msg;
	ui->label_fluidTab_settingsName->setText(QString::fromStdString(mssg));
}

/**
 * Update all main window ui objects to.
 * @param none
 * @return none
 */
void MainWindow::update()
{
	static bool oneTimeInitialized = false;

	if (!oneTimeInitialized)
	{
		oneTimeInitialized = true;
		// Perform first time initialization of ui objects
		ui->radioButton_sketch_1->setChecked(true);
		
	}

	ui->horizontalSlider_masterVolume->blockSignals(true);
	ui->horizontalSlider_masterVolume->setValue(mod_synth_get_active_master_volume());
	ui->horizontalSlider_masterVolume->blockSignals(false);


	main_tab->update();
	fluid_synth_tab->update();
	oscilators_tab->update();
	noise_mso_tab->update();
	ksp_pad_tab->update();
	filter_amp_kbd_tab->update();
	modulatorsTab->update();
	effectsTab->update();
	midiMixerTab->update();
}

/**
 * Update specific module ui object.
 * @param moduleId	synth module GUI
 * @return none
 */
void MainWindow::updateModuleGui(int moduleId)
{
	switch (moduleId)
	{
		case _OSC_1_EVENT:
			oscilators_tab->update();	
			break;
				
		case _OSC_2_EVENT:
			oscilators_tab->update();	
			break;	
			
		case _LFO_1_EVENT:
		case _LFO_2_EVENT:
		case _LFO_3_EVENT:
		case _LFO_4_EVENT:
		case _LFO_5_EVENT:
		case _ENV_1_EVENT:
		case _ENV_2_EVENT:
		case _ENV_3_EVENT:
		case _ENV_4_EVENT:
		case _ENV_5_EVENT:
			modulatorsTab->update();
			break;

		case _FILTER_1_EVENT:
			filter_amp_kbd_tab->update();	
			break;
			
		case _FILTER_2_EVENT:
			filter_amp_kbd_tab->update();	
			break;
			
		case _AMP_CH1_EVENT:
			filter_amp_kbd_tab->update();	
			break;
			
		case _AMP_CH2_EVENT:
			filter_amp_kbd_tab->update();	
			break;
			
		case _KBD_1_EVENT:
			filter_amp_kbd_tab->update();	
			break;
			
		case _NOISE_1_EVENT:
			noise_mso_tab->update();	
			break;
			
		case _KARPLUS_1_EVENT:
			ksp_pad_tab->update_kps();	
			break;
			
		case _REVERB_EVENT:
			effectsTab->update();	
			break;
			
		case _DISTORTION_1_EVENT:
			effectsTab->update();	
			break;
			
		case _DISTORTION_2_EVENT:
			effectsTab->update();	
			break;		
			
		case _BAND_EQUALIZER_EVENT:
			effectsTab->update();	
			break;

		case _MSO_1_EVENT:
			noise_mso_tab->update();	
			break;

		case _MIDI_MAPPING_EVENT:
				
			break;

		case _PAD_1_EVENT:
			ksp_pad_tab->update_pad();	
			break;

		case _SEQUENCER_1_EVENT:
				
			break;

		case _RECORDER_1_EVENT:
				
			break;
				
		case _MIDI_MIXER_1_EVENT:
			midiMixerTab->update();	
			break;
				
		case _FLUID_SYNTH_1_EVENT:
			fluid_synth_tab->update();	
			break;
				
		case _MOD_SYNTH_EVENT:
			main_tab->update();
		
			ui->horizontalSlider_masterVolume->blockSignals(true);
			ui->horizontalSlider_masterVolume->setValue(mod_synth_get_active_master_volume());
			ui->horizontalSlider_masterVolume->blockSignals(false);
		
			break;
	}
}

/**
 * Set the DSP utilization value (used calc time out of block period time).
 * @param utl	DSP utilization value
 * @return void
 */
void MainWindow::setUtilization(int utl)
{
	if (utl < 0)
		utilization = 0;
	else if (utl > 100)
		utilization = 100;
	else
		utilization = utl;
}

/**
 * Return the DSP utilization value.
 * @param none
 * @return the DSP utilization value.
 */
int MainWindow::getUtilization() { return utilization; }

void MainWindow::setUtilizationBar(int ut)
{
	ui->progressBar_dspUtilization->setValue(ut);
		
}

void MainWindow::setUtilizationBar()
{
	ui->progressBar_dspUtilization->setValue(utilization);
	ui->label_dspUtilization->setText(QString::number(utilization) + "%");

	QPalette p = ui->progressBar_outSignalRight->palette();

	if (utilization > 80)
	{
		p.setColor(QPalette::Highlight, QColor(Qt::red));
	}
	else
	{
		p.setColor(QPalette::Highlight, QColor(Qt::green));
	}

	ui->progressBar_dspUtilization->setPalette(p);
}


void MainWindow::timerEvent(QTimerEvent *event)
{
	killTimer(event->timerId());
	startUpdateTimer(_UPDATE_TIMER_MS);
}








/**
 * A SLOT callback activated when the master-volume slider value is changed.
 * @param the new slider (volume) value.
 * @return none
 */
void MainWindow::MainVolumeChanged(int vol)
{
	char mssg[128];

	mod_synth_set_master_volume(vol);

	sprintf(mssg, "Master-volume %i", vol);
	updateStatusDisplayText(std::string(mssg));
}

/**
*   @brief  A SLOT callback ctivated when the Panic push button is cliked (turn off all sounds)
*   @param  none
*   @return void
*/
void MainWindow::PanicClicked(bool val)
{
	if (val)
	{
		ui->pushButton_panic->blockSignals(true);
		ui->pushButton_panic->setChecked(false);
		ui->pushButton_panic->blockSignals(false);

		mod_synth_panic_action();
	}
}

/**
*   @brief  A SLOT callback ctivated when the Sketch 1 Radio Button is cliked 
*   @param  none
*   @return void
*/
void MainWindow::Sketch1clicked(bool val)
{
	if (val)
	{
		mod_synth_set_active_sketch(_SKETCH_PROGRAM_1);
		update();
		// All notes off
		mod_synth_panic_action();
	}
}

/**
*   @brief  A SLOT callback ctivated when the Sketch 2 Radio Button is cliked 
*   @param  none
*   @return void
*/
void MainWindow::Sketch2clicked(bool val)
{
	if (val)
	{
		mod_synth_set_active_sketch(_SKETCH_PROGRAM_2);
		update();
		// All notes off
		mod_synth_panic_action();
	}
}

/**
*   @brief  A SLOT callback ctivated when the Sketch 3 Radio Button is cliked 
*   @param  none
*   @return void
*/
void MainWindow::Sketch3clicked(bool val)
{
	if (val)
	{
		mod_synth_set_active_sketch(_SKETCH_PROGRAM_3);
		update();
		// All notes off
		mod_synth_panic_action();
	}
}

/**
*   @brief  A SLOT callback ctivated when the scope sensitivity slider is changed 
*   @param  int sens  sensitivity 0-100 (0.5-16)
*   @return void
*/
void MainWindow::ScopeSensitivityChanged(int sens)
{
	char mssg[128];
	
	scopeL->setSensitivity(sens);
	scopeR->setSensitivity(sens);
	
	sprintf(mssg, "Osciloscope Sensitivity %.2f", 0.5f + sens / 4.0f);
	updateStatusDisplayText(std::string(mssg));
}


/**
* Extract file name from full path (file.ext)
*/
std::string MainWindow::getFileName(std::string fullpath)
{
	std::string name;
	int pos1, pos2;
	
	if (fullpath == "")
	{
		name = "";
	}
	else
	{
		pos2 = fullpath.size();
		pos1 = fullpath.find_last_of("/", pos2);
		if ((pos2 - pos1) >= 1)
		{
			name = fullpath.substr(pos1 + 1, pos2);
		}
		else
		{
			name = "";
		}		
	}	
	
	return name;
}

/**
* Extract file name without the extension or multiple extensions (no more ".")
*/
std::string MainWindow::removeFileExtention(std::string file_name)
{
	std::string name = file_name;
	int pos1 = name.size();

	if (file_name == "")
	{
		return "";
	}
	else
	{
		// Remove all .ext
		while(pos1 > 0)
		{
			pos1 = name.find_last_of(".", name.size());
			if (pos1 > 0)
			{
				name = name.substr(0, pos1);
			}
		}
	}

	return name;
}

