/**
* @file		Dialog_KbdControlMap.h
*	@author		Nahum Budin
*	@date		23-May-2020
*	@version	1.0
*
*	@brief		Used for setting a map between an ext. MIDI keyboard
*				controls (knobs, slider....) and ModSynth controls.
*
*/

#include <QDialog>
#include <QFileDialog>

#include "libAdjHeartModSynth_2.h"

#include "Dialog_KbdControlMap.h"
#include "ui_Dialog_KbdControlMap.h"

Dialog_KbdControlMap *Dialog_KbdControlMap::dialog_KbdControlMapInstance = NULL;

void updateMidiControlSequencesDataWrapper(int ch, int contNum, int val)
{
	Dialog_KbdControlMap::getInstance()->updateMidiControlSequencesData(ch, contNum, val);
}

void updateSynthControlsDataWrapper(int module, int contId, int val)
{
	Dialog_KbdControlMap::getInstance()->updateSynthControlsData(module, contId, val);
}

Dialog_KbdControlMap::Dialog_KbdControlMap(QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::Dialog_KbdControlMap)
{
	ui->setupUi(this);
	dialog_KbdControlMapInstance = this;
	
	register_update_midi_control_sequnces_data_callback(&updateMidiControlSequencesDataWrapper);
	register_update_synth_controls_data_callback(&updateSynthControlsDataWrapper);
	
	connect(ui->pushButton_kbdControlSequncesTrain,
		SIGNAL(clicked(bool)),
		this,
		SLOT(trainPushButtonPressed(bool)));
	
	connect(ui->pushButton_kbdControlSequncesMap,
		SIGNAL(clicked(bool)),
		this,
		SLOT(mapPushButtonPressed(bool)));
	
	connect(ui->pushButton_kbdControlFileOpen,
		SIGNAL(clicked(bool)),
		this,
		SLOT(openPushButtonPressed(bool)));
	
	connect(ui->pushButton_kbdControlFileSave,
		SIGNAL(clicked(bool)),
		this,
		SLOT(savePushButtonPressed(bool)));

	connect(ui->checkBox_synthControlMap_ignoreChannel,
			SIGNAL(stateChanged(int)),
			this,
			SLOT(ignoreChannelChanged(int)));
	
}

Dialog_KbdControlMap *Dialog_KbdControlMap::getInstance()
{
	return dialog_KbdControlMapInstance;
}

Dialog_KbdControlMap::~Dialog_KbdControlMap()
{

}

void Dialog_KbdControlMap::closeEvent(QCloseEvent *event)
{

}

void Dialog_KbdControlMap::updateMappingDisplay()
{
	ui->textEdit_midiControlSequenceData_ch->setText(midiControlSequenceChannelStr);
	ui->textEdit_midiControlSequenceData_controlNum->setText(midiControlSequenceControlNumStr);
	ui->textEdit_midiControlSequenceData_val->setText(midiControlSequenceValueStr);
	
	ui->textEdit_synthControlData_module->setText(synthControlsModuleStr);
	ui->textEdit_synthControlData_controlId ->setText(synthControlsControlIdtr);
	ui->textEdit_synthControlData_val->setText(synthControlsValueStr);
}

void Dialog_KbdControlMap::updateMidiControlSequencesData(int ch, int contNum, int val)
{	
	
	if (mod_synth_get_midi_control_sequences_training_enabled())
	{
		midiControlSequenceChannelStr = QString::number(ch, 10);
		midiControlSequenceControlNumStr = QString::number(contNum, 10);
		midiControlSequenceValueStr = QString::number(val, 10);
	}
}

void Dialog_KbdControlMap::updateSynthControlsData(int module, int contId, int val)
{
	if (mod_synth_get_midi_control_sequences_training_enabled())
	{
		synthControlsModuleStr = QString::number(module, 10);
		synthControlsControlIdtr = QString::number(contId, 10);
		synthControlsValueStr = QString::number(val, 10);
	}
}

void Dialog_KbdControlMap::trainPushButtonPressed(bool val)
{
	if (val)
	{
		mod_synth_enable_midi_control_sequences_training();
	}
	else
	{
		mod_synth_disable_midi_control_sequences_training();
	}
}

void Dialog_KbdControlMap::mapPushButtonPressed(bool val)
{
	int res;
	
	if (val)
	{
		ui->pushButton_kbdControlSequncesMap->blockSignals(true);
		ui->pushButton_kbdControlSequncesMap->setChecked(false);
		ui->pushButton_kbdControlSequncesMap->blockSignals(false);
		
		res = mod_synth_map_control_sequence_event();
	}	
}

void Dialog_KbdControlMap::openPushButtonPressed(bool val)
{
	int res = -1;

	ui->pushButton_kbdControlFileOpen->blockSignals(true);
	ui->pushButton_kbdControlFileOpen->setChecked(false);
	ui->pushButton_kbdControlFileOpen->blockSignals(false);

	QString mapName = QFileDialog::getOpenFileName(this,
													  tr("Load Keboard Control Mapping File "),
													  "/home/pi/AdjHeartModSynth_2/Keyboard_Maps",
													  tr("Presets (*.xml *.XML);;All Files (*)"));

	if (!mapName.isEmpty())
	{
		res = mod_synth_load_midi_keyboard_control_map_file(mapName.toStdString());
	}	
}

void Dialog_KbdControlMap::ignoreChannelChanged(int val)
{
	if (val == Qt::Unchecked)
	{
		mod_synth_set_midi_control_sequences_use_channel(false);
	}
	else
	{
		mod_synth_set_midi_control_sequences_use_channel(true);
	}
}

void Dialog_KbdControlMap::savePushButtonPressed(bool val)
{
	int res = -1;

	QString mapName = QFileDialog::getSaveFileName(this,
												   tr("Save Keboard Control Mapping File "),
												   "/home/pi/AdjHeartModSynth/Keyboard_Maps",
												   tr("Presets (*.xml *.XML);;All Files (*)"));

	if (!mapName.isEmpty())
	{
		res = mod_synth_save_midi_keyboard_control_map_file(mapName.toStdString());
	}

	ui->pushButton_kbdControlFileSave->blockSignals(true);
	ui->pushButton_kbdControlFileSave->setChecked(false);
	ui->pushButton_kbdControlFileSave->blockSignals(false);
	
}




