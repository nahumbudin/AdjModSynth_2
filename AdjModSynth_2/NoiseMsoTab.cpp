/**
*	@file		NoiseMsoTab.cpp
*	@author		Nahum Budin
*	@date		16-Jan-2021
*	@version	1.1 
*				1. Adding Control Widgets control through Knob and Slider
*	
*	Version	1.0		11-Nov-2019
*
*	@brief		Noise and MSO Tab ui handling.
*/

#include "MainWindow.h"
#include "NoiseMsoTab.h"
#include "libAdjHeartModSynth_2.h"

NoiseMsoTabUiHandling *NoiseMsoTabUiHandling::noiseMsoTabUiHandling = NULL;


// MSO Sine-wave preset positions
static const int presetSinus[] = { 512, 517, 1024, 1029, 1536, 1542 };
// Symetric square-wave preset positions
static const int presetSquar[] = { 1, 1011, 1016, 1021, 1026, 2046 };
// Symetric square-wave preset positions
static const int presetPulse[] = { 1, 200, 205, 210, 215, 2046 };
// Sawtooth-wave preset positions
static const int presetSaw[] = { 1, 7, 1024, 1029, 2041, 2046 };

NoiseMsoTabUiHandling::NoiseMsoTabUiHandling(Ui_MainWindow *mainWind)
{
	mainWindow = mainWind;
	
	stringNoiseColorsList.append("White");
	stringNoiseColorsList.append("Pink");
	stringNoiseColorsList.append("Brown");
	
	updateMsoPlot = true;
	
	stringMsoPresetList.append("User-defined");
	stringMsoPresetList.append("Sine");
	stringMsoPresetList.append("Square");
	stringMsoPresetList.append("Pulse");
	stringMsoPresetList.append("Saw");
}


NoiseMsoTabUiHandling *NoiseMsoTabUiHandling::getInstance() 
{
	return noiseMsoTabUiHandling;
}

void NoiseMsoTabUiHandling::setTrigers()
{
	connect(mainWindow->comboBox_NoiseColor,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(noiseColorChanged(int)));

	connect(mainWindow->dial_NoiseFilterSend_1,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(noiseSendFilter1Changed(int)));

	connect(mainWindow->dial_NoiseFilterSend_2,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(noiseSendFilter2Changed(int)));

	connect(mainWindow->comboBox_NoiseAmpModLfo,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(noiseAmpModLfoChanged(int)));

	connect(mainWindow->dial_NoiseAmpModLfoLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(noiseAmpModLevelLfoChanged(int)));

	connect(mainWindow->comboBox_NoiseAmpModEnv,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(noiseAmpModEnvChanged(int)));
	
	connect(mainWindow->dial_NoiseAmpModEnvLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(noiseAmpModLevelEnvChanged(int)));

	connect(mainWindow->checkBox_enable_noise_gen,
		SIGNAL(toggled(bool)),
		this,
		SLOT(noiseEnableChanged(bool)));
	
	
	connect(mainWindow->checkBox_enableMso,
		SIGNAL(toggled(bool)),
		this,
		SLOT(msoEnableChanged(bool)));

	connect(mainWindow->verticalSlider_MsoPos_a,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(point_a_moved(int)));

	connect(mainWindow->verticalSlider_MsoPos_b,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(point_b_moved(int)));

	connect(mainWindow->verticalSlider_MsoPos_c,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(point_c_moved(int)));

	connect(mainWindow->verticalSlider_MsoPos_d,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(point_d_moved(int)));

	connect(mainWindow->verticalSlider_MsoPos_e,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(point_e_moved(int)));

	connect(mainWindow->verticalSlider_MsoPos_f,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(point_f_moved(int)));

	connect(mainWindow->horizontalSlider_MsoSymetry,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(symetryChanged(int)));

	connect(mainWindow->comboBox_MsoTuneOct,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(msoDetuneOctaveChanged(int)));

	connect(mainWindow->comboBox_MsoTuneSemi,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(msoDetuneSeminotesChanged(int)));

	connect(mainWindow->comboBox_MsoTuneCents,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(msoDetuneCentsChanged(int)));

	connect(mainWindow->dial_MsoFilterSend_1,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(msoSendFilter1Changed(int)));

	connect(mainWindow->dial_MsoFilterSend_2,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(msoSendFilter2Changed(int)));

	connect(mainWindow->comboBox_MsoFreqModLfo,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(msoFreqModLfoChanged(int)));

	connect(mainWindow->dial_MsoFreqModLfoLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(msoFreqModLevelLfoChanged(int)));

	connect(mainWindow->comboBox_MsoFreqModEnv,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(msoFreqModEnvChanged(int)));

	connect(mainWindow->dial_MsoFreqModEnvLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(msoFreqModLevelEnvChanged(int)));

	connect(mainWindow->comboBox_MsoPwmModLfo,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(msoPwmModLfoChanged(int)));

	connect(mainWindow->dial_MsoPwmModLfoLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(msoPwmModLevelLfoChanged(int)));

	connect(mainWindow->comboBox_MsoPwmModEnv,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(msoPwmModEnvChanged(int)));

	connect(mainWindow->dial_MsoPwmModEnvLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(msoPwmModLevelEnvChanged(int)));

	connect(mainWindow->comboBox_MsoAmpModLfo,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(msoAmpModLfoChanged(int)));

	connect(mainWindow->dial_MsoAmpModLfoLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(msoAmpModLevelLfoChanged(int)));

	connect(mainWindow->comboBox_MsoAmpModEnv,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(msoAmpModEnvChanged(int)));

	connect(mainWindow->dial_MsoAmpModEnvLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(msoAmpModLevelEnvChanged(int)));

	connect(mainWindow->comboBox_MsoPreset,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(msoPresetChanged(int)));
}

void NoiseMsoTabUiHandling::setWidgetsInfoMap()
{
	// Widgets Ids
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_NoiseFilterSend_1, _NOISE_1_EVENT * 10000 + _NOISE_SEND_1);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_NoiseFilterSend_2, _NOISE_1_EVENT * 10000 + _NOISE_SEND_2);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_NoiseAmpModLfoLevel, _NOISE_1_EVENT * 10000 + _NOISE_AMP_MOD_LFO_LEVEL);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_NoiseAmpModEnvLevel, _NOISE_1_EVENT * 10000 + _NOISE_AMP_MOD_ENV_LEVEL);

	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MsoFilterSend_1, _MSO_1_EVENT * 10000 + _MSO_FILTER_SEND_1);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MsoFilterSend_2, _MSO_1_EVENT * 10000 + _MSO_FILTER_SEND_2);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MsoFreqModLfoLevel, _MSO_1_EVENT * 10000 + _MSO_FREQ_MOD_LFO_LEVEL);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MsoFreqModEnvLevel, _MSO_1_EVENT * 10000 + _MSO_FREQ_MOD_ENV_LEVEL);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MsoPwmModLfoLevel, _MSO_1_EVENT * 10000 + _MSO_PWM_MOD_LFO_LEVEL);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MsoPwmModEnvLevel, _MSO_1_EVENT * 10000 + _MSO_PWM_MOD_ENV_LEVEL);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MsoAmpModLfoLevel, _MSO_1_EVENT * 10000 + _MSO_AMP_MOD_LFO_LEVEL);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MsoAmpModEnvLevel, _MSO_1_EVENT * 10000 + _MSO_AMP_MOD_ENV_LEVEL);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->verticalSlider_MsoPos_a, _MSO_1_EVENT * 10000 + _MSO_SEGMENT_A_POSITION);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->verticalSlider_MsoPos_b, _MSO_1_EVENT * 10000 + _MSO_SEGMENT_B_POSITION);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->verticalSlider_MsoPos_c, _MSO_1_EVENT * 10000 + _MSO_SEGMENT_C_POSITION);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->verticalSlider_MsoPos_d, _MSO_1_EVENT * 10000 + _MSO_SEGMENT_D_POSITION);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->verticalSlider_MsoPos_e, _MSO_1_EVENT * 10000 + _MSO_SEGMENT_E_POSITION);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->verticalSlider_MsoPos_f, _MSO_1_EVENT * 10000 + _MSO_SEGMENT_F_POSITION);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->horizontalSlider_MsoSymetry, _MSO_1_EVENT * 10000 + _MSO_SYMETRY);

	// Widgets types
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_NoiseFilterSend_1, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_NoiseFilterSend_2, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_NoiseAmpModLfoLevel, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_NoiseAmpModEnvLevel, _CONTROL_TYPE_DIAL);

	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MsoFilterSend_1, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MsoFilterSend_2, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MsoFreqModLfoLevel, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MsoFreqModEnvLevel, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MsoPwmModLfoLevel, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MsoPwmModEnvLevel, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MsoAmpModLfoLevel, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MsoAmpModEnvLevel, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->verticalSlider_MsoPos_a, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->verticalSlider_MsoPos_b, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->verticalSlider_MsoPos_c, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->verticalSlider_MsoPos_d, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->verticalSlider_MsoPos_e, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->verticalSlider_MsoPos_f, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->horizontalSlider_MsoSymetry, _CONTROL_TYPE_SLIDER);
	
}

void NoiseMsoTabUiHandling::update()
{
	static bool oneTimeInitialized = false;

	if (!oneTimeInitialized)
	{
		oneTimeInitialized = true;
		
		mainWindow->comboBox_NoiseColor->blockSignals(true);
		mainWindow->comboBox_NoiseColor->addItems(stringNoiseColorsList);
		mainWindow->comboBox_NoiseColor->blockSignals(false);

		mainWindow->comboBox_NoiseAmpModEnv->blockSignals(true);
		mainWindow->comboBox_NoiseAmpModEnv->addItems(MainWindow::getInstance()->stringEnvsList);
		mainWindow->comboBox_NoiseAmpModEnv->blockSignals(false);

		mainWindow->comboBox_NoiseAmpModLfo->blockSignals(true);
		mainWindow->comboBox_NoiseAmpModLfo->addItems(MainWindow::getInstance()->stringLfosList);
		mainWindow->comboBox_NoiseAmpModLfo->blockSignals(false);
		
		
		mainWindow->comboBox_MsoPreset->blockSignals(true);
		mainWindow->comboBox_MsoPreset->addItems(stringMsoPresetList);
		mainWindow->comboBox_MsoPreset->setCurrentIndex(1); // Sine
		mainWindow->comboBox_MsoPreset->blockSignals(false);
		
		mainWindow->comboBox_MsoTuneOct->blockSignals(true);
		mainWindow->comboBox_MsoTuneSemi->blockSignals(true);
		mainWindow->comboBox_MsoTuneCents->blockSignals(true);
		for (int i = mod_synth_get_osc_detune_min_octave(); i <= mod_synth_get_osc_detune_max_octave(); i++)
		{
			mainWindow->comboBox_MsoTuneOct->addItem(QString::number(i));
		}

		for (int i = mod_synth_get_osc_detune_min_semitones(); i <= mod_synth_get_osc_detune_max_semitones(); i++)
		{
			mainWindow->comboBox_MsoTuneSemi->addItem(QString::number(i));
		}

		for (int i = 4 * mod_synth_get_osc_detune_min_cents(); i <= 4 * mod_synth_get_osc_detune_max_cents(); i++)
		{
			// 0.25 steps
			mainWindow->comboBox_MsoTuneCents->addItem(QString::number(i / 4.f));
		}

		mainWindow->comboBox_MsoTuneOct->blockSignals(false);
		mainWindow->comboBox_MsoTuneSemi->blockSignals(false);
		mainWindow->comboBox_MsoTuneCents->blockSignals(false);

		mainWindow->comboBox_MsoFreqModEnv->blockSignals(true);
		mainWindow->comboBox_MsoFreqModEnv->addItems(MainWindow::getInstance()->stringEnvsList);
		mainWindow->comboBox_MsoFreqModEnv->blockSignals(false);

		mainWindow->comboBox_MsoFreqModLfo->blockSignals(true);
		mainWindow->comboBox_MsoFreqModLfo->addItems(MainWindow::getInstance()->stringLfosList);
		mainWindow->comboBox_MsoFreqModLfo->blockSignals(false);

		mainWindow->comboBox_MsoPwmModEnv->blockSignals(true);
		mainWindow->comboBox_MsoPwmModEnv->addItems(MainWindow::getInstance()->stringEnvsList);
		mainWindow->comboBox_MsoPwmModEnv->blockSignals(false);

		mainWindow->comboBox_MsoPwmModLfo->blockSignals(true);
		mainWindow->comboBox_MsoPwmModLfo->addItems(MainWindow::getInstance()->stringLfosList);
		mainWindow->comboBox_MsoPwmModLfo->blockSignals(false);

		mainWindow->comboBox_MsoAmpModEnv->blockSignals(true);
		mainWindow->comboBox_MsoAmpModEnv->addItems(MainWindow::getInstance()->stringEnvsList);
		mainWindow->comboBox_MsoAmpModEnv->blockSignals(false);

		mainWindow->comboBox_MsoAmpModLfo->blockSignals(true);
		mainWindow->comboBox_MsoAmpModLfo->addItems(MainWindow::getInstance()->stringLfosList);
		mainWindow->comboBox_MsoAmpModLfo->blockSignals(false);	
	}
	
	mainWindow->comboBox_NoiseColor->blockSignals(true);
	mainWindow->comboBox_NoiseColor->setCurrentIndex(mod_synth_get_active_noise_color());
	mainWindow->comboBox_NoiseColor->blockSignals(false);

	mainWindow->dial_NoiseFilterSend_1->blockSignals(true);
	mainWindow->dial_NoiseFilterSend_1->setValue(mod_synth_get_active_noise_send_filter_1());
	mainWindow->dial_NoiseFilterSend_1->blockSignals(false);

	mainWindow->dial_NoiseFilterSend_2->blockSignals(true);
	mainWindow->dial_NoiseFilterSend_2->setValue(mod_synth_get_active_noise_send_filter_2());
	mainWindow->dial_NoiseFilterSend_2->blockSignals(false);

	mainWindow->comboBox_NoiseAmpModLfo->blockSignals(true);
	mainWindow->comboBox_NoiseAmpModLfo->setCurrentIndex(mod_synth_get_active_noise_amp_mod_lfo());
	mainWindow->comboBox_NoiseAmpModLfo->blockSignals(false);

	mainWindow->dial_NoiseAmpModLfoLevel->blockSignals(true);
	mainWindow->dial_NoiseAmpModLfoLevel->setValue(mod_synth_get_active_noise_amp_mod_lfo_level());
	mainWindow->dial_NoiseAmpModLfoLevel->blockSignals(false);

	mainWindow->comboBox_NoiseAmpModEnv->blockSignals(true);
	mainWindow->comboBox_NoiseAmpModEnv->setCurrentIndex(mod_synth_get_active_noise_amp_mod_env());
	mainWindow->comboBox_NoiseAmpModEnv->blockSignals(false);

	mainWindow->dial_NoiseAmpModEnvLevel->blockSignals(true);
	mainWindow->dial_NoiseAmpModEnvLevel->setValue(mod_synth_get_active_noise_amp_mod_env_level());
	mainWindow->dial_NoiseAmpModEnvLevel->blockSignals(false);

	noise_enabled = mod_synth_get_active_noise_enable_state();
	mainWindow->checkBox_enable_noise_gen->blockSignals(true);
	mainWindow->checkBox_enable_noise_gen->setChecked(noise_enabled);
	mainWindow->checkBox_enable_noise_gen->blockSignals(false);
	if (noise_enabled)
	{
		mainWindow->groupBox_NoiseGenerator->setEnabled(true);
	}
	else	
	{
		mainWindow->groupBox_NoiseGenerator->setEnabled(false);
	}
	
//	mainWindow->comboBox_MsoPreset->blockSignals(true);
//	mainWindow->comboBox_MsoPreset->setCurrentIndex(1);
//	mainWindow->comboBox_MsoPreset->blockSignals(false);
	
	mainWindow->verticalSlider_MsoPos_a->blockSignals(true);
	mainWindow->verticalSlider_MsoPos_a->setValue(mod_synth_get_active_mso_table_segment_point(0));
	mainWindow->verticalSlider_MsoPos_a->blockSignals(false);

	mainWindow->verticalSlider_MsoPos_b->blockSignals(true);
	mainWindow->verticalSlider_MsoPos_b->setValue(mod_synth_get_active_mso_table_segment_point(1));
	mainWindow->verticalSlider_MsoPos_b->blockSignals(false);

	mainWindow->verticalSlider_MsoPos_c->blockSignals(true);
	mainWindow->verticalSlider_MsoPos_c->setValue(mod_synth_get_active_mso_table_segment_point(2));
	mainWindow->verticalSlider_MsoPos_c->blockSignals(false);

	mainWindow->verticalSlider_MsoPos_d->blockSignals(true);
	mainWindow->verticalSlider_MsoPos_d->setValue(mod_synth_get_active_mso_table_segment_point(3));
	mainWindow->verticalSlider_MsoPos_d->blockSignals(false);

	mainWindow->verticalSlider_MsoPos_e->blockSignals(true);
	mainWindow->verticalSlider_MsoPos_e->setValue(mod_synth_get_active_mso_table_segment_point(4));
	mainWindow->verticalSlider_MsoPos_e->blockSignals(false);

	mainWindow->verticalSlider_MsoPos_f->blockSignals(true);
	mainWindow->verticalSlider_MsoPos_f->setValue(mod_synth_get_active_mso_table_segment_point(5));
	mainWindow->verticalSlider_MsoPos_f->blockSignals(false);

	mainWindow->horizontalSlider_MsoSymetry->blockSignals(true);
	mainWindow->horizontalSlider_MsoSymetry->setValue(mod_synth_get_active_mso_symetry());
	mainWindow->horizontalSlider_MsoSymetry->blockSignals(false);
	
	mso_enabled = mod_synth_get_active_mso_enable_state();
	mainWindow->checkBox_enableMso->blockSignals(true);
	mainWindow->checkBox_enableMso->setChecked(mso_enabled);
	mainWindow->checkBox_enableMso->blockSignals(false);
	if (mso_enabled)
	{
		mainWindow->groupBox_MSO->setEnabled(true);
	}
	else
	{
		mainWindow->groupBox_MSO->setEnabled(false);
	}

	mainWindow->comboBox_MsoTuneOct->blockSignals(true);
	mainWindow->comboBox_MsoTuneOct->setCurrentIndex(mod_synth_get_active_mso_detune_octave() - mod_synth_get_osc_detune_min_octave());
	mainWindow->comboBox_MsoTuneOct->blockSignals(false);

	mainWindow->comboBox_MsoTuneSemi->blockSignals(true);
	mainWindow->comboBox_MsoTuneSemi->setCurrentIndex(mod_synth_get_active_mso_detune_semitones() - mod_synth_get_osc_detune_min_semitones());
	mainWindow->comboBox_MsoTuneSemi->blockSignals(false);

	mainWindow->comboBox_MsoTuneCents->blockSignals(true);
	mainWindow->comboBox_MsoTuneCents->setCurrentIndex(mod_synth_get_active_mso_detune_cents() - mod_synth_get_osc_detune_min_cents() * 4.f);
	mainWindow->comboBox_MsoTuneCents->blockSignals(false);

	mainWindow->dial_MsoFilterSend_1->blockSignals(true);
	mainWindow->dial_MsoFilterSend_1->setValue(mod_synth_get_active_mso_send_filter_1());
	mainWindow->dial_MsoFilterSend_1->blockSignals(false);

	mainWindow->dial_MsoFilterSend_2->blockSignals(true);
	mainWindow->dial_MsoFilterSend_2->setValue(mod_synth_get_active_mso_send_filter_2());
	mainWindow->dial_MsoFilterSend_2->blockSignals(false);

	mainWindow->comboBox_MsoFreqModLfo->blockSignals(true);
	mainWindow->comboBox_MsoFreqModLfo->setCurrentIndex(mod_synth_get_active_mso_freq_mod_lfo());
	mainWindow->comboBox_MsoFreqModLfo->blockSignals(false);

	mainWindow->dial_MsoFreqModLfoLevel->blockSignals(true);
	mainWindow->dial_MsoFreqModLfoLevel->setValue(mod_synth_get_active_mso_freq_mod_lfo_level());
	mainWindow->dial_MsoFreqModLfoLevel->blockSignals(false);

	mainWindow->comboBox_MsoFreqModEnv->blockSignals(true);
	mainWindow->comboBox_MsoFreqModEnv->setCurrentIndex(mod_synth_get_active_mso_freq_mod_env());
	mainWindow->comboBox_MsoFreqModEnv->blockSignals(false);

	mainWindow->dial_MsoFreqModEnvLevel->blockSignals(true);
	mainWindow->dial_MsoFreqModEnvLevel->setValue(mod_synth_get_active_mso_freq_mod_env_level());
	mainWindow->dial_MsoFreqModEnvLevel->blockSignals(false);

	mainWindow->comboBox_MsoPwmModLfo->blockSignals(true);
	mainWindow->comboBox_MsoPwmModLfo->setCurrentIndex(mod_synth_get_active_mso_pwm_mod_lfo());
	mainWindow->comboBox_MsoPwmModLfo->blockSignals(false);

	mainWindow->dial_MsoPwmModLfoLevel->blockSignals(true);
	mainWindow->dial_MsoPwmModLfoLevel->setValue(mod_synth_get_active_mso_pwm_mod_lfo_level());
	mainWindow->dial_MsoPwmModLfoLevel->blockSignals(false);

	mainWindow->comboBox_MsoPwmModEnv->blockSignals(true);
	mainWindow->comboBox_MsoPwmModEnv->setCurrentIndex(mod_synth_get_active_mso_pwm_mod_env());
	mainWindow->comboBox_MsoPwmModEnv->blockSignals(false);

	mainWindow->dial_MsoPwmModEnvLevel->blockSignals(true);
	mainWindow->dial_MsoPwmModEnvLevel->setValue(mod_synth_get_active_mso_pwm_mod_env_level());
	mainWindow->dial_MsoPwmModEnvLevel->blockSignals(false);

	mainWindow->comboBox_MsoAmpModLfo->blockSignals(true);
	mainWindow->comboBox_MsoAmpModLfo->setCurrentIndex(mod_synth_get_active_mso_amp_mod_lfo());
	mainWindow->comboBox_MsoAmpModLfo->blockSignals(false);

	mainWindow->dial_MsoAmpModLfoLevel->blockSignals(true);
	mainWindow->dial_MsoAmpModLfoLevel->setValue(mod_synth_get_active_mso_amp_mod_lfo_level());
	mainWindow->dial_MsoAmpModLfoLevel->blockSignals(false);

	mainWindow->comboBox_MsoAmpModEnv->blockSignals(true);
	mainWindow->comboBox_MsoAmpModEnv->setCurrentIndex(mod_synth_get_active_mso_amp_mod_env());
	mainWindow->comboBox_MsoAmpModEnv->blockSignals(false);

	mainWindow->dial_MsoAmpModEnvLevel->blockSignals(true);
	mainWindow->dial_MsoAmpModEnvLevel->setValue(mod_synth_get_active_mso_amp_mod_env_level());
	mainWindow->dial_MsoAmpModEnvLevel->blockSignals(false);

	if (MainWindow::getInstance()->updateMSOwaveformPlot == false)
	{
		// Do it only if last update was already completed.
		setupMsoPlot(mainWindow->customPlotMSOwaveform);
		// Enable actual refresh waveform plot on GUI update timer interupt
		MainWindow::getInstance()->updateMSOwaveformPlot = true;
	}
	
}

void NoiseMsoTabUiHandling::updateMSOwaveformPlot()
{
//	if (mainWindow)
//	{
//		setupMsoPlot(mainWindow->customPlot);
//		mainWindow->customPlot->replot();
//	}
}

void NoiseMsoTabUiHandling::setupMsoPlot(QCustomPlot *customPlot)
{
	if (updateMsoPlot && mod_synth_get_mso_morphed_lookup_table())
	{
		mod_synth_mso_event(_MSO_1_EVENT, _MSO_CALC_BASE_LUT, mod_synth_get_active_sketch());
		// Recalculates morphed waveform.
		mod_synth_mso_event(_MSO_1_EVENT, _MSO_CALC_MORPHED_LUT, mod_synth_get_active_sketch());

		// add two new graphs and set their look:
		QPen pen;
		pen.setStyle(Qt::SolidLine);
		pen.setWidth(3);
		pen.setColor(QColor("#0080FF"));
		customPlot->addGraph();
		customPlot->graph(0)->setPen(pen);   // line color blue for first graph
//		customPlot->addGraph();
//		customPlot->graph(1)->setPen(QPen(Qt::red));   // line color red for second graph

		customPlot->setBackground(QBrush(QColor("#929292")));
		
		QVector<double> x(mod_synth_get_mso_table_length() + 1), y0(mod_synth_get_mso_table_length() + 1);
		for (int i = 0; i < mod_synth_get_mso_table_length() / 4; ++i)
		{
			x[i] = i;
			y0[i] = mod_synth_get_mso_morphed_lookup_table()[i * 4];   // Table length is getMsoTableLength * 4 
			//	y1[i] = 52.f + 47.f*qCos(2 * 3.14 * i / 256);
		}
		//x[256] = 257; y0[256] = -2; y1[256] = -2;
		customPlot->xAxis->setVisible(false);
		customPlot->xAxis->setTickLabels(false);
		customPlot->yAxis->setVisible(false);
		customPlot->yAxis->setTickLabels(false);
		// make left and bottom axes always transfer their ranges to right and top axes:
		//connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
		//connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));
		// pass data points to graphs:
		customPlot->graph(0)->setData(x, y0);
		// let the ranges scale themselves so graph 0 fits perfectly in the visible area:
		customPlot->graph(0)->rescaleAxes();
	}
}

// Slots

void NoiseMsoTabUiHandling::noiseColorChanged(int val)
{
	mod_synth_noise_event(_NOISE_1_EVENT, _NOISE_COLOR, val);
}

void NoiseMsoTabUiHandling::noiseSendFilter1Changed(int val)
{
	mod_synth_noise_event(_NOISE_1_EVENT, _NOISE_SEND_1, val);
	sprintf(mssg1, "Noise Send 1: %.2f", (float)val / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void NoiseMsoTabUiHandling::noiseSendFilter2Changed(int val)
{
	mod_synth_noise_event(_NOISE_1_EVENT, _NOISE_SEND_2, val);
	sprintf(mssg1, "Noise Send 2: %.2f", (float)val / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void NoiseMsoTabUiHandling::noiseAmpModLfoChanged(int val)
{
	mod_synth_noise_event(_NOISE_1_EVENT, _NOISE_AMP_MOD_LFO, val);
}

void NoiseMsoTabUiHandling::noiseAmpModLevelLfoChanged(int val)
{
	mod_synth_noise_event(_NOISE_1_EVENT, _NOISE_AMP_MOD_LFO_LEVEL, val);
	sprintf(mssg1, "Noise Amp Modulation LFO Level: %.2f", (float)val / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void NoiseMsoTabUiHandling::noiseAmpModEnvChanged(int val)
{
	mod_synth_noise_event(_NOISE_1_EVENT, _NOISE_AMP_MOD_ENV, val);
}

void NoiseMsoTabUiHandling::noiseAmpModLevelEnvChanged(int val)
{
	mod_synth_noise_event(_NOISE_1_EVENT, _NOISE_AMP_MOD_ENV_LEVEL, val);
	sprintf(mssg1, "Noise Amp Modulation ENV Level: %.2f", (float)val / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1)); 
}

void NoiseMsoTabUiHandling::noiseEnableChanged(bool val)
{
	if (val)
	{
		noise_enabled = true;
		mod_synth_enable_noise();
	}
	else
	{
		noise_enabled = false;
		mod_synth_disable_noise();
	}
}


void NoiseMsoTabUiHandling::msoEnableChanged(bool val)
{
	if (val)
		mod_synth_enable_morphsin();
	else
		mod_synth_disable_morphsin();
}

void NoiseMsoTabUiHandling::point_a_moved(int val)
{
	mod_synth_mso_event(_MSO_1_EVENT, _MSO_SEGMENT_A_POSITION, val);
	setupMsoPlot(mainWindow->customPlotMSOwaveform);
	mainWindow->customPlotMSOwaveform->replot();
	sprintf(mssg1, "MSO 1 Point a: %i", (int)((float)val / 20.46f));
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	// No more a preset
	if(mainWindow->comboBox_MsoPreset->currentIndex() != 0)
	{
		mainWindow->comboBox_MsoPreset->blockSignals(true);
		mainWindow->comboBox_MsoPreset->setCurrentIndex(0);
		mainWindow->comboBox_MsoPreset->blockSignals(false);
	}
}

void NoiseMsoTabUiHandling::point_b_moved(int val)
{
	mod_synth_mso_event(_MSO_1_EVENT, _MSO_SEGMENT_B_POSITION, val);
	setupMsoPlot(mainWindow->customPlotMSOwaveform);
	mainWindow->customPlotMSOwaveform->replot();
	sprintf(mssg1, "MSO 1 Point b: %i", (int)((float)val / 20.46f));
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1)); 
	// No more a preset
	if(mainWindow->comboBox_MsoPreset->currentIndex() != 0)
	{
		mainWindow->comboBox_MsoPreset->blockSignals(true);
		mainWindow->comboBox_MsoPreset->setCurrentIndex(0);
		mainWindow->comboBox_MsoPreset->blockSignals(false);
	}
}

void NoiseMsoTabUiHandling::point_c_moved(int val)
{
	mod_synth_mso_event(_MSO_1_EVENT, _MSO_SEGMENT_C_POSITION, val);
	setupMsoPlot(mainWindow->customPlotMSOwaveform);
	mainWindow->customPlotMSOwaveform->replot();
	sprintf(mssg1, "MSO 1 Point c: %i", (int)((float)val / 20.46f));
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	// No more a preset
	if(mainWindow->comboBox_MsoPreset->currentIndex() != 0)
	{
		mainWindow->comboBox_MsoPreset->blockSignals(true);
		mainWindow->comboBox_MsoPreset->setCurrentIndex(0);
		mainWindow->comboBox_MsoPreset->blockSignals(false);
	}
}

void NoiseMsoTabUiHandling::point_d_moved(int val)
{
	mod_synth_mso_event(_MSO_1_EVENT, _MSO_SEGMENT_D_POSITION, val);
	setupMsoPlot(mainWindow->customPlotMSOwaveform);
	mainWindow->customPlotMSOwaveform->replot();
	sprintf(mssg1, "MSO 1 Point d:%i", (int)((float)val / 20.46f));
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	// No more a preset
	if(mainWindow->comboBox_MsoPreset->currentIndex() != 0)
	{
		mainWindow->comboBox_MsoPreset->blockSignals(true);
		mainWindow->comboBox_MsoPreset->setCurrentIndex(0);
		mainWindow->comboBox_MsoPreset->blockSignals(false);
	}
}

void NoiseMsoTabUiHandling::point_e_moved(int val)
{
	mod_synth_mso_event(_MSO_1_EVENT, _MSO_SEGMENT_E_POSITION, val);
	setupMsoPlot(mainWindow->customPlotMSOwaveform);
	mainWindow->customPlotMSOwaveform->replot();
	sprintf(mssg1, "MSO 1 Point e: %i", (int)((float)val / 20.46f));
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	// No more a preset
	if(mainWindow->comboBox_MsoPreset->currentIndex() != 0)
	{
		mainWindow->comboBox_MsoPreset->blockSignals(true);
		mainWindow->comboBox_MsoPreset->setCurrentIndex(0);
		mainWindow->comboBox_MsoPreset->blockSignals(false);
	}
}

void NoiseMsoTabUiHandling::point_f_moved(int val)
{
	mod_synth_mso_event(_MSO_1_EVENT, _MSO_SEGMENT_F_POSITION, val);
	setupMsoPlot(mainWindow->customPlotMSOwaveform);
	mainWindow->customPlotMSOwaveform->replot();
	sprintf(mssg1, "MSO 1 Point f: %f", (float)val / 20.46);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	// No more a preset
	if(mainWindow->comboBox_MsoPreset->currentIndex() != 0)
	{
		mainWindow->comboBox_MsoPreset->blockSignals(true);
		mainWindow->comboBox_MsoPreset->setCurrentIndex(0);
		mainWindow->comboBox_MsoPreset->blockSignals(false);
	}
}

void NoiseMsoTabUiHandling::symetryChanged(int val)
{
	mod_synth_mso_event(_MSO_1_EVENT, _MSO_SYMETRY, val);
	setupMsoPlot(mainWindow->customPlotMSOwaveform);
	mainWindow->customPlotMSOwaveform->replot();
	sprintf(mssg1, "MSO 1 Morphed Symetry: %i", val);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	// No more a preset
	if(mainWindow->comboBox_MsoPreset->currentIndex() != 0)
	{
		mainWindow->comboBox_MsoPreset->blockSignals(true);
		mainWindow->comboBox_MsoPreset->setCurrentIndex(0);
		mainWindow->comboBox_MsoPreset->blockSignals(false);
	}
}

void NoiseMsoTabUiHandling::msoDetuneOctaveChanged(int val)
{
	mod_synth_mso_event(_MSO_1_EVENT, _MSO_DETUNE_OCTAVE, val);
}

void NoiseMsoTabUiHandling::msoDetuneSeminotesChanged(int val)
{
	mod_synth_mso_event(_MSO_1_EVENT, _MSO_DETUNE_SEMITONES, val);
}

void NoiseMsoTabUiHandling::msoDetuneCentsChanged(int val)
{
	mod_synth_mso_event(_MSO_1_EVENT, _MSO_DETUNE_CENTS, val);
}

void NoiseMsoTabUiHandling::msoSendFilter1Changed(int val)
{
	mod_synth_mso_event(_MSO_1_EVENT, _MSO_FILTER_SEND_1, val);
	sprintf(mssg1, "MSO 1 send Filter 1: %.2f", (float)val / 100.0);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void NoiseMsoTabUiHandling::msoSendFilter2Changed(int val)
{
	mod_synth_mso_event(_MSO_1_EVENT, _MSO_FILTER_SEND_2, val);
	sprintf(mssg1, "MSO 1 send Filter 2: %.2f", (float)val / 100.0);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void NoiseMsoTabUiHandling::msoFreqModLfoChanged(int val)
{
	mod_synth_mso_event(_MSO_1_EVENT, _MSO_FREQ_MOD_LFO, val);
}

void NoiseMsoTabUiHandling::msoFreqModLevelLfoChanged(int val)
{
	mod_synth_mso_event(_MSO_1_EVENT, _MSO_FREQ_MOD_LFO_LEVEL, val);
	sprintf(mssg1, "MSO 1 LFO freq modulation level: %.2f", (float)val / 100.0);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void NoiseMsoTabUiHandling::msoFreqModEnvChanged(int val)
{
	mod_synth_mso_event(_MSO_1_EVENT, _MSO_FREQ_MOD_ENV, val);
}

void NoiseMsoTabUiHandling::msoFreqModLevelEnvChanged(int val)
{
	mod_synth_mso_event(_MSO_1_EVENT, _MSO_FREQ_MOD_ENV_LEVEL, val);
	sprintf(mssg1, "MSO 1 ENV freq modulation level: %.2f", (float)val / 100.0);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void NoiseMsoTabUiHandling::msoPwmModLfoChanged(int val)
{
	mod_synth_mso_event(_MSO_1_EVENT, _MSO_PWM_MOD_LFO, val);
}

void NoiseMsoTabUiHandling::msoPwmModLevelLfoChanged(int val)
{
	mod_synth_mso_event(_MSO_1_EVENT, _MSO_PWM_MOD_LFO_LEVEL, val);
	sprintf(mssg1, "MSO 1 LFO pwm modulation level: %.2f", (float)val / 100.0);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void NoiseMsoTabUiHandling::msoPwmModEnvChanged(int val)
{
	mod_synth_mso_event(_MSO_1_EVENT, _MSO_PWM_MOD_ENV, val);
}

void NoiseMsoTabUiHandling::msoPwmModLevelEnvChanged(int val)
{
	mod_synth_mso_event(_MSO_1_EVENT, _MSO_PWM_MOD_ENV_LEVEL, val);
	sprintf(mssg1, "MSO 1 ENV pwm modulation level: %.2f", (float)val / 100.0);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void NoiseMsoTabUiHandling::msoAmpModLfoChanged(int val)
{
	mod_synth_mso_event(_MSO_1_EVENT, _MSO_AMP_MOD_LFO, val);
}

void NoiseMsoTabUiHandling::msoAmpModLevelLfoChanged(int val)
{
	mod_synth_mso_event(_MSO_1_EVENT, _MSO_AMP_MOD_LFO_LEVEL, val);
	sprintf(mssg1, "MSO 1 LFO amp modulation level: %.2f", (float)val / 100.0);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void NoiseMsoTabUiHandling::msoAmpModEnvChanged(int val)
{
	mod_synth_mso_event(_MSO_1_EVENT, _MSO_AMP_MOD_ENV, val);
}

void NoiseMsoTabUiHandling::msoAmpModLevelEnvChanged(int val)
{
	mod_synth_mso_event(_MSO_1_EVENT, _MSO_AMP_MOD_ENV_LEVEL, val);
	sprintf(mssg1, "MSO 1 ENV amp modulation level: %.2f", (float)val / 100.0);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void NoiseMsoTabUiHandling::msoPresetChanged(int val)
{
	handlePresetChange(val);
	// The above set back to default
	mainWindow->comboBox_MsoPreset->blockSignals(true);
	mainWindow->comboBox_MsoPreset->setCurrentIndex(val);
	mainWindow->comboBox_MsoPreset->blockSignals(false);
}

void NoiseMsoTabUiHandling::setPositions(const int pos[])
{
	// Put all points to their max value to enable any setup
	updateMsoPlot = false;		
	point_f_moved(2035);	
	point_e_moved(2033);
	point_d_moved(2031);
	point_c_moved(2029);
	point_b_moved(2027);
	point_a_moved(2025);

	point_a_moved(pos[0]);
	point_b_moved(pos[1]);
	point_c_moved(pos[2]);
	point_d_moved(pos[3]);
	point_e_moved(pos[4]);
	point_f_moved(pos[5]);
	updateMsoPlot = true;
	symetryChanged(70);

	mainWindow->verticalSlider_MsoPos_a->blockSignals(true);
	mainWindow->verticalSlider_MsoPos_a->setValue(pos[0]);
	mainWindow->verticalSlider_MsoPos_a->blockSignals(false);

	mainWindow->verticalSlider_MsoPos_b->blockSignals(true);
	mainWindow->verticalSlider_MsoPos_b->setValue(pos[1]);
	mainWindow->verticalSlider_MsoPos_b->blockSignals(false);

	mainWindow->verticalSlider_MsoPos_c->blockSignals(true);
	mainWindow->verticalSlider_MsoPos_c->setValue(pos[2]);
	mainWindow->verticalSlider_MsoPos_c->blockSignals(false);

	mainWindow->verticalSlider_MsoPos_d->blockSignals(true);
	mainWindow->verticalSlider_MsoPos_d->setValue(pos[3]);
	mainWindow->verticalSlider_MsoPos_d->blockSignals(false);

	mainWindow->verticalSlider_MsoPos_e->blockSignals(true);
	mainWindow->verticalSlider_MsoPos_e->setValue(pos[4]);
	mainWindow->verticalSlider_MsoPos_e->blockSignals(false);
	
	mainWindow->verticalSlider_MsoPos_f->blockSignals(true);
	mainWindow->verticalSlider_MsoPos_f->setValue(pos[5]);
	mainWindow->verticalSlider_MsoPos_f->blockSignals(false);

	mainWindow->horizontalSlider_MsoSymetry->blockSignals(true);
	mainWindow->horizontalSlider_MsoSymetry->setValue(70);
	mainWindow->horizontalSlider_MsoSymetry->blockSignals(false);
}

/**
*
*	@brief: Presets are handeled by UI to leave more freedom.
*			Presets just set a predefined set of parameters.
*/
void NoiseMsoTabUiHandling::handlePresetChange(int newPres)
{
	switch (newPres)
	{
	case 1:
		setPositions(presetSinus);
		break;

	case 2:
		setPositions(presetSquar);
		break;

	case 3:
		setPositions(presetPulse);
		break;

	case 4:
		setPositions(presetSaw);
		break;
	}
}
