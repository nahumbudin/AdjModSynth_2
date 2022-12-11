/**
* @file		FluidSynthTab.cpp
*	@author		Nahum Budin
*	@date		16-Jan-2021
*	@version	1.1 
*				1. Adding Control Widgets control through Knob and Slider
*	
*	Version	1.0		20-Oct-2019
*
*	@brief		Fluid Synthesizer ui handling.
*/

#include "MainWindow.h"
#include "FluidSynthTab.h"
#include "libAdjHeartModSynth_2.h"

#include <QFileDialog>
#include <QMessageBox>

#include <QWebView>


extern "C" {

#include <glib-2.0/glib.h>
#include <glib-2.0/glib/galloca.h>
}



FluidSynthUiHandling *FluidSynthUiHandling::fluidSynthUiHandlingInstance = NULL;

/** Constructor */
FluidSynthUiHandling::FluidSynthUiHandling(Ui_MainWindow *mainWind)
{
	mainWindow = mainWind;	

	fluidSynthUiHandlingInstance = this;
	

}

/**
*   @brief  Returns the instance of this class.
*   @param  none
*   @return the instance of this class
*/
FluidSynthUiHandling *FluidSynthUiHandling::getInstance()
{
	return fluidSynthUiHandlingInstance;
}





/**
*   @brief  Connect all Signals to their Slots
*   @param  none
*   @return void
*/
void FluidSynthUiHandling::setTrigers()
{
	connect(mainWindow->verticalSlider_master_mixer_fluidVolume,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(FluidVolumeChanged(int)));
	
	connect(mainWindow->dial_fluidTab_reverbRoom,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(ReverbRoomSizeChanged(int)));

	connect(mainWindow->dial_fluidTab_reverbDamp,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(ReverbDampChanged(int)));

	connect(mainWindow->dial_fluidTab_reverbWidth,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(ReverbWidthChanged(int)));

	connect(mainWindow->dial_fluidTab_reverbLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(ReverbLevelChanged(int)));

	connect(mainWindow->dial_fluidTab_chorusN,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(ChorusNumberChanged(int)));

	connect(mainWindow->dial_fluidTab_chorusLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(ChorusLevelChanged(int)));

	connect(mainWindow->dial_fluidTab_chorusSpeed,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(ChorusSpeedChanged(int)));

	connect(mainWindow->dial_fluidTab_chorusDepth,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(ChorusDepthChanged(int)));

	connect(mainWindow->comboBox_fluidTab_chorusWaveform,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(ChorusWaveformChanged(int)));

	connect(mainWindow->checkBox_fluidTab_reverbActive,
		SIGNAL(toggled(bool)),
		this,
		SLOT(ReverbActivationChanged(bool)));

	connect(mainWindow->checkBox_fluidTab_chorusActive,
		SIGNAL(toggled(bool)),
		this,
		SLOT(ChorusActivationChanged(bool)));

//	connect(mainWindow->pushButton_fluidTab_refersh,
//		SIGNAL(toggled(bool)),
//		this,
//		SLOT(ChannelsTableRefreshClicked(bool)));
}

void FluidSynthUiHandling::setWidgetsInfoMap()
{
	// Widgets Ids
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_fluidTab_reverbRoom, _FLUID_SYNTH_1_EVENT * 10000 + _FLUID_SYNTH_REVERB_ROOM_SIZE);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_fluidTab_reverbDamp, _FLUID_SYNTH_1_EVENT * 10000 + _FLUID_SYNTH_REVERB_DAMP);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_fluidTab_reverbWidth, _FLUID_SYNTH_1_EVENT * 10000 + _FLUID_SYNTH_REVERB_WIDTH);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_fluidTab_reverbLevel, _FLUID_SYNTH_1_EVENT * 10000 + _FLUID_SYNTH_REVERB_LEVEL);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_fluidTab_chorusN, _FLUID_SYNTH_1_EVENT * 10000 + _FLUID_SYNTH_CHORUS_NUMBER);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_fluidTab_chorusLevel, _FLUID_SYNTH_1_EVENT * 10000 + _FLUID_SYNTH_CHORUS_LEVEL);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_fluidTab_chorusSpeed, _FLUID_SYNTH_1_EVENT * 10000 + _FLUID_SYNTH_CHORUS_SPEED);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_fluidTab_chorusDepth, _FLUID_SYNTH_1_EVENT * 10000 + _FLUID_SYNTH_CHORUS_DEPTH);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->verticalSlider_master_mixer_fluidVolume, _FLUID_SYNTH_1_EVENT * 10000 + _FLUID_SYNTH_VOLUME);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->checkBox_enableFluidSynth, _FLUID_SYNTH_1_EVENT * 10000 + _FLUID_SYNTH_ENABLE);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->checkBox_fluidTab_chorusActive, _FLUID_SYNTH_1_EVENT * 10000 + _FLUID_SYNTH_CHORUS_ENABLE);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->checkBox_fluidTab_reverbActive, _FLUID_SYNTH_1_EVENT * 10000 + _FLUID_SYNTH_REVERB_ENABLE);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->comboBox_fluidTab_chorusWaveform, _FLUID_SYNTH_1_EVENT * 10000 + _FLUID_SYNTH_CHORUS_WAVEFORM);
	

	// Widgets types
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_fluidTab_reverbRoom, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_fluidTab_reverbDamp, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_fluidTab_reverbWidth, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_fluidTab_reverbLevel, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_fluidTab_chorusN, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_fluidTab_chorusLevel, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_fluidTab_chorusSpeed, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_fluidTab_chorusDepth, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->verticalSlider_master_mixer_fluidVolume, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->checkBox_enableFluidSynth, _CONTROL_TYPE_CHECK);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->checkBox_fluidTab_chorusActive, _CONTROL_TYPE_CHECK);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->checkBox_fluidTab_reverbActive, _CONTROL_TYPE_CHECK);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->comboBox_fluidTab_chorusWaveform, _CONTROL_TYPE_LIST);
}

/**
*   @brief  Update the fluid synthesizer tab UI
*   @param  none
*   @return void
*/
void FluidSynthUiHandling::update()
{
	static bool oneTimeInitialized = false;

	if (!oneTimeInitialized)
	{
		oneTimeInitialized = true;
		// Perform first time initialization of ui objects
		mainWindow->comboBox_fluidTab_chorusWaveform->blockSignals(true);
		mainWindow->comboBox_fluidTab_chorusWaveform->addItem("Sine");
		mainWindow->comboBox_fluidTab_chorusWaveform->addItem("Triangle");
		mainWindow->comboBox_fluidTab_chorusWaveform->blockSignals(false);
	}
	
	mainWindow->verticalSlider_master_mixer_fluidVolume->blockSignals(true);
	mainWindow->verticalSlider_master_mixer_fluidVolume->setValue(mod_synth_get_active_fluid_synth_volume());
	mainWindow->verticalSlider_master_mixer_fluidVolume->blockSignals(false);

	mainWindow->dial_fluidTab_reverbRoom->blockSignals(true);
	mainWindow->dial_fluidTab_reverbRoom->setValue(mod_synth_get_active_fluid_synth_reverb_room_size());
	mainWindow->dial_fluidTab_reverbRoom->blockSignals(false);

	mainWindow->dial_fluidTab_reverbDamp->blockSignals(true);
	mainWindow->dial_fluidTab_reverbDamp->setValue(mod_synth_get_active_fluid_synth_reverb_damp());
	mainWindow->dial_fluidTab_reverbDamp->blockSignals(false);

	mainWindow->dial_fluidTab_reverbWidth->blockSignals(true);
	mainWindow->dial_fluidTab_reverbWidth->setValue(mod_synth_get_active_fluid_synth_reverb_width());
	mainWindow->dial_fluidTab_reverbWidth->blockSignals(false);

	mainWindow->dial_fluidTab_reverbLevel->blockSignals(true);
	mainWindow->dial_fluidTab_reverbLevel->setValue(mod_synth_get_active_fluid_synth_reverb_level());
	mainWindow->dial_fluidTab_reverbLevel->blockSignals(false);

	mainWindow->dial_fluidTab_chorusN->blockSignals(true);
	mainWindow->dial_fluidTab_chorusN->setValue(mod_synth_get_active_fluid_synth_chorus_number());
	mainWindow->dial_fluidTab_chorusN->blockSignals(false);

	mainWindow->dial_fluidTab_chorusLevel->blockSignals(true);
	mainWindow->dial_fluidTab_chorusLevel->setValue(mod_synth_get_active_fluid_synth_chorus_level());
	mainWindow->dial_fluidTab_chorusLevel->blockSignals(false);

	mainWindow->dial_fluidTab_chorusSpeed->blockSignals(true);
	mainWindow->dial_fluidTab_chorusSpeed->setValue(mod_synth_get_active_fluid_synth_chorus_speed());
	mainWindow->dial_fluidTab_chorusSpeed->blockSignals(false);

	mainWindow->dial_fluidTab_chorusDepth->blockSignals(true);
	mainWindow->dial_fluidTab_chorusDepth->setValue(mod_synth_get_active_fluid_synth_chorus_depth());
	mainWindow->dial_fluidTab_chorusDepth->blockSignals(false);

	mainWindow->comboBox_fluidTab_chorusWaveform->blockSignals(true);
	mainWindow->comboBox_fluidTab_chorusWaveform->setCurrentIndex(mod_synth_get_active_fluid_synth_chorus_waveform());
	mainWindow->comboBox_fluidTab_chorusWaveform->blockSignals(false);

//	mainWindow->checkBox_fluidTab_reverbActive->blockSignals(true);
	mainWindow->checkBox_fluidTab_reverbActive->setChecked(mod_synth_get_active_fluid_synth_reverb_activation_state());
//	mainWindow->checkBox_fluidTab_reverbActive->blockSignals(false);

//	mainWindow->checkBox_fluidTab_chorusActive->blockSignals(true);
	mainWindow->checkBox_fluidTab_chorusActive->setChecked(mod_synth_get_active_fluid_synth_chorus_activation_state());
//	mainWindow->checkBox_fluidTab_chorusActive->blockSignals(false);

//	mainWindow->lineEdit_fluidTab_soundfont->blockSignals(true);
//	mainWindow->lineEdit_fluidTab_soundfont->setText(QString::fromStdString(mod_synth_get_fluid_synth_soundfont()));
//	mainWindow->lineEdit_fluidTab_soundfont->blockSignals(false);
}

/**
 * A SLOT callback activated when the fluid_synth-volume slider value is changed.
 * @param the new slider (volume) value.
 * @return none
 */
void FluidSynthUiHandling::FluidVolumeChanged(int vol)
{
	char mssg[128];

	mod_synth_set_fluid_synth_volume(vol);

	sprintf(mssg, "Fluid-synthesizer-volume %i", vol);
	updateStatusDisplayTextWraper(std::string(mssg));
}

/**
 * A SLOT callback activated when the fluid_synth reverb room size slider or spinbox value is changed.
 * @param the new slider or spiner value.
 * @return none
 */
void FluidSynthUiHandling::ReverbRoomSizeChanged(int val)
{
	sprintf(mssg1, "FluidSynth Reverb Room Size: %.2f", (float)val / 100.0);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	mod_synth_set_fluid_synth_reverb_room_size(val);
}

/**
 * A SLOT callback activated when the fluid_synth reverb damp slider or spinbox value is changed.
 * @param the new slider or spiner value.
 * @return none
 */
void FluidSynthUiHandling::ReverbDampChanged(int val)
{
	sprintf(mssg1, "FluidSynth Reverb Damp: %.2f", (float)val / 100.0);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	mod_synth_set_fluid_synth_reverb_damp(val);
}

/**
 * A SLOT callback activated when the fluid_synth reverb width slider or spinbox value is changed.
 * @param the new slider or spiner value.
 * @return none
 */
void FluidSynthUiHandling::ReverbWidthChanged(int val)
{
	sprintf(mssg1, "FluidSynth Reverb Width: %.2f", (float)val / 100.0);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	mod_synth_set_fluid_synth_reverb_width(val);
}

/**
 * A SLOT callback activated when the fluid_synth reverb level slider or spinbox value is changed.
 * @param the new slider or spiner value.
 * @return none
 */
void FluidSynthUiHandling::ReverbLevelChanged(int val)
{
	sprintf(mssg1, "FluidSynth Reverb Level: %.2f", (float)val / 100.0);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	mod_synth_set_fluid_synth_reverb_level(val);
}

/**
 * A SLOT callback activated when the fluid_synth chrus number slider or spinbox value is changed.
 * @param the new slider or spiner value.
 * @return none
 */
void FluidSynthUiHandling::ChorusNumberChanged(int val)
{
	sprintf(mssg1, "FluidSynth Chorus Number of Stages: %i", val);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	mod_synth_set_fluid_synth_chorus_number(val);
}

/**
 * A SLOT callback activated when the fluid_synth chrus level slider or spinbox value is changed.
 * @param the new slider or spiner value.
 * @return none
 */
void FluidSynthUiHandling::ChorusLevelChanged(int val)
{
	sprintf(mssg1, "FluidSynth Chorus Level: %.2f", (float)val / 10.0);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	mod_synth_set_fluid_synth_chorus_level(val);
}

/**
 * A SLOT callback activated when the fluid_synth chrus speed slider or spinbox value is changed.
 * @param the new slider or spiner value.
 * @return none
 */
void FluidSynthUiHandling::ChorusSpeedChanged(int val)
{
	sprintf(mssg1, "FluidSynth Chorus Speed: %.2f", (float)val / 100.0);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	mod_synth_set_fluid_synth_chorus_speed(val);
}

/**
 * A SLOT callback activated when the fluid_synth chorus depth slider or spinbox value is changed.
 * @param the new slider or spiner value.
 * @return none
 */
void FluidSynthUiHandling::ChorusDepthChanged(int val)
{
	sprintf(mssg1, "FluidSynth Chorus Depth: %.2f", (float)val / 10.0);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	mod_synth_set_fluid_synth_chorus_depth(val);
}

/**
 * A SLOT callback activated when the fluid_synth chorus waveform combo-box value is changed.
 * @param the new slider or spiner value.
 * @return none
 */
void FluidSynthUiHandling::ChorusWaveformChanged(int val)
{
	mod_synth_set_fluid_synth_chorus_waveform(val);
}

/**
 * A SLOT callback activated when the fluid_synth reverb activation checkbox value is changed.
 * @param the new checkbox value.
 * @return none
 */
void FluidSynthUiHandling::ReverbActivationChanged(bool val)
{
	if (val == true)
	{
		mod_synth_set_fluid_synth_enable_reverb();
	}
	else
	{
		mod_synth_set_fluid_synth_disable_reverb();
	}
}

/**
 * A SLOT callback activated when the fluid_synth reverb activation checkbox value is changed.
 * @param the new checkbox value.
 * @return none
 */
void FluidSynthUiHandling::ChorusActivationChanged(bool val)
{
	if (val)
	{
		mod_synth_set_fluid_synth_enable_chorus();
	}
	else
	{
		mod_synth_set_fluid_synth_disable_chorus();
	}
}








