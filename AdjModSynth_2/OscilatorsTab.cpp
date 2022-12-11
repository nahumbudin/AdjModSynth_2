/**
* @file		OscilatorsTab.cpp
*	@author		Nahum Budin
*	@date		16-Jan-2021
*	@version	1.1 
*				1. Adding Control Widgets control through Knob and Slider
*	
*	Version	1.0		09-Nov-2019
*
*	@brief		Oscilators Tab ui handling.
*/

#include "MainWindow.h"
#include "OscilatorsTab.h"
#include "libAdjHeartModSynth_2.h"

OscilatorsTabUiHandling *OscilatorsTabUiHandling::oscilatorsTabUiHandling = NULL;

void osc1unisonModeSelectedWrapper(int mod)
{ 
	OscilatorsTabUiHandling::getInstance()->osc1SetUnisonMode(mod);
}

OscilatorsTabUiHandling::OscilatorsTabUiHandling(Ui_MainWindow *mainWind)
{
	oscilatorsTabUiHandling = this;
	
	mainWindow = mainWind;
	
	unisonLevelSliders = new QSlider*[mod_synth_get_osc1_num_of_drawbars()];
	
	unisonLevelSliders[0] = mainWindow->verticalSlider_Osc1unisonLev1;
	unisonLevelSliders[1] = mainWindow->verticalSlider_Osc1unisonLev2;
	unisonLevelSliders[2] = mainWindow->verticalSlider_Osc1unisonLev3;
	unisonLevelSliders[3] = mainWindow->verticalSlider_Osc1unisonLev4;
	unisonLevelSliders[4] = mainWindow->verticalSlider_Osc1unisonLev5;
	unisonLevelSliders[5] = mainWindow->verticalSlider_Osc1unisonLev6;
	unisonLevelSliders[6] = mainWindow->verticalSlider_Osc1unisonLev7;
	unisonLevelSliders[7] = mainWindow->verticalSlider_Osc1unisonLev8;
	unisonLevelSliders[8] = mainWindow->verticalSlider_Osc1unisonLev9;
	
	stringWaveformsList.append("Sine");
	stringWaveformsList.append("Square");
	stringWaveformsList.append("Pulse");
	stringWaveformsList.append("Triangle");
	stringWaveformsList.append("Sample & Hold");

	stringUnisonModesList.append("Harmonized");
	stringUnisonModesList.append("Hammond");
	stringUnisonModesList.append("Octaves");
	stringUnisonModesList.append("C Chord");
	stringUnisonModesList.append("Cm Chord");
	stringUnisonModesList.append("C7 Chord");
	stringUnisonModesList.append("Cm7 Chord");

	stringUnisonLabelsHarmonized.append("1");
	stringUnisonLabelsHarmonized.append("2");
	stringUnisonLabelsHarmonized.append("3");
	stringUnisonLabelsHarmonized.append("4");
	stringUnisonLabelsHarmonized.append("5");
	stringUnisonLabelsHarmonized.append("6");
	stringUnisonLabelsHarmonized.append("7");
	stringUnisonLabelsHarmonized.append("8  ");

	stringUnisonLabelsHammond.append("16");
	stringUnisonLabelsHammond.append("5 1/3");
	stringUnisonLabelsHammond.append("8");
	stringUnisonLabelsHammond.append("4");
	stringUnisonLabelsHammond.append("2 2/3");
	stringUnisonLabelsHammond.append("2");
	stringUnisonLabelsHammond.append("1 3/5");
	stringUnisonLabelsHammond.append("1 1/3");
	stringUnisonLabelsHammond.append("1");

	stringHammondModesList.append("Percusion OFF");
	stringHammondModesList.append("Percusion 2nd Soft Slow");
	stringHammondModesList.append("Percusion 2nd Soft Fast");
	stringHammondModesList.append("Percusion 2nd Norm Slow");
	stringHammondModesList.append("Percusion 2nd Norm Fast");
	stringHammondModesList.append("Percusion 3rd Soft Slow");
	stringHammondModesList.append("Percusion 3rd Soft Fast");
	stringHammondModesList.append("Percusion 3rd Norm Slow");
	stringHammondModesList.append("Percusion 3rd Norm Fast");

	stringUnisonLabelsOctaves.append("1");
	stringUnisonLabelsOctaves.append("2");
	stringUnisonLabelsOctaves.append("4");
	stringUnisonLabelsOctaves.append("8  ");

	stringUnisonLabelsCchord.append("I");
	stringUnisonLabelsCchord.append("III");
	stringUnisonLabelsCchord.append("V");

	stringUnisonLabelsCmChord.append("i");
	stringUnisonLabelsCmChord.append("iii");
	stringUnisonLabelsCmChord.append("v");

	stringUnisonLabelsC7chord.append("I");
	stringUnisonLabelsC7chord.append("III");
	stringUnisonLabelsC7chord.append("V");
	stringUnisonLabelsC7chord.append("VII");

	stringUnisonLabelsCm7chord.append("i");
	stringUnisonLabelsCm7chord.append("iii");
	stringUnisonLabelsCm7chord.append("v");
	stringUnisonLabelsCm7chord.append("vii");
	
	register_set_osc1_unison_mode_callback(&osc1unisonModeSelectedWrapper);
}

OscilatorsTabUiHandling *OscilatorsTabUiHandling::getInstance() 
{
	return oscilatorsTabUiHandling;
}

void OscilatorsTabUiHandling::setTrigers()
{
	connect(mainWindow->comboBox_Osc1Waveform,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(osc1waveformSelected(int)));

	connect(mainWindow->horizontalSlider_Osc1Symetry,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(osc1symmetryChanged(int)));

	connect(mainWindow->comboBox_Osc1TuneOct,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(osc1detuneOctaveChanged(int)));

	connect(mainWindow->comboBox_Osc1TuneSemi,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(osc1detuneSeminotesChanged(int)));

	connect(mainWindow->comboBox_Osc1TuneCents,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(osc1detuneCentsChanged(int)));

	connect(mainWindow->dial_Osc1FilterSend1,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(osc1SendFilter1Changed(int)));

	connect(mainWindow->dial_Osc1FilterSend2,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(osc1SendFilter2Changed(int)));

	connect(mainWindow->comboBox_Osc1FreqModLfo,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(osc1FreqModLfoChanged(int)));

	connect(mainWindow->dial_Osc1FreqModLfoLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(osc1FreqModLevelLfoChanged(int)));

	connect(mainWindow->comboBox_Osc1FreqModEnv,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(osc1FreqModEnvChanged(int)));

	connect(mainWindow->dial_Osc1FreqModEnvLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(osc1FreqModLevelEnvChanged(int)));

	connect(mainWindow->comboBox_Osc1PwmModLfo,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(osc1PwmModLfoChanged(int)));

	connect(mainWindow->dial_Osc1PwmModLfoLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(osc1PwmModLevelLfoChanged(int)));

	connect(mainWindow->comboBox_Osc1PwmModEnv,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(osc1PwmModEnvChanged(int)));

	connect(mainWindow->dial_Osc1PwmModEnvLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(osc1PwmModLevelEnvChanged(int)));

	connect(mainWindow->comboBox_Osc1AmpModLfo,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(osc1AmpModLfoChanged(int)));

	connect(mainWindow->dial_Osc1AmpModLfoLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(osc1AmpModLevelLfoChanged(int)));

	connect(mainWindow->comboBox_Osc1AmpModEnv,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(osc1AmpModEnvChanged(int)));

	connect(mainWindow->dial_Osc1AmpModEnvLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(osc1AmpModLevelEnvChanged(int)));

	connect(mainWindow->comboBox_Osc1UnisonMode,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(osc1unisonModeSelected(int)));

	connect(mainWindow->comboBox_Osc1HammondMode,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(osc1hammondModeSelected(int)));

	connect(mainWindow->verticalSlider_Osc1unisonLev1,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(osc1unisonLev1Changed(int)));

	connect(mainWindow->verticalSlider_Osc1unisonLev2,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(osc1unisonLev2Changed(int)));

	connect(mainWindow->verticalSlider_Osc1unisonLev3,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(osc1unisonLev3Changed(int)));

	connect(mainWindow->verticalSlider_Osc1unisonLev4,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(osc1unisonLev4Changed(int)));

	connect(mainWindow->verticalSlider_Osc1unisonLev5,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(osc1unisonLev5Changed(int)));

	connect(mainWindow->verticalSlider_Osc1unisonLev6,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(osc1unisonLev6Changed(int)));

	connect(mainWindow->verticalSlider_Osc1unisonLev7,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(osc1unisonLev7Changed(int)));

	connect(mainWindow->verticalSlider_Osc1unisonLev8,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(osc1unisonLev8Changed(int)));

	connect(mainWindow->verticalSlider_Osc1unisonLev9,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(osc1unisonLev9Changed(int)));

	connect(mainWindow->verticalSlider_Osc1unisonLevDist,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(osc1unisonDistortionChanged(int)));

	connect(mainWindow->verticalSlider_Osc1unisonLevDetune,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(osc1unisonDetuneChanged(int)));

	connect(mainWindow->checkBox_Osc1unisonSqr,
		SIGNAL(toggled(bool)),
		this,
		SLOT(osc1unisonSquareChanges(bool)));

	connect(mainWindow->checkBox_enableOSC1,
		SIGNAL(toggled(bool)),
		this,
		SLOT(osc1EnableChanged(bool)));
	
	connect(mainWindow->comboBox_Osc2Waveform, 
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(osc2waveformSelected(int)));

	connect(mainWindow->horizontalSlider_Osc2Symetry,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(osc2symmetryChanged(int)));

	connect(mainWindow->comboBox_Osc2TuneOct,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(osc2detuneOctaveChanged(int)));

	connect(mainWindow->comboBox_Osc2TuneSemi,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(osc2detuneSeminotesChanged(int)));

	connect(mainWindow->comboBox_Osc2TuneCents,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(osc2detuneCentsChanged(int)));

	connect(mainWindow->dial_Osc2FilterSend1,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(osc2SendFilter1Changed(int)));

	connect(mainWindow->dial_Osc2FilterSend2,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(osc2SendFilter2Changed(int)));

	connect(mainWindow->comboBox_Osc2FreqModLfo,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(osc2FreqModLfoChanged(int)));

	connect(mainWindow->dial_Osc2FreqModLfoLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(osc2FreqModLevelLfoChanged(int)));

	connect(mainWindow->comboBox_Osc2FreqModEnv,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(osc2FreqModEnvChanged(int)));

	connect(mainWindow->dial_Osc2FreqModEnvLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(osc2FreqModLevelEnvChanged(int)));

	connect(mainWindow->comboBox_Osc2PwmModLfo,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(osc2PwmModLfoChanged(int)));

	connect(mainWindow->dial_Osc2PwmModLfoLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(osc2PwmModLevelLfoChanged(int)));

	connect(mainWindow->comboBox_Osc2PwmModEnv,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(osc2PwmModEnvChanged(int)));

	connect(mainWindow->dial_Osc2PwmModEnvLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(osc2PwmModLevelEnvChanged(int)));

	connect(mainWindow->comboBox_Osc2AmpModLfo,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(osc2AmpModLfoChanged(int)));

	connect(mainWindow->dial_Osc2AmpModLfoLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(osc2AmpModLevelLfoChanged(int)));

	connect(mainWindow->comboBox_Osc2AmpModEnv,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(osc2AmpModEnvChanged(int)));

	connect(mainWindow->dial_Osc2AmpModEnvLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(osc2AmpModLevelEnvChanged(int)));

	connect(mainWindow->checkBox_Osc2SyncOsc1,
		SIGNAL(toggled(bool)),
		this,
		SLOT(osc2syncOsc1Changed(bool)));

//	connect(mainWindow->checkBox_SyncOsc2FixTone,
//		SIGNAL(toggled(bool)),
//		this,
//		SLOT(osc2fixToneChanged(bool)));

	connect(mainWindow->checkBox_enableOSC2,
		SIGNAL(toggled(bool)),
		this,
		SLOT(osc2EnableChanged(bool)));
}

void OscilatorsTabUiHandling::setWidgetsInfoMap()
{
	// Widgets Ids
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_Osc1FilterSend1, _OSC_1_EVENT * 10000 + _OSC_FILTER_SEND_1);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_Osc1FilterSend2, _OSC_1_EVENT * 10000 + _OSC_FILTER_SEND_2);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->horizontalSlider_Osc1Symetry, _OSC_1_EVENT * 10000 + _OSC_PWM_SYMMETRY);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_Osc1FreqModLfoLevel, _OSC_1_EVENT * 10000 + _OSC_FREQ_MOD_LFO_LEVEL);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_Osc1FreqModEnvLevel, _OSC_1_EVENT * 10000 + _OSC_FREQ_MOD_ENV_LEVEL);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_Osc1PwmModLfoLevel, _OSC_1_EVENT * 10000 + _OSC_PWM_MOD_LFO_LEVEL);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_Osc1PwmModEnvLevel, _OSC_1_EVENT * 10000 + _OSC_PWM_MOD_ENV_LEVEL);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_Osc1AmpModLfoLevel, _OSC_1_EVENT * 10000 + _OSC_AMP_MOD_LFO_LEVEL);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_Osc1AmpModEnvLevel, _OSC_1_EVENT * 10000 + _OSC_AMP_MOD_ENV_LEVEL);

	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->verticalSlider_Osc1unisonLev1, _OSC_1_EVENT * 10000 + _OSC_UNISON_LEVEL_1);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->verticalSlider_Osc1unisonLev2, _OSC_1_EVENT * 10000 + _OSC_UNISON_LEVEL_2);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->verticalSlider_Osc1unisonLev3, _OSC_1_EVENT * 10000 + _OSC_UNISON_LEVEL_3);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->verticalSlider_Osc1unisonLev4, _OSC_1_EVENT * 10000 + _OSC_UNISON_LEVEL_4);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->verticalSlider_Osc1unisonLev5, _OSC_1_EVENT * 10000 + _OSC_UNISON_LEVEL_5);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->verticalSlider_Osc1unisonLev6, _OSC_1_EVENT * 10000 + _OSC_UNISON_LEVEL_6);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->verticalSlider_Osc1unisonLev7, _OSC_1_EVENT * 10000 + _OSC_UNISON_LEVEL_7);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->verticalSlider_Osc1unisonLev8, _OSC_1_EVENT * 10000 + _OSC_UNISON_LEVEL_8);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->verticalSlider_Osc1unisonLev9, _OSC_1_EVENT * 10000 + _OSC_UNISON_LEVEL_9);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->verticalSlider_Osc1unisonLevDist, _OSC_1_EVENT * 10000 + _OSC_UNISON_DISTORTION);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->verticalSlider_Osc1unisonLevDetune, _OSC_1_EVENT * 10000 + _OSC_UNISON_DETUNE);

	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_Osc2FilterSend1, _OSC_2_EVENT * 10000 + _OSC_FILTER_SEND_1);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_Osc2FilterSend2, _OSC_2_EVENT * 10000 + _OSC_FILTER_SEND_2);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->horizontalSlider_Osc2Symetry, _OSC_2_EVENT * 10000 + _OSC_PWM_SYMMETRY);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_Osc2FreqModLfoLevel, _OSC_2_EVENT * 10000 + _OSC_FREQ_MOD_LFO_LEVEL);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_Osc2FreqModEnvLevel, _OSC_2_EVENT * 10000 + _OSC_FREQ_MOD_ENV_LEVEL);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_Osc2PwmModLfoLevel, _OSC_2_EVENT * 10000 + _OSC_PWM_MOD_LFO_LEVEL);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_Osc2PwmModEnvLevel, _OSC_2_EVENT * 10000 + _OSC_PWM_MOD_ENV_LEVEL);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_Osc2AmpModLfoLevel, _OSC_2_EVENT * 10000 + _OSC_AMP_MOD_LFO_LEVEL);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_Osc2AmpModEnvLevel, _OSC_2_EVENT * 10000 + _OSC_AMP_MOD_ENV_LEVEL);

	// Widgets types
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_Osc1FilterSend1, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_Osc1FilterSend2, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->horizontalSlider_Osc1Symetry, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_Osc1FreqModLfoLevel, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_Osc1FreqModEnvLevel, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_Osc1PwmModLfoLevel, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_Osc1PwmModEnvLevel, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_Osc1AmpModLfoLevel, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_Osc1AmpModEnvLevel, _CONTROL_TYPE_DIAL);

	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->verticalSlider_Osc1unisonLev1, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->verticalSlider_Osc1unisonLev2, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->verticalSlider_Osc1unisonLev3, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->verticalSlider_Osc1unisonLev4, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->verticalSlider_Osc1unisonLev5, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->verticalSlider_Osc1unisonLev6, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->verticalSlider_Osc1unisonLev7, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->verticalSlider_Osc1unisonLev8, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->verticalSlider_Osc1unisonLev9, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->verticalSlider_Osc1unisonLevDist, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->verticalSlider_Osc1unisonLevDetune, _CONTROL_TYPE_SLIDER);

	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_Osc2FilterSend1, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_Osc2FilterSend2, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->horizontalSlider_Osc2Symetry, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_Osc2FreqModLfoLevel, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_Osc2FreqModEnvLevel, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_Osc2PwmModLfoLevel, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_Osc2PwmModEnvLevel, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_Osc2AmpModLfoLevel, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_Osc2AmpModEnvLevel, _CONTROL_TYPE_DIAL);
}

void OscilatorsTabUiHandling::update()
{
	static bool oneTimeInitialized = false;

	if (!oneTimeInitialized)
	{
		oneTimeInitialized = true;

		mainWindow->comboBox_Osc1Waveform->blockSignals(true);
		mainWindow->comboBox_Osc1Waveform->addItems(stringWaveformsList);
		mainWindow->comboBox_Osc1Waveform->blockSignals(false);

		mainWindow->comboBox_Osc1TuneOct->blockSignals(true);
		mainWindow->comboBox_Osc1TuneSemi->blockSignals(true);
		mainWindow->comboBox_Osc1TuneCents->blockSignals(true);
		for (int i = mod_synth_get_osc_detune_min_octave(); i <= mod_synth_get_osc_detune_max_octave(); i++)
		{
			mainWindow->comboBox_Osc1TuneOct->addItem(QString::number(i));
		}

		for (int i = mod_synth_get_osc_detune_min_semitones(); i <= mod_synth_get_osc_detune_max_semitones(); i++)
		{
			mainWindow->comboBox_Osc1TuneSemi->addItem(QString::number(i));
		}

		for (int i = 4 * mod_synth_get_osc_detune_min_cents(); i <= 4 * mod_synth_get_osc_detune_max_cents(); i++)
		{
			// 0.25 steps
			mainWindow->comboBox_Osc1TuneCents->addItem(QString::number(i / 4.f));
		}

		mainWindow->comboBox_Osc1TuneOct->blockSignals(false);
		mainWindow->comboBox_Osc1TuneSemi->blockSignals(false);
		mainWindow->comboBox_Osc1TuneCents->blockSignals(false);

		mainWindow->comboBox_Osc1UnisonMode->blockSignals(true);
		mainWindow->comboBox_Osc1UnisonMode->addItems(stringUnisonModesList);
		mainWindow->comboBox_Osc1UnisonMode->blockSignals(false);

		mainWindow->comboBox_Osc1HammondMode->blockSignals(true);
		mainWindow->comboBox_Osc1HammondMode->addItems(stringHammondModesList);
		mainWindow->comboBox_Osc1HammondMode->setVisible(false);
		mainWindow->comboBox_Osc1HammondMode->blockSignals(false);

		mainWindow->comboBox_Osc1FreqModEnv->blockSignals(true);
		mainWindow->comboBox_Osc1FreqModEnv->addItems(MainWindow::getInstance()->stringEnvsList);
		mainWindow->comboBox_Osc1FreqModEnv->blockSignals(false);

		mainWindow->comboBox_Osc1FreqModLfo->blockSignals(true);
		mainWindow->comboBox_Osc1FreqModLfo->addItems(MainWindow::getInstance()->stringLfosList);
		mainWindow->comboBox_Osc1FreqModLfo->blockSignals(false);

		mainWindow->comboBox_Osc1PwmModEnv->blockSignals(true);
		mainWindow->comboBox_Osc1PwmModEnv->addItems(MainWindow::getInstance()->stringEnvsList);
		mainWindow->comboBox_Osc1PwmModEnv->blockSignals(false);

		mainWindow->comboBox_Osc1PwmModLfo->blockSignals(true);
		mainWindow->comboBox_Osc1PwmModLfo->addItems(MainWindow::getInstance()->stringLfosList);
		mainWindow->comboBox_Osc1PwmModLfo->blockSignals(false);

		mainWindow->comboBox_Osc1AmpModEnv->blockSignals(true);
		mainWindow->comboBox_Osc1AmpModEnv->addItems(MainWindow::getInstance()->stringEnvsList);
		mainWindow->comboBox_Osc1AmpModEnv->blockSignals(false);

		mainWindow->comboBox_Osc1AmpModLfo->blockSignals(true);
		mainWindow->comboBox_Osc1AmpModLfo->addItems(MainWindow::getInstance()->stringLfosList);
		mainWindow->comboBox_Osc1AmpModLfo->blockSignals(false);
		
		
		mainWindow->comboBox_Osc2Waveform->blockSignals(true);
		mainWindow->comboBox_Osc2Waveform->addItems(stringWaveformsList);
		mainWindow->comboBox_Osc2Waveform->blockSignals(false);

		mainWindow->comboBox_Osc2TuneOct->blockSignals(true);
		mainWindow->comboBox_Osc2TuneSemi->blockSignals(true);
		mainWindow->comboBox_Osc2TuneCents->blockSignals(true);
		for (int i = mod_synth_get_osc_detune_min_octave(); i <= mod_synth_get_osc_detune_max_octave(); i++)
		{
			mainWindow->comboBox_Osc2TuneOct->addItem(QString::number(i));
		}

		for (int i = mod_synth_get_osc_detune_min_semitones(); i <= mod_synth_get_osc_detune_max_semitones(); i++)
		{
			mainWindow->comboBox_Osc2TuneSemi->addItem(QString::number(i));
		}

		for (int i = 4 * mod_synth_get_osc_detune_min_cents(); i <= 4 * mod_synth_get_osc_detune_max_cents(); i++)
		{
			// 0.25 steps
			mainWindow->comboBox_Osc2TuneCents->addItem(QString::number(i / 4.f));
		}

		mainWindow->comboBox_Osc2TuneOct->blockSignals(false);
		mainWindow->comboBox_Osc2TuneSemi->blockSignals(false);
		mainWindow->comboBox_Osc2TuneCents->blockSignals(false);

		mainWindow->comboBox_Osc2FreqModEnv->blockSignals(true);
		mainWindow->comboBox_Osc2FreqModEnv->addItems(MainWindow::getInstance()->stringEnvsList);
		mainWindow->comboBox_Osc2FreqModEnv->blockSignals(false);

		mainWindow->comboBox_Osc2FreqModLfo->blockSignals(true);
		mainWindow->comboBox_Osc2FreqModLfo->addItems(MainWindow::getInstance()->stringLfosList);
		mainWindow->comboBox_Osc2FreqModLfo->blockSignals(false);

		mainWindow->comboBox_Osc2PwmModEnv->blockSignals(true);
		mainWindow->comboBox_Osc2PwmModEnv->addItems(MainWindow::getInstance()->stringEnvsList);
		mainWindow->comboBox_Osc2PwmModEnv->blockSignals(false);

		mainWindow->comboBox_Osc2PwmModLfo->blockSignals(true);
		mainWindow->comboBox_Osc2PwmModLfo->addItems(MainWindow::getInstance()->stringLfosList);
		mainWindow->comboBox_Osc2PwmModLfo->blockSignals(false);

		mainWindow->comboBox_Osc2AmpModEnv->blockSignals(true);
		mainWindow->comboBox_Osc2AmpModEnv->addItems(MainWindow::getInstance()->stringEnvsList);
		mainWindow->comboBox_Osc2AmpModEnv->blockSignals(false);

		mainWindow->comboBox_Osc2AmpModLfo->blockSignals(true);
		mainWindow->comboBox_Osc2AmpModLfo->addItems(MainWindow::getInstance()->stringLfosList);
		mainWindow->comboBox_Osc2AmpModLfo->blockSignals(false);
	}

	mainWindow->comboBox_Osc1Waveform->blockSignals(true);
	mainWindow->comboBox_Osc1Waveform->setCurrentIndex(mod_synth_get_active_osc1_waveform());
	mainWindow->comboBox_Osc1Waveform->blockSignals(false);

	mainWindow->horizontalSlider_Osc1Symetry->blockSignals(true);
	mainWindow->horizontalSlider_Osc1Symetry->setValue(mod_synth_get_active_osc1_pwm_percents());
	mainWindow->horizontalSlider_Osc1Symetry->blockSignals(false);

	mainWindow->comboBox_Osc1TuneOct->blockSignals(true);
	mainWindow->comboBox_Osc1TuneOct->setCurrentIndex(mod_synth_get_active_osc1_detune_octave() - mod_synth_get_osc_detune_min_octave());
	mainWindow->comboBox_Osc1TuneOct->blockSignals(false);

	mainWindow->comboBox_Osc1TuneSemi->blockSignals(true);
	mainWindow->comboBox_Osc1TuneSemi->setCurrentIndex(mod_synth_get_active_osc1_detune_semitones() - mod_synth_get_osc_detune_min_semitones());
	mainWindow->comboBox_Osc1TuneSemi->blockSignals(false);

	mainWindow->comboBox_Osc1TuneCents->blockSignals(true);
	mainWindow->comboBox_Osc1TuneCents->setCurrentIndex(mod_synth_get_active_osc1_detune_cents() - mod_synth_get_osc_detune_min_cents() * 4.f);
	mainWindow->comboBox_Osc1TuneCents->blockSignals(false);

	mainWindow->dial_Osc1FilterSend1->blockSignals(true);
	mainWindow->dial_Osc1FilterSend1->setValue(mod_synth_get_active_osc1_send_filter_1());
	mainWindow->dial_Osc1FilterSend1->blockSignals(false);

	mainWindow->dial_Osc1FilterSend2->blockSignals(true);
	mainWindow->dial_Osc1FilterSend2->setValue(mod_synth_get_active_osc1_send_filter_2());
	mainWindow->dial_Osc1FilterSend2->blockSignals(false);

	mainWindow->comboBox_Osc1FreqModLfo->blockSignals(true);
	mainWindow->comboBox_Osc1FreqModLfo->setCurrentIndex(mod_synth_get_active_osc1_freq_mod_lfo());
	mainWindow->comboBox_Osc1FreqModLfo->blockSignals(false);

	mainWindow->dial_Osc1FreqModLfoLevel->blockSignals(true);
	mainWindow->dial_Osc1FreqModLfoLevel->setValue(mod_synth_get_active_osc1_freq_mod_lfo_level());
	mainWindow->dial_Osc1FreqModLfoLevel->blockSignals(false);

	mainWindow->comboBox_Osc1FreqModEnv->blockSignals(true);
	mainWindow->comboBox_Osc1FreqModEnv->setCurrentIndex(mod_synth_get_active_osc1_freq_mod_env());
	mainWindow->comboBox_Osc1FreqModEnv->blockSignals(false);

	mainWindow->dial_Osc1FreqModEnvLevel->blockSignals(true);
	mainWindow->dial_Osc1FreqModEnvLevel->setValue(mod_synth_get_active_osc1_freq_mod_env_level());
	mainWindow->dial_Osc1FreqModEnvLevel->blockSignals(false);

	mainWindow->comboBox_Osc1PwmModLfo->blockSignals(true);
	mainWindow->comboBox_Osc1PwmModLfo->setCurrentIndex(mod_synth_get_active_osc1_pwm_mod_lfo());
	mainWindow->comboBox_Osc1PwmModLfo->blockSignals(false);

	mainWindow->dial_Osc1PwmModLfoLevel->blockSignals(true);
	mainWindow->dial_Osc1PwmModLfoLevel->setValue(mod_synth_get_active_osc1_pwm_mod_lfo_level());
	mainWindow->dial_Osc1PwmModLfoLevel->blockSignals(false);

	mainWindow->comboBox_Osc1PwmModEnv->blockSignals(true);
	mainWindow->comboBox_Osc1PwmModEnv->setCurrentIndex(mod_synth_get_active_osc1_pwm_mod_env());
	mainWindow->comboBox_Osc1PwmModEnv->blockSignals(false);

	mainWindow->dial_Osc1PwmModEnvLevel->blockSignals(true);
	mainWindow->dial_Osc1PwmModEnvLevel->setValue(mod_synth_get_active_osc1_pwm_mod_env_level());
	mainWindow->dial_Osc1PwmModEnvLevel->blockSignals(false);

	mainWindow->comboBox_Osc1AmpModLfo->blockSignals(true);
	mainWindow->comboBox_Osc1AmpModLfo->setCurrentIndex(mod_synth_get_active_osc1_amp_mod_lfo());
	mainWindow->comboBox_Osc1AmpModLfo->blockSignals(false);

	mainWindow->dial_Osc1AmpModLfoLevel->blockSignals(true);
	mainWindow->dial_Osc1AmpModLfoLevel->setValue(mod_synth_get_active_osc1_amp_mod_lfo_level());
	mainWindow->dial_Osc1AmpModLfoLevel->blockSignals(false);

	mainWindow->comboBox_Osc1AmpModEnv->blockSignals(true);
	mainWindow->comboBox_Osc1AmpModEnv->setCurrentIndex(mod_synth_get_active_osc1_amp_mod_env());
	mainWindow->comboBox_Osc1AmpModEnv->blockSignals(false);

	mainWindow->dial_Osc1AmpModEnvLevel->blockSignals(true);
	mainWindow->dial_Osc1AmpModEnvLevel->setValue(mod_synth_get_active_osc1_amp_mod_env_level());
	mainWindow->dial_Osc1AmpModEnvLevel->blockSignals(false);

	mainWindow->comboBox_Osc1UnisonMode->blockSignals(true);
	mainWindow->comboBox_Osc1UnisonMode->setCurrentIndex(mod_synth_get_active_osc1_unison_mode());
	mainWindow->comboBox_Osc1UnisonMode->blockSignals(false);

	//	osc1unisonModeSelected(getActiveOsc1unisonMode()); <<<<<<<<<<<<<<<<<<

	mainWindow->verticalSlider_Osc1unisonLev1->blockSignals(true);
	mainWindow->verticalSlider_Osc1unisonLev1->setValue(mod_synth_get_active_osc1_harmonies_levels(0));
	mainWindow->verticalSlider_Osc1unisonLev1->blockSignals(false);

	mainWindow->verticalSlider_Osc1unisonLev2->blockSignals(true);
	mainWindow->verticalSlider_Osc1unisonLev2->setValue(mod_synth_get_active_osc1_harmonies_levels(1));
	mainWindow->verticalSlider_Osc1unisonLev2->blockSignals(false);

	mainWindow->verticalSlider_Osc1unisonLev3->blockSignals(true);
	mainWindow->verticalSlider_Osc1unisonLev3->setValue(mod_synth_get_active_osc1_harmonies_levels(2));
	mainWindow->verticalSlider_Osc1unisonLev3->blockSignals(false);

	mainWindow->verticalSlider_Osc1unisonLev4->blockSignals(true);
	mainWindow->verticalSlider_Osc1unisonLev4->setValue(mod_synth_get_active_osc1_harmonies_levels(3));
	mainWindow->verticalSlider_Osc1unisonLev4->blockSignals(false);

	mainWindow->verticalSlider_Osc1unisonLev5->blockSignals(true);
	mainWindow->verticalSlider_Osc1unisonLev5->setValue(mod_synth_get_active_osc1_harmonies_levels(4));
	mainWindow->verticalSlider_Osc1unisonLev5->blockSignals(false);

	mainWindow->verticalSlider_Osc1unisonLev6->blockSignals(true);
	mainWindow->verticalSlider_Osc1unisonLev6->setValue(mod_synth_get_active_osc1_harmonies_levels(5));
	mainWindow->verticalSlider_Osc1unisonLev6->blockSignals(false);

	mainWindow->verticalSlider_Osc1unisonLev7->blockSignals(true);
	mainWindow->verticalSlider_Osc1unisonLev7->setValue(mod_synth_get_active_osc1_harmonies_levels(6));
	mainWindow->verticalSlider_Osc1unisonLev7->blockSignals(false);

	mainWindow->verticalSlider_Osc1unisonLev8->blockSignals(true);
	mainWindow->verticalSlider_Osc1unisonLev8->setValue(mod_synth_get_active_osc1_harmonies_levels(7));
	mainWindow->verticalSlider_Osc1unisonLev8->blockSignals(false);

	mainWindow->verticalSlider_Osc1unisonLevDetune->blockSignals(true);
	mainWindow->verticalSlider_Osc1unisonLevDetune->setValue(mod_synth_get_active_osc1_harmonies_detune_factor());
	mainWindow->verticalSlider_Osc1unisonLevDetune->blockSignals(false);

	mainWindow->verticalSlider_Osc1unisonLevDist->blockSignals(true);
	mainWindow->verticalSlider_Osc1unisonLevDist->setValue(mod_synth_get_active_osc1_harmonies_dist_factor());
	mainWindow->verticalSlider_Osc1unisonLevDist->blockSignals(false);

	if (mod_synth_get_active_osc1_unison_mode() == _OSC_UNISON_MODE_HAMMOND)
	{
		mainWindow->comboBox_Osc1HammondMode->blockSignals(true);
		mainWindow->comboBox_Osc1HammondMode->setVisible(true);
		mainWindow->comboBox_Osc1HammondMode->setCurrentIndex(mod_synth_get_active_osc1_hammond_mode());
		mainWindow->comboBox_Osc1HammondMode->blockSignals(false);

		mainWindow->checkBox_Osc1unisonSqr->blockSignals(true);
		mainWindow->checkBox_Osc1unisonSqr->setVisible(false);
		mainWindow->checkBox_Osc1unisonSqr->blockSignals(false);
		// Disable square wave
		mod_synth_vco_event_bool(_OSC_1_EVENT, _OSC_1_UNISON_SQUARE, false);
		mainWindow->checkBox_Osc1unisonSqr->blockSignals(true);
		mainWindow->checkBox_Osc1unisonSqr->setChecked(false);
		mainWindow->checkBox_Osc1unisonSqr->blockSignals(false);
	}
	
	osc1enabled = mod_synth_get_active_osc1_enable_state();  
	mainWindow->checkBox_enableOSC1->blockSignals(true);		
	mainWindow->checkBox_enableOSC1->setChecked(osc1enabled);
	mainWindow->checkBox_enableOSC1->blockSignals(false);
	if (osc1enabled)
	{
		mainWindow->groupBox_Osc1->setEnabled(true);
	}
	else
	{
		mainWindow->groupBox_Osc1->setEnabled(false);
	}
	
	mainWindow->comboBox_Osc2Waveform->blockSignals(true);
	mainWindow->comboBox_Osc2Waveform->setCurrentIndex(mod_synth_get_active_osc2_waveform());
	mainWindow->comboBox_Osc2Waveform->blockSignals(false);

	mainWindow->horizontalSlider_Osc2Symetry->blockSignals(true);
	mainWindow->horizontalSlider_Osc2Symetry->setValue(mod_synth_get_active_osc2_pwm_percents());
	mainWindow->horizontalSlider_Osc2Symetry->blockSignals(false);

	mainWindow->comboBox_Osc2TuneOct->blockSignals(true);
	mainWindow->comboBox_Osc2TuneOct->setCurrentIndex(mod_synth_get_active_osc2_detune_octave() - mod_synth_get_osc_detune_min_octave());
	mainWindow->comboBox_Osc2TuneOct->blockSignals(false);

	mainWindow->comboBox_Osc2TuneSemi->blockSignals(true);
	mainWindow->comboBox_Osc2TuneSemi->setCurrentIndex(mod_synth_get_active_osc2_detune_semitones() - mod_synth_get_osc_detune_min_semitones());
	mainWindow->comboBox_Osc2TuneSemi->blockSignals(false);

	mainWindow->comboBox_Osc2TuneCents->blockSignals(true);
	mainWindow->comboBox_Osc2TuneCents->setCurrentIndex(mod_synth_get_active_osc2_detune_cents() - mod_synth_get_osc_detune_min_cents() * 4.f);
	mainWindow->comboBox_Osc2TuneCents->blockSignals(false);

	mainWindow->dial_Osc2FilterSend1->blockSignals(true);
	mainWindow->dial_Osc2FilterSend1->setValue(mod_synth_get_active_osc2_send_filter_1());
	mainWindow->dial_Osc2FilterSend1->blockSignals(false);

	mainWindow->dial_Osc2FilterSend2->blockSignals(true);
	mainWindow->dial_Osc2FilterSend2->setValue(mod_synth_get_active_osc2_send_filter_2());
	mainWindow->dial_Osc2FilterSend2->blockSignals(false);

	mainWindow->checkBox_Osc2SyncOsc1->blockSignals(true);
	mainWindow->checkBox_Osc2SyncOsc1->setChecked(mod_synth_get_active_osc2_sync_is_on_state());
	mainWindow->checkBox_Osc2SyncOsc1->blockSignals(false);

	//mainWindow->check_BoxSyncOsc2FixTone->blockSignals(true);
	//mainWindow->check_BoxSyncOsc2FixTone->setChecked(getActiveOsc2FixToneIsOnState());
	//mainWindow->check_BoxSyncOsc2FixTone->blockSignals(false);

	mainWindow->comboBox_Osc2FreqModLfo->blockSignals(true);
	mainWindow->comboBox_Osc2FreqModLfo->setCurrentIndex(mod_synth_get_active_osc2_freq_mod_lfo());
	mainWindow->comboBox_Osc2FreqModLfo->blockSignals(false);

	mainWindow->dial_Osc2FreqModLfoLevel->blockSignals(true);
	mainWindow->dial_Osc2FreqModLfoLevel->setValue(mod_synth_get_active_osc2_freq_mod_lfo_level());
	mainWindow->dial_Osc2FreqModLfoLevel->blockSignals(false);

	mainWindow->comboBox_Osc2FreqModEnv->blockSignals(true);
	mainWindow->comboBox_Osc2FreqModEnv->setCurrentIndex(mod_synth_get_active_osc2_freq_mod_env());
	mainWindow->comboBox_Osc2FreqModEnv->blockSignals(false);

	mainWindow->dial_Osc2FreqModEnvLevel->blockSignals(true);
	mainWindow->dial_Osc2FreqModEnvLevel->setValue(mod_synth_get_active_osc2_freq_mod_env_level());
	mainWindow->dial_Osc2FreqModEnvLevel->blockSignals(false);

	mainWindow->comboBox_Osc2PwmModLfo->blockSignals(true);
	mainWindow->comboBox_Osc2PwmModLfo->setCurrentIndex(mod_synth_get_active_osc2_pwm_mod_lfo());
	mainWindow->comboBox_Osc2PwmModLfo->blockSignals(false);

	mainWindow->dial_Osc2PwmModLfoLevel->blockSignals(true);
	mainWindow->dial_Osc2PwmModLfoLevel->setValue(mod_synth_get_active_osc2_pwm_mod_lfo_level());
	mainWindow->dial_Osc2PwmModLfoLevel->blockSignals(false);

	mainWindow->comboBox_Osc2PwmModEnv->blockSignals(true);
	mainWindow->comboBox_Osc2PwmModEnv->setCurrentIndex(mod_synth_get_active_osc2_pwm_mod_env());
	mainWindow->comboBox_Osc2PwmModEnv->blockSignals(false);

	mainWindow->dial_Osc2PwmModEnvLevel->blockSignals(true);
	mainWindow->dial_Osc2PwmModEnvLevel->setValue(mod_synth_get_active_osc2_pwm_mod_env_level());
	mainWindow->dial_Osc2PwmModEnvLevel->blockSignals(false);

	mainWindow->comboBox_Osc2AmpModLfo->blockSignals(true);
	mainWindow->comboBox_Osc2AmpModLfo->setCurrentIndex(mod_synth_get_active_osc2_amp_mod_lfo());
	mainWindow->comboBox_Osc2AmpModLfo->blockSignals(false);

	mainWindow->dial_Osc2AmpModLfoLevel->blockSignals(true);
	mainWindow->dial_Osc2AmpModLfoLevel->setValue(mod_synth_get_active_osc2_amp_mod_lfo_level());
	mainWindow->dial_Osc2AmpModLfoLevel->blockSignals(false);

	mainWindow->comboBox_Osc2AmpModEnv->blockSignals(true);
	mainWindow->comboBox_Osc2AmpModEnv->setCurrentIndex(mod_synth_get_active_osc2_amp_mod_env());
	mainWindow->comboBox_Osc2AmpModEnv->blockSignals(false);

	mainWindow->dial_Osc2AmpModEnvLevel->blockSignals(true);
	mainWindow->dial_Osc2AmpModEnvLevel->setValue(mod_synth_get_active_osc2_amp_mod_env_level());
	mainWindow->dial_Osc2AmpModEnvLevel->blockSignals(false);

	osc2enabled = mod_synth_get_active_osc2_enable_state();  
	mainWindow->checkBox_enableOSC2->blockSignals(true);
	mainWindow->checkBox_enableOSC2->setChecked(osc2enabled);
	mainWindow->checkBox_enableOSC2->blockSignals(false);
	if (osc2enabled)
	{
		mainWindow->groupBox_Osc2->setEnabled(true);
	}
	else
	{
		mainWindow->groupBox_Osc2->setEnabled(false);
	}

}


void  OscilatorsTabUiHandling::osc1enDisSliders(uint16_t mask)
{
	if (mask & 0x01)
		mainWindow->verticalSlider_Osc1unisonLev1->setVisible(true);
	else
		mainWindow->verticalSlider_Osc1unisonLev1->setVisible(false);

	if (mask & 0x02)
		mainWindow->verticalSlider_Osc1unisonLev2->setVisible(true);
	else
		mainWindow->verticalSlider_Osc1unisonLev2->setVisible(false);

	if (mask & 0x04)
		mainWindow->verticalSlider_Osc1unisonLev3->setVisible(true);
	else
		mainWindow->verticalSlider_Osc1unisonLev3->setVisible(false);

	if (mask & 0x08)
		mainWindow->verticalSlider_Osc1unisonLev4->setVisible(true);
	else
		mainWindow->verticalSlider_Osc1unisonLev4->setVisible(false);

	if (mask & 0x10)
		mainWindow->verticalSlider_Osc1unisonLev5->setVisible(true);
	else
		mainWindow->verticalSlider_Osc1unisonLev5->setVisible(false);

	if (mask & 0x20)
		mainWindow->verticalSlider_Osc1unisonLev6->setVisible(true);
	else
		mainWindow->verticalSlider_Osc1unisonLev6->setVisible(false);

	if (mask & 0x40)
		mainWindow->verticalSlider_Osc1unisonLev7->setVisible(true);
	else
		mainWindow->verticalSlider_Osc1unisonLev7->setVisible(false);

	if (mask & 0x80)
		mainWindow->verticalSlider_Osc1unisonLev8->setVisible(true);
	else
		mainWindow->verticalSlider_Osc1unisonLev8->setVisible(false);

	if (mask & 0x100)
		mainWindow->verticalSlider_Osc1unisonLev9->setVisible(true);
	else
		mainWindow->verticalSlider_Osc1unisonLev9->setVisible(false);
}

void OscilatorsTabUiHandling::osc1setUnisonLabales(QList<QString> str, uint16_t mask)
{
	int i = 0;

	if (mask & 0x01)
		mainWindow->label_Osc1HarmLevel1->setText(str.at(i++));
	else
		mainWindow->label_Osc1HarmLevel1->setText(" ");

	if (mask & 0x02)
		mainWindow->label_Osc1HarmLevel2->setText(str.at(i++));
	else
		mainWindow->label_Osc1HarmLevel2->setText(" ");

	if (mask & 0x04)
		mainWindow->label_Osc1HarmLevel3->setText(str.at(i++));
	else
		mainWindow->label_Osc1HarmLevel3->setText(" ");

	if (mask & 0x08)
		mainWindow->label_Osc1HarmLevel4->setText(str.at(i++));
	else
		mainWindow->label_Osc1HarmLevel4->setText(" ");

	if (mask & 0x10)
		mainWindow->label_Osc1HarmLevel5->setText(str.at(i++));
	else
		mainWindow->label_Osc1HarmLevel5->setText(" ");

	if (mask & 0x20)
		mainWindow->label_Osc1HarmLevel6->setText(str.at(i++));
	else
		mainWindow->label_Osc1HarmLevel6->setText(" ");

	if (mask & 0x40)
		mainWindow->label_Osc1HarmLevel7->setText(str.at(i++));
	else
		mainWindow->label_Osc1HarmLevel7->setText(" ");

	if (mask & 0x80)
		mainWindow->label_Osc1HarmLevel8->setText(str.at(i++));
	else
		mainWindow->labelOsc1HarmLevel8->setText(" ");

	if (mask & 0x100)
		mainWindow->label_Osc1HarmLevel9->setText(str.at(i++));
	else
		mainWindow->label_Osc1HarmLevel9->setText(" ");
}

void OscilatorsTabUiHandling::osc1setUnisonLabales(int mode)
{
	switch (mode)
	{
	case _OSC_UNISON_MODE_12345678:
		osc1enDisSliders(0xff);
		osc1setUnisonLabales(stringUnisonLabelsHarmonized, 0xff);
		break;

	case _OSC_UNISON_MODE_HAMMOND:
		osc1enDisSliders(0x1ff);
		osc1setUnisonLabales(stringUnisonLabelsHammond, 0x1ff);
		break;

	case _OSC_UNISON_MODE_OCTAVES:
		osc1enDisSliders(0x8b);
		osc1setUnisonLabales(stringUnisonLabelsOctaves, 0x8b);
		break;

	case _OSC_UNISON_MODE_C_CHORD:
		osc1enDisSliders(0x07);
		osc1setUnisonLabales(stringUnisonLabelsCchord, 0x07);
		break;

	case _OSC_UNISON_MODE_Cm_CHORD:
		osc1enDisSliders(0x07);
		osc1setUnisonLabales(stringUnisonLabelsCmChord, 0x07);
		break;

	case _OSC_UNISON_MODE_C7_CHORD:
		osc1enDisSliders(0x0f);
		osc1setUnisonLabales(stringUnisonLabelsC7chord, 0x0f);
		break;

	case _OSC_UNISON_MODE_Cm7_CHORD:
		osc1enDisSliders(0x0f);
		osc1setUnisonLabales(stringUnisonLabelsCm7chord, 0x0f);
		break;

	default:
		return;
	}
}

void OscilatorsTabUiHandling::osc1SetUnisonMode(int mode)
{
	int i;

	osc1setUnisonLabales(mode);
	if (mode != _OSC_UNISON_MODE_HAMMOND)
	{
		for (i = 0; i < mod_synth_get_osc1_num_of_drawbars(); i++)
		{
			unisonLevelSliders[i]->blockSignals(true);
			unisonLevelSliders[i]->setSingleStep(1);
			unisonLevelSliders[i]->setMaximum(100);
			unisonLevelSliders[i]->setMinimum(0);
			unisonLevelSliders[i]->setInvertedAppearance(false);
			unisonLevelSliders[i]->blockSignals(false);
		}

		mainWindow->comboBox_Osc1HammondMode->blockSignals(true);
		mainWindow->comboBox_Osc1HammondMode->setVisible(false);
		mainWindow->comboBox_Osc1HammondMode->blockSignals(false);

		mainWindow->checkBox_Osc1unisonSqr->blockSignals(true);
		mainWindow->checkBox_Osc1unisonSqr->setVisible(true);
		mainWindow->checkBox_Osc1unisonSqr->blockSignals(false);

	}
	else if (mode == _OSC_UNISON_MODE_HAMMOND)
	{
		for (i = 0; i < mod_synth_get_osc1_num_of_drawbars(); i++)
		{
			unisonLevelSliders[i]->blockSignals(true);
			unisonLevelSliders[i]->setSingleStep(12);
			unisonLevelSliders[i]->setMaximum(96);
			unisonLevelSliders[i]->setMinimum(0);
			unisonLevelSliders[i]->setInvertedAppearance(true);
			unisonLevelSliders[i]->blockSignals(false);
		}

		mainWindow->comboBox_Osc1HammondMode->blockSignals(true);
		mainWindow->comboBox_Osc1HammondMode->setVisible(true);
		mainWindow->comboBox_Osc1HammondMode->blockSignals(false);

		mainWindow->checkBox_Osc1unisonSqr->blockSignals(true);
		mainWindow->checkBox_Osc1unisonSqr->setVisible(false);
		mainWindow->checkBox_Osc1unisonSqr->blockSignals(false);
		
		mainWindow->checkBox_Osc1unisonSqr->blockSignals(true);
		mainWindow->checkBox_Osc1unisonSqr->setChecked(false);
		mainWindow->checkBox_Osc1unisonSqr->blockSignals(false);
	}
}


// Slots

void OscilatorsTabUiHandling::osc1unisonModeSelected(int val)
{
	mod_synth_vco_event(_OSC_1_EVENT, _OSC_UNISON_MODE, val);
	if (val == _OSC_UNISON_MODE_HAMMOND)
	{
		// Disable square wave	
		mod_synth_vco_event_bool(_OSC_1_EVENT, _OSC_1_UNISON_SQUARE, false);
	}
}
	

void OscilatorsTabUiHandling::osc1waveformSelected(int val)
{
	mod_synth_vco_event(_OSC_1_EVENT, _OSC_PARAM_WAVEFORM, val);
}

void OscilatorsTabUiHandling::osc1symmetryChanged(int val)
{
	char str[5];

	//	sprintf(str, "%i%c", val, '%');
	//	ui->lineEditOsc1SymmetryVal->setText(str);
	mod_synth_vco_event(_OSC_1_EVENT, _OSC_PWM_SYMMETRY, val);
	sprintf(mssg1, "Osc1 Symetryl: %.2f", (float)val / 100.0);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void OscilatorsTabUiHandling::osc1detuneOctaveChanged(int val)
{
	mod_synth_vco_event(_OSC_1_EVENT, _OSC_DETUNE_OCTAVE, val);
}

void OscilatorsTabUiHandling::osc1detuneSeminotesChanged(int val)
{
	mod_synth_vco_event(_OSC_1_EVENT, _OSC_DETUNE_SEMITONES, val);
}

void OscilatorsTabUiHandling::osc1detuneCentsChanged(int val)
{
	mod_synth_vco_event(_OSC_1_EVENT, _OSC_DETUNE_CENTS, val);
}

void OscilatorsTabUiHandling::osc1SendFilter1Changed(int val)
{
	mod_synth_vco_event(_OSC_1_EVENT, _OSC_FILTER_SEND_1, val);
	sprintf(mssg1, "Osc1 Filter 1 Send Level: %.2f", (float)val / 100.0);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void OscilatorsTabUiHandling::osc1SendFilter2Changed(int val)
{
	mod_synth_vco_event(_OSC_1_EVENT, _OSC_FILTER_SEND_2, val);
	sprintf(mssg1, "Osc1 Filter 2 Send Level: %.2f", (float)val / 100.0);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void OscilatorsTabUiHandling::osc1FreqModLfoChanged(int val)
{
	mod_synth_vco_event(_OSC_1_EVENT, _OSC_FREQ_MOD_LFO, val);
}

void OscilatorsTabUiHandling::osc1FreqModLevelLfoChanged(int val)
{
	int updateUiWrapper = mod_synth_log_scale_100_int(0, 100, 10, val);
	mod_synth_vco_event(_OSC_1_EVENT, _OSC_FREQ_MOD_LFO_LEVEL, updateUiWrapper);
	sprintf(mssg1, "Osc1 Freq Modulation LFO Level: %.2f", (float)updateUiWrapper / 100.0);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void OscilatorsTabUiHandling::osc1FreqModEnvChanged(int val)
{
	mod_synth_vco_event(_OSC_1_EVENT, _OSC_FREQ_MOD_ENV, val);
}

void OscilatorsTabUiHandling::osc1FreqModLevelEnvChanged(int val)
{
	mod_synth_vco_event(_OSC_1_EVENT, _OSC_FREQ_MOD_ENV_LEVEL, val);
	sprintf(mssg1, "Osc1 Freq Modulation ENV Level: %.2f", (float)val / 100.0);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void OscilatorsTabUiHandling::osc1PwmModLfoChanged(int val)
{
	mod_synth_vco_event(_OSC_1_EVENT, _OSC_PWM_MOD_LFO, val);
}

void OscilatorsTabUiHandling::osc1PwmModLevelLfoChanged(int val)
{
	mod_synth_vco_event(_OSC_1_EVENT, _OSC_PWM_MOD_LFO_LEVEL, val);
	sprintf(mssg1, "Osc1 PWM Modulation LFO Level: %.2f", (float)val / 100.0);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void OscilatorsTabUiHandling::osc1PwmModEnvChanged(int val)
{
	mod_synth_vco_event(_OSC_1_EVENT, _OSC_PWM_MOD_ENV, val);
}

void OscilatorsTabUiHandling::osc1PwmModLevelEnvChanged(int val)
{
	mod_synth_vco_event(_OSC_1_EVENT, _OSC_PWM_MOD_ENV_LEVEL, val);
	sprintf(mssg1, "Osc1 PWM Modulation ENV Level: %.2f", (float)val / 100.0);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void OscilatorsTabUiHandling::osc1AmpModLfoChanged(int val)
{
	mod_synth_vco_event(_OSC_1_EVENT, _OSC_AMP_MOD_LFO, val);
}

void OscilatorsTabUiHandling::osc1AmpModLevelLfoChanged(int val)
{
	mod_synth_vco_event(_OSC_1_EVENT, _OSC_AMP_MOD_LFO_LEVEL, val);
	sprintf(mssg1, "Osc1 Amp Modulation LFO Level: %.2f", (float)val / 100.0);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void OscilatorsTabUiHandling::osc1AmpModEnvChanged(int val)
{
	mod_synth_vco_event(_OSC_1_EVENT, _OSC_AMP_MOD_ENV, val);
}

void OscilatorsTabUiHandling::osc1AmpModLevelEnvChanged(int val)
{
	mod_synth_vco_event(_OSC_1_EVENT, _OSC_AMP_MOD_ENV_LEVEL, val);
	sprintf(mssg1, "Osc1 Amp Modulation ENV Level: %.2f", (float)val / 100.0);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void OscilatorsTabUiHandling::osc1hammondModeSelected(int val)
{
	if ((val >= _HAMMOND_PERCUSION_MODE_OFF) && (val <= _HAMMOND_PERCUSION_MODE_3RD_NORM_FAST))
	{
		mod_synth_vco_event(_OSC_1_EVENT, _OSC_HAMMOND_PERCUSION_MODE, val);
		update();
		MainWindow::getInstance()->updateGUI(); 
//		MainWindow::getInstance()->adsrsDialog->update();
//		MainWindow::getInstance()->lfosDialog->update();
	}
}

void OscilatorsTabUiHandling::osc1unisonLev1Changed(int val)
{
	if (mod_synth_get_active_osc1_unison_mode() != _OSC_UNISON_MODE_HAMMOND)
	{
		mod_synth_vco_event(_OSC_1_EVENT, _OSC_UNISON_LEVEL_1, val);
		sprintf(mssg1, "Osc1 Unison Level 1: %i", val);
	}
	else if (mod_synth_get_active_osc1_unison_mode() == _OSC_UNISON_MODE_HAMMOND)
	{
		// Hmmond registers: 0-8
		int reg = val / 12;  // 0-96 -> "0-8"
		unisonLevelSliders[0]->blockSignals(true);
		unisonLevelSliders[0]->setValue(reg * 12);
		unisonLevelSliders[0]->blockSignals(false);
		mod_synth_vco_event(_OSC_1_EVENT, _OSC_UNISON_LEVEL_1, reg * 12);
		sprintf(mssg1, "Osc1 Unison Level 1: %i", reg);
	}

	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void OscilatorsTabUiHandling::osc1unisonLev2Changed(int val)
{
	if (mod_synth_get_active_osc1_unison_mode() != _OSC_UNISON_MODE_HAMMOND)
	{
		mod_synth_vco_event(_OSC_1_EVENT, _OSC_UNISON_LEVEL_2, val);
		sprintf(mssg1, "Osc1 Unison Level 2: %i", val);
	}
	else if (mod_synth_get_active_osc1_unison_mode() == _OSC_UNISON_MODE_HAMMOND)
	{
		// Hmmond registers: 0-8
		int reg = val / 12;   // 0-96 -> "0-8"
		unisonLevelSliders[1]->blockSignals(true);
		unisonLevelSliders[1]->setValue(reg * 12);
		unisonLevelSliders[1]->blockSignals(false);
		mod_synth_vco_event(_OSC_1_EVENT, _OSC_UNISON_LEVEL_2, reg * 12);
		sprintf(mssg1, "Osc1 Unison Level 2: %i", reg);
	}

	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void OscilatorsTabUiHandling::osc1unisonLev3Changed(int val)
{
	if (mod_synth_get_active_osc1_unison_mode() != _OSC_UNISON_MODE_HAMMOND)
	{
		mod_synth_vco_event(_OSC_1_EVENT, _OSC_UNISON_LEVEL_3, val);
		sprintf(mssg1, "Osc1 Unison Level 3: %i", val);
	}
	else if (mod_synth_get_active_osc1_unison_mode() == _OSC_UNISON_MODE_HAMMOND)
	{
		// Hmmond registers: 0-8
		int reg = val / 12;   // 0-96 -> "0-8"
		unisonLevelSliders[2]->blockSignals(true);
		unisonLevelSliders[2]->setValue(reg * 12);
		unisonLevelSliders[2]->blockSignals(false);
		mod_synth_vco_event(_OSC_1_EVENT, _OSC_UNISON_LEVEL_3, reg * 12);
		sprintf(mssg1, "Osc1 Unison Level 3: %i", reg);
	}

	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void OscilatorsTabUiHandling::osc1unisonLev4Changed(int val)
{
	if (mod_synth_get_active_osc1_unison_mode() != _OSC_UNISON_MODE_HAMMOND)
	{
		mod_synth_vco_event(_OSC_1_EVENT, _OSC_UNISON_LEVEL_4, val);
		sprintf(mssg1, "Osc1 Unison Level 4: %i", val);
	}
	else if (mod_synth_get_active_osc1_unison_mode() == _OSC_UNISON_MODE_HAMMOND)
	{
		// Hmmond registers: 0-8
		int reg = val / 12;   // 0-96 -> "0-8"
		unisonLevelSliders[3]->blockSignals(true);
		unisonLevelSliders[3]->setValue(reg * 12);
		unisonLevelSliders[3]->blockSignals(false);
		mod_synth_vco_event(_OSC_1_EVENT, _OSC_UNISON_LEVEL_4, reg * 12);
		sprintf(mssg1, "Osc1 Unison Level 4: %i", reg);
	}

	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void OscilatorsTabUiHandling::osc1unisonLev5Changed(int val)
{
	if (mod_synth_get_active_osc1_unison_mode() != _OSC_UNISON_MODE_HAMMOND)
	{
		mod_synth_vco_event(_OSC_1_EVENT, _OSC_UNISON_LEVEL_5, val);
		sprintf(mssg1, "Osc1 Unison Level 5: %i", val);
	}
	else if (mod_synth_get_active_osc1_unison_mode() == _OSC_UNISON_MODE_HAMMOND)
	{
		// Hmmond registers: 0-8
		int reg = val / 12;   // 0-96 -> "0-8"
		unisonLevelSliders[4]->blockSignals(true);
		unisonLevelSliders[4]->setValue(reg * 12);
		unisonLevelSliders[4]->blockSignals(false);
		mod_synth_vco_event(_OSC_1_EVENT, _OSC_UNISON_LEVEL_5, reg * 12);
		sprintf(mssg1, "Osc1 Unison Level 5: %i", reg);
	}

	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void OscilatorsTabUiHandling::osc1unisonLev6Changed(int val)
{
	if (mod_synth_get_active_osc1_unison_mode() != _OSC_UNISON_MODE_HAMMOND)
	{
		mod_synth_vco_event(_OSC_1_EVENT, _OSC_UNISON_LEVEL_6, val);
		sprintf(mssg1, "Osc1 Unison Level 6: %i", val);
	}
	else if (mod_synth_get_active_osc1_unison_mode() == _OSC_UNISON_MODE_HAMMOND)
	{
		// Hmmond registers: 0-8
		int reg = val / 12;   // 0-96 -> "0-8"
		unisonLevelSliders[5]->blockSignals(true);
		unisonLevelSliders[5]->setValue(reg * 12);
		unisonLevelSliders[5]->blockSignals(false);
		mod_synth_vco_event(_OSC_1_EVENT, _OSC_UNISON_LEVEL_6, reg * 12);
		sprintf(mssg1, "Osc1 Unison Level 6: %i", reg);
	}

	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void OscilatorsTabUiHandling::osc1unisonLev7Changed(int val)
{
	if (mod_synth_get_active_osc1_unison_mode() != _OSC_UNISON_MODE_HAMMOND)
	{
		mod_synth_vco_event(_OSC_1_EVENT, _OSC_UNISON_LEVEL_7, val);
		sprintf(mssg1, "Osc1 Unison Level 7: %i", val);
	}
	else if (mod_synth_get_active_osc1_unison_mode() == _OSC_UNISON_MODE_HAMMOND)
	{
		// Hmmond registers: 0-8
		int reg = val / 12;   // 0-96 -> "0-8"
		unisonLevelSliders[6]->blockSignals(true);
		unisonLevelSliders[6]->setValue(reg * 12);
		unisonLevelSliders[6]->blockSignals(false);
		mod_synth_vco_event(_OSC_1_EVENT, _OSC_UNISON_LEVEL_7, reg * 12);
		sprintf(mssg1, "Osc1 Unison Level 7: %i", reg);
	}

	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void OscilatorsTabUiHandling::osc1unisonLev8Changed(int val)
{
	if (mod_synth_get_active_osc1_unison_mode() != _OSC_UNISON_MODE_HAMMOND)
	{
		mod_synth_vco_event(_OSC_1_EVENT, _OSC_UNISON_LEVEL_8, val);
		sprintf(mssg1, "Osc1 Unison Level 8: %i", val);
	}
	else if (mod_synth_get_active_osc1_unison_mode() == _OSC_UNISON_MODE_HAMMOND)
	{
		// Hmmond registers: 0-8
		int reg = val / 12;   // 0-96 -> "0-8"
		unisonLevelSliders[7]->blockSignals(true);
		unisonLevelSliders[7]->setValue(reg * 12);
		unisonLevelSliders[7]->blockSignals(false);
		mod_synth_vco_event(_OSC_1_EVENT, _OSC_UNISON_LEVEL_8, reg * 12);
		sprintf(mssg1, "Osc1 Unison Level 8: %i", reg);
	}

	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void OscilatorsTabUiHandling::osc1unisonLev9Changed(int val)
{
	if (mod_synth_get_active_osc1_unison_mode() != _OSC_UNISON_MODE_HAMMOND)
	{
		mod_synth_vco_event(_OSC_1_EVENT, _OSC_UNISON_LEVEL_9, val);
		sprintf(mssg1, "Osc1 Unison Level 9: %i", val);
	}
	else if (mod_synth_get_active_osc1_unison_mode() == _OSC_UNISON_MODE_HAMMOND)
	{
		// Hmmond registers: 0-8
		int reg = val / 12;   // 0-96 -> "0-8"
		unisonLevelSliders[8]->blockSignals(true);
		unisonLevelSliders[8]->setValue(reg * 12);
		unisonLevelSliders[8]->blockSignals(false);
		mod_synth_vco_event(_OSC_1_EVENT, _OSC_UNISON_LEVEL_9, reg * 12);
		sprintf(mssg1, "Osc1 Unison Level 9: %i", reg);
	}

	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void OscilatorsTabUiHandling::osc1unisonDistortionChanged(int val)
{
	mod_synth_vco_event(_OSC_1_EVENT, _OSC_UNISON_DISTORTION, val);
	sprintf(mssg1, "Osc1 Unison Distortion Level: %i", val);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void OscilatorsTabUiHandling::osc1unisonDetuneChanged(int val)
{
	mod_synth_vco_event(_OSC_1_EVENT, _OSC_UNISON_DETUNE, val);
	sprintf(mssg1, "Osc1 Unison Detune Level: %i", val);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void OscilatorsTabUiHandling::osc1unisonSquareChanges(bool val)
{
	mod_synth_vco_event_bool(_OSC_1_EVENT, _OSC_1_UNISON_SQUARE, val);
}

void OscilatorsTabUiHandling::osc1EnableChanged(bool val)
{
	if (val)
	{
		osc1enabled = true;
		mod_synth_enable_osc1();
	}
	else
	{
		osc1enabled = false;
		mod_synth_disable_osc1();
	}
}


void OscilatorsTabUiHandling::osc2waveformSelected(int val)
{
	mod_synth_vco_event(_OSC_2_EVENT, _OSC_PARAM_WAVEFORM, val);
}

void OscilatorsTabUiHandling::osc2symmetryChanged(int val)
{
	char str[5];

	//	sprintf(str, "%i%c", val, '%');
	//	ui->lineEditOsc2SymmetryVal->setText(str);
	mod_synth_vco_event(_OSC_2_EVENT, _OSC_PWM_SYMMETRY, val);
	sprintf(mssg1, "Osc2 Symetryl: %.2f", (float)val / 100.0);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void OscilatorsTabUiHandling::osc2detuneOctaveChanged(int val)
{
	mod_synth_vco_event(_OSC_2_EVENT, _OSC_DETUNE_OCTAVE, val);
}

void OscilatorsTabUiHandling::osc2detuneSeminotesChanged(int val)
{
	mod_synth_vco_event(_OSC_2_EVENT, _OSC_DETUNE_SEMITONES, val);
}

void OscilatorsTabUiHandling::osc2detuneCentsChanged(int val)
{
	mod_synth_vco_event(_OSC_2_EVENT, _OSC_DETUNE_CENTS, val);
}

void OscilatorsTabUiHandling::osc2SendFilter1Changed(int val)
{
	mod_synth_vco_event(_OSC_2_EVENT, _OSC_FILTER_SEND_1, val);
	sprintf(mssg1, "Osc2 Filter 1 Send Level: %.2f", (float)val / 100.0);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void OscilatorsTabUiHandling::osc2SendFilter2Changed(int val)
{
	mod_synth_vco_event(_OSC_2_EVENT, _OSC_FILTER_SEND_2, val);
	sprintf(mssg1, "Osc2 Filter 2 Send Level 0: %.2f", (float)val / 100.0);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void OscilatorsTabUiHandling::osc2FreqModLfoChanged(int val)
{
	mod_synth_vco_event(_OSC_2_EVENT, _OSC_FREQ_MOD_LFO, val);
}

void OscilatorsTabUiHandling::osc2FreqModLevelLfoChanged(int val)
{
	int updateUiWrapper = mod_synth_log_scale_100_int(0, 100, 10, val);

	mod_synth_vco_event(_OSC_2_EVENT, _OSC_FREQ_MOD_LFO_LEVEL, updateUiWrapper);
	sprintf(mssg1, "Osc2 Freq Modulation LFO Level: %.2f", (float)updateUiWrapper / 100.0);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void OscilatorsTabUiHandling::osc2FreqModEnvChanged(int val)
{
	mod_synth_vco_event(_OSC_2_EVENT, _OSC_FREQ_MOD_ENV, val);
}

void OscilatorsTabUiHandling::osc2FreqModLevelEnvChanged(int val)
{
	mod_synth_vco_event(_OSC_2_EVENT, _OSC_FREQ_MOD_ENV_LEVEL, val);
	sprintf(mssg1, "Osc2 Freq Modulation ENV Level: %.2f", (float)val / 100.0);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void OscilatorsTabUiHandling::osc2PwmModLfoChanged(int val)
{
	mod_synth_vco_event(_OSC_2_EVENT, _OSC_PWM_MOD_LFO, val);
}

void OscilatorsTabUiHandling::osc2PwmModLevelLfoChanged(int val)
{
	mod_synth_vco_event(_OSC_2_EVENT, _OSC_PWM_MOD_LFO_LEVEL, val);
	sprintf(mssg1, "Osc2 PWM Modulation LFO Level: %.2f", (float)val / 100.0);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void OscilatorsTabUiHandling::osc2PwmModEnvChanged(int val)
{
	mod_synth_vco_event(_OSC_2_EVENT, _OSC_PWM_MOD_ENV, val);
}

void OscilatorsTabUiHandling::osc2PwmModLevelEnvChanged(int val)
{
	mod_synth_vco_event(_OSC_2_EVENT, _OSC_PWM_MOD_ENV_LEVEL, val);
	sprintf(mssg1, "Osc1 PWM Modulation ENV Level: %.2f", (float)val / 100.0);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void OscilatorsTabUiHandling::osc2AmpModLfoChanged(int val)
{
	mod_synth_vco_event(_OSC_2_EVENT, _OSC_AMP_MOD_LFO, val);
}

void OscilatorsTabUiHandling::osc2AmpModLevelLfoChanged(int val)
{
	mod_synth_vco_event(_OSC_2_EVENT, _OSC_AMP_MOD_LFO_LEVEL, val);
	sprintf(mssg1, "Osc2 Amp Modulation LFO Level: %.2f", (float)val / 100.0);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void OscilatorsTabUiHandling::osc2AmpModEnvChanged(int val)
{
	mod_synth_vco_event(_OSC_2_EVENT, _OSC_AMP_MOD_ENV, val);
}

void OscilatorsTabUiHandling::osc2AmpModLevelEnvChanged(int val)
{
	mod_synth_vco_event(_OSC_2_EVENT, _OSC_AMP_MOD_ENV_LEVEL, val);
	sprintf(mssg1, "Osc2 Amp Modulation ENV Level: %.2f", (float)val / 100.0);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void OscilatorsTabUiHandling::osc2syncOsc1Changed(bool val)
{
	mod_synth_vco_event_bool(_OSC_2_EVENT, _OSC_SYNC, val);
}

//void OscilatorsTabUiHandling::osc2fixToneChanged(bool val)
//{
//	mod_synth_vco_event(_OSC_1_EVENT, _OSC_FIX_TONE, val);
//}

void OscilatorsTabUiHandling::osc2EnableChanged(bool val)
{
	if (val)
	{
		osc2enabled = true;
		mod_synth_enable_osc2();
	}
	else
	{
		osc2enabled = false;
		mod_synth_disable_osc2();
	}
}

