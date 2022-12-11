/**
*	@file		EffectsTab.cpp
*	@author		Nahum Budin
*	@date		15-Nov-2019
*	@version	1.0
*
*	@brief		Effects (Reverb, Distortion and Band Equalizer) Tab ui handling.
*/

#include "MainWindow.h"
#include "EffectsTab.h"
#include "libAdjHeartModSynth_2.h"

EffectsTabUiHandling *EffectsTabUiHandling::effectsTabUiHandling = NULL;

EffectsTabUiHandling::EffectsTabUiHandling(Ui_MainWindow *mainWind)
{
	mainWindow = mainWind;
	effectsTabUiHandling = this;
	
	stringReverbModeList.append("Default");
	stringReverbModeList.append("Small Hall 1");
	stringReverbModeList.append("Small Hall 2");
	stringReverbModeList.append("Medium Hall 1");
	stringReverbModeList.append("Medium Hall 2");
	stringReverbModeList.append("Large Hall 1");
	stringReverbModeList.append("Large Hall 2");
	stringReverbModeList.append("Small Room 1");
	stringReverbModeList.append("Small Room 2");
	stringReverbModeList.append("Medium Room 1");
	stringReverbModeList.append("Medium Room 2");
	stringReverbModeList.append("Large Room 1");
	stringReverbModeList.append("Large Room 2");
	stringReverbModeList.append("Medium R 1");
	stringReverbModeList.append("Medium R 2");
	stringReverbModeList.append("Plate High");
	stringReverbModeList.append("Plate Low");
	stringReverbModeList.append("Long Reverb 1");
	stringReverbModeList.append("Long Reverb 2");	
}

EffectsTabUiHandling *EffectsTabUiHandling::getInstance() 
{
	return effectsTabUiHandling;
}

void EffectsTabUiHandling::setTrigers()
{
	connect(mainWindow->checkBox_enableFreeverb,
		SIGNAL(toggled(bool)),
		this,
		SLOT(reverbEnableChanged(bool)));

	connect(mainWindow->dial_ReverbRoomSize,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(reverbRoomSizeChanged(int)));

	connect(mainWindow->dial_ReverbDamp,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(reverbDampChanged(int)));

	connect(mainWindow->dial_ReverbWet,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(reverbWetChanged(int)));

	connect(mainWindow->dial_ReverbDry,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(reverbDryChanged(int)));

	connect(mainWindow->dial_ReverbWidth,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(reverbWidthChanged(int)));

	connect(mainWindow->dial_ReverbMode,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(reverbModeChanged(int)));

	// Freeverb 3 Mod
	connect(mainWindow->checkBox_enableFreeVerb3,
		SIGNAL(toggled(bool)),
		this,
		SLOT(reverb3MenableChanged(bool)));

	connect(mainWindow->comboBox_ReverbType,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(reverbTypeSelected(int)));
	
	
	connect(mainWindow->checkBox_enableDistortion,
		SIGNAL(toggled(bool)),
		this,
		SLOT(distortionEnableChanged(bool)));

	connect(mainWindow->checkBox_enableDistortionAutoGain,
		SIGNAL(toggled(bool)),
		this,
		SLOT(distortionAutoGainChanged(bool)));
	
	connect(mainWindow->dial_DistortionDrive_1,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(distortion1driveChanged(int)));
	
	connect(mainWindow->dial_DistortionRange_1,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(distortion1rangeChanged(int)));
	
	connect(mainWindow->dial_DistortionBlend_1,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(distortion1blendChanged(int)));
	
	connect(mainWindow->dial_DistortionDrive_2,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(distortion2driveChanged(int)));
	
	connect(mainWindow->dial_DistortionRange_2,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(distortion2rangeChanged(int)));
	
	connect(mainWindow->dial_DistortionBlend_2,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(distortion2blendChanged(int)));
	
	
	connect(mainWindow->verticalSlider_BandEquilizer31,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(bandEquilizerBand31Changed(int)));

	connect(mainWindow->verticalSlider_BandEquilizer62,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(bandEquilizerBand62Changed(int)));

	connect(mainWindow->verticalSlider_BandEquilizer125,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(bandEquilizerBand125Changed(int)));

	connect(mainWindow->verticalSlider_BandEquilizer250,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(bandEquilizerBand250Changed(int)));

	connect(mainWindow->verticalSlider_BandEquilizer500,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(bandEquilizerBand500Changed(int)));

	connect(mainWindow->verticalSlider_BandEquilizer1K,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(bandEquilizerBand1KChanged(int)));

	connect(mainWindow->verticalSlider_BandEquilizer2K,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(bandEquilizerBand2KChanged(int)));

	connect(mainWindow->verticalSlider_BandEquilizer4K,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(bandEquilizerBand4KChanged(int)));

	connect(mainWindow->verticalSlider_BandEquilizer8K,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(bandEquilizerBand8KChanged(int)));

	connect(mainWindow->verticalSlider_BandEquilizer16K,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(bandEquilizerBand16KChanged(int)));

	connect(mainWindow->comboBox_BandEquilizerPreset,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(bandEquilizerBandPresetChanged(int)));

	connect(mainWindow->pushButton_EquilizerSetAllZero,
		SIGNAL(toggled(bool)),
		this,
		SLOT(bandEquilizerSetAllZeroClicked(bool)));
}

void EffectsTabUiHandling::update()
{
	static bool oneTimeInitialized = false;

	if (!oneTimeInitialized)
	{
		oneTimeInitialized = true;
		
		mainWindow->comboBox_ReverbType->blockSignals(true);
		mainWindow->comboBox_ReverbType->addItems(stringReverbModeList);
		mainWindow->comboBox_ReverbType->blockSignals(false);
		
	}
	
	mainWindow->checkBox_enableFreeverb->blockSignals(true);
	mainWindow->checkBox_enableFreeverb->setChecked(mod_synth_get_active_reverb_enable_state());
	mainWindow->checkBox_enableFreeverb->blockSignals(false);

	mainWindow->dial_ReverbRoomSize->blockSignals(true);
	mainWindow->dial_ReverbRoomSize->setValue(mod_synth_get_active_reverb_room_size());
	mainWindow->dial_ReverbRoomSize->blockSignals(false);

	mainWindow->dial_ReverbDamp->blockSignals(true);
	mainWindow->dial_ReverbDamp->setValue(mod_synth_get_active_reverb_damp());
	mainWindow->dial_ReverbDamp->blockSignals(false);

	mainWindow->dial_ReverbWet->blockSignals(true);
	mainWindow->dial_ReverbWet->setValue(mod_synth_get_active_reverb_wet());
	mainWindow->dial_ReverbWet->blockSignals(false);

	mainWindow->dial_ReverbDry->blockSignals(true);
	mainWindow->dial_ReverbDry->setValue(mod_synth_get_active_reverb_dry());
	mainWindow->dial_ReverbDry->blockSignals(false);

	mainWindow->dial_ReverbWidth->blockSignals(true);
	mainWindow->dial_ReverbWidth->setValue(mod_synth_get_active_reverb_width());
	mainWindow->dial_ReverbWidth->blockSignals(false);

	mainWindow->dial_ReverbMode->blockSignals(true);
	mainWindow->dial_ReverbMode->setValue(mod_synth_get_active_reverb_mode());
	mainWindow->dial_ReverbMode->blockSignals(false);

	mainWindow->checkBox_enableFreeVerb3->blockSignals(true);
	mainWindow->checkBox_enableFreeVerb3->setChecked(mod_synth_get_active_reverb_3m_enable_state());
	mainWindow->checkBox_enableFreeVerb3->blockSignals(false);
	if (mod_synth_get_active_reverb_enable_state())
	{
		mainWindow->groupBox_FreeReverb->setEnabled(true);
	}
	else
	{
		mainWindow->groupBox_FreeReverb->setEnabled(false);
	}
	
	mainWindow->comboBox_ReverbType->blockSignals(true);
	mainWindow->comboBox_ReverbType->setCurrentIndex(mod_synth_get_active_reverb_enable_state());
	mainWindow->comboBox_ReverbType->blockSignals(false);
	if (mod_synth_get_active_reverb_3m_enable_state())
	{
		mainWindow->groupBox_reverb3M->setEnabled(true);
	}
	else
	{
		mainWindow->groupBox_reverb3M->setEnabled(false);
	}	
	
	mainWindow->checkBox_enableDistortion ->blockSignals(true);
	mainWindow->checkBox_enableDistortion->setChecked(mod_synth_get_active_distortion_enable_state()); 
	mainWindow->checkBox_enableDistortion->blockSignals(false);
	if (mod_synth_get_active_distortion_enable_state())
	{
		mainWindow->groupBox_DistLeft->setEnabled(true);
		mainWindow->groupBox_DistRight->setEnabled(true);
	}
	else
	{
		mainWindow->groupBox_DistLeft->setEnabled(false);
		mainWindow->groupBox_DistRight->setEnabled(false);
	}

	mainWindow->checkBox_enableDistortionAutoGain ->blockSignals(true);
	mainWindow->checkBox_enableDistortionAutoGain->setChecked(mod_synth_get_active_distortion_auto_gain_state());
	mainWindow->checkBox_enableDistortionAutoGain->blockSignals(false);
	
	mainWindow->dial_DistortionDrive_1->blockSignals(true);
	mainWindow->dial_DistortionDrive_1->setValue(mod_synth_get_active_distortion_1_drive());
	mainWindow->dial_DistortionDrive_1->blockSignals(false);
	
	mainWindow->dial_DistortionRange_1->blockSignals(true);
	mainWindow->dial_DistortionRange_1->setValue(mod_synth_get_active_distortion_1_range());
	mainWindow->dial_DistortionRange_1->blockSignals(false);
	
	mainWindow->dial_DistortionBlend_1->blockSignals(true);
	mainWindow->dial_DistortionBlend_1->setValue(mod_synth_get_active_distortion_1_blend());
	mainWindow->dial_DistortionBlend_1->blockSignals(false);
	
	mainWindow->dial_DistortionDrive_2->blockSignals(true);
	mainWindow->dial_DistortionDrive_2->setValue(mod_synth_get_active_distortion_2_drive());
	mainWindow->dial_DistortionDrive_2->blockSignals(false);
	
	mainWindow->dial_DistortionRange_2->blockSignals(true);
	mainWindow->dial_DistortionRange_2->setValue(mod_synth_get_active_distortion_2_range());
	mainWindow->dial_DistortionRange_2->blockSignals(false);
	
	mainWindow->dial_DistortionBlend_2->blockSignals(true);
	mainWindow->dial_DistortionBlend_2->setValue(mod_synth_get_active_distortion_2_blend());
	mainWindow->dial_DistortionBlend_2->blockSignals(false);	
	
	
	mainWindow->verticalSlider_BandEquilizer31->blockSignals(true);
	mainWindow->verticalSlider_BandEquilizer31->setValue(mod_synth_get_active_equilizer_band31_level() + 20);   // -20 ... +20 -> 0 .. 40
	mainWindow->verticalSlider_BandEquilizer31->blockSignals(false);

	mainWindow->verticalSlider_BandEquilizer62->blockSignals(true);
	mainWindow->verticalSlider_BandEquilizer62->setValue(mod_synth_get_active_equilizer_band62_level() + 20);
	mainWindow->verticalSlider_BandEquilizer62->blockSignals(false);

	mainWindow->verticalSlider_BandEquilizer125->blockSignals(true);
	mainWindow->verticalSlider_BandEquilizer125->setValue(mod_synth_get_active_equilizer_band125_level() + 20);
	mainWindow->verticalSlider_BandEquilizer125->blockSignals(false);

	mainWindow->verticalSlider_BandEquilizer250->blockSignals(true);
	mainWindow->verticalSlider_BandEquilizer250->setValue(mod_synth_get_active_equilizer_band250_level() + 20);
	mainWindow->verticalSlider_BandEquilizer250->blockSignals(false);

	mainWindow->verticalSlider_BandEquilizer500->blockSignals(true);
	mainWindow->verticalSlider_BandEquilizer500->setValue(mod_synth_get_active_equilizer_band500_level() + 20);
	mainWindow->verticalSlider_BandEquilizer500->blockSignals(false);

	mainWindow->verticalSlider_BandEquilizer1K->blockSignals(true);
	mainWindow->verticalSlider_BandEquilizer1K->setValue(mod_synth_get_active_equilizer_band1k_level() + 20);
	mainWindow->verticalSlider_BandEquilizer1K->blockSignals(false);

	mainWindow->verticalSlider_BandEquilizer2K->blockSignals(true);
	mainWindow->verticalSlider_BandEquilizer2K->setValue(mod_synth_get_active_equilizer_band2k_level() + 20);
	mainWindow->verticalSlider_BandEquilizer2K->blockSignals(false);

	mainWindow->verticalSlider_BandEquilizer4K->blockSignals(true);
	mainWindow->verticalSlider_BandEquilizer4K->setValue(mod_synth_get_active_equilizer_band4k_level() + 20);
	mainWindow->verticalSlider_BandEquilizer4K->blockSignals(false);

	mainWindow->verticalSlider_BandEquilizer8K->blockSignals(true);
	mainWindow->verticalSlider_BandEquilizer8K->setValue(mod_synth_get_active_equilizer_band8k_level() + 20);
	mainWindow->verticalSlider_BandEquilizer8K->blockSignals(false);

	mainWindow->verticalSlider_BandEquilizer16K->blockSignals(true);
	mainWindow->verticalSlider_BandEquilizer16K->setValue(mod_synth_get_active_equilizer_band16k_level() + 20);
	mainWindow->verticalSlider_BandEquilizer16K->blockSignals(false);

	mainWindow->comboBox_BandEquilizerPreset->blockSignals(true);
	mainWindow->comboBox_BandEquilizerPreset->setCurrentIndex(mod_synth_get_active_equilizer_preset());
	mainWindow->comboBox_BandEquilizerPreset->blockSignals(false);	
}

void EffectsTabUiHandling::reverb3MenableChanged(bool val)
{
	mod_synth_reverb_event_bool(_REVERB_EVENT, _REVERB3M_ENABLE, val);
	if (val)
	{
		mainWindow->checkBox_enableFreeverb->blockSignals(true);
		mainWindow->checkBox_enableFreeverb->setChecked(false);
		mainWindow->checkBox_enableFreeverb->blockSignals(false);
		mainWindow->groupBox_FreeReverb->setEnabled(false);
	}
}
void EffectsTabUiHandling::reverbEnableChanged(bool val)
{
	mod_synth_reverb_event_bool(_REVERB_EVENT, _REVERB_ENABLE, val);
	if (val)
	{
		mainWindow->checkBox_enableFreeVerb3->blockSignals(true);
		mainWindow->checkBox_enableFreeVerb3->setChecked(false);
		mainWindow->checkBox_enableFreeVerb3->blockSignals(false);
		mainWindow->groupBox_reverb3M->setEnabled(false);
	}
}

void EffectsTabUiHandling::reverbTypeSelected(int val)
{
	mod_synth_reverb_event(_REVERB_EVENT, _REVERB_PRESET, val);
}


void EffectsTabUiHandling::reverbRoomSizeChanged(int val)
{
	mod_synth_reverb_event(_REVERB_EVENT, _REVERB_ROOM_SIZE, val);
	sprintf(mssg1, "Reverb Room Size: %.2f", (float)val / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void EffectsTabUiHandling::reverbDampChanged(int val)
{
	mod_synth_reverb_event(_REVERB_EVENT, _REVERB_DAMP, val);
	sprintf(mssg1, "Reverb Damp: %.2f", (float)val / 100.0f);  // 0.01 - 0.99
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void EffectsTabUiHandling::reverbWetChanged(int val)
{
	mod_synth_reverb_event(_REVERB_EVENT, _REVERB_WET, val);    // 0-100
	sprintf(mssg1, "Reverb Wet: %.2f", (float)val / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void EffectsTabUiHandling::reverbDryChanged(int val)
{
	mod_synth_reverb_event(_REVERB_EVENT, _REVERB_DRY, val);    // 0-100
	sprintf(mssg1, "Reverb Dry: %.2f", (float)val / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void EffectsTabUiHandling::reverbWidthChanged(int val)
{
	mod_synth_reverb_event(_REVERB_EVENT, _REVERB_WIDTH, val);    // 0-100
	sprintf(mssg1, "Reverb Width: %.2f", (float)val / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void EffectsTabUiHandling::reverbModeChanged(int val)
{
	mod_synth_reverb_event(_REVERB_EVENT, _REVERB_MODE, val);   // 0-50 -> 0.0-0.5
	sprintf(mssg1, "Reverb Mode: %.2f", (float)val / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}


void EffectsTabUiHandling::distortionEnableChanged(bool val)
{
	mod_synth_distortion_event_bool(_DISTORTION_1_EVENT, _ENABLE_DISTORTION, val);
}

void EffectsTabUiHandling::distortionAutoGainChanged(bool val)
{
	mod_synth_distortion_event_bool(_DISTORTION_1_EVENT, _DISTORTION_AUTO_GAIN, val);
}

void EffectsTabUiHandling::distortion1driveChanged(int val)
{
	mod_synth_distortion_event(_DISTORTION_1_EVENT, _DISTORTION_DRIVE, val);
	sprintf(mssg1, "Distortion 1 Drive: %.2f", (float)val / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void EffectsTabUiHandling::distortion1rangeChanged(int val)
{
	mod_synth_distortion_event(_DISTORTION_1_EVENT, _DISTORTION_RANGE, val);
	sprintf(mssg1, "Distortion 1 Range: %.2f", (float)val);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void EffectsTabUiHandling::distortion1blendChanged(int val)
{
	mod_synth_distortion_event(_DISTORTION_1_EVENT, _DISTORTION_BLEND, val);
	sprintf(mssg1, "Distortion 1 Blend: %.2f", (float)val / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void EffectsTabUiHandling::distortion2driveChanged(int val)
{
	mod_synth_distortion_event(_DISTORTION_2_EVENT, _DISTORTION_DRIVE, val);
	sprintf(mssg1, "Distortion 2 Drive: %.2f", (float)val / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void EffectsTabUiHandling::distortion2rangeChanged(int val)
{
	mod_synth_distortion_event(_DISTORTION_2_EVENT, _DISTORTION_RANGE, val);
	sprintf(mssg1, "Distortion 2 Range: %.2f", (float)val);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void EffectsTabUiHandling::distortion2blendChanged(int val)
{
	mod_synth_distortion_event(_DISTORTION_2_EVENT, _DISTORTION_BLEND, val);
	sprintf(mssg1, "Distortion 2 Blend: %.2f", (float)val / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}


void EffectsTabUiHandling::bandEquilizerBand31Changed(int val)
{
	mod_synth_band_equalizer_event(_BAND_EQUALIZER_EVENT, _BAND_EQUALIZER_BAND_31_LEVEL, val - 20);     // 0..40 -> -20..+20db
	sprintf(mssg1, "Band Equalizer 31Hz Level: %i db", val - 20);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void EffectsTabUiHandling::bandEquilizerBand62Changed(int val)
{
	mod_synth_band_equalizer_event(_BAND_EQUALIZER_EVENT, _BAND_EQUALIZER_BAND_62_LEVEL, val - 20);
	sprintf(mssg1, "Band Equalizer 62Hz Level: %i db", val - 20);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void EffectsTabUiHandling::bandEquilizerBand125Changed(int val)
{
	mod_synth_band_equalizer_event(_BAND_EQUALIZER_EVENT, _BAND_EQUALIZER_BAND_125_LEVEL, val - 20);
	sprintf(mssg1, "Band Equalizer 125Hz Level: %i db", val - 20);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void EffectsTabUiHandling::bandEquilizerBand250Changed(int val)
{
	mod_synth_band_equalizer_event(_BAND_EQUALIZER_EVENT, _BAND_EQUALIZER_BAND_250_LEVEL, val - 20);
	sprintf(mssg1, "Band Equalizer 250Hz Level: %i db", val - 20);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void EffectsTabUiHandling::bandEquilizerBand500Changed(int val)
{
	mod_synth_band_equalizer_event(_BAND_EQUALIZER_EVENT, _BAND_EQUALIZER_BAND_500_LEVEL, val - 20);
	sprintf(mssg1, "Band Equalizer 500Hz Level: %i db", val - 20);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void EffectsTabUiHandling::bandEquilizerBand1KChanged(int val)
{
	mod_synth_band_equalizer_event(_BAND_EQUALIZER_EVENT, _BAND_EQUALIZER_BAND_1K_LEVEL, val - 20);
	sprintf(mssg1, "Band Equalizer 1KHz Level: %i db", val - 20);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void EffectsTabUiHandling::bandEquilizerBand2KChanged(int val)
{
	mod_synth_band_equalizer_event(_BAND_EQUALIZER_EVENT, _BAND_EQUALIZER_BAND_2K_LEVEL, val - 20);
	sprintf(mssg1, "Band Equalizer 2KHz Level: %i db", val - 20);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void EffectsTabUiHandling::bandEquilizerBand4KChanged(int val)
{
	mod_synth_band_equalizer_event(_BAND_EQUALIZER_EVENT, _BAND_EQUALIZER_BAND_4K_LEVEL, val - 20);
	sprintf(mssg1, "Band Equalizer 4KHz Level: %i db", val - 20);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void EffectsTabUiHandling::bandEquilizerBand8KChanged(int val)
{
	mod_synth_band_equalizer_event(_BAND_EQUALIZER_EVENT, _BAND_EQUALIZER_BAND_8K_LEVEL, val - 20);
	sprintf(mssg1, "Band Equalizer 8KHz Level: %i db", val - 20);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void EffectsTabUiHandling::bandEquilizerBand16KChanged(int val)
{
	mod_synth_band_equalizer_event(_BAND_EQUALIZER_EVENT, _BAND_EQUALIZER_BAND_16K_LEVEL, val - 20);
	sprintf(mssg1, "Band Equalizer 16KHz Level: %i db", val - 20);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void EffectsTabUiHandling::bandEquilizerBandPresetChanged(int val)
{
	mod_synth_band_equalizer_event(_BAND_EQUALIZER_EVENT, _BAND_EQUALIZER_PRESET, val);
}

void EffectsTabUiHandling::bandEquilizerSetAllZeroClicked(bool val)
{
	mod_synth_band_equalizer_event(_BAND_EQUALIZER_EVENT, _BAND_EQUALIZER_SET_ALL_ZERO, 1);
	mainWindow->pushButton_EquilizerSetAllZero->blockSignals(true);
	mainWindow->pushButton_EquilizerSetAllZero->setChecked(false);
	mainWindow->pushButton_EquilizerSetAllZero->blockSignals(false);
}

