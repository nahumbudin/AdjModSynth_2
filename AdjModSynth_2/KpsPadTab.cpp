/**
*	@file		KpsPadTab.cpp
*	@author		Nahum Budin
*	@date		12-Nov-2019
*	@version	1.0
*
*	@brief		Karplus Strong string and PAD synthesizers Tab ui handling.
*/

#include "MainWindow.h"
#include "KpsPadTab.h"
#include "libAdjHeartModSynth_2.h"

KspPadTabUiHandling *KspPadTabUiHandling::kspPadTabUiHandling = NULL;

KspPadTabUiHandling::KspPadTabUiHandling(Ui_MainWindow *mainWind)
{
	mainWindow = mainWind;
	
	update_profile_plot = true;
	update_spectrum_plot = true;

	update_plots = false;

	stringKarplusExcitationWaveformList.append("White Noise");
	stringKarplusExcitationWaveformList.append("Pink Noise");
	stringKarplusExcitationWaveformList.append("Brown Noise");
	stringKarplusExcitationWaveformList.append("Sine Chirp");
	stringKarplusExcitationWaveformList.append("Decayed Sine");
	stringKarplusExcitationWaveformList.append("Sawtooth Wave");
	stringKarplusExcitationWaveformList.append("Square Wave");

	stringKarplusStringDampingCalcModeList.append("Direct");
	stringKarplusStringDampingCalcModeList.append("Magic");
	
	stringQualitiesList.append("32K");
	stringQualitiesList.append("64K");
	stringQualitiesList.append("128K");
	stringQualitiesList.append("256K");
	stringQualitiesList.append("512K");
	stringQualitiesList.append("1024K");

	stringBaseNotesList.append("C2");
	stringBaseNotesList.append("G2");
	stringBaseNotesList.append("C3");
	stringBaseNotesList.append("G3");
	stringBaseNotesList.append("C4");
	stringBaseNotesList.append("G4");
	stringBaseNotesList.append("C5");
	stringBaseNotesList.append("G5");
	stringBaseNotesList.append("C6");
	stringBaseNotesList.append("G6");

	stringShapesList.append("Rectangular");
	stringShapesList.append("Gaussian");
	stringShapesList.append("Double Exp.");

	stringShapeCutoffsList.append("Full");
	stringShapeCutoffsList.append("Upper");
	stringShapeCutoffsList.append("Lower");

	update_pad();
	update_kps();
}

KspPadTabUiHandling *KspPadTabUiHandling::getInstance() 
{
	return kspPadTabUiHandling;
}

void KspPadTabUiHandling::setTrigers()
{
	connect(mainWindow->comboBox_KarplusExcitationWaveform,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(karplusExcitationWaveformChanged(int)));

	connect(mainWindow->horizontalSlider_KarplusWaveformVariations,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(karplusExcitationWaveformVariationsChanged(int)));

	connect(mainWindow->comboBox_KarplusStringDampingCalculationMode,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(karplusStringDampingCalcModeChanged(int)));

	connect(mainWindow->horizontalSlider_KarplusStringDamping,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(karplusStringDampingChanged(int)));

	connect(mainWindow->horizontalSlider_KarplusStringDampingVariation,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(karplusStringDampingVariationChanged(int)));
	
	connect(mainWindow->horizontalSlider_KarplusPluckDamping,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(karplusPluckDampingChanged(int)));

	connect(mainWindow->horizontalSlider_KarplusPluckDampingVariation,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(karplusPluckDampingVariationChanged(int)));

	connect(mainWindow->horizontalSlider_KarplusDecayOn,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(karplusOnDecayChanged(int)));

	connect(mainWindow->horizontalSlider_KarplusDecayOff,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(karplusOffDecayChanged(int)));

	connect(mainWindow->dial_KarplusFilterSend_1,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(karplusSendFilter1Changed(int)));

	connect(mainWindow->dial_KarplusFilterSend_2,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(karplusSendFilter2Changed(int)));

	connect(mainWindow->checkBox_enableKarplus,
		SIGNAL(toggled(bool)),
		this,
		SLOT(karplusEnableChanged(bool)));
	
	connect(mainWindow->checkBox_enablePadSynth,
		SIGNAL(toggled(bool)),
		this,
		SLOT(padEnableChanged(bool)));

	connect(mainWindow->pushButton_PanGenerate,
		SIGNAL(toggled(bool)),
		this,
		SLOT(padGenerateClicked(bool)));

	connect(mainWindow->comboBox_PadTuneOct,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(padDetuneOctaveChanged(int)));

	connect(mainWindow->comboBox_PadTuneSemi,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(padDetuneSeminotesChanged(int)));

	connect(mainWindow->comboBox_PadTuneCents,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(padDetuneCentsChanged(int)));

	connect(mainWindow->dial_padFilterSend_1,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(padSendFilter1Changed(int)));

	connect(mainWindow->dial_padFilterSend_2,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(padSendFilter2Changed(int)));

	connect(mainWindow->comboBox_PadFreqModLfo,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(padFreqModLfoChanged(int)));

	connect(mainWindow->dial_PadFreqModLfoLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(padFreqModLevelLfoChanged(int)));

	connect(mainWindow->comboBox_PadFreqModEnv,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(padFreqModEnvChanged(int)));

	connect(mainWindow->dial_PadFreqModEnvLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(padFreqModLevelEnvChanged(int)));

	connect(mainWindow->comboBox_PadAmpModLfo,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(padAmpModLfoChanged(int)));

	connect(mainWindow->dial_PadAmpModLfoLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(padAmpModLevelLfoChanged(int)));

	connect(mainWindow->comboBox_PadAmpModEnv,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(padAmpModEnvChanged(int)));

	connect(mainWindow->dial_PadAmpModEnvLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(padAmpModLevelEnvChanged(int)));

	connect(mainWindow->comboBox_PadBaseNote,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(padBaseNoteChanged(int)));

	connect(mainWindow->comboBox_PadQuality,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(padQualityChanged(int)));

	connect(mainWindow->comboBox_PadShape,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(padShapeChanged(int)));

	connect(mainWindow->comboBox_PadShapeCutoff,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(padShapeCutoffChanged(int)));

	connect(mainWindow->horizontalSlider_PadBaseWidth,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(padBaseWidthChanged(int)));

	connect(mainWindow->verticalSlider_PadHarmony_1,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(padHarmony1levelChanged(int)));

	connect(mainWindow->verticalSlider_PadHarmony_2,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(padHarmony2levelChanged(int)));

	connect(mainWindow->verticalSlider_PadHarmony_3,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(padHarmony3levelChanged(int)));

	connect(mainWindow->verticalSlider_PadHarmony_4,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(padHarmony4levelChanged(int)));

	connect(mainWindow->verticalSlider_PadHarmony_5,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(padHarmony5levelChanged(int)));

	connect(mainWindow->verticalSlider_PadHarmony_6,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(padHarmony6levelChanged(int)));

	connect(mainWindow->verticalSlider_PadHarmony_7,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(padHarmony7levelChanged(int)));

	connect(mainWindow->verticalSlider_PadHarmony_8,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(padHarmony8levelChanged(int)));
	
	connect(mainWindow->verticalSlider_PadHarmony_9,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(padHarmony9levelChanged(int)));
	
	connect(mainWindow->verticalSlider_PadHarmony_10,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(padHarmony10levelChanged(int)));

	connect(mainWindow->verticalSlider_PadHarmonyDetune,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(padHarmoniesDetuneChanged(int)));
	
}

void KspPadTabUiHandling::setWidgetsInfoMap()
{
	// Widgets Ids
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->horizontalSlider_KarplusWaveformVariations, _KARPLUS_1_EVENT * 10000 + _KARPLUS_STRONG_EXCITATION_WAVEFORM_VARIATIONS);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->horizontalSlider_KarplusDecayOn, _KARPLUS_1_EVENT * 10000 + _KARPLUS_STRONG_ON_DECAY);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->horizontalSlider_KarplusDecayOff, _KARPLUS_1_EVENT * 10000 + _KARPLUS_STRONG_OFF_DECAY);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->horizontalSlider_KarplusStringDamping, _KARPLUS_1_EVENT * 10000 + _KARPLUS_STRONG_STRING_DAMPING);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->horizontalSlider_KarplusStringDampingVariation, _KARPLUS_1_EVENT * 10000 + _KARPLUS_STRONG_STRING_DAMPING_VARIATION);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->horizontalSlider_KarplusPluckDamping, _KARPLUS_1_EVENT * 10000 + _KARPLUS_STRONG_PLUCK_DAMPING);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->horizontalSlider_KarplusPluckDampingVariation, _KARPLUS_1_EVENT * 10000 + _KARPLUS_STRONG_PLUCK_DAMPING_VARIATION);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_KarplusFilterSend_1, _KARPLUS_1_EVENT * 10000 + _KARPLUS_STRONG_SEND_1);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_KarplusFilterSend_2, _KARPLUS_1_EVENT * 10000 + _KARPLUS_STRONG_SEND_2);

	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_padFilterSend_1, _PAD_1_EVENT * 10000 + _PAD_FILTER_SEND_1);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_padFilterSend_2, _PAD_1_EVENT * 10000 + _PAD_FILTER_SEND_2);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_PadFreqModLfoLevel, _PAD_1_EVENT * 10000 + _PAD_FREQ_MOD_LFO_LEVEL);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_PadFreqModEnvLevel, _PAD_1_EVENT * 10000 + _PAD_FREQ_MOD_ENV_LEVEL);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_PadAmpModLfoLevel, _PAD_1_EVENT * 10000 + _PAD_AMP_MOD_LFO_LEVEL);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_PadAmpModEnvLevel, _PAD_1_EVENT * 10000 + _PAD_AMP_MOD_ENV_LEVEL);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->horizontalSlider_PadBaseWidth, _PAD_1_EVENT * 10000 + _PAD_BASE_WIDTH);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->verticalSlider_PadHarmony_1, _PAD_1_EVENT * 10000 + _PAD_HARMONY_LEVEL_1);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->verticalSlider_PadHarmony_2, _PAD_1_EVENT * 10000 + _PAD_HARMONY_LEVEL_2);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->verticalSlider_PadHarmony_3, _PAD_1_EVENT * 10000 + _PAD_HARMONY_LEVEL_3);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->verticalSlider_PadHarmony_4, _PAD_1_EVENT * 10000 + _PAD_HARMONY_LEVEL_4);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->verticalSlider_PadHarmony_5, _PAD_1_EVENT * 10000 + _PAD_HARMONY_LEVEL_5);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->verticalSlider_PadHarmony_6, _PAD_1_EVENT * 10000 + _PAD_HARMONY_LEVEL_6);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->verticalSlider_PadHarmony_7, _PAD_1_EVENT * 10000 + _PAD_HARMONY_LEVEL_7);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->verticalSlider_PadHarmony_8, _PAD_1_EVENT * 10000 + _PAD_HARMONY_LEVEL_8);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->verticalSlider_PadHarmony_9, _PAD_1_EVENT * 10000 + _PAD_HARMONY_LEVEL_9);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->verticalSlider_PadHarmony_10, _PAD_1_EVENT * 10000 + _PAD_HARMONY_LEVEL_10);

	
	// Widgets types
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->horizontalSlider_KarplusWaveformVariations, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->horizontalSlider_KarplusDecayOn, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->horizontalSlider_KarplusDecayOff, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->horizontalSlider_KarplusStringDamping, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->horizontalSlider_KarplusStringDampingVariation, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->horizontalSlider_KarplusPluckDamping, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->horizontalSlider_KarplusPluckDampingVariation, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_KarplusFilterSend_1, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_KarplusFilterSend_2, _CONTROL_TYPE_DIAL);

	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_padFilterSend_1, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_padFilterSend_2, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_PadFreqModLfoLevel, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_PadFreqModEnvLevel, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_PadAmpModLfoLevel, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_PadAmpModEnvLevel, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->horizontalSlider_PadBaseWidth, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->verticalSlider_PadHarmony_1, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->verticalSlider_PadHarmony_2, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->verticalSlider_PadHarmony_3, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->verticalSlider_PadHarmony_4, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->verticalSlider_PadHarmony_5, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->verticalSlider_PadHarmony_6, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->verticalSlider_PadHarmony_7, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->verticalSlider_PadHarmony_8, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->verticalSlider_PadHarmony_9, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->verticalSlider_PadHarmony_10, _CONTROL_TYPE_SLIDER);
}

void KspPadTabUiHandling::update_kps()
{
	static bool oneTimeInitialized = false;

	if (!oneTimeInitialized)
	{
		oneTimeInitialized = true;
		
		mainWindow->comboBox_KarplusExcitationWaveform->blockSignals(true);
		mainWindow->comboBox_KarplusExcitationWaveform->addItems(stringKarplusExcitationWaveformList);
		mainWindow->comboBox_KarplusExcitationWaveform->blockSignals(false);

		mainWindow->comboBox_KarplusStringDampingCalculationMode->blockSignals(true);
		mainWindow->comboBox_KarplusStringDampingCalculationMode->addItems(stringKarplusStringDampingCalcModeList);
		mainWindow->comboBox_KarplusStringDampingCalculationMode->blockSignals(false);		
	}
	
	mainWindow->comboBox_KarplusExcitationWaveform->blockSignals(true);
	mainWindow->comboBox_KarplusExcitationWaveform->setCurrentIndex(mod_synth_get_active_karplus_excitation_waveform_type());
	mainWindow->comboBox_KarplusExcitationWaveform->blockSignals(false);

	mainWindow->comboBox_KarplusStringDampingCalculationMode->blockSignals(true);
	mainWindow->comboBox_KarplusStringDampingCalculationMode->setCurrentIndex(mod_synth_get_active_karplus_string_damping_calculation_mode());
	mainWindow->comboBox_KarplusStringDampingCalculationMode->blockSignals(false);

	mainWindow->horizontalSlider_KarplusWaveformVariations->blockSignals(true);
	mainWindow->horizontalSlider_KarplusWaveformVariations->setValue(mod_synth_get_active_karplus_excitation_waveform_variations());
	mainWindow->horizontalSlider_KarplusWaveformVariations->blockSignals(false);

	mainWindow->horizontalSlider_KarplusStringDamping->blockSignals(true);
	mainWindow->horizontalSlider_KarplusStringDamping->setValue(mod_synth_get_active_karplus_string_damping());
	mainWindow->horizontalSlider_KarplusStringDamping->blockSignals(false);
	
	mainWindow->horizontalSlider_KarplusPluckDamping->blockSignals(true);
	mainWindow->horizontalSlider_KarplusPluckDamping->setValue(mod_synth_get_active_karplus_pluck_damping());
	mainWindow->horizontalSlider_KarplusPluckDamping->blockSignals(false);

	mainWindow->horizontalSlider_KarplusDecayOn->blockSignals(true);
	mainWindow->horizontalSlider_KarplusDecayOn->setValue(mod_synth_get_active_karplus_string_on_decay());
	mainWindow->horizontalSlider_KarplusDecayOn->blockSignals(false);

	mainWindow->horizontalSlider_KarplusDecayOff->blockSignals(true);
	mainWindow->horizontalSlider_KarplusDecayOff->setValue(mod_synth_get_active_karplus_string_off_decay());
	mainWindow->horizontalSlider_KarplusDecayOff->blockSignals(false);

	mainWindow->horizontalSlider_KarplusStringDampingVariation->blockSignals(true);
	mainWindow->horizontalSlider_KarplusStringDampingVariation->setValue(mod_synth_get_active_karplus_string_damping_variation());
	mainWindow->horizontalSlider_KarplusStringDampingVariation->blockSignals(false);
	
	mainWindow->horizontalSlider_KarplusPluckDampingVariation->blockSignals(true);
	mainWindow->horizontalSlider_KarplusPluckDampingVariation->setValue(mod_synth_get_active_karplus_pluck_damping_variation());
	mainWindow->horizontalSlider_KarplusPluckDampingVariation->blockSignals(false);

	mainWindow->dial_KarplusFilterSend_1->blockSignals(true);
	mainWindow->dial_KarplusFilterSend_1->setValue(mod_synth_get_active_karplus_send_filter_1());
	mainWindow->dial_KarplusFilterSend_1->blockSignals(false);
									  
	mainWindow->dial_KarplusFilterSend_2->blockSignals(true);
	mainWindow->dial_KarplusFilterSend_2->setValue(mod_synth_get_active_karplus_send_filter_2());
	mainWindow->dial_KarplusFilterSend_2->blockSignals(false);

	karplus_enabled = mod_synth_get_active_karplus_enable_state(); 
	mainWindow->checkBox_enableKarplus->blockSignals(true);
	mainWindow->checkBox_enableKarplus->setChecked(karplus_enabled);
	mainWindow->checkBox_enableKarplus->blockSignals(false);
	if (karplus_enabled)
	{
		mainWindow->groupBox_Karplus->setEnabled(true);
	}
	else
	{
		mainWindow->groupBox_Karplus->setEnabled(false);
	}		
}

void KspPadTabUiHandling::update_pad()
{
	static bool oneTimeInitialized = false;

	if (!oneTimeInitialized)
	{
		oneTimeInitialized = true;

		mainWindow->comboBox_PadQuality->blockSignals(true);
		mainWindow->comboBox_PadQuality->addItems(stringQualitiesList);
		mainWindow->comboBox_PadQuality->blockSignals(false);

		mainWindow->comboBox_PadBaseNote->blockSignals(true);
		mainWindow->comboBox_PadBaseNote->addItems(stringBaseNotesList);
		mainWindow->comboBox_PadBaseNote->blockSignals(false);

		mainWindow->comboBox_PadShape->blockSignals(true);
		mainWindow->comboBox_PadShape->addItems(stringShapesList);
		mainWindow->comboBox_PadShape->blockSignals(false);

		mainWindow->comboBox_PadShapeCutoff->blockSignals(true);
		mainWindow->comboBox_PadShapeCutoff->addItems(stringShapeCutoffsList);
		mainWindow->comboBox_PadShapeCutoff->blockSignals(false);

		mainWindow->comboBox_PadTuneOct->blockSignals(true);
		mainWindow->comboBox_PadTuneSemi->blockSignals(true);
		mainWindow->comboBox_PadTuneCents->blockSignals(true);
		for (int i = mod_synth_get_osc_detune_min_octave(); i <= mod_synth_get_osc_detune_max_octave(); i++)
		{
			mainWindow->comboBox_PadTuneOct->addItem(QString::number(i));
		}

		for (int i = mod_synth_get_osc_detune_min_semitones(); i <= mod_synth_get_osc_detune_max_semitones(); i++)
		{
			mainWindow->comboBox_PadTuneSemi->addItem(QString::number(i));
		}

		for (int i = 4 * mod_synth_get_osc_detune_min_cents(); i <= 4 * mod_synth_get_osc_detune_max_cents(); i++)
		{
			// 0.25 steps
			mainWindow->comboBox_PadTuneCents->addItem(QString::number(i / 4.f));
		}

		mainWindow->comboBox_PadTuneOct->blockSignals(false);
		mainWindow->comboBox_PadTuneSemi->blockSignals(false);
		mainWindow->comboBox_PadTuneCents->blockSignals(false);

		mainWindow->comboBox_PadFreqModEnv->blockSignals(true);
		mainWindow->comboBox_PadFreqModEnv->addItems(MainWindow::getInstance()->stringEnvsList);
		mainWindow->comboBox_PadFreqModEnv->blockSignals(false);

		mainWindow->comboBox_PadFreqModLfo->blockSignals(true);
		mainWindow->comboBox_PadFreqModLfo->addItems(MainWindow::getInstance()->stringLfosList);
		mainWindow->comboBox_PadFreqModLfo->blockSignals(false);

		mainWindow->comboBox_PadAmpModEnv->blockSignals(true);
		mainWindow->comboBox_PadAmpModEnv->addItems(MainWindow::getInstance()->stringEnvsList);
		mainWindow->comboBox_PadAmpModEnv->blockSignals(false);

		mainWindow->comboBox_PadAmpModLfo->blockSignals(true);
		mainWindow->comboBox_PadAmpModLfo->addItems(MainWindow::getInstance()->stringLfosList);
		mainWindow->comboBox_PadAmpModLfo->blockSignals(false);		
	}

	pad_enabled = mod_synth_get_active_pad_enable_state();
	mainWindow->checkBox_enablePadSynth->blockSignals(true);
	mainWindow->checkBox_enablePadSynth->setChecked(pad_enabled);
	mainWindow->checkBox_enablePadSynth->blockSignals(false);
	if (pad_enabled)
	{
		mainWindow->groupBox_PadSynthesizer->setEnabled(true);
	}
	else
	{
		mainWindow->groupBox_PadSynthesizer->setEnabled(false);
	}

	mainWindow->comboBox_PadTuneOct->blockSignals(true);
	mainWindow->comboBox_PadTuneOct->setCurrentIndex(mod_synth_get_active_pad_detune_octave() - mod_synth_get_osc_detune_min_octave());
	mainWindow->comboBox_PadTuneOct->blockSignals(false);

	mainWindow->comboBox_PadTuneSemi->blockSignals(true);
	mainWindow->comboBox_PadTuneSemi->setCurrentIndex(mod_synth_get_active_pad_detune_semitones() - mod_synth_get_osc_detune_min_semitones());
	mainWindow->comboBox_PadTuneSemi->blockSignals(false);

	mainWindow->comboBox_PadTuneCents->blockSignals(true);
	mainWindow->comboBox_PadTuneCents->setCurrentIndex(mod_synth_get_active_pad_detune_cents() - mod_synth_get_osc_detune_min_cents() * 4.f);
	mainWindow->comboBox_PadTuneCents->blockSignals(false);

	mainWindow->dial_padFilterSend_1->blockSignals(true);
	mainWindow->dial_padFilterSend_1->setValue(mod_synth_get_active_pad_send_filter_1());
	mainWindow->dial_padFilterSend_1->blockSignals(false);

	mainWindow->dial_padFilterSend_2->blockSignals(true);
	mainWindow->dial_padFilterSend_2->setValue(mod_synth_get_active_pad_send_filter_2());
	mainWindow->dial_padFilterSend_2->blockSignals(false);

	mainWindow->comboBox_PadFreqModLfo->blockSignals(true);
	mainWindow->comboBox_PadFreqModLfo->setCurrentIndex(mod_synth_get_active_pad_freq_mod_lfo());
	mainWindow->comboBox_PadFreqModLfo->blockSignals(false);

	mainWindow->dial_PadFreqModLfoLevel->blockSignals(true);
	mainWindow->dial_PadFreqModLfoLevel->setValue(mod_synth_get_active_pad_freq_mod_lfo_level());
	mainWindow->dial_PadFreqModLfoLevel->blockSignals(false);

	mainWindow->comboBox_PadFreqModEnv->blockSignals(true);
	mainWindow->comboBox_PadFreqModEnv->setCurrentIndex(mod_synth_get_active_pad_freq_mod_env());
	mainWindow->comboBox_PadFreqModEnv->blockSignals(false);

	mainWindow->dial_PadFreqModEnvLevel->blockSignals(true);
	mainWindow->dial_PadFreqModEnvLevel->setValue(mod_synth_get_active_pad_freq_mod_env_level());
	mainWindow->dial_PadFreqModEnvLevel->blockSignals(false);

	mainWindow->comboBox_PadAmpModLfo->blockSignals(true);
	mainWindow->comboBox_PadAmpModLfo->setCurrentIndex(mod_synth_get_active_pad_amp_mod_lfo());
	mainWindow->comboBox_PadAmpModLfo->blockSignals(false);

	mainWindow->dial_PadAmpModLfoLevel->blockSignals(true);
	mainWindow->dial_PadAmpModLfoLevel->setValue(mod_synth_get_active_pad_amp_mod_lfo_level());
	mainWindow->dial_PadAmpModLfoLevel->blockSignals(false);

	mainWindow->comboBox_PadAmpModEnv->blockSignals(true);
	mainWindow->comboBox_PadAmpModEnv->setCurrentIndex(mod_synth_get_active_pad_amp_mod_env());
	mainWindow->comboBox_PadAmpModEnv->blockSignals(false);

	mainWindow->dial_PadAmpModEnvLevel->blockSignals(true);
	mainWindow->dial_PadAmpModEnvLevel->setValue(mod_synth_get_active_pad_amp_mod_env_level());
	mainWindow->dial_PadAmpModEnvLevel->blockSignals(false);

	mainWindow->comboBox_PadQuality->blockSignals(true);
	mainWindow->comboBox_PadQuality->setCurrentIndex(mod_synth_get_active_pad_quality());
	mainWindow->comboBox_PadQuality->blockSignals(false);

	mainWindow->comboBox_PadShape->blockSignals(true);
	mainWindow->comboBox_PadShape->setCurrentIndex(mod_synth_get_active_pad_shape());
	mainWindow->comboBox_PadShape->blockSignals(false);

	mainWindow->comboBox_PadShapeCutoff->blockSignals(true);
	mainWindow->comboBox_PadShapeCutoff->setCurrentIndex(mod_synth_get_active_pad_shape_cutoff());
	mainWindow->comboBox_PadShapeCutoff->blockSignals(false);

	mainWindow->comboBox_PadBaseNote->blockSignals(true);
	mainWindow->comboBox_PadBaseNote->setCurrentIndex(mod_synth_get_active_pad_base_note());
	mainWindow->comboBox_PadBaseNote->blockSignals(false);

	mainWindow->horizontalSlider_PadBaseWidth->blockSignals(true);
	mainWindow->horizontalSlider_PadBaseWidth->setValue(mod_synth_get_active_pad_base_width());
	mainWindow->horizontalSlider_PadBaseWidth->blockSignals(false);

	mainWindow->verticalSlider_PadHarmony_1->blockSignals(true);
	mainWindow->verticalSlider_PadHarmony_1->setValue(mod_synth_get_active_pad_harmony_level(0));
	mainWindow->verticalSlider_PadHarmony_1->blockSignals(false);

	mainWindow->verticalSlider_PadHarmony_2->blockSignals(true);
	mainWindow->verticalSlider_PadHarmony_2->setValue(mod_synth_get_active_pad_harmony_level(1));
	mainWindow->verticalSlider_PadHarmony_2->blockSignals(false);

	mainWindow->verticalSlider_PadHarmony_3->blockSignals(true);
	mainWindow->verticalSlider_PadHarmony_3->setValue(mod_synth_get_active_pad_harmony_level(2));
	mainWindow->verticalSlider_PadHarmony_3->blockSignals(false);

	mainWindow->verticalSlider_PadHarmony_4->blockSignals(true);
	mainWindow->verticalSlider_PadHarmony_4->setValue(mod_synth_get_active_pad_harmony_level(3));
	mainWindow->verticalSlider_PadHarmony_4->blockSignals(false);

	mainWindow->verticalSlider_PadHarmony_5->blockSignals(true);
	mainWindow->verticalSlider_PadHarmony_5->setValue(mod_synth_get_active_pad_harmony_level(4));
	mainWindow->verticalSlider_PadHarmony_5->blockSignals(false);

	mainWindow->verticalSlider_PadHarmony_6->blockSignals(true);
	mainWindow->verticalSlider_PadHarmony_6->setValue(mod_synth_get_active_pad_harmony_level(5));
	mainWindow->verticalSlider_PadHarmony_6->blockSignals(false);

	mainWindow->verticalSlider_PadHarmony_7->blockSignals(true);
	mainWindow->verticalSlider_PadHarmony_7->setValue(mod_synth_get_active_pad_harmony_level(6));
	mainWindow->verticalSlider_PadHarmony_7->blockSignals(false);

	mainWindow->verticalSlider_PadHarmony_8->blockSignals(true);
	mainWindow->verticalSlider_PadHarmony_8->setValue(mod_synth_get_active_pad_harmony_level(7));
	mainWindow->verticalSlider_PadHarmony_8->blockSignals(false);

	mainWindow->verticalSlider_PadHarmony_9->blockSignals(true);
	mainWindow->verticalSlider_PadHarmony_9->setValue(mod_synth_get_active_pad_harmony_level(8));
	mainWindow->verticalSlider_PadHarmony_9->blockSignals(false);

	mainWindow->verticalSlider_PadHarmony_10->blockSignals(true);
	mainWindow->verticalSlider_PadHarmony_10->setValue(mod_synth_get_active_pad_harmony_level(9));
	mainWindow->verticalSlider_PadHarmony_10->blockSignals(false);

	mainWindow->verticalSlider_PadHarmonyDetune->blockSignals(true);
	mainWindow->verticalSlider_PadHarmonyDetune->setValue(mod_synth_get_active_pad_harmony_detune());
	mainWindow->verticalSlider_PadHarmonyDetune->blockSignals(false);

	update_plots = true;
}

// Slots

void KspPadTabUiHandling::karplusExcitationWaveformChanged(int val)
{
	mod_synth_karplus_event(_KARPLUS_1_EVENT, _KARPLUS_STRONG_EXCITATION_WAVEFORM, val);
}

void KspPadTabUiHandling::karplusExcitationWaveformVariationsChanged(int val)
{
	mod_synth_karplus_event(_KARPLUS_1_EVENT, _KARPLUS_STRONG_EXCITATION_WAVEFORM_VARIATIONS, val);
	sprintf(mssg1, "Karplus Waveform Variations: %.2f", (float)val / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void KspPadTabUiHandling::karplusStringDampingChanged(int val)
{
	mod_synth_karplus_event(_KARPLUS_1_EVENT, _KARPLUS_STRONG_STRING_DAMPING, val);
	sprintf(mssg1,
		"Karplus String Damping: %.2f",
		mod_synth_get_karplus_strong_min_string_damping() + 
		((float)val / 100.0f) * (mod_synth_get_karplus_strong_max_string_damping() - mod_synth_get_karplus_strong_min_string_damping()));
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void KspPadTabUiHandling::KspPadTabUiHandling::karplusPluckDampingChanged(int val)
{
	mod_synth_karplus_event(_KARPLUS_1_EVENT, _KARPLUS_STRONG_PLUCK_DAMPING, val);
	sprintf(mssg1,
		"Karplus Pluck Damping: %.2f",
		mod_synth_get_karplus_strong_min_pluck_damping() + 
		((float)val / 100.0f) * (mod_synth_get_karplus_strong_max_pluck_damping() - mod_synth_get_karplus_strong_min_pluck_damping()));
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void KspPadTabUiHandling::karplusOnDecayChanged(int val)
{
	mod_synth_karplus_event(_KARPLUS_1_EVENT, _KARPLUS_STRONG_ON_DECAY, val);
	sprintf(mssg1,
		"Karplus On Decay: %.3f",
		mod_synth_get_karplus_strong_min_decay() + 
		((float)val / 100.0f) * (mod_synth_get_karplus_strong_max_decay() - mod_synth_get_karplus_strong_min_decay()));
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void KspPadTabUiHandling::karplusOffDecayChanged(int val)
{
	mod_synth_karplus_event(_KARPLUS_1_EVENT, _KARPLUS_STRONG_OFF_DECAY, val);
	sprintf(mssg1,
		"Karplus Off Decay: %.3f",
		mod_synth_get_karplus_strong_min_decay() + ((float)val / 100.0f) * (mod_synth_get_karplus_strong_max_decay() - 
			mod_synth_get_karplus_strong_min_decay()));
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void KspPadTabUiHandling::karplusStringDampingVariationChanged(int val)
{
	mod_synth_karplus_event(_KARPLUS_1_EVENT, _KARPLUS_STRONG_STRING_DAMPING_VARIATION, val);
	sprintf(mssg1,
		"Karplus String Damping Variation: %.2f",
		mod_synth_get_karplus_strong_min_string_damping_variations() + ((float)val / 100.0f) *
		(mod_synth_get_karplus_strong_max_string_damping_variations() - 
		mod_synth_get_karplus_strong_min_string_damping_variations()));
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void KspPadTabUiHandling::karplusPluckDampingVariationChanged(int val)
{
	mod_synth_karplus_event(_KARPLUS_1_EVENT, _KARPLUS_STRONG_PLUCK_DAMPING_VARIATION, val);
	sprintf(mssg1,
		"Karplus Pluck Damping Variation: %.2f",
		mod_synth_get_karplus_strong_min_pluck_damping_variations() + ((float)val / 100.0f) *
		(mod_synth_get_karplus_strong_max_pluck_damping_variations() - 
		mod_synth_get_karplus_strong_min_pluck_damping_variations()));
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void KspPadTabUiHandling::karplusStringDampingCalcModeChanged(int val)
{
	mod_synth_karplus_event(_KARPLUS_1_EVENT, _KARPLUS_STRONG_STRING_DUMP_CALC_MODE, val);
}

void KspPadTabUiHandling::karplusSendFilter1Changed(int val)
{
	mod_synth_karplus_event(_KARPLUS_1_EVENT, _KARPLUS_STRONG_SEND_1, val);
	sprintf(mssg1, "Karplus Filter 1 Send Level: %.2f", (float)val / 100.0);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void KspPadTabUiHandling::karplusSendFilter2Changed(int val)
{
	mod_synth_karplus_event(_KARPLUS_1_EVENT, _KARPLUS_STRONG_SEND_2, val);
	sprintf(mssg1, "Karplus Filter 2 Send Level: %.2f", (float)val / 100.0);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void KspPadTabUiHandling::karplusEnableChanged(bool val)
{
	if (val)
	{
		karplus_enabled = true;
		mod_synth_enable_karplus();
	}
	else
	{
		karplus_enabled = false;
		mod_synth_disable_karplus();
	}
}

void KspPadTabUiHandling::padEnableChanged(bool val)
{
	if (val)
	{	
		mod_synth_enable_pad_synth();
	}
	else
	{	
		mod_synth_disable_pad_synth();
	}
}

void KspPadTabUiHandling::padDetuneOctaveChanged(int val)
{
	mod_synth_pad_event(_PAD_1_EVENT, _PAD_DETUNE_OCTAVE, val);
}

void KspPadTabUiHandling::padDetuneSeminotesChanged(int val)
{
	mod_synth_pad_event(_PAD_1_EVENT, _PAD_DETUNE_SEMITONES, val);
}

void KspPadTabUiHandling::padDetuneCentsChanged(int val)
{
	mod_synth_pad_event(_PAD_1_EVENT, _PAD_DETUNE_CENTS, val);
}

void KspPadTabUiHandling::padSendFilter1Changed(int val)
{
	mod_synth_pad_event(_PAD_1_EVENT, _PAD_FILTER_SEND_1, val);
	sprintf(mssg1, "PAD 1 send Filter 1: %.2f", (float)val / 100.0);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void KspPadTabUiHandling::padSendFilter2Changed(int val)
{
	mod_synth_pad_event(_PAD_1_EVENT, _PAD_FILTER_SEND_2, val);
	sprintf(mssg1, "PAD 1 send Filter 2: %.2f", (float)val / 100.0);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void KspPadTabUiHandling::padFreqModLfoChanged(int val)
{
	mod_synth_pad_event(_PAD_1_EVENT, _PAD_FREQ_MOD_LFO, val);
}

void KspPadTabUiHandling::padFreqModLevelLfoChanged(int val)
{
	mod_synth_pad_event(_PAD_1_EVENT, _PAD_FREQ_MOD_LFO_LEVEL, val);
	sprintf(mssg1, "PAD 1 LFO freq modulation level: %.2f", (float)val / 100.0);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void KspPadTabUiHandling::padFreqModEnvChanged(int val)
{
	mod_synth_pad_event(_PAD_1_EVENT, _PAD_FREQ_MOD_ENV, val);
}

void KspPadTabUiHandling::padFreqModLevelEnvChanged(int val)
{
	mod_synth_pad_event(_PAD_1_EVENT, _PAD_FREQ_MOD_ENV_LEVEL, val);
	sprintf(mssg1, "PAD 1 ENV freq modulation level: %.2f", (float)val / 100.0);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void KspPadTabUiHandling::padAmpModLfoChanged(int val)
{
	mod_synth_pad_event(_PAD_1_EVENT, _PAD_AMP_MOD_LFO, val);
}

void KspPadTabUiHandling::padAmpModLevelLfoChanged(int val)
{
	mod_synth_pad_event(_PAD_1_EVENT, _PAD_AMP_MOD_LFO_LEVEL, val);
	sprintf(mssg1, "PAD 1 LFO amp modulation level: %.2f", (float)val / 100.0);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void KspPadTabUiHandling::padAmpModEnvChanged(int val)
{
	mod_synth_pad_event(_PAD_1_EVENT, _PAD_AMP_MOD_ENV, val);
}

void KspPadTabUiHandling::padAmpModLevelEnvChanged(int val)
{
	mod_synth_pad_event(_PAD_1_EVENT, _PAD_AMP_MOD_ENV_LEVEL, val);
	sprintf(mssg1, "PAD 1 ENV amp modulation level: %.2f", (float)val / 100.0);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void KspPadTabUiHandling::padQualityChanged(int val)
{
	mod_synth_disable_pad_synth();
	mod_synth_pad_event(_PAD_1_EVENT, _PAD_QUALITY, val);
	replotProfile();
	replotSpectrum();
	mod_synth_enable_pad_synth();
}

void KspPadTabUiHandling::padBaseNoteChanged(int val)
{
	mod_synth_disable_pad_synth();
	mod_synth_pad_event(_PAD_1_EVENT, _PAD_BASE_NOTE, val);
	replotSpectrum();
	replotProfile();
	replotSpectrum();
	mod_synth_enable_pad_synth();
}

void KspPadTabUiHandling::padBaseWidthChanged(int val)
{
	mod_synth_disable_pad_synth();
	mod_synth_pad_event(_PAD_1_EVENT, _PAD_BASE_WIDTH, val);
	sprintf(mssg1, "PAD 1 Base Width: %.2f", (float)val / 100.0);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	replotProfile();
	replotSpectrum();
	mod_synth_enable_pad_synth();
}

void KspPadTabUiHandling::padShapeChanged(int val)
{
	mod_synth_disable_pad_synth();
	mod_synth_pad_event(_PAD_1_EVENT, _PAD_SHAPE, val);
	replotProfile();
	replotSpectrum();
	mod_synth_enable_pad_synth();
}

void KspPadTabUiHandling::padShapeCutoffChanged(int val)
{
	mod_synth_disable_pad_synth();
	mod_synth_pad_event(_PAD_1_EVENT, _PAD_SHAPE_CUTOFF, val);
	replotProfile();
	replotSpectrum();
	mod_synth_enable_pad_synth();
}

void KspPadTabUiHandling::padGenerateClicked(bool val)
{
	mod_synth_disable_pad_synth();
	replotProfile();
	replotSpectrum();
	
	mainWindow->checkBox_enablePadSynth->blockSignals(true);
	mainWindow->checkBox_enablePadSynth->clicked(false);
	mainWindow->checkBox_enablePadSynth->blockSignals(false);
	mod_synth_enable_pad_synth();
}


void KspPadTabUiHandling::padHarmony1levelChanged(int val)
{
	mod_synth_disable_pad_synth();
	mod_synth_pad_event(_PAD_1_EVENT, _PAD_HARMONY_LEVEL_1, val);
	sprintf(mssg1, "PAD 1 Harmony 1 level: %.2f", (float)val / 100.0);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	replotProfile();
	replotSpectrum();
	mod_synth_enable_pad_synth();
}

void KspPadTabUiHandling::padHarmony2levelChanged(int val)
{
	mod_synth_disable_pad_synth();
	mod_synth_pad_event(_PAD_1_EVENT, _PAD_HARMONY_LEVEL_2, val);
	sprintf(mssg1, "PAD 1 Harmony 2 level: %.2f", (float)val / 100.0);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	replotProfile();
	replotSpectrum();
	mod_synth_enable_pad_synth();
}

void KspPadTabUiHandling::padHarmony3levelChanged(int val)
{
	mod_synth_disable_pad_synth();
	mod_synth_pad_event(_PAD_1_EVENT, _PAD_HARMONY_LEVEL_3, val);
	sprintf(mssg1, "PAD 1 Harmony 3 level: %.2f", (float)val / 100.0);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	replotProfile();
	replotSpectrum();
	mod_synth_enable_pad_synth();
}

void KspPadTabUiHandling::padHarmony4levelChanged(int val)
{
	mod_synth_disable_pad_synth();
	mod_synth_pad_event(_PAD_1_EVENT, _PAD_HARMONY_LEVEL_4, val);
	sprintf(mssg1, "PAD 1 Harmony 4 level: %.2f", (float)val / 100.0);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	replotProfile();
	replotSpectrum();
	mod_synth_enable_pad_synth();
}

void KspPadTabUiHandling::padHarmony5levelChanged(int val)
{
	mod_synth_disable_pad_synth();
	mod_synth_pad_event(_PAD_1_EVENT, _PAD_HARMONY_LEVEL_5, val);
	sprintf(mssg1, "PAD 1 Harmony 5 level: %.2f", (float)val / 100.0);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	replotProfile();
	replotSpectrum();
	mod_synth_enable_pad_synth();
}

void KspPadTabUiHandling::padHarmony6levelChanged(int val)
{
	mod_synth_disable_pad_synth();
	mod_synth_pad_event(_PAD_1_EVENT, _PAD_HARMONY_LEVEL_6, val);
	sprintf(mssg1, "PAD 1 Harmony 6 level: %.2f", (float)val / 100.0);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	replotProfile();
	replotSpectrum();
	mod_synth_enable_pad_synth();
}

void KspPadTabUiHandling::padHarmony7levelChanged(int val)
{
	mod_synth_disable_pad_synth();
	mod_synth_pad_event(_PAD_1_EVENT, _PAD_HARMONY_LEVEL_7, val);
	sprintf(mssg1, "PAD 1 Harmony 7 level: %.2f", (float)val / 100.0);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	replotProfile();
	mod_synth_enable_pad_synth();
	replotSpectrum();
}

void KspPadTabUiHandling::padHarmony8levelChanged(int val)
{
	mod_synth_disable_pad_synth();
	mod_synth_pad_event(_PAD_1_EVENT, _PAD_HARMONY_LEVEL_8, val);
	sprintf(mssg1, "PAD 1 Harmony 8 level: %.2f", (float)val / 100.0);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	replotProfile();
	replotSpectrum();
	mod_synth_enable_pad_synth();
}

void KspPadTabUiHandling::padHarmony9levelChanged(int val)
{
	mod_synth_disable_pad_synth();
	mod_synth_pad_event(_PAD_1_EVENT, _PAD_HARMONY_LEVEL_9, val);
	sprintf(mssg1, "PAD 1 Harmony 9 level: %.2f", (float)val / 100.0);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	replotProfile();
	replotSpectrum();
	mod_synth_enable_pad_synth();
}

void KspPadTabUiHandling::padHarmony10levelChanged(int val)
{
	mod_synth_disable_pad_synth();
	mod_synth_pad_event(_PAD_1_EVENT, _PAD_HARMONY_LEVEL_10, val);
	sprintf(mssg1, "PAD 1 Harmony 10 level: %.2f", (float)val / 100.0);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	replotProfile();
	replotSpectrum();
	mod_synth_enable_pad_synth();
}

void KspPadTabUiHandling::padHarmoniesDetuneChanged(int val)
{
	mod_synth_pad_event(_PAD_1_EVENT, _PAD_DETUNE, val);
	sprintf(mssg1, "PAD 1 Harmonies Detune: %.2f", (float)val / 100.0);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	replotProfile();
	replotSpectrum();
}


void KspPadTabUiHandling::setupProfilePlot(QCustomPlot *profilePlot)
{
	if (update_profile_plot && mod_synth_get_pad_base_harmony_profile())
	{
		// add two new graphs and set their look:
		QPen pen;
		pen.setStyle(Qt::SolidLine);
		pen.setWidth(3);
		pen.setColor(Qt::blue);
		profilePlot->addGraph();
		profilePlot->graph(0)->setPen(pen);
		profilePlot->addGraph();

		profilePlot->setBackground(QBrush(QColor("#929292")));
		
		//		customPlot->graph(1)->setPen(QPen(Qt::red));  // line color red for second graph
		QVector<double> x(mod_synth_get_pad_base_harmony_profile_size() + 1), y0(mod_synth_get_pad_base_harmony_profile_size() + 1);
		
		for (int i = 0; i < mod_synth_get_pad_base_harmony_profile_size(); ++i)
		{
			x[i] = i;
			y0[i] = *(mod_synth_get_pad_base_harmony_profile() + i);
		}
		profilePlot->xAxis->setVisible(false);
		profilePlot->xAxis->setTickLabels(false);
		profilePlot->yAxis->setVisible(false);
		profilePlot->yAxis->setTickLabels(false);
		profilePlot->graph(0)->setData(x, y0);
		// let the ranges scale themselves so graph 0 fits perfectly in the visible area:
		profilePlot->graph(0)->rescaleAxes();
	}
}

void KspPadTabUiHandling::setupSpectrumPlot(QCustomPlot *spectrumPlot)
{
	const int width = 12;
	float sum;
	
	if (update_spectrum_plot && (mod_synth_get_pad_spectrum() /*!= NULL*/))
	{
		// add two new graphs and set their look:
		QPen pen;
		pen.setStyle(Qt::SolidLine);
		pen.setWidth(3);
		pen.setColor(Qt::blue);
		spectrumPlot->addGraph();
		spectrumPlot->graph(0)->setPen(pen);
		spectrumPlot->addGraph();

		spectrumPlot->setBackground(QBrush(QColor("#929292")));
		
		int spectrumSize = mod_synth_get_pad_spectrum_size();
		int step = spectrumSize / 1024;
		QVector<double> x(1024), y0(1024);
		for (int i = 0; i < 1024; ++i)
		{
			x[i] = i;
			sum = 0;
			for (int j = -width / 2; j < width / 2 + 1; j++)
			{
				if (((i * step / width + j) >= 0) && ((i * step / width + j) < spectrumSize))
				{
					sum += *(mod_synth_get_pad_spectrum() + i * step / width + j);
				}
			}
			y0[i] = sum / width;
//			y0[i] = *(mod_synth_get_pad_spectrum() + i * step / width );   //  /2 no such high freq
		}
		spectrumPlot->xAxis->setVisible(false);
		spectrumPlot->xAxis->setTickLabels(false);
		spectrumPlot->yAxis->setVisible(false);
		spectrumPlot->yAxis->setTickLabels(false);
		spectrumPlot->graph(0)->setData(x, y0);
		// let the ranges scale themselves so graph 0 fits perfectly in the visible area:
		spectrumPlot->graph(0)->rescaleAxes();
	}
}

// Must not be called from a callback, only from main window
void KspPadTabUiHandling::replotProfile()
{
	mod_synth_pad_event(_PAD_1_EVENT, _PAD_GENERATE, 1);
	setupProfilePlot(mainWindow->widget_PadProfilePlot);
	mainWindow->widget_PadProfilePlot->replot();
}

// Must not be called from a callback, only from main window
void KspPadTabUiHandling::replotSpectrum()
{
	setupSpectrumPlot(mainWindow->widget_PadSpectrumPlot);
	mainWindow->widget_PadSpectrumPlot->replot();
}





