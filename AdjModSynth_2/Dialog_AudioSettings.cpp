/**
* @file		Dialog_AudioSettings.cpp
*	@author		Nahum Budin
*	@date		17-Jan-2021
*	@version	1.0
*
*	@brief		Used for selecting JACK parameters
*
*/

#include <QDialog>
#include <QMessageBox>

#include "ui_Dialog_AudioSettings.h"
#include "libAdjHeartModSynth_2.h"

#include "Dialog_AudioSettings.h"
//#include "ui_Dialog_JackSettings.h"

Dialog_AudioSettings *Dialog_AudioSettings::dialog_AudioSettingsInstance = NULL;

/** Constructor */
Dialog_AudioSettings::Dialog_AudioSettings(QWidget *parent)
	: QDialog(parent),
	  ui(new Ui::Dialog_AudioSettings)
{
	ui->setupUi(this);
	dialog_AudioSettingsInstance = this;

	update();

	connect(ui->radioButton_AudioDriverJack,
			SIGNAL(clicked(bool)),
			this,
			SLOT(driverJackChanged(bool)));

	connect(ui->radioButton_AudioDriverALSA,
			SIGNAL(clicked(bool)),
			this,
			SLOT(driverAlsaChanged(bool)));
	
	connect(ui->radioButton_JackParamsManualMode,
			SIGNAL(clicked(bool)),
			this,
			SLOT(manualModeChanged(bool)));

	connect(ui->radioButton_JackParamsAutoMode,
			SIGNAL(clicked(bool)),
			this,
			SLOT(autoModeChanged(bool)));

	connect(ui->checkBox_JackParamsAutoStart,
			SIGNAL(toggled(bool)),
			this,
			SLOT(autoStartChanged(bool)));

	connect(ui->checkBox_JackParamsAutoConnect,
			SIGNAL(toggled(bool)),
			this,
			SLOT(autoConnectChanged(bool)));

	connect(ui->comboBox_AudioParamsSampleRate,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(sampleRateChanged(int)));

	connect(ui->comboBox_AudioParamsBlockSize,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(blockSizeChanged(int)));

	connect(ui->buttonBox_AudioParamsOkCancel,
			SIGNAL(accepted()),
			this,
			SLOT(audioSettingsAccepted()));

	connect(ui->buttonBox_AudioParamsOkCancel,
			SIGNAL(rejected()),
			this,
			SLOT(audioSettingsCanceled()));
}

Dialog_AudioSettings::~Dialog_AudioSettings()
{
	
}

void Dialog_AudioSettings::closeEvent(QCloseEvent *event)
{
	
}

void Dialog_AudioSettings::update()
{
	static bool oneTimeInitialized = false;

	driver = mod_synth_get_audio_driver();
	blockSize = mod_synth_get_audio_block_size();
	sampleRate = mod_synth_get_audio_sample_rate();
	mode = mod_synth_get_jack_mode();
	autoStart = mod_synth_get_jack_auto_start_state();
//	autoConnect = mod_synth_get_jack_auto_connect_state();

	if (!oneTimeInitialized)
	{
		oneTimeInitialized = true;

		stringSamplRatesList.append("44100 Hz");
		stringSamplRatesList.append("48000 Hz");

		for (int i = 0; i < stringSamplRatesList.size(); i++)
		{
			ui->comboBox_AudioParamsSampleRate->addItem(stringSamplRatesList.at(i));
		}

		stringBlockSizeList.append("256 frames");
		stringBlockSizeList.append("512 frames");
		stringBlockSizeList.append("1024 frames");

		for (int i = 0; i < stringBlockSizeList.size(); i++)
		{
			ui->comboBox_AudioParamsBlockSize->addItem(stringBlockSizeList.at(i));
		}
	}
	else
	{
		
	}

	ui->radioButton_AudioDriverJack->blockSignals(true);
	if (driver == _AUDIO_JACK)
	{
		ui->radioButton_AudioDriverJack->setChecked(true);
	}
	else
	{
		ui->radioButton_AudioDriverALSA->setChecked(false);
	}
	ui->radioButton_AudioDriverJack->blockSignals(false);

	ui->radioButton_AudioDriverALSA->blockSignals(true);
	if (driver == _AUDIO_ALSA)
	{
		ui->radioButton_AudioDriverALSA->setChecked(true);
	}
	else
	{
		ui->radioButton_AudioDriverALSA->setChecked(false);
	}
	ui->radioButton_AudioDriverALSA->blockSignals(false);

	ui->comboBox_AudioParamsSampleRate->blockSignals(true);
	if (sampleRate == 48000)
	{
		ui->comboBox_AudioParamsSampleRate->setCurrentIndex(1);
	}
	else
	{
		ui->comboBox_AudioParamsSampleRate->setCurrentIndex(0);
	}
	ui->comboBox_AudioParamsSampleRate->blockSignals(false);

	ui->comboBox_AudioParamsBlockSize->blockSignals(true);
	if (blockSize == 256)
	{
		ui->comboBox_AudioParamsBlockSize->setCurrentIndex(0);
	}
	else if (blockSize == 1024)
	{
		ui->comboBox_AudioParamsBlockSize->setCurrentIndex(2);
	}
	else
	{
		ui->comboBox_AudioParamsBlockSize->setCurrentIndex(1);
	}
	ui->comboBox_AudioParamsBlockSize->blockSignals(false);

	ui->radioButton_JackParamsAutoMode->blockSignals(true);
	if (mode == _JACK_MODE_SERVER_CONTROL)
	{
		ui->radioButton_JackParamsAutoMode->setChecked(true);
		ui->radioButton_JackParamsManualMode->setChecked(false);
		if (driver == _AUDIO_JACK)
		{
			ui->comboBox_AudioParamsBlockSize->setDisabled(true);
			ui->comboBox_AudioParamsSampleRate->setDisabled(true);
		}
	}
	else
	{
		ui->radioButton_JackParamsAutoMode->setChecked(false);
		ui->radioButton_JackParamsManualMode->setChecked(true);
		if (driver == _AUDIO_JACK)
		{
			ui->comboBox_AudioParamsBlockSize->setEnabled(true);
			ui->comboBox_AudioParamsSampleRate->setEnabled(true);
		}
	}
	ui->radioButton_JackParamsAutoMode->blockSignals(false);

	ui->checkBox_JackParamsAutoStart->blockSignals(true);
	if (autoStart)
	{
		ui->checkBox_JackParamsAutoStart->setChecked(true);
	}
	else
	{
		ui->checkBox_JackParamsAutoStart->setChecked(false);
	}
	ui->checkBox_JackParamsAutoStart->blockSignals(false);

	ui->checkBox_JackParamsAutoConnect->blockSignals(true);
	if (autoConnect)
	{
		ui->checkBox_JackParamsAutoConnect->setChecked(true);
	}
	else
	{
		ui->checkBox_JackParamsAutoConnect->setChecked(false);
	}
	ui->checkBox_JackParamsAutoConnect->blockSignals(false);
}

void Dialog_AudioSettings::driverJackChanged(bool val)
{
	if (val)
	{
		mode = _AUDIO_JACK;
	}
}

void Dialog_AudioSettings::driverAlsaChanged(bool val)
{
	if (val)
	{
		mode = _AUDIO_ALSA;
	}
}

void Dialog_AudioSettings::manualModeChanged(bool val)
{
	if (val)
	{
		mode = _JACK_MODE_APP_CONTROL;
	}
}

void Dialog_AudioSettings::autoModeChanged(bool val)
{
	if (val)
	{
		mode = _JACK_MODE_SERVER_CONTROL;
	}
}

void Dialog_AudioSettings::autoStartChanged(bool val)
{
	autoStart = val;
}

void Dialog_AudioSettings::autoConnectChanged(bool val)
{
	autoConnect = val;
}

void Dialog_AudioSettings::sampleRateChanged(int val)
{
	if (val == 1)
	{
		sampleRate = _SAMPLE_RATE_48;
	}
	else
	{
		sampleRate = _SAMPLE_RATE_44;
	}

	update();
}

void Dialog_AudioSettings::blockSizeChanged(int val)
{
	if (val == 0)
	{
		blockSize = _AUDIO_BLOCK_SIZE_256;
	}
	else if (val == 2)
	{
		blockSize = _AUDIO_BLOCK_SIZE_1024;
	}
	else
	{
		blockSize = _AUDIO_BLOCK_SIZE_512;
	}
}

void Dialog_AudioSettings::audioSettingsAccepted()
{
	QMessageBox msgBox;
	msgBox.setIcon(QMessageBox::Critical);
	msgBox.setWindowTitle("Warning?");
	msgBox.setText("Are you sure you want to save all changes?\nApplication must be restarted if changes are saved!");
	msgBox.setStandardButtons(QMessageBox::Yes);
	msgBox.addButton(QMessageBox::No);
	msgBox.setDefaultButton(QMessageBox::No);
	if (msgBox.exec() == QMessageBox::Yes)
	{
		mod_synth_on_exit();

		mod_synth_audio_event_int(_AUDIO_EVENT_1, _AUDIO_JACK_MODE, mode);
		mod_synth_audio_event_int(_AUDIO_EVENT_1, _AUDIO_SAMPLE_RATE, sampleRate);
		mod_synth_audio_event_int(_AUDIO_EVENT_1, _AUDIO_BLOCK_SIZE, blockSize);
		mod_synth_audio_event_int(_AUDIO_EVENT_1, _AUDIO_DRIVER, driver);

		mod_synth_audio_event_bool(_AUDIO_EVENT_1, _AUDIO_JACK_AUTO_START, autoStart);
		mod_synth_audio_event_bool(_AUDIO_EVENT_1, _AUDIO_JACK_AUTO_CONNECT, autoConnect);

		mod_synth_save_mod_synth_general_settings_file("/home/pi/AdjHeartModSynth/Settings/AdjSynth_general_settings_1.xml");
	}
}

void Dialog_AudioSettings::audioSettingsCanceled()
{
	QMessageBox msgBox;
	msgBox.setIcon(QMessageBox::Critical);
	msgBox.setWindowTitle("Warning");
	msgBox.setText("Are you sure you want to ignore all changes?");
	msgBox.setStandardButtons(QMessageBox::Yes);
	msgBox.addButton(QMessageBox::No);
	msgBox.setDefaultButton(QMessageBox::No);
	if (msgBox.exec() == QMessageBox::Yes)
	{
		this->close();
	}
	
}
