/**
*	@file		ModulatorsTab.h
*	@author		Nahum Budin
*	@date		14-Nov-2019
*	@version	1.0
*
*	@brief		Modulators (LFOs Envelope (ADSR) generators) Tab ui handling.
*/

#include "MainWindow.h"
#include "ModulatorsTab.h"
#include "libAdjHeartModSynth_2.h"

ModulatorsTabUiHandling *ModulatorsTabUiHandling::modulatorsTabUiHandling = NULL;

ModulatorsTabUiHandling::ModulatorsTabUiHandling(Ui_MainWindow *mainWind)
{
	mainWindow = mainWind;
	
	stringLfosWaveformsList.append("Sine");
	stringLfosWaveformsList.append("Square");
	stringLfosWaveformsList.append("Pulse");
	stringLfosWaveformsList.append("Triangle");
	stringLfosWaveformsList.append("Sample & Hold");
	
	adsrViewWidgetAttack = 5;
	adsrViewWidgetDecay = 10;
	adsrViewWidgetSustain = 80;
	adsrViewWidgetRelease = 10;
	
	adsrCurveMaxAttack = mod_synth_get_adsr_max_attack_time_sec();
	adsrCurveMaxDecay = mod_synth_get_adsr_max_decay_time_sec();
	adsrCurveMaxSustain = 100;  // %
	adsrCurveMaxRelease = mod_synth_get_adsr_max_release_time_sec();
	
	setAdsrViewWidgetPoints();
	
	plot = new QCustomPlot(mainWindow->widget_adsrCurvePlot);
	
	QPen pen;
	pen.setStyle(Qt::SolidLine);
	pen.setWidth(2);
	pen.setColor(QColor("#0080ff"));
	plot->addGraph();
	plot->graph(0)->setPen(pen);
	plot->addGraph();
		
	plot->xAxis->setVisible(false);
	plot->xAxis->setTickLabels(true);
	plot->yAxis->setVisible(false);
	plot->yAxis->setTickLabels(true);
		
	plotLength = _ADSR_CURVE_START_POINT + _ADSR_CURVE_SUSTAIN_SEGMENT_LENGTH +
		(adsrCurveMaxAttack + adsrCurveMaxDecay + adsrCurveMaxRelease) * _ADSR_CURVE_TIME_MULTIPLIER;

	plot->yAxis->setRange(0, _ADSR_CURVE_HEIGHT);
	plot->xAxis->setRange(0, plotLength);
	
	plot->setMinimumSize(plotLength, _ADSR_CURVE_HEIGHT);
	plot->setBackground(QColor("#d2d2d2"));	
	
	mainWindow->widget_adsrCurvePlot->hide();	
}	

ModulatorsTabUiHandling *ModulatorsTabUiHandling::getInstance() 
{
	return modulatorsTabUiHandling;
}

void ModulatorsTabUiHandling::setTrigers()
{
	connect(mainWindow->verticalSlider_ModulatorAttack_1,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(mod1AttackLevelChanged(int)));

	connect(mainWindow->verticalSlider_ModulatorDecay_1,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(mod1DecayLevelChanged(int)));

	connect(mainWindow->verticalSlider_ModulatorSustain_1,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(mod1SustainLevelChanged(int)));

	connect(mainWindow->verticalSlider_ModulatorRelease_1,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(mod1ReleaseLevelChanged(int)));

	connect(mainWindow->verticalSlider_ModulatorAttack_2,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(mod2AttackLevelChanged(int)));

	connect(mainWindow->verticalSlider_ModulatorDecay_2,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(mod2DecayLevelChanged(int)));

	connect(mainWindow->verticalSlider_ModulatorSustain_2,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(mod2SustainLevelChanged(int)));

	connect(mainWindow->verticalSlider_ModulatorRelease_2,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(mod2ReleaseLevelChanged(int)));

	connect(mainWindow->verticalSlider_ModulatorAttack_3,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(mod3AttackLevelChanged(int)));

	connect(mainWindow->verticalSlider_ModulatorDecay_3,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(mod3DecayLevelChanged(int)));

	connect(mainWindow->verticalSlider_ModulatorSustain_3,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(mod3SustainLevelChanged(int)));

	connect(mainWindow->verticalSlider_ModulatorRelease_3,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(mod3ReleaseLevelChanged(int)));
	
	connect(mainWindow->verticalSlider_ModulatorAttack_4,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(mod4AttackLevelChanged(int)));

	connect(mainWindow->verticalSlider_ModulatorDecay_4,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(mod4DecayLevelChanged(int)));

	connect(mainWindow->verticalSlider_ModulatorSustain_4,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(mod4SustainLevelChanged(int)));

	connect(mainWindow->verticalSlider_ModulatorRelease_4,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(mod4ReleaseLevelChanged(int)));
	
	connect(mainWindow->verticalSlider_ModulatorAttack_5,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(mod5AttackLevelChanged(int)));

	connect(mainWindow->verticalSlider_ModulatorDecay_5,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(mod5DecayLevelChanged(int)));

	connect(mainWindow->verticalSlider_ModulatorSustain_5,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(mod5SustainLevelChanged(int)));

	connect(mainWindow->verticalSlider_ModulatorRelease_5,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(mod5ReleaseLevelChanged(int)));
	
	
	connect(mainWindow->horizontalSlider_ModulatorLfoRate_1,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(mod1LfoRateChanged(int)));

	connect(mainWindow->horizontalSlider_ModulatorLfoSymmetry_1,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(mod1LfoSymmetryChanged(int)));

	connect(mainWindow->comboBox_ModulatorLfoWaveform_1,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(mod1LfoWaveformChanged(int)));

	connect(mainWindow->horizontalSlider_ModulatorLfoRate_2,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(mod2LfoRateChanged(int)));

	connect(mainWindow->horizontalSlider_ModulatorLfoSymmetry_2,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(mod2LfoSymmetryChanged(int)));

	connect(mainWindow->comboBox_ModulatorLfoWaveform_2,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(mod2LfoWaveformChanged(int)));

	connect(mainWindow->horizontalSlider_ModulatorLfoRate_3,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(mod3LfoRateChanged(int)));

	connect(mainWindow->horizontalSlider_ModulatorLfoSymmetry_3,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(mod3LfoSymmetryChanged(int)));

	connect(mainWindow->comboBox_ModulatorLfoWaveform_3,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(mod3LfoWaveformChanged(int)));
	
	connect(mainWindow->horizontalSlider_ModulatorLfoRate_4,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(mod4LfoRateChanged(int)));

	connect(mainWindow->horizontalSlider_ModulatorLfoSymmetry_4,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(mod4LfoSymmetryChanged(int)));

	connect(mainWindow->comboBox_ModulatorLfoWaveform_4,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(mod4LfoWaveformChanged(int)));
	
	connect(mainWindow->horizontalSlider_ModulatorLfoRate_5,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(mod5LfoRateChanged(int)));

	connect(mainWindow->horizontalSlider_ModulatorLfoSymmetry_5,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(mod5LfoSymmetryChanged(int)));

	connect(mainWindow->comboBox_ModulatorLfoWaveform_5,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(mod5LfoWaveformChanged(int)));	
}

void ModulatorsTabUiHandling::setWidgetsInfoMap()
{
	// Widgets Ids
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->horizontalSlider_ModulatorLfoSymmetry_1, _LFO_1_EVENT * 10000 + _MOD_LFO_SYMMETRY);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->horizontalSlider_ModulatorLfoRate_1, _LFO_1_EVENT * 10000 + _MOD_LFO_RATE);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->horizontalSlider_ModulatorLfoSymmetry_2, _LFO_2_EVENT * 10000 + _MOD_LFO_SYMMETRY);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->horizontalSlider_ModulatorLfoRate_2, _LFO_2_EVENT * 10000 + _MOD_LFO_RATE);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->horizontalSlider_ModulatorLfoSymmetry_3, _LFO_3_EVENT * 10000 + _MOD_LFO_SYMMETRY);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->horizontalSlider_ModulatorLfoRate_3, _LFO_3_EVENT * 10000 + _MOD_LFO_RATE);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->horizontalSlider_ModulatorLfoSymmetry_4, _LFO_4_EVENT * 10000 + _MOD_LFO_SYMMETRY);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->horizontalSlider_ModulatorLfoRate_4, _LFO_4_EVENT * 10000 + _MOD_LFO_RATE);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->horizontalSlider_ModulatorLfoSymmetry_5, _LFO_5_EVENT * 10000 + _MOD_LFO_SYMMETRY);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->horizontalSlider_ModulatorLfoRate_5, _LFO_5_EVENT * 10000 + _MOD_LFO_RATE);

	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->verticalSlider_ModulatorAttack_1, _ENV_1_EVENT * 10000 + _MOD_ADSR_ATTACK);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->verticalSlider_ModulatorDecay_1, _ENV_1_EVENT * 10000 + _MOD_ADSR_DECAY);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->verticalSlider_ModulatorSustain_1, _ENV_1_EVENT * 10000 + _MOD_ADSR_SUSTAIN);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->verticalSlider_ModulatorRelease_1, _ENV_1_EVENT * 10000 + _MOD_ADSR_RELEASE);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->verticalSlider_ModulatorAttack_2, _ENV_2_EVENT * 10000 + _MOD_ADSR_ATTACK);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->verticalSlider_ModulatorDecay_2, _ENV_2_EVENT * 10000 + _MOD_ADSR_DECAY);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->verticalSlider_ModulatorSustain_2, _ENV_2_EVENT * 10000 + _MOD_ADSR_SUSTAIN);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->verticalSlider_ModulatorRelease_2, _ENV_2_EVENT * 10000 + _MOD_ADSR_RELEASE);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->verticalSlider_ModulatorAttack_3, _ENV_3_EVENT * 10000 + _MOD_ADSR_ATTACK);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->verticalSlider_ModulatorDecay_3, _ENV_3_EVENT * 10000 + _MOD_ADSR_DECAY);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->verticalSlider_ModulatorSustain_3, _ENV_3_EVENT * 10000 + _MOD_ADSR_SUSTAIN);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->verticalSlider_ModulatorRelease_3, _ENV_3_EVENT * 10000 + _MOD_ADSR_RELEASE);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->verticalSlider_ModulatorAttack_4, _ENV_4_EVENT * 10000 + _MOD_ADSR_ATTACK);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->verticalSlider_ModulatorDecay_4, _ENV_4_EVENT * 10000 + _MOD_ADSR_DECAY);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->verticalSlider_ModulatorSustain_4, _ENV_4_EVENT * 10000 + _MOD_ADSR_SUSTAIN);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->verticalSlider_ModulatorRelease_4, _ENV_4_EVENT * 10000 + _MOD_ADSR_RELEASE);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->verticalSlider_ModulatorAttack_5, _ENV_5_EVENT * 10000 + _MOD_ADSR_ATTACK);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->verticalSlider_ModulatorDecay_5, _ENV_5_EVENT * 10000 + _MOD_ADSR_DECAY);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->verticalSlider_ModulatorSustain_5, _ENV_5_EVENT * 10000 + _MOD_ADSR_SUSTAIN);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->verticalSlider_ModulatorRelease_5, _ENV_5_EVENT * 10000 + _MOD_ADSR_RELEASE);
	

	// Widgets types
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->horizontalSlider_ModulatorLfoSymmetry_1, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->horizontalSlider_ModulatorLfoRate_1, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->horizontalSlider_ModulatorLfoSymmetry_2, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->horizontalSlider_ModulatorLfoRate_2, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->horizontalSlider_ModulatorLfoSymmetry_3, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->horizontalSlider_ModulatorLfoRate_3, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->horizontalSlider_ModulatorLfoSymmetry_4, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->horizontalSlider_ModulatorLfoRate_4, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->horizontalSlider_ModulatorLfoSymmetry_5, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->horizontalSlider_ModulatorLfoRate_5, _CONTROL_TYPE_SLIDER);

	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->verticalSlider_ModulatorAttack_1, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->verticalSlider_ModulatorDecay_1, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->verticalSlider_ModulatorSustain_1, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->verticalSlider_ModulatorRelease_1, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->verticalSlider_ModulatorAttack_2, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->verticalSlider_ModulatorDecay_2, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->verticalSlider_ModulatorSustain_2, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->verticalSlider_ModulatorRelease_2, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->verticalSlider_ModulatorAttack_3, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->verticalSlider_ModulatorDecay_3, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->verticalSlider_ModulatorSustain_3, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->verticalSlider_ModulatorRelease_3, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->verticalSlider_ModulatorAttack_4, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->verticalSlider_ModulatorDecay_4, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->verticalSlider_ModulatorSustain_4, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->verticalSlider_ModulatorRelease_4, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->verticalSlider_ModulatorAttack_5, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->verticalSlider_ModulatorDecay_5, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->verticalSlider_ModulatorSustain_5, _CONTROL_TYPE_SLIDER);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->verticalSlider_ModulatorRelease_5, _CONTROL_TYPE_SLIDER);
}

void ModulatorsTabUiHandling::update()
{
	static bool oneTimeInitialized = false;

	if (!oneTimeInitialized)
	{
		oneTimeInitialized = true;
		
		mainWindow->comboBox_ModulatorLfoWaveform_1->blockSignals(true);
		mainWindow->comboBox_ModulatorLfoWaveform_1->addItems(stringLfosWaveformsList);
		mainWindow->comboBox_ModulatorLfoWaveform_1->blockSignals(false);

		mainWindow->comboBox_ModulatorLfoWaveform_2->blockSignals(true);
		mainWindow->comboBox_ModulatorLfoWaveform_2->addItems(stringLfosWaveformsList);
		mainWindow->comboBox_ModulatorLfoWaveform_2->blockSignals(false);

		mainWindow->comboBox_ModulatorLfoWaveform_3->blockSignals(true);
		mainWindow->comboBox_ModulatorLfoWaveform_3->addItems(stringLfosWaveformsList);
		mainWindow->comboBox_ModulatorLfoWaveform_3->blockSignals(false);
		
		mainWindow->comboBox_ModulatorLfoWaveform_4->blockSignals(true);
		mainWindow->comboBox_ModulatorLfoWaveform_4->addItems(stringLfosWaveformsList);
		mainWindow->comboBox_ModulatorLfoWaveform_4->blockSignals(false);
		
		mainWindow->comboBox_ModulatorLfoWaveform_5->blockSignals(true);
		mainWindow->comboBox_ModulatorLfoWaveform_5->addItems(stringLfosWaveformsList);
		mainWindow->comboBox_ModulatorLfoWaveform_5->blockSignals(false);
	}
	
	mainWindow->verticalSlider_ModulatorAttack_1->blockSignals(true);
	mainWindow->verticalSlider_ModulatorAttack_1->setValue(mod_synth_get_active_env_mod_1_attack());
	mainWindow->verticalSlider_ModulatorAttack_1->blockSignals(false);

	mainWindow->verticalSlider_ModulatorDecay_1->blockSignals(true);
	mainWindow->verticalSlider_ModulatorDecay_1->setValue(mod_synth_get_active_env_mod_1_decay());
	mainWindow->verticalSlider_ModulatorDecay_1->blockSignals(false);

	mainWindow->verticalSlider_ModulatorSustain_1->blockSignals(true);
	mainWindow->verticalSlider_ModulatorSustain_1->setValue(mod_synth_get_active_env_mod_1_sustain());
	mainWindow->verticalSlider_ModulatorSustain_1->blockSignals(false);

	mainWindow->verticalSlider_ModulatorRelease_1->blockSignals(true);
	mainWindow->verticalSlider_ModulatorRelease_1->setValue(mod_synth_get_active_env_mod_1_release());
	mainWindow->verticalSlider_ModulatorRelease_1->blockSignals(false);
											   
	mainWindow->verticalSlider_ModulatorAttack_2->blockSignals(true);
	mainWindow->verticalSlider_ModulatorAttack_2->setValue(mod_synth_get_active_env_mod_2_attack());
	mainWindow->verticalSlider_ModulatorAttack_2->blockSignals(false);

	mainWindow->verticalSlider_ModulatorDecay_2->blockSignals(true);
	mainWindow->verticalSlider_ModulatorDecay_2->setValue(mod_synth_get_active_env_mod_2_decay());
	mainWindow->verticalSlider_ModulatorDecay_2->blockSignals(false);

	mainWindow->verticalSlider_ModulatorSustain_2->blockSignals(true);
	mainWindow->verticalSlider_ModulatorSustain_2->setValue(mod_synth_get_active_env_mod_2_sustain());
	mainWindow->verticalSlider_ModulatorSustain_2->blockSignals(false);

	mainWindow->verticalSlider_ModulatorRelease_2->blockSignals(true);
	mainWindow->verticalSlider_ModulatorRelease_2->setValue(mod_synth_get_active_env_mod_2_release());
	mainWindow->verticalSlider_ModulatorRelease_2->blockSignals(false);
											   
	mainWindow->verticalSlider_ModulatorAttack_3->blockSignals(true);
	mainWindow->verticalSlider_ModulatorAttack_3->setValue(mod_synth_get_active_env_mod_3_attack());
	mainWindow->verticalSlider_ModulatorAttack_3->blockSignals(false);

	mainWindow->verticalSlider_ModulatorDecay_3->blockSignals(true);
	mainWindow->verticalSlider_ModulatorDecay_3->setValue(mod_synth_get_active_env_mod_3_decay());
	mainWindow->verticalSlider_ModulatorDecay_3->blockSignals(false);

	mainWindow->verticalSlider_ModulatorSustain_3->blockSignals(true);
	mainWindow->verticalSlider_ModulatorSustain_3->setValue(mod_synth_get_active_env_mod_3_sustain());
	mainWindow->verticalSlider_ModulatorSustain_3->blockSignals(false);

	mainWindow->verticalSlider_ModulatorRelease_3->blockSignals(true);
	mainWindow->verticalSlider_ModulatorRelease_3->setValue(mod_synth_get_active_env_mod_3_release());
	mainWindow->verticalSlider_ModulatorRelease_3->blockSignals(false);
	
	mainWindow->verticalSlider_ModulatorAttack_4->blockSignals(true);
	mainWindow->verticalSlider_ModulatorAttack_4->setValue(mod_synth_get_active_env_mod_4_attack());
	mainWindow->verticalSlider_ModulatorAttack_4->blockSignals(false);

	mainWindow->verticalSlider_ModulatorDecay_4->blockSignals(true);
	mainWindow->verticalSlider_ModulatorDecay_4->setValue(mod_synth_get_active_env_mod_4_decay());
	mainWindow->verticalSlider_ModulatorDecay_4->blockSignals(false);

	mainWindow->verticalSlider_ModulatorSustain_4->blockSignals(true);
	mainWindow->verticalSlider_ModulatorSustain_4->setValue(mod_synth_get_active_env_mod_4_sustain());
	mainWindow->verticalSlider_ModulatorSustain_4->blockSignals(false);

	mainWindow->verticalSlider_ModulatorRelease_4->blockSignals(true);
	mainWindow->verticalSlider_ModulatorRelease_4->setValue(mod_synth_get_active_env_mod_4_release());
	mainWindow->verticalSlider_ModulatorRelease_4->blockSignals(false);
	
	mainWindow->verticalSlider_ModulatorAttack_5->blockSignals(true);
	mainWindow->verticalSlider_ModulatorAttack_5->setValue(mod_synth_get_active_env_mod_5_attack());
	mainWindow->verticalSlider_ModulatorAttack_5->blockSignals(false);

	mainWindow->verticalSlider_ModulatorDecay_5->blockSignals(true);
	mainWindow->verticalSlider_ModulatorDecay_5->setValue(mod_synth_get_active_env_mod_5_decay());
	mainWindow->verticalSlider_ModulatorDecay_5->blockSignals(false);

	mainWindow->verticalSlider_ModulatorSustain_5->blockSignals(true);
	mainWindow->verticalSlider_ModulatorSustain_5->setValue(mod_synth_get_active_env_mod_5_sustain());
	mainWindow->verticalSlider_ModulatorSustain_5->blockSignals(false);

	mainWindow->verticalSlider_ModulatorRelease_5->blockSignals(true);
	mainWindow->verticalSlider_ModulatorRelease_5->setValue(mod_synth_get_active_env_mod_5_release());
	mainWindow->verticalSlider_ModulatorRelease_5->blockSignals(false);
	
	
	mainWindow->comboBox_ModulatorLfoWaveform_1->blockSignals(true);
	mainWindow->comboBox_ModulatorLfoWaveform_1->setCurrentIndex(mod_synth_get_active_lfo_mod_1_waveform());
	mainWindow->comboBox_ModulatorLfoWaveform_1->blockSignals(false);

	mainWindow->horizontalSlider_ModulatorLfoSymmetry_1->blockSignals(true);
	mainWindow->horizontalSlider_ModulatorLfoSymmetry_1->setValue(mod_synth_get_active_lfo_mod_1_symmetry());
	mainWindow->horizontalSlider_ModulatorLfoSymmetry_1->blockSignals(false);

	mainWindow->horizontalSlider_ModulatorLfoRate_1->blockSignals(true);
	mainWindow->horizontalSlider_ModulatorLfoRate_1->setValue(mod_synth_get_active_lfo_mod_1_rate());
	mainWindow->horizontalSlider_ModulatorLfoRate_1->blockSignals(false);

	mainWindow->comboBox_ModulatorLfoWaveform_2->blockSignals(true);
	mainWindow->comboBox_ModulatorLfoWaveform_2->setCurrentIndex(mod_synth_get_active_lfo_mod_2_waveform());
	mainWindow->comboBox_ModulatorLfoWaveform_2->blockSignals(false);

	mainWindow->horizontalSlider_ModulatorLfoSymmetry_2->blockSignals(true);
	mainWindow->horizontalSlider_ModulatorLfoSymmetry_2->setValue(mod_synth_get_active_lfo_mod_2_symmetry());
	mainWindow->horizontalSlider_ModulatorLfoSymmetry_2->blockSignals(false);

	mainWindow->horizontalSlider_ModulatorLfoRate_2->blockSignals(true);
	mainWindow->horizontalSlider_ModulatorLfoRate_2->setValue(mod_synth_get_active_lfo_mod_2_rate());
	mainWindow->horizontalSlider_ModulatorLfoRate_2->blockSignals(false);

	mainWindow->comboBox_ModulatorLfoWaveform_3->blockSignals(true);
	mainWindow->comboBox_ModulatorLfoWaveform_3->setCurrentIndex(mod_synth_get_active_lfo_mod_3_waveform());
	mainWindow->comboBox_ModulatorLfoWaveform_3->blockSignals(false);

	mainWindow->horizontalSlider_ModulatorLfoSymmetry_3->blockSignals(true);
	mainWindow->horizontalSlider_ModulatorLfoSymmetry_3->setValue(mod_synth_get_active_lfo_mod_3_symmetry());
	mainWindow->horizontalSlider_ModulatorLfoSymmetry_3->blockSignals(false);

	mainWindow->horizontalSlider_ModulatorLfoRate_3->blockSignals(true);
	mainWindow->horizontalSlider_ModulatorLfoRate_3->setValue(mod_synth_get_active_lfo_mod_3_rate());
	mainWindow->horizontalSlider_ModulatorLfoRate_3->blockSignals(false);
	
	mainWindow->comboBox_ModulatorLfoWaveform_4->blockSignals(true);
	mainWindow->comboBox_ModulatorLfoWaveform_4->setCurrentIndex(mod_synth_get_active_lfo_mod_4_waveform());
	mainWindow->comboBox_ModulatorLfoWaveform_4->blockSignals(false);

	mainWindow->horizontalSlider_ModulatorLfoSymmetry_4->blockSignals(true);
	mainWindow->horizontalSlider_ModulatorLfoSymmetry_4->setValue(mod_synth_get_active_lfo_mod_4_symmetry());
	mainWindow->horizontalSlider_ModulatorLfoSymmetry_4->blockSignals(false);

	mainWindow->horizontalSlider_ModulatorLfoRate_4->blockSignals(true);
	mainWindow->horizontalSlider_ModulatorLfoRate_4->setValue(mod_synth_get_active_lfo_mod_4_rate());
	mainWindow->horizontalSlider_ModulatorLfoRate_4->blockSignals(false);
	
	mainWindow->comboBox_ModulatorLfoWaveform_5->blockSignals(true);
	mainWindow->comboBox_ModulatorLfoWaveform_5->setCurrentIndex(mod_synth_get_active_lfo_mod_5_waveform());
	mainWindow->comboBox_ModulatorLfoWaveform_5->blockSignals(false);

	mainWindow->horizontalSlider_ModulatorLfoSymmetry_5->blockSignals(true);
	mainWindow->horizontalSlider_ModulatorLfoSymmetry_5->setValue(mod_synth_get_active_lfo_mod_5_symmetry());
	mainWindow->horizontalSlider_ModulatorLfoSymmetry_5->blockSignals(false);
													 
	mainWindow->horizontalSlider_ModulatorLfoRate_5->blockSignals(true);
	mainWindow->horizontalSlider_ModulatorLfoRate_5->setValue(mod_synth_get_active_lfo_mod_5_rate());
	mainWindow->horizontalSlider_ModulatorLfoRate_5->blockSignals(false);	
}

// SLOTS

void ModulatorsTabUiHandling::mod1AttackLevelChanged(int val)
{
	//	mod1Params.attckLevel = val;
	mod_synth_modulator_event(_ENV_1_EVENT, _MOD_ADSR_ATTACK, val);
	sprintf(mssg1, "ADSR1 Attack: %.2f", mod_synth_log_scale_100_float(0.0, mod_synth_get_adsr_max_attack_time_sec(), 10.0, val));
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	lastModifiedAdsr = _ENV_1;
	refreshAdsrCurveView();
}

void ModulatorsTabUiHandling::mod1DecayLevelChanged(int val)
{
	//	mod1Params.decayLevel = val;
	mod_synth_modulator_event(_ENV_1_EVENT, _MOD_ADSR_DECAY, val);
	sprintf(mssg1, "ADSR1 Decay: %.2f", mod_synth_log_scale_100_float(0.0, mod_synth_get_adsr_max_decay_time_sec(), 10.0, val));
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	lastModifiedAdsr = _ENV_1;
	refreshAdsrCurveView();
}

void ModulatorsTabUiHandling::mod1ReleaseLevelChanged(int val)
{
	//	mod1Params.releaseLevel = val;
	mod_synth_modulator_event(_ENV_1_EVENT, _MOD_ADSR_RELEASE, val);
	sprintf(mssg1, "ADSR1 Release: %.2f", mod_synth_log_scale_100_float(0.0, mod_synth_get_adsr_max_release_time_sec(), 10.0, val));
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	lastModifiedAdsr = _ENV_1;
	refreshAdsrCurveView();
}

void ModulatorsTabUiHandling::mod1SustainLevelChanged(int val)
{
	//	mod1Params.sustainLevel = val;
	mod_synth_modulator_event(_ENV_1_EVENT, _MOD_ADSR_SUSTAIN, val);
	sprintf(mssg1, "ADSR1 Sustain: %i%c", val, '%');
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	lastModifiedAdsr = _ENV_1;
	refreshAdsrCurveView(); 
}

void ModulatorsTabUiHandling::mod2AttackLevelChanged(int val)
{
	//	mod1Params.attckLevel = val;
	mod_synth_modulator_event(_ENV_2_EVENT, _MOD_ADSR_ATTACK, val);
	sprintf(mssg1, "ADSR2 Attack: %.2f", mod_synth_log_scale_100_float(0.0, mod_synth_get_adsr_max_attack_time_sec(), 10.0, val));
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	lastModifiedAdsr = _ENV_2;
	refreshAdsrCurveView();
}

void ModulatorsTabUiHandling::mod2DecayLevelChanged(int val)
{
	//	mod1Params.decayLevel = val;
	mod_synth_modulator_event(_ENV_2_EVENT, _MOD_ADSR_DECAY, val);
	sprintf(mssg1, "ADSR2 Decay: %.2f", mod_synth_log_scale_100_float(0.0, mod_synth_get_adsr_max_decay_time_sec(), 10.0, val));
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	lastModifiedAdsr = _ENV_2;
	refreshAdsrCurveView();
}

void ModulatorsTabUiHandling::mod2ReleaseLevelChanged(int val)
{
	//	mod1Params.releaseLevel = val;
	mod_synth_modulator_event(_ENV_2_EVENT, _MOD_ADSR_RELEASE, val);
	sprintf(mssg1, "ADSR2 Release: %.2f", mod_synth_log_scale_100_float(0.0, mod_synth_get_adsr_max_release_time_sec(), 10.0, val));
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	lastModifiedAdsr = _ENV_2;
	refreshAdsrCurveView();
}

void ModulatorsTabUiHandling::mod2SustainLevelChanged(int val)
{
	//	mod1Params.sustainLevel = val;
	mod_synth_modulator_event(_ENV_2_EVENT, _MOD_ADSR_SUSTAIN, val);
	sprintf(mssg1, "ADSR2 Sustain: %i%c", val, '%');
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	lastModifiedAdsr = _ENV_2;
	refreshAdsrCurveView();
}

void ModulatorsTabUiHandling::mod3AttackLevelChanged(int val)
{
	//	mod1Params.attckLevel = val;
	mod_synth_modulator_event(_ENV_3_EVENT, _MOD_ADSR_ATTACK, val);
	sprintf(mssg1, "ADSR3 Attack: %.2f", mod_synth_log_scale_100_float(0.0, mod_synth_get_adsr_max_attack_time_sec(), 10.0, val));
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	lastModifiedAdsr = _ENV_3;
	refreshAdsrCurveView();
}

void ModulatorsTabUiHandling::mod3DecayLevelChanged(int val)
{
	//	mod1Params.decayLevel = val;
	mod_synth_modulator_event(_ENV_3_EVENT, _MOD_ADSR_DECAY, val);
	sprintf(mssg1, "ADSR3 Decay: %.2f", mod_synth_log_scale_100_float(0.0, mod_synth_get_adsr_max_decay_time_sec(), 10.0, val));
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	lastModifiedAdsr = _ENV_3;
	refreshAdsrCurveView();
}

void ModulatorsTabUiHandling::mod3ReleaseLevelChanged(int val)
{
	//	mod1Params.releaseLevel = val;
	mod_synth_modulator_event(_ENV_3_EVENT, _MOD_ADSR_RELEASE, val);
	sprintf(mssg1, "ADSR3 Release: %.2f", mod_synth_log_scale_100_float(0.0, mod_synth_get_adsr_max_release_time_sec(), 10.0, val));
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	lastModifiedAdsr = _ENV_3;
	refreshAdsrCurveView();
}

void ModulatorsTabUiHandling::mod3SustainLevelChanged(int val)
{
	//	mod1Params.sustainLevel = val;
	mod_synth_modulator_event(_ENV_3_EVENT, _MOD_ADSR_SUSTAIN, val);
	sprintf(mssg1, "ADSR3 Sustain: %i%c", val, '%');
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	lastModifiedAdsr = _ENV_3;
	refreshAdsrCurveView();
}

void ModulatorsTabUiHandling::mod4AttackLevelChanged(int val)
{
	//	mod1Params.attckLevel = val;
	mod_synth_modulator_event(_ENV_4_EVENT, _MOD_ADSR_ATTACK, val);
	sprintf(mssg1, "ADSR4 Attack: %.2f", mod_synth_log_scale_100_float(0.0, mod_synth_get_adsr_max_attack_time_sec(), 10.0, val));
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	lastModifiedAdsr = _ENV_4;
	refreshAdsrCurveView();
}

void ModulatorsTabUiHandling::mod4DecayLevelChanged(int val)
{
	//	mod1Params.decayLevel = val;
	mod_synth_modulator_event(_ENV_4_EVENT, _MOD_ADSR_DECAY, val);
	sprintf(mssg1, "ADSR4 Decay: %.2f", mod_synth_log_scale_100_float(0.0, mod_synth_get_adsr_max_decay_time_sec(), 10.0, val));
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	lastModifiedAdsr = _ENV_4;
	refreshAdsrCurveView();
}

void ModulatorsTabUiHandling::mod4ReleaseLevelChanged(int val)
{
	//	mod1Params.releaseLevel = val;
	mod_synth_modulator_event(_ENV_4_EVENT, _MOD_ADSR_RELEASE, val);
	sprintf(mssg1, "ADSR4 Release: %.2f", mod_synth_log_scale_100_float(0.0, mod_synth_get_adsr_max_release_time_sec(), 10.0, val));
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	lastModifiedAdsr = _ENV_4;
	refreshAdsrCurveView();
}

void ModulatorsTabUiHandling::mod4SustainLevelChanged(int val)
{
	//	mod1Params.sustainLevel = val;
	mod_synth_modulator_event(_ENV_4_EVENT, _MOD_ADSR_SUSTAIN, val);
	sprintf(mssg1, "ADSR4 Sustain: %i%c", val, '%');
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	lastModifiedAdsr = _ENV_4;
	refreshAdsrCurveView();
}

void ModulatorsTabUiHandling::mod5AttackLevelChanged(int val)
{
	//	mod1Params.attckLevel = val;
	mod_synth_modulator_event(_ENV_5_EVENT, _MOD_ADSR_ATTACK, val);
	sprintf(mssg1, "ADSR5 Attack: %.2f", mod_synth_log_scale_100_float(0.0, mod_synth_get_adsr_max_attack_time_sec(), 10.0, val));
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	lastModifiedAdsr = _ENV_5;
	refreshAdsrCurveView();
}

void ModulatorsTabUiHandling::mod5DecayLevelChanged(int val)
{
	//	mod1Params.decayLevel = val;
	mod_synth_modulator_event(_ENV_5_EVENT, _MOD_ADSR_DECAY, val);
	sprintf(mssg1, "ADSR5 Decay: %.2f", mod_synth_log_scale_100_float(0.0, mod_synth_get_adsr_max_decay_time_sec(), 10.0, val));
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	lastModifiedAdsr = _ENV_5;
	refreshAdsrCurveView();
}

void ModulatorsTabUiHandling::mod5ReleaseLevelChanged(int val)
{
	//	mod1Params.releaseLevel = val;
	mod_synth_modulator_event(_ENV_5_EVENT, _MOD_ADSR_RELEASE, val);
	sprintf(mssg1, "ADSR5 Release: %.2f", mod_synth_log_scale_100_float(0.0, mod_synth_get_adsr_max_release_time_sec(), 10.0, val));
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	lastModifiedAdsr = _ENV_5;
	refreshAdsrCurveView();
}

void ModulatorsTabUiHandling::mod5SustainLevelChanged(int val)
{
	//	mod1Params.sustainLevel = val;
	mod_synth_modulator_event(_ENV_5_EVENT, _MOD_ADSR_SUSTAIN, val);
	sprintf(mssg1, "ADSR5 Sustain: %i%c", val, '%');
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	lastModifiedAdsr = _ENV_5;
	refreshAdsrCurveView();
}

void ModulatorsTabUiHandling::mod1LfoWaveformChanged(int val)
{
	//	mod1Params.lfoWaveform = val;
	mod_synth_modulator_event(_LFO_1_EVENT, _MOD_LFO_WAVEFORM, val);
}

void ModulatorsTabUiHandling::mod1LfoSymmetryChanged(int val)
{
	//	mod1Params.lfoSymmetry = val;
	mod_synth_modulator_event(_LFO_1_EVENT, _MOD_LFO_SYMMETRY, val);
	sprintf(mssg1, "LFO1 Symmetry: %i%c", val, '%');
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	mainWindow->widget_adsrCurvePlot->hide();
}

void ModulatorsTabUiHandling::mod1LfoRateChanged(int val)
{
	//	mod1Params.lfoRate = val;
	mod_synth_modulator_event(_LFO_1_EVENT, _MOD_LFO_RATE, val);
	sprintf(mssg1, "LFO1 Rate: %.2f", mod_synth_log_scale_100_float(mod_synth_get_lfo_min_frequency(), mod_synth_get_lfo_max_frequency(), 10.0, val));
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	mainWindow->widget_adsrCurvePlot->hide();
}

void ModulatorsTabUiHandling::mod2LfoWaveformChanged(int val)
{
	//	mod1Params.lfoWaveform = val;
	mod_synth_modulator_event(_LFO_2_EVENT, _MOD_LFO_WAVEFORM, val);
	mainWindow->widget_adsrCurvePlot->hide();
}

void ModulatorsTabUiHandling::mod2LfoSymmetryChanged(int val)
{
	//	mod1Params.lfoSymmetry = val;
	mod_synth_modulator_event(_LFO_2_EVENT, _MOD_LFO_SYMMETRY, val);
	sprintf(mssg1, "LFO2 Symmetry: %i%c", val, '%');
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	mainWindow->widget_adsrCurvePlot->hide();
}

void ModulatorsTabUiHandling::mod2LfoRateChanged(int val)
{
	//	mod1Params.lfoRate = val;
	mod_synth_modulator_event(_LFO_2_EVENT, _MOD_LFO_RATE, val);
	sprintf(mssg1, "LFO2 Rate: %.2f", mod_synth_log_scale_100_float(mod_synth_get_lfo_min_frequency(), mod_synth_get_lfo_max_frequency(), 10.0, val));
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	mainWindow->widget_adsrCurvePlot->hide();
}

void ModulatorsTabUiHandling::mod3LfoWaveformChanged(int val)
{
	//	mod1Params.lfoWaveform = val;
	mod_synth_modulator_event(_LFO_3_EVENT, _MOD_LFO_WAVEFORM, val);
	mainWindow->widget_adsrCurvePlot->hide();
}

void ModulatorsTabUiHandling::mod3LfoSymmetryChanged(int val)
{
	//	mod1Params.lfoSymmetry = val;
	mod_synth_modulator_event(_LFO_3_EVENT, _MOD_LFO_SYMMETRY, val);
	sprintf(mssg1, "LFO3 Symmetry: %i%c", val, '%');
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	mainWindow->widget_adsrCurvePlot->hide();
}

void ModulatorsTabUiHandling::mod3LfoRateChanged(int val)
{
	//	mod1Params.lfoRate = val;
	mod_synth_modulator_event(_LFO_3_EVENT, _MOD_LFO_RATE, val);
	sprintf(mssg1, "LFO3 Rate: %.2f", mod_synth_log_scale_100_float(mod_synth_get_lfo_min_frequency(), mod_synth_get_lfo_max_frequency(), 10.0, val));
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	mainWindow->widget_adsrCurvePlot->hide();
}

void ModulatorsTabUiHandling::mod4LfoWaveformChanged(int val)
{
	//	mod1Params.lfoWaveform = val;
	mod_synth_modulator_event(_LFO_4_EVENT, _MOD_LFO_WAVEFORM, val);
	mainWindow->widget_adsrCurvePlot->hide();
}

void ModulatorsTabUiHandling::mod4LfoSymmetryChanged(int val)
{
	//	mod1Params.lfoSymmetry = val;
	mod_synth_modulator_event(_LFO_4_EVENT, _MOD_LFO_SYMMETRY, val);
	sprintf(mssg1, "LFO4 Symmetry: %i%c", val, '%');
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	mainWindow->widget_adsrCurvePlot->hide();
}

void ModulatorsTabUiHandling::mod4LfoRateChanged(int val)
{
	//	mod1Params.lfoRate = val;
	mod_synth_modulator_event(_LFO_4_EVENT, _MOD_LFO_RATE, val);
	sprintf(mssg1, "LFO4 Rate: %.2f", mod_synth_log_scale_100_float(mod_synth_get_lfo_min_frequency(), mod_synth_get_lfo_max_frequency(), 10.0, val));
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	mainWindow->widget_adsrCurvePlot->hide();
}

void ModulatorsTabUiHandling::mod5LfoWaveformChanged(int val)
{
	//	mod1Params.lfoWaveform = val;
	mod_synth_modulator_event(_LFO_5_EVENT, _MOD_LFO_WAVEFORM, val);
	mainWindow->widget_adsrCurvePlot->hide();
}

void ModulatorsTabUiHandling::mod5LfoSymmetryChanged(int val)
{
	//	mod1Params.lfoSymmetry = val;
	mod_synth_modulator_event(_LFO_5_EVENT, _MOD_LFO_SYMMETRY, val);
	sprintf(mssg1, "LFO5 Symmetry: %i%c", val, '%');
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	mainWindow->widget_adsrCurvePlot->hide();
}

void ModulatorsTabUiHandling::mod5LfoRateChanged(int val)
{
	//	mod1Params.lfoRate = val;
	mod_synth_modulator_event(_LFO_5_EVENT, _MOD_LFO_RATE, val);
	sprintf(mssg1, "LFO5 Rate: %.2f", mod_synth_log_scale_100_float(mod_synth_get_lfo_min_frequency(), mod_synth_get_lfo_max_frequency(), 10.0, val));
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
	mainWindow->widget_adsrCurvePlot->hide();
}

void ModulatorsTabUiHandling::setAdsrViewWidgetPoints()
{	
	const int maxParamValue = 100;
	
	switch (lastModifiedAdsr)
	{
		case _ENV_1:
			adsrViewWidgetAttack = mod_synth_get_active_env_mod_1_attack();
			adsrViewWidgetDecay = mod_synth_get_active_env_mod_1_decay();
			adsrViewWidgetSustain = mod_synth_get_active_env_mod_1_sustain();
			adsrViewWidgetRelease = mod_synth_get_active_env_mod_1_release();
			mainWindow->widget_adsrCurvePlot->move(20, 305);
			break;
			
		case _ENV_2:
			adsrViewWidgetAttack = mod_synth_get_active_env_mod_2_attack();
			adsrViewWidgetDecay = mod_synth_get_active_env_mod_2_decay();
			adsrViewWidgetSustain = mod_synth_get_active_env_mod_2_sustain();
			adsrViewWidgetRelease = mod_synth_get_active_env_mod_2_release();
		mainWindow->widget_adsrCurvePlot->move(220, 305);
			break;
			
		case _ENV_3:
			adsrViewWidgetAttack = mod_synth_get_active_env_mod_3_attack();
			adsrViewWidgetDecay = mod_synth_get_active_env_mod_3_decay();
			adsrViewWidgetSustain = mod_synth_get_active_env_mod_3_sustain();
			adsrViewWidgetRelease = mod_synth_get_active_env_mod_3_release();
		mainWindow->widget_adsrCurvePlot->move(420, 305);
			break;
			
		case _ENV_4:
			adsrViewWidgetAttack = mod_synth_get_active_env_mod_4_attack();
			adsrViewWidgetDecay = mod_synth_get_active_env_mod_4_decay();
			adsrViewWidgetSustain = mod_synth_get_active_env_mod_4_sustain();
			adsrViewWidgetRelease = mod_synth_get_active_env_mod_4_release();
		mainWindow->widget_adsrCurvePlot->move(620, 305);
			break;
			
		case _ENV_5:
			adsrViewWidgetAttack = mod_synth_get_active_env_mod_5_attack();
			adsrViewWidgetDecay = mod_synth_get_active_env_mod_5_decay();
			adsrViewWidgetSustain = mod_synth_get_active_env_mod_5_sustain();
			adsrViewWidgetRelease = mod_synth_get_active_env_mod_5_release();
		mainWindow->widget_adsrCurvePlot->move(820, 305);
			break;
			
		default:
			return;
	}
	
	adsrViewWidgetAttack = mod_synth_log_scale_100_int(0, maxParamValue, 10, adsrViewWidgetAttack);
	adsrViewWidgetDecay = mod_synth_log_scale_100_int(0, maxParamValue, 10, adsrViewWidgetDecay);	
	adsrViewWidgetRelease = mod_synth_log_scale_100_int(0, maxParamValue, 10, adsrViewWidgetRelease);	
	
	adsrCurveAttackEndPoint = 
		_ADSR_CURVE_START_POINT + 1 + 
		((adsrViewWidgetAttack * adsrCurveMaxAttack * _ADSR_CURVE_TIME_MULTIPLIER) / 
		maxParamValue);
	
	adsrCurveDecayEndPoint = 
		adsrCurveAttackEndPoint + 1 +
		((adsrViewWidgetDecay * adsrCurveMaxDecay * _ADSR_CURVE_TIME_MULTIPLIER) / 
		maxParamValue);
	
	adsrCurveSustainEndPoint = 
		adsrCurveDecayEndPoint + 1 + 
		_ADSR_CURVE_SUSTAIN_SEGMENT_LENGTH;
	
	adsrCurveReleaseEndPoint = 
		adsrCurveSustainEndPoint + 1 + 
		((adsrViewWidgetRelease * adsrCurveMaxRelease *
		_ADSR_CURVE_TIME_MULTIPLIER)  / 
		maxParamValue); 
}

void ModulatorsTabUiHandling::refreshAdsrCurveView()
{
	setAdsrViewWidgetPoints();
	
	if (plot != NULL)
	{
		QVector<double> x(8), y(8);
		
		x[0] = 0;
		y[0] = 0;
		
		x[1] = _ADSR_CURVE_START_POINT;
		y[1] = 0;
		
		x[2] = adsrCurveAttackEndPoint;
		y[2] = _ADSR_CURVE_HEIGHT;
		
		x[3] = adsrCurveDecayEndPoint;
		y[3] = adsrViewWidgetSustain;
		
		x[4] = adsrCurveSustainEndPoint;
		y[4] = adsrViewWidgetSustain;
		
		x[5] = adsrCurveReleaseEndPoint;
		y[5] = 0;
		
		x[6] = plotLength;
		y[6] = 0;
			
		plot->graph(0)->setData(x, y);
		plot->xAxis->setRange(0, plotLength);

		QPen pen;
		pen.setStyle(Qt::SolidLine);
		pen.setWidth(1);
		pen.setColor(QColor("#FFE018"));
		plot->addGraph();
		plot->graph(0)->setPen(pen);
		plot->addGraph();

		plot->setBackground(QBrush(QColor("#606060")));
		
		plot->replot();
		
		mainWindow->widget_adsrCurvePlot->show();
		
		adsrViewGadgetTimer = 0;
	}	
}

/* Called by main window GUI update timer */
void ModulatorsTabUiHandling::timerUpdate()
{
	adsrViewGadgetTimer++;
	if (adsrViewGadgetTimer >= _ADSR_CURVE_VIEW_WIDGET_SHOW_TIME_SEC * 1000 / _UPDATE_TIMER_MS)
	{
		adsrViewGadgetTimer = 0;
		mainWindow->widget_adsrCurvePlot->hide();
	}
}
