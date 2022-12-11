/**
*	@file		FiltAmpKbdTab.cpp
*	@author		Nahum Budin
*	@date		12-Nov-2019
*	@version	1.0
*
*	@brief		Filters, Amplifier and Keyboard Tab ui handling.
*/

#include "MainWindow.h"
#include "FiltAmpKbdTab.h"
#include "libAdjHeartModSynth_2.h"

FiltAmpKbdTabUiHandling *FiltAmpKbdTabUiHandling::filtAmpKbdTabUiHandling = NULL;

FiltAmpKbdTabUiHandling::FiltAmpKbdTabUiHandling(Ui_MainWindow *mainWind)
{
	mainWindow = mainWind;
	
	stringFilterBandsList.append("Lowpass");
	stringFilterBandsList.append("Highpass");
	stringFilterBandsList.append("Bandpass");
	stringFilterBandsList.append("Allpass");
	
	stringKeyboardSlipList.append("---");
	stringKeyboardSlipList.append("C2");
	stringKeyboardSlipList.append("C3");
	stringKeyboardSlipList.append("C4");
	stringKeyboardSlipList.append("C5");
	
	mapKbdControlDialogShown = false;
	
	dialog_KbdControlMap = new Dialog_KbdControlMap(this);
}

FiltAmpKbdTabUiHandling *FiltAmpKbdTabUiHandling::getInstance() 
{
	return filtAmpKbdTabUiHandling;
}

void FiltAmpKbdTabUiHandling::setTrigers()
{
	connect(mainWindow->dial_Filter1_Freq,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(filter1freqChanged(int)));

	connect(mainWindow->dial_Filter1_Oct,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(filter1octChanged(int)));

	connect(mainWindow->dial_Filter1_Q,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(filter1Qchanged(int)));

	connect(mainWindow->dial_Filter1_Kbd_Track,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(filter1kbdTrackChanged(int)));

	connect(mainWindow->comboBox_Filter1_Band,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(filter1bandChanged(int)));

	connect(mainWindow->comboBox_Filter1FreqModLfo,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(filter1FreqModLfoChanged(int)));

	connect(mainWindow->dial_Filter1FreqModLfoLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(filter1FreqModLevelLfoChanged(int)));

	connect(mainWindow->comboBox_Filter1FreqModEnv,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(filter1FreqModEnvChanged(int)));

	connect(mainWindow->dial_Filter1FreqModEnvLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(filter1FreqModLevelEnvChanged(int)));

	connect(mainWindow->dial_Filter2_Freq,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(filter2freqChanged(int)));

	connect(mainWindow->dial_Filter2_Oct,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(filter2octChanged(int)));

	connect(mainWindow->dial_Filter2_Q,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(filter2Qchanged(int)));

	connect(mainWindow->dial_Filter2_Kbd_Track,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(filter2kbdTrackChanged(int)));

	connect(mainWindow->comboBox_Filter2_Band,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(filter2bandChanged(int)));

	connect(mainWindow->checkBox_Filter2_Track_Filter_1,
		SIGNAL(toggled(bool)),
		this,
		SLOT(filter2trackFilter1Changed(bool)));

	connect(mainWindow->comboBox_Filter2FreqModLfo,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(filter2FreqModLfoChanged(int)));

	connect(mainWindow->dial_Filter2FreqModLfoLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(filter2FreqModLevelLfoChanged(int)));

	connect(mainWindow->comboBox_Filter2FreqModEnv,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(filter2FreqModEnvChanged(int)));

	connect(mainWindow->dial_Filter2FreqModEnvLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(filter2FreqModLevelEnvChanged(int)));
	
	connect(mainWindow->dial_AmpLevel_1,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(amp1LevelChanged(int)));
	
	connect(mainWindow->dial_AmpPan_1,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(amp1PanChanged(int)));
	
	connect(mainWindow->dial_AmpSend_1,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(amp1SendChanged(int)));
	
	connect(mainWindow->dial_AmpLevel_2,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(amp2LevelChanged(int)));
	
	connect(mainWindow->dial_AmpPan_2,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(amp2PanChanged(int)));
	
	connect(mainWindow->dial_AmpSend_2,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(amp2SendChanged(int)));
	
	connect(mainWindow->comboBox_AmpPanModLfo_1,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(amp1PanModLfoChanged(int)));
	
	connect(mainWindow->dial_AmpPanModLevel_1,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(amp1PanModLevelLfoChanged(int)));
	
	connect(mainWindow->comboBox_AmpPanModLfo_2,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(amp2PanModLfoChanged(int)));
	
	connect(mainWindow->dial_AmpPanModLevel_2,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(amp2PanModLevelLfoChanged(int)));

	connect(mainWindow->checkBox_AmpFix,
		SIGNAL(toggled(bool)),
		this,
		SLOT(fixedChanged(bool)));
	
	connect(mainWindow->checkBox_keyboardEnablePortamento,
		SIGNAL(toggled(bool)),
		this,
		SLOT(kbdPortamentoEnableChanged(bool)));
	
	connect(mainWindow->dial_keyboardPortamento,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(kbdPortamentoLevelChanged(int)));
	
	connect(mainWindow->dialSensitivity,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(kbdSensitivityChanged(int)));

	connect(mainWindow->dialSensitivity_Low,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(kbdLowSensitivityChanged(int)));

	connect(mainWindow->comboBox_KbdSplit,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(kbdSplitChanged(int)));

	connect(mainWindow->radioButton_KbdModePoly,
		SIGNAL(clicked(bool)),
		this,
		SLOT(polyFifoClicked(bool)));

	connect(mainWindow->radioButton_KbdModeSolo,
		SIGNAL(clicked(bool)),
		this,
		SLOT(polyLimitClicked(bool)));
	
	connect(mainWindow->radioButton_KbdModeMidi,
		SIGNAL(clicked(bool)),
		this,
		SLOT(polyReuseClicked(bool)));
	
	connect(mainWindow->pushButton_KbdControlsMap,
		SIGNAL(clicked(bool)),
		this,
		SLOT(kbdControlsMapCliked(bool)));
}

void FiltAmpKbdTabUiHandling::setWidgetsInfoMap()
{
	// Widgets Ids
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_Filter1_Freq, _FILTER_1_EVENT * 10000 + _FILTER_FREQ);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_Filter1_Oct, _FILTER_1_EVENT * 10000 + _FILTER_OCT);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_Filter1_Q, _FILTER_1_EVENT * 10000 + _FILTER_Q);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_Filter1_Kbd_Track, _FILTER_1_EVENT * 10000 + _FILTER_KBD_TRACK);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_Filter1FreqModLfoLevel, _FILTER_1_EVENT * 10000 + _FILTER_FREQ_MOD_LFO_LEVEL);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_Filter1FreqModEnvLevel, _FILTER_1_EVENT * 10000 + _FILTER_FREQ_MOD_ENV_LEVEL);

	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_Filter2_Freq, _FILTER_2_EVENT * 10000 + _FILTER_FREQ);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_Filter2_Oct, _FILTER_2_EVENT * 10000 + _FILTER_OCT);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_Filter2_Q, _FILTER_2_EVENT * 10000 + _FILTER_Q);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_Filter2_Kbd_Track, _FILTER_2_EVENT * 10000 + _FILTER_KBD_TRACK);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_Filter2FreqModLfoLevel, _FILTER_2_EVENT * 10000 + _FILTER_FREQ_MOD_LFO_LEVEL);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_Filter2FreqModEnvLevel, _FILTER_2_EVENT * 10000 + _FILTER_FREQ_MOD_ENV_LEVEL);

	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_AmpLevel_1, _AMP_CH1_EVENT * 10000 + _AMP_LEVEL);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_AmpPan_1, _AMP_CH1_EVENT * 10000 + _AMP_PAN);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_AmpSend_1, _AMP_CH1_EVENT * 10000 + _AMP_SEND);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_AmpPanModLevel_1, _AMP_CH1_EVENT * 10000 + _AMP_PAN_MOD_LFO_LEVEL);

	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_AmpLevel_2, _AMP_CH2_EVENT * 10000 + _AMP_LEVEL);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_AmpPan_2, _AMP_CH2_EVENT * 10000 + _AMP_PAN);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_AmpSend_2, _AMP_CH2_EVENT * 10000 + _AMP_SEND);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_AmpPanModLevel_2, _AMP_CH2_EVENT * 10000 + _AMP_PAN_MOD_LFO_LEVEL);

	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_keyboardPortamento, _KBD_1_EVENT * 10000 + _KBD_PORTAMENTO_LEVEL);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dialSensitivity_Low, _KBD_1_EVENT * 10000 + _KBD_LOW_SENSITIVITY_LEVEL);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dialSensitivity, _KBD_1_EVENT * 10000 + _KBD_SENSITIVITY_LEVEL);

	
	// Widgets types
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_Filter1_Freq, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_Filter1_Oct, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_Filter1_Q, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_Filter1_Kbd_Track, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_Filter1FreqModLfoLevel, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_Filter1FreqModEnvLevel, _CONTROL_TYPE_DIAL);

	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_Filter2_Freq, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_Filter2_Oct, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_Filter2_Q, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_Filter2_Kbd_Track, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_Filter2FreqModLfoLevel, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_Filter2FreqModEnvLevel, _CONTROL_TYPE_DIAL);

	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_AmpLevel_1, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_AmpPan_1, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_AmpSend_1, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_AmpPanModLevel_1, _CONTROL_TYPE_DIAL);

	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_AmpLevel_2, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_AmpPan_2, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_AmpSend_2, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_AmpPanModLevel_2, _CONTROL_TYPE_DIAL);

	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_keyboardPortamento, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dialSensitivity_Low, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dialSensitivity, _CONTROL_TYPE_DIAL);
}

void FiltAmpKbdTabUiHandling::update()
{
	static bool oneTimeInitialized = false;

	if (!oneTimeInitialized)
	{
		oneTimeInitialized = true;
		
		mainWindow->comboBox_Filter1_Band->blockSignals(true);
		mainWindow->comboBox_Filter1_Band->addItems(stringFilterBandsList);
		mainWindow->comboBox_Filter1_Band->blockSignals(false);
		
		mainWindow->comboBox_Filter1FreqModEnv->blockSignals(true);
		mainWindow->comboBox_Filter1FreqModEnv->addItems(MainWindow::getInstance()->stringEnvsList);
		mainWindow->comboBox_Filter1FreqModEnv->blockSignals(false);

		mainWindow->comboBox_Filter1FreqModLfo->blockSignals(true);
		mainWindow->comboBox_Filter1FreqModLfo->addItems(MainWindow::getInstance()->stringLfosList);
		mainWindow->comboBox_Filter1FreqModLfo->blockSignals(false);

		mainWindow->comboBox_Filter2_Band->blockSignals(true);
		mainWindow->comboBox_Filter2_Band->addItems(stringFilterBandsList);
		mainWindow->comboBox_Filter2_Band->blockSignals(false);

		mainWindow->comboBox_Filter2FreqModEnv->blockSignals(true);
		mainWindow->comboBox_Filter2FreqModEnv->addItems(MainWindow::getInstance()->stringEnvsList);
		mainWindow->comboBox_Filter2FreqModEnv->blockSignals(false);

		mainWindow->comboBox_Filter2FreqModLfo->blockSignals(true);
		mainWindow->comboBox_Filter2FreqModLfo->addItems(MainWindow::getInstance()->stringLfosList);
		mainWindow->comboBox_Filter2FreqModLfo->blockSignals(false);
		
		mainWindow->comboBox_AmpPanModLfo_1->blockSignals(true);
		mainWindow->comboBox_AmpPanModLfo_1->addItem("-----");
		mainWindow->comboBox_AmpPanModLfo_1->addItem("LFO 1");
		mainWindow->comboBox_AmpPanModLfo_1->addItem("LFO 2");
		mainWindow->comboBox_AmpPanModLfo_1->addItem("LFO 3");
		mainWindow->comboBox_AmpPanModLfo_1->addItem("LFO 4");
		mainWindow->comboBox_AmpPanModLfo_1->addItem("LFO 5");
		mainWindow->comboBox_AmpPanModLfo_1->blockSignals(false);
		
		mainWindow->comboBox_AmpPanModLfo_2->blockSignals(true);
		mainWindow->comboBox_AmpPanModLfo_2->addItem("-----");
		mainWindow->comboBox_AmpPanModLfo_2->addItem("LFO 1");
		mainWindow->comboBox_AmpPanModLfo_2->addItem("LFO 2");
		mainWindow->comboBox_AmpPanModLfo_2->addItem("LFO 3");
		mainWindow->comboBox_AmpPanModLfo_2->addItem("LFO 4");
		mainWindow->comboBox_AmpPanModLfo_2->addItem("LFO 5");
		mainWindow->comboBox_AmpPanModLfo_2->blockSignals(false);
		
		mainWindow->comboBox_KbdSplit->blockSignals(true);
		mainWindow->comboBox_KbdSplit->addItems(stringKeyboardSlipList);
		mainWindow->comboBox_KbdSplit->blockSignals(false);			
	}
	
	mainWindow->dial_Filter1_Freq->blockSignals(true);
	mainWindow->dial_Filter1_Freq->setValue(mod_synth_get_active_filter_1_freq());
	mainWindow->dial_Filter1_Freq->blockSignals(false);

	mainWindow->dial_Filter1_Oct->blockSignals(true);
	mainWindow->dial_Filter1_Oct->setValue(mod_synth_get_active_filter_1_oct());
	mainWindow->dial_Filter1_Oct->blockSignals(false);

	mainWindow->dial_Filter1_Q->blockSignals(true);
	mainWindow->dial_Filter1_Q->setValue(mod_synth_get_active_filter_1_q());
	mainWindow->dial_Filter1_Q->blockSignals(false);

	mainWindow->dial_Filter1_Kbd_Track->blockSignals(true);
	mainWindow->dial_Filter1_Kbd_Track->setValue(mod_synth_get_active_filter_1_kbd_track());
	mainWindow->dial_Filter1_Kbd_Track->blockSignals(false);

	mainWindow->comboBox_Filter1_Band->blockSignals(true);
	mainWindow->comboBox_Filter1_Band->setCurrentIndex(mod_synth_get_active_filter_1_band());
	mainWindow->comboBox_Filter1_Band->blockSignals(false);

	mainWindow->comboBox_Filter1FreqModLfo->blockSignals(true);
	mainWindow->comboBox_Filter1FreqModLfo->setCurrentIndex(mod_synth_get_active_filter_1_Freq_mod_lfo());
	mainWindow->comboBox_Filter1FreqModLfo->blockSignals(false);

	mainWindow->dial_Filter1FreqModLfoLevel->blockSignals(true);
	mainWindow->dial_Filter1FreqModLfoLevel->setValue(mod_synth_get_active_filter_1_Freq_mod_lfo_level());
	mainWindow->dial_Filter1FreqModLfoLevel->blockSignals(false);

	mainWindow->comboBox_Filter1FreqModEnv->blockSignals(true);
	mainWindow->comboBox_Filter1FreqModEnv->setCurrentIndex(mod_synth_get_active_filter_1_Freq_mod_env());
	mainWindow->comboBox_Filter1FreqModEnv->blockSignals(false);

	mainWindow->dial_Filter1FreqModEnvLevel->blockSignals(true);
	mainWindow->dial_Filter1FreqModEnvLevel->setValue(mod_synth_get_active_filter_1_Freq_mod_env_level());
	mainWindow->dial_Filter1FreqModEnvLevel->blockSignals(false);

	mainWindow->dial_Filter2_Freq->blockSignals(true);
	mainWindow->dial_Filter2_Freq->setValue(mod_synth_get_active_filter_2_freq());
	mainWindow->dial_Filter2_Freq->blockSignals(false);

	mainWindow->dial_Filter2_Oct->blockSignals(true);
	mainWindow->dial_Filter2_Oct->setValue(mod_synth_get_active_filter_2_oct());
	mainWindow->dial_Filter2_Oct->blockSignals(false);

	mainWindow->dial_Filter2_Q->blockSignals(true);
	mainWindow->dial_Filter2_Q->setValue(mod_synth_get_active_filter_2_q());
	mainWindow->dial_Filter2_Q->blockSignals(false);

	mainWindow->dial_Filter2_Kbd_Track->blockSignals(true);
	mainWindow->dial_Filter2_Kbd_Track->setValue(mod_synth_get_active_filter_2_kbd_track());
	mainWindow->dial_Filter2_Kbd_Track->blockSignals(false);

	mainWindow->comboBox_Filter2_Band->blockSignals(true);
	mainWindow->comboBox_Filter2_Band->setCurrentIndex(mod_synth_get_active_filter_2_band());
	mainWindow->comboBox_Filter2_Band->blockSignals(false);

//	mainWindow->checkBox_Filter2_Track_Filter_1->blockSignals(true);
//	mainWindow->checkBox_Filter2_Track_Filter_1->setChecked(mod_synth_get_active_filter_2_Trac_filter_1_state());
//	mainWindow->checkBox_Filter2_Track_Filter_1->blockSignals(false);

//	filter2FollowsFilter1 = mod_synth_get_active_filter_2_Trac_filter_1_state();

	mainWindow->comboBox_Filter2FreqModLfo->blockSignals(true);
	mainWindow->comboBox_Filter2FreqModLfo->setCurrentIndex(mod_synth_get_active_filter_2_Freq_mod_lfo());
	mainWindow->comboBox_Filter2FreqModLfo->blockSignals(false);

	mainWindow->dial_Filter2FreqModLfoLevel->blockSignals(true);
	mainWindow->dial_Filter2FreqModLfoLevel->setValue(mod_synth_get_active_filter_2_Freq_mod_lfo_level());
	mainWindow->dial_Filter2FreqModLfoLevel->blockSignals(false);

	mainWindow->comboBox_Filter2FreqModEnv->blockSignals(true);
	mainWindow->comboBox_Filter2FreqModEnv->setCurrentIndex(mod_synth_get_active_filter_2_Freq_mod_env());
	mainWindow->comboBox_Filter2FreqModEnv->blockSignals(false);

	mainWindow->dial_Filter2FreqModEnvLevel->blockSignals(true);
	mainWindow->dial_Filter2FreqModEnvLevel->setValue(mod_synth_get_active_filter_2_Freq_mod_env_level());
	mainWindow->dial_Filter2FreqModEnvLevel->blockSignals(false);
	
	mainWindow->dial_AmpLevel_1->blockSignals(true);
	mainWindow->dial_AmpLevel_1->setValue(mod_synth_get_active_ch_1_level());
	mainWindow->dial_AmpLevel_1->blockSignals(false);

	mainWindow->dial_AmpPan_1->blockSignals(true);
	mainWindow->dial_AmpPan_1->setValue(mod_synth_get_active_ch_1_pan());
	mainWindow->dial_AmpPan_1->blockSignals(false);
		
	mainWindow->dial_AmpSend_1->blockSignals(true);
	mainWindow->dial_AmpSend_1->setValue(mod_synth_get_active_ch_1_send());
	mainWindow->dial_AmpSend_1->blockSignals(false);

	mainWindow->dial_AmpLevel_2->blockSignals(true);
	mainWindow->dial_AmpLevel_2->setValue(mod_synth_get_active_ch_2_level());
	mainWindow->dial_AmpLevel_2->blockSignals(false);

	mainWindow->dial_AmpPan_2->blockSignals(true);
	mainWindow->dial_AmpPan_2->setValue(mod_synth_get_active_ch_2_pan());
	mainWindow->dial_AmpPan_2->blockSignals(false);
		
	mainWindow->dial_AmpSend_2->blockSignals(true);
	mainWindow->dial_AmpSend_2->setValue(mod_synth_get_active_ch_2_send());
	mainWindow->dial_AmpSend_2->blockSignals(false);
	
	mainWindow->comboBox_AmpPanModLfo_1->blockSignals(true);
	mainWindow->comboBox_AmpPanModLfo_1->setCurrentIndex(mod_synth_get_active_ch_1_pan_mod_lfo());
	mainWindow->comboBox_AmpPanModLfo_1->blockSignals(false);

	mainWindow->dial_AmpPanModLevel_1->blockSignals(true);
	mainWindow->dial_AmpPanModLevel_1->setValue(mod_synth_get_active_ch_1_pan_mod_lfo_level());
	mainWindow->dial_AmpPanModLevel_1->blockSignals(false);

	mainWindow->comboBox_AmpPanModLfo_2->blockSignals(true);
	mainWindow->comboBox_AmpPanModLfo_2->setCurrentIndex(mod_synth_get_active_ch_2_pan_mod_lfo());
	mainWindow->comboBox_AmpPanModLfo_2->blockSignals(false);

	mainWindow->dial_AmpPanModLevel_2->blockSignals(true);
	mainWindow->dial_AmpPanModLevel_2->setValue(mod_synth_get_active_ch_2_pan_mod_lfo_level());
	mainWindow->dial_AmpPanModLevel_2->blockSignals(false);
	
	mainWindow->dial_keyboardPortamento->blockSignals(true);
	mainWindow->dial_keyboardPortamento->setValue(mod_synth_get_active_keyboard_portamento_level());
	mainWindow->dial_keyboardPortamento->blockSignals(false);

	mainWindow->checkBox_keyboardEnablePortamento->blockSignals(true);
	mainWindow->checkBox_keyboardEnablePortamento->setChecked(mod_synth_get_active_keyboard_portamento_enabled_state());
	mainWindow->checkBox_keyboardEnablePortamento->blockSignals(false);

	mainWindow->dialSensitivity->blockSignals(true);
	mainWindow->dialSensitivity->setValue(mod_synth_get_active_keyboard_sensitivity());
	mainWindow->dialSensitivity->blockSignals(false);
	
	mainWindow->dialSensitivity_Low->blockSignals(true);
	mainWindow->dialSensitivity_Low->setValue(mod_synth_get_active_keyboard_sensitivity_low());
	mainWindow->dialSensitivity_Low->blockSignals(false);
	
	mainWindow->comboBox_KbdSplit->blockSignals(true);
	mainWindow->comboBox_KbdSplit->setCurrentIndex(mod_synth_get_active_keyboard_split_point());
	mainWindow->comboBox_KbdSplit->blockSignals(false);	

	mainWindow->radioButton_kbdPolyFifo->blockSignals(true);
	mainWindow->radioButton_kbdPolyLimit->blockSignals(true);
	mainWindow->radioButton_kbdPolyReuse->blockSignals(true);
	if (mod_synth_get_active_keyboard_poly_mode() == _KBD_POLY_MODE_FIFO) 
	{
		mainWindow->radioButton_kbdPolyFifo->setChecked(true);
		mainWindow->radioButton_kbdPolyLimit->setChecked(false);
		mainWindow->radioButton_kbdPolyReuse->setChecked(false);
	}
	else if (mod_synth_get_active_keyboard_poly_mode() == _KBD_POLY_MODE_LIMIT) 
	{
		mainWindow->radioButton_kbdPolyFifo->setChecked(false);
		mainWindow->radioButton_kbdPolyLimit->setChecked(true);
		mainWindow->radioButton_kbdPolyReuse->setChecked(false);
	}
	else if (mod_synth_get_active_keyboard_poly_mode() == _KBD_POLY_MODE_REUSE) 
	{
		mainWindow->radioButton_kbdPolyFifo->setChecked(false);
		mainWindow->radioButton_kbdPolyLimit->setChecked(false);
		mainWindow->radioButton_kbdPolyReuse->setChecked(true);
	}
	mainWindow->radioButton_kbdPolyFifo->blockSignals(false);
	mainWindow->radioButton_kbdPolyLimit->blockSignals(false);
	mainWindow->radioButton_kbdPolyReuse->blockSignals(false);
}

// SLOTS

void FiltAmpKbdTabUiHandling::filter1freqChanged(int val)
{
	mod_synth_filter_event(_FILTER_1_EVENT, _FILTER_FREQ, val);
	sprintf(mssg1, "Filter1 freq: %.1f", mod_synth_get_filter_min_center_freq() + 
			(mod_synth_get_filter_max_center_freq() - 
			mod_synth_get_filter_min_center_freq()) * val / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	if (filter2FollowsFilter1)
	{
		mod_synth_filter_event(_FILTER_2_EVENT, _FILTER_FREQ, val);
		mainWindow->dial_Filter2_Freq->blockSignals(true);
		mainWindow->dial_Filter2_Freq->setValue(val);
		mainWindow->dial_Filter2_Freq->blockSignals(false);
		// The above call resets the flag when the SIGNAL is initiated
		filter2FollowsFilter1 = true;
		mainWindow->checkBox_Filter2_Track_Filter_1->setChecked(true);
	}
}

void FiltAmpKbdTabUiHandling::filter1octChanged(int val)
{
	mod_synth_filter_event(_FILTER_1_EVENT, _FILTER_OCT, val);
	sprintf(mssg1, "Filter1 octave: %.4f", (float)val * 6.9999f / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	if (filter2FollowsFilter1)
	{
		mod_synth_filter_event(_FILTER_2_EVENT, _FILTER_OCT, val);
		mainWindow->dial_Filter2_Oct->blockSignals(true);
		mainWindow->dial_Filter2_Oct->setValue(val);
		mainWindow->dial_Filter2_Oct->blockSignals(false);
		filter2FollowsFilter1 = true;
		mainWindow->checkBox_Filter2_Track_Filter_1->setChecked(true);
	}
}

void FiltAmpKbdTabUiHandling::filter1Qchanged(int val)
{
	mod_synth_filter_event(_FILTER_1_EVENT, _FILTER_Q, val);
	sprintf(mssg1, "Filter1 Q: %.1f", mod_synth_get_filter_min_Q() + 
				(mod_synth_get_filter_max_Q() - 
				mod_synth_get_filter_min_Q()) * val / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	if (filter2FollowsFilter1)
	{
		mod_synth_filter_event(_FILTER_2_EVENT, _FILTER_Q, val);
		mainWindow->dial_Filter2_Q->blockSignals(true);
		mainWindow->dial_Filter2_Q->setValue(val);
		mainWindow->dial_Filter2_Q->blockSignals(false);
		filter2FollowsFilter1 = true;
		mainWindow->checkBox_Filter2_Track_Filter_1->setChecked(true);
	}
}

void FiltAmpKbdTabUiHandling::filter1kbdTrackChanged(int val)
{
	mod_synth_filter_event(_FILTER_1_EVENT, _FILTER_KBD_TRACK, val);
	sprintf(mssg1, "Filter1 Track Kbd: %i%c", val, '%');
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	if (filter2FollowsFilter1)
	{
		mod_synth_filter_event(_FILTER_2_EVENT, _FILTER_KBD_TRACK, val);
		mainWindow->dial_Filter2_Kbd_Track->blockSignals(true);
		mainWindow->dial_Filter2_Kbd_Track->setValue(val);
		mainWindow->dial_Filter2_Kbd_Track->blockSignals(false);
		filter2FollowsFilter1 = true;
		mainWindow->checkBox_Filter2_Track_Filter_1->setChecked(true);
	}
}

void FiltAmpKbdTabUiHandling::filter1bandChanged(int val)
{
	mod_synth_filter_event(_FILTER_1_EVENT, _FILTER_BAND, val);
	if (filter2FollowsFilter1)
	{
		mod_synth_filter_event(_FILTER_2_EVENT, _FILTER_BAND, val);
		mainWindow->comboBox_Filter2_Band->blockSignals(true);
		mainWindow->comboBox_Filter2_Band->setCurrentIndex(val);
		mainWindow->comboBox_Filter2_Band->blockSignals(false);
		filter2FollowsFilter1 = true;
		mainWindow->checkBox_Filter2_Track_Filter_1->setChecked(true);
	}
}

void FiltAmpKbdTabUiHandling::filter1FreqModLfoChanged(int val)
{
	mod_synth_filter_event(_FILTER_1_EVENT, _FILTER_FREQ_MOD_LFO, val);
}

void FiltAmpKbdTabUiHandling::filter1FreqModLevelLfoChanged(int val)
{
	mod_synth_filter_event(_FILTER_1_EVENT, _FILTER_FREQ_MOD_LFO_LEVEL, val);
	sprintf(mssg1, "Filter1 Freq Modulation LFO Level: %.2f", (float)val / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void FiltAmpKbdTabUiHandling::filter1FreqModEnvChanged(int val)
{
	mod_synth_filter_event(_FILTER_1_EVENT, _FILTER_FREQ_MOD_ENV, val);
}

void FiltAmpKbdTabUiHandling::filter1FreqModLevelEnvChanged(int val)
{
	mod_synth_filter_event(_FILTER_1_EVENT, _FILTER_FREQ_MOD_ENV_LEVEL, val);
	sprintf(mssg1, "Filter1 Freq Modulation ENV Level: %.2f", (float)val / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}


void FiltAmpKbdTabUiHandling::filter2freqChanged(int val)
{
	mod_synth_filter_event(_FILTER_2_EVENT, _FILTER_FREQ, val);
	filter2FollowsFilter1 = false;
	mainWindow->checkBox_Filter2_Track_Filter_1->setChecked(false);
	sprintf(mssg1, "Filter2 freq: %.1f", mod_synth_get_filter_min_center_freq() + 
				(mod_synth_get_filter_max_center_freq() - 
				mod_synth_get_filter_min_center_freq()) * val / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void FiltAmpKbdTabUiHandling::filter2octChanged(int val)
{
	mod_synth_filter_event(_FILTER_2_EVENT, _FILTER_OCT, val);
	filter2FollowsFilter1 = false;
	mainWindow->checkBox_Filter2_Track_Filter_1->setChecked(false);
	sprintf(mssg1, "Filter2 octave: %.4f", (float)val * 6.9999f / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void FiltAmpKbdTabUiHandling::filter2Qchanged(int val)
{
	mod_synth_filter_event(_FILTER_2_EVENT, _FILTER_Q, val);
	filter2FollowsFilter1 = false;
	mainWindow->checkBox_Filter2_Track_Filter_1->setChecked(false);
	sprintf(mssg1, "Filter2 Q: %.1f", mod_synth_get_filter_min_Q() + 
				(mod_synth_get_filter_max_Q() - 
				mod_synth_get_filter_min_Q()) * val / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void FiltAmpKbdTabUiHandling::filter2kbdTrackChanged(int val)
{
	mod_synth_filter_event(_FILTER_2_EVENT, _FILTER_KBD_TRACK, val);
	filter2FollowsFilter1 = false;
	mainWindow->checkBox_Filter2_Track_Filter_1->setChecked(false);
	sprintf(mssg1, "Filter2 TRack Kbd: %i%c", val, '%');
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void FiltAmpKbdTabUiHandling::filter2bandChanged(int val)
{
	mod_synth_filter_event(_FILTER_2_EVENT, _FILTER_BAND, val);
	filter2FollowsFilter1 = false;
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

/** This function works in GUI level only. Setting Filter1 controls activates the Trigers */
void FiltAmpKbdTabUiHandling::filter2trackFilter1Changed(bool val)
{
	filter2FollowsFilter1 = val;
	if (val)
	{
		mainWindow->dial_Filter2_Freq->setValue(mod_synth_get_active_filter_1_freq());
		mainWindow->dial_Filter2_Oct->setValue(mod_synth_get_active_filter_1_oct());
		mainWindow->dial_Filter2_Q->setValue(mod_synth_get_active_filter_1_q());
		mainWindow->dial_Filter2_Kbd_Track->setValue(mod_synth_get_active_filter_1_kbd_track());
		mainWindow->comboBox_Filter2_Band->setCurrentIndex(mod_synth_get_active_filter_1_band());
	}
}

void FiltAmpKbdTabUiHandling::filter2FreqModLfoChanged(int val)
{
	mod_synth_filter_event(_FILTER_2_EVENT, _FILTER_FREQ_MOD_LFO, val);
}

void FiltAmpKbdTabUiHandling::filter2FreqModLevelLfoChanged(int val)
{
	mod_synth_filter_event(_FILTER_2_EVENT, _FILTER_FREQ_MOD_LFO_LEVEL, val);
	sprintf(mssg1, "Filter2 Freq Modulation LFO Level: %.2f", (float)val / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void FiltAmpKbdTabUiHandling::filter2FreqModEnvChanged(int val)
{
	mod_synth_filter_event(_FILTER_2_EVENT, _FILTER_FREQ_MOD_ENV, val);
}

void FiltAmpKbdTabUiHandling::filter2FreqModLevelEnvChanged(int val)
{
	mod_synth_filter_event(_FILTER_2_EVENT, _FILTER_FREQ_MOD_ENV_LEVEL, val);
	sprintf(mssg1, "Filter2 Freq Modulation ENV Level: %.2f", (float)val / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}


void FiltAmpKbdTabUiHandling::amp1LevelChanged(int val)
{
	mod_synth_amp_event(_AMP_CH1_EVENT, _AMP_LEVEL, val);
	sprintf(mssg1, "Amp1 Level: %.2f", (float)val / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void FiltAmpKbdTabUiHandling::amp1PanChanged(int val)
{
	mod_synth_amp_event(_AMP_CH1_EVENT, _AMP_PAN, val);
	sprintf(mssg1, "Amp1 Pan: %.2f", (((float)val / 100.0f) - 0.5f) * 2.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void FiltAmpKbdTabUiHandling::amp1SendChanged(int val)
{
	mod_synth_amp_event(_AMP_CH1_EVENT, _AMP_SEND, val);
	sprintf(mssg1, "Amp1 Send: %.2f", (float)val / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void FiltAmpKbdTabUiHandling::amp1PanModLfoChanged(int val)
{
	mod_synth_amp_event(_AMP_CH1_EVENT, _AMP_PAN_MOD_LFO, val);
}

void FiltAmpKbdTabUiHandling::amp1PanModLevelLfoChanged(int val)
{
	mod_synth_amp_event(_AMP_CH1_EVENT, _AMP_PAN_MOD_LFO_LEVEL, val);
	sprintf(mssg1, "Amp1 Pan Modulation LFO Level: %.2f", (float)val / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void FiltAmpKbdTabUiHandling::amp2LevelChanged(int val)
{
	mod_synth_amp_event(_AMP_CH2_EVENT, _AMP_LEVEL, val);
	sprintf(mssg1, "Amp2 Level: %.2f", (float)val / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void FiltAmpKbdTabUiHandling::amp2PanChanged(int val)
{
	mod_synth_amp_event(_AMP_CH2_EVENT, _AMP_PAN, val);
	sprintf(mssg1, "Amp2 Pan: %.2f", (((float)val / 100.0f) - 0.5f) * 2.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void FiltAmpKbdTabUiHandling::amp2SendChanged(int val)
{
	mod_synth_amp_event(_AMP_CH2_EVENT, _AMP_SEND, val);
	sprintf(mssg1, "Amp2 Send: %.2f", (float)val / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void FiltAmpKbdTabUiHandling::amp2PanModLfoChanged(int val)
{
	mod_synth_amp_event(_AMP_CH2_EVENT, _AMP_PAN_MOD_LFO, val);
}

void FiltAmpKbdTabUiHandling::amp2PanModLevelLfoChanged(int val)
{
	mod_synth_amp_event(_AMP_CH2_EVENT, _AMP_PAN_MOD_LFO_LEVEL, val);
	sprintf(mssg1, "Amp2 Pan Modulation LFO Level: %.2f", (float)val / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void FiltAmpKbdTabUiHandling::fixedChanged(bool val)
{
	if (val)
	{
		mod_synth_amp_event(_AMP_CH1_EVENT, _AMP_FIXED_LEVELS, _AMP_FIXED_LEVELS_ENABLE);
	}
	else
	{
		mod_synth_amp_event(_AMP_CH1_EVENT, _AMP_FIXED_LEVELS, _AMP_FIXED_LEVELS_DISABLE);
	}			
}


void FiltAmpKbdTabUiHandling::kbdPortamentoLevelChanged(int val)
{
	mod_synth_keyboard_event(_KBD_1_EVENT, _KBD_PORTAMENTO_LEVEL, val);
	sprintf(mssg1, "Keyboard Portamento: %.2f", mod_synth_log_scale_100_float(0.0, mod_synth_get_portamento_max_time_sec(), 10.0, val));
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void FiltAmpKbdTabUiHandling::kbdPortamentoEnableChanged(bool val)
{
	mod_synth_keyboard_event_bool(_KBD_1_EVENT, _KBD_PORTAMENTO_ENABLE, val);
}

void FiltAmpKbdTabUiHandling::kbdSensitivityChanged(int val)
{
	mod_synth_keyboard_event(_KBD_1_EVENT, _KBD_SENSITIVITY_LEVEL, val);
	sprintf(mssg1, "Keyboard High Split Sensitivity: %.2f", (float)val / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void FiltAmpKbdTabUiHandling::kbdLowSensitivityChanged(int val)
{
	mod_synth_keyboard_event(_KBD_1_EVENT, _KBD_LOW_SENSITIVITY_LEVEL, val);
	sprintf(mssg1, "Keyboard Low SplitSensitivity: %.2f", (float)val / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

void FiltAmpKbdTabUiHandling::kbdSplitChanged(int val)
{
	mod_synth_keyboard_event(_KBD_1_EVENT, _KBD_SPLIT_POINT, val);
}

void FiltAmpKbdTabUiHandling::kbdControlsMapCliked(bool Val)
{
	mapKbdControlDialogShown = !mapKbdControlDialogShown;
	if (mapKbdControlDialogShown)
	{
		dialog_KbdControlMap->show();
		dialog_KbdControlMap->move(120, 150);
	}
	else
	{
		dialog_KbdControlMap->hide();
	}
}

void FiltAmpKbdTabUiHandling::polyFifoClicked(bool val) 
{
	mod_synth_keyboard_event_bool(_KBD_1_EVENT, _KBD_POLY_MODE_FIFO, val);
}

void FiltAmpKbdTabUiHandling::polyLimitClicked(bool val)
{
	mod_synth_keyboard_event_bool(_KBD_1_EVENT, _KBD_POLY_MODE_LIMIT, val);
}

void FiltAmpKbdTabUiHandling::polyReuseClicked(bool val)
{
	mod_synth_keyboard_event_bool(_KBD_1_EVENT, _KBD_POLY_MODE_REUSE, val);
}
