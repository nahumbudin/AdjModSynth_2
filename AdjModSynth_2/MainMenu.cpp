/**
* @file		MainMenu.h
*	@author		Nahum Budin
*	@date		16-Jan-2021
*	@version	1.1 
*					1. Adding ALSA Midi connections handling
*					2. Adding Audio menue
*					3. Adding JACK parameters selection options |(Auto/Manual).
*	
*	Version	1.0		18-Oct-2019
*
*	@brief		Main Menu actions handling.
*/

#include <QFileDialog>
#include <QMessageBox>
#include <QAction>
#include <QFont>

#include <string>

#include "MainWindow.h"
#include "MainMenue.h"
#include "libAdjHeartModSynth_2.h"


MainMenuHandling::MainMenuHandling(Ui_MainWindow *mainWind)
{
	mainWindow = mainWind;
	
	update_audio_menu_params();

	
	build_audio_menu();
	
	dialog_MidiClients = new Dialog_MidiClients(this);
	dialog_MidiClients->move(40, 150);

	dialog_jack_clients = new Dialog_JackClients(this);
	dialog_jack_clients->move(40, 150);

	//	dialog_AudioSettings = new Dialog_AudioSettings(this);
	//	dialog_AudioSettings->move(40, 150);
}

void MainMenuHandling::setTrigers()
{
	connect(mainWindow->actionFileSaveFluidSettings,
		SIGNAL(triggered()),
		this,
		SLOT(SaveFluidSynthSettingsMenuAction()));

	connect(mainWindow->actionFileOpenFluidSettings,
		SIGNAL(triggered()),
		this,
		SLOT(OpenFluidSynthSettingsMenuAction()));
	
	connect(mainWindow->actionSave_AdjSynthPatch,
		SIGNAL(triggered()),
		this,
		SLOT(SaveAdjSynthPatchMenuAction()));

	connect(mainWindow->actionOpen_AdjSyntPatch,
		SIGNAL(triggered()),
		this,
		SLOT(OpenAdjSynthPatchMenuAction()));
	
	connect(mainWindow->actionSave_AdjSynthSettings,
		SIGNAL(triggered()),
		this,
		SLOT(SaveAdjSynthSettingsMenuAction()));

	connect(mainWindow->actionOpen_AdjSynthSettings,
		SIGNAL(triggered()),
		this,
		SLOT(OpenAdjSynthSettingsMenuAction()));

	connect(mainWindow->actionSave_ModSynthGeneralSettings,
			SIGNAL(triggered()),
			this,
			SLOT(SaveModSynthGeneralSettingsMenuAction()));

	connect(mainWindow->actionOpen_ModSynthGeneralSettings,
			SIGNAL(triggered()),
			this,
			SLOT(OpenModSynthGeneralSettingsMenuAction()));

	connect(mainWindow->actionOpen_SoundFont_File,
		SIGNAL(triggered()),
		this,
		SLOT(OpenSoundfontFileMenuAction()));
	
	connect(mainWindow->actionCopy_Sketch_1_to_Sketch_2,
		SIGNAL(triggered()),
		this,
		SLOT(CopySketch1toSketch2MenuAction()));
	
	connect(mainWindow->actionCopy_Sketch_1_to_Sketch_3,
		SIGNAL(triggered()),
		this,
		SLOT(CopySketch1toSketch3MenuAction()));
	
	connect(mainWindow->actionCopy_Sketch_2_to_Sketch_1,
		SIGNAL(triggered()),
		this,
		SLOT(CopySketch2toSketch1MenuAction()));
	
	connect(mainWindow->actionCopy_Sketch_2_to_Sketch_3,
		SIGNAL(triggered()),
		this,
		SLOT(CopySketch2toSketch3MenuAction()));
	
	connect(mainWindow->actionCopy_Sketch_3_to_Sketch_1,
		SIGNAL(triggered()),
		this,
		SLOT(CopySketch3toSketch1MenuAction()));
	
	connect(mainWindow->actionCopy_Sketch_3_to_Sketch_2,
		SIGNAL(triggered()),
		this,
		SLOT(CopySketch3toSketch2MenuAction()));

	connect(mainWindow->action_audio_settings,
			SIGNAL(triggered()),
			this,
			SLOT(OpenJackSettingsDialog()));

	connect(mainWindow->action_jack_clients,
			SIGNAL(triggered()),
			this,
			SLOT(open_jack_clients_dialog()));
	
	
	connect(mainWindow->actionMidiDevices,
		SIGNAL(triggered()),
		this,
		SLOT(OpenMidiDevicesDialog()));
	
//	connect(mainWindow->action_midi_devices_scan,
//		SIGNAL(triggered()),
//		this,
//		SLOT(scan_midi_devices()));
}


/**
 * A SLOT callback activated when the File menu-bar Save FluidSynth Settings file is clicked.
 * @param none.
 * @return none
 */
void MainMenuHandling::SaveFluidSynthSettingsMenuAction()
{
	QString fileName = QFileDialog::getSaveFileName(this,
		tr("Save Settings File"), "/home/pi/AdjHeartModSynth/Settings",
		tr("Settings (*.xml *.XML);;All Files (*)"));

	if (!fileName.isEmpty())
	{
		mod_synth_save_fluid_synth_settings_file(fileName.toStdString());
	}
}

/**
 * A SLOT callback activated when the File menu-bar Open FluidSynth Settings file is clicked.
 * @param none.
 * @return none
 */
void MainMenuHandling::OpenFluidSynthSettingsMenuAction()
{
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Open Settings File"), "/home/pi/AdjHeartModSynth/Settings",
		tr("Settings (*.xml *.XML);;All Files (*)"));

	if (!fileName.isEmpty())
	{
		mod_synth_open_fluid_synth_settings_file(fileName.toStdString());
	}
}

/**
 * A SLOT callback activated when the File menu-bar Save AdjSynth Patch file is clicked.
 * @param none.
 * @return none
 */
void MainMenuHandling::SaveAdjSynthPatchMenuAction()
{
	QString fileName = QFileDialog::getSaveFileName(this,
		tr("Save Patch File"),
		"/home/pi/AdjHeartModSynth/Settings",
		tr("Settings (*.xml *.XML);;All Files (*)"));

	if (!fileName.isEmpty())
	{
		mod_synth_save_adj_synth_patch_file(fileName.toStdString());
	}
}

/**
 * A SLOT callback activated when the File menu-bar Open AdjSynth Patch file is clicked.
 * @param none.
 * @return none
 */
void MainMenuHandling::OpenAdjSynthPatchMenuAction()
{
	QMessageBox msgBox;
	int ret;
	
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Open Patch File"),
		"/home/pi/AdjHeartModSynth/Settings",
		tr("Settings (*.xml *.XML);;All Files (*)"));

	if (!fileName.isEmpty())
	{
		msgBox.setIcon(QMessageBox::Critical);
		msgBox.setText("Warning.");		
		msgBox.setInformativeText(QString("Are you sure you want to overide Sketch %1?") 
							.arg(mod_synth_get_active_sketch() - _SKETCH_PROGRAM_1 + 1));
		msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
		msgBox.setDefaultButton(QMessageBox::Cancel);
		ret = msgBox.exec();
		if (ret == QMessageBox::Yes)
		{
			mod_synth_open_adj_synth_patch_file(fileName.toStdString(), mod_synth_get_active_sketch());
		}
	}
	
	MainWindow::getInstance()->update();
}

/**
 * A SLOT callback activated when the File menu-bar Save AdjSynth Settings file is clicked.
 * @param none.
 * @return none
 */
void MainMenuHandling::SaveAdjSynthSettingsMenuAction()
{
	QString fileName = QFileDialog::getSaveFileName(this,
		tr("Save Settings File"),
		"/home/pi/AdjHeartModSynth/Settings",
		tr("Settings (*.xml *.XML);;All Files (*)"));

	if (!fileName.isEmpty())
	{
		mod_synth_save_adj_synth_settings_file(fileName.toStdString());
	}
}

/**
 * A SLOT callback activated when the File menu-bar Open AdjSynth Settings file is clicked.
 * @param none.
 * @return none
 */
void MainMenuHandling::OpenAdjSynthSettingsMenuAction()
{
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Open Settings File"),
		"/home/pi/AdjHeartModSynth/Settings",
		tr("Settings (*.xml *.XML);;All Files (*)"));

	if (!fileName.isEmpty())
	{
		mod_synth_open_adj_synth_settings_file(fileName.toStdString());
	}
	
	MainWindow::getInstance()->update();
}

/**
 * A SLOT callback activated when the File menu-bar Save ModSynth General Settings file is clicked.
 * @param none.
 * @return none
 */
void MainMenuHandling::SaveModSynthGeneralSettingsMenuAction()
{
	QString fileName = QFileDialog::getSaveFileName(this,
													tr("Save General Settings File"),
													"/home/pi/AdjHeartModSynth/Settings",
													tr("Settings (*.xml *.XML);;All Files (*)"));

	if (!fileName.isEmpty())
	{
		mod_synth_save_mod_synth_general_settings_file(fileName.toStdString());
	}
}

/**
 * A SLOT callback activated when the File menu-bar Open ModSynth General Settings file is clicked.
 * @param none.
 * @return none
 */
void MainMenuHandling::OpenModSynthGeneralSettingsMenuAction()
{
	QString fileName = QFileDialog::getOpenFileName(this,
													tr("Open General Settings File"),
													"/home/pi/AdjHeartModSynth/Settings",
													tr("Settings (*.xml *.XML);;All Files (*)"));

	if (!fileName.isEmpty())
	{
		mod_synth_open_mod_synth_general_settings_file(fileName.toStdString());
	}

	MainWindow::getInstance()->update();
}

/**
 * A SLOT callback activated when the soundfont Open pushbutton is pressed.
 * @param the new checkbox value.
 * @return none
 */
void MainMenuHandling::OpenSoundfontFileMenuAction()
{
	bool ok;
	int ret;
	QMessageBox msgBox;

	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Open Patch File"), _FLUID_DEFAULT_SOUNDFONT_DIR,
		tr("Settings (*.sf2 *.SF2);;All Files (*)"));

	if (!fileName.isEmpty())
	{
		msgBox.setIcon(QMessageBox::Critical);
		msgBox.setText("Soundfont file has been selected.");
		msgBox.setInformativeText("Are you sure you want to use it?");
		msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
		msgBox.setDefaultButton(QMessageBox::Cancel);
		ret = msgBox.exec();

		if (ret == QMessageBox::Yes)
		{
			char mssg[256];
			sprintf(mssg, "%s SoundFont was loaded.", fileName.toStdString().c_str());
			MainWindow::getInstance()->updateStatusDisplayText(mssg);
			mod_synth_set_fluid_synth_soundfont(fileName.toStdString());
			printf("%s", mssg);
		}
	}
}

/**
 * A SLOT callback activated when the copy Sketch 1 to Sketch 2 menu item is selected.
 * @param the new checkbox value.
 * @return none
 */
void MainMenuHandling::CopySketch1toSketch2MenuAction()
{
	QMessageBox msgBox;
	msgBox.setIcon(QMessageBox::Critical);
	msgBox.setWindowTitle("Warning");
	msgBox.setText("Are you sure you want to overide Sketch 2?");
	msgBox.setStandardButtons(QMessageBox::Yes);
	msgBox.addButton(QMessageBox::No);
	msgBox.setDefaultButton(QMessageBox::No);
	if (msgBox.exec() == QMessageBox::Yes) 
	{
		mod_synth_copy_sketch(_SKETCH_PROGRAM_1, _SKETCH_PROGRAM_2);
		MainWindow::getInstance()->update();
	}
	else 
	{
		return;
	}
}

/**
 * A SLOT callback activated when the copy Sketch 1 to Sketch 3 menu item is selected.
 * @param the new checkbox value.
 * @return none
 */
void MainMenuHandling::CopySketch1toSketch3MenuAction()
{
	QMessageBox msgBox;
	msgBox.setIcon(QMessageBox::Critical);
	msgBox.setWindowTitle("Warning");
	msgBox.setText("Are you sure you want to overide Sketch 3?");
	msgBox.setStandardButtons(QMessageBox::Yes);
	msgBox.addButton(QMessageBox::No);
	msgBox.setDefaultButton(QMessageBox::No);
	if (msgBox.exec() == QMessageBox::Yes) 
	{
		mod_synth_copy_sketch(_SKETCH_PROGRAM_1, _SKETCH_PROGRAM_3);
		MainWindow::getInstance()->update();
	}
	else 
	{
		return;
	}
}

/**
 * A SLOT callback activated when the copy Sketch 2 to Sketch 1 menu item is selected.
 * @param the new checkbox value.
 * @return none
 */
void MainMenuHandling::CopySketch2toSketch1MenuAction()
{
	QMessageBox msgBox;
	msgBox.setIcon(QMessageBox::Critical);
	msgBox.setWindowTitle("Warning");
	msgBox.setText("Are you sure you want to overide Sketch 1?");
	msgBox.setStandardButtons(QMessageBox::Yes);
	msgBox.addButton(QMessageBox::No);
	msgBox.setDefaultButton(QMessageBox::No);
	if (msgBox.exec() == QMessageBox::Yes) 
	{
		mod_synth_copy_sketch(_SKETCH_PROGRAM_2, _SKETCH_PROGRAM_1);
		MainWindow::getInstance()->update();
	}
	else 
	{
		return;
	}
}

/**
 * A SLOT callback activated when the copy Sketch 2 to Sketch 3 menu item is selected.
 * @param none.
 * @return none
 */
void MainMenuHandling::CopySketch2toSketch3MenuAction()
{
	QMessageBox msgBox;
	msgBox.setIcon(QMessageBox::Critical);
	msgBox.setWindowTitle("Warning");
	msgBox.setText("Are you sure you want to overide Sketch 3?");
	msgBox.setStandardButtons(QMessageBox::Yes);
	msgBox.addButton(QMessageBox::No);
	msgBox.setDefaultButton(QMessageBox::No);
	if (msgBox.exec() == QMessageBox::Yes) 
	{
		mod_synth_copy_sketch(_SKETCH_PROGRAM_2, _SKETCH_PROGRAM_3);
		MainWindow::getInstance()->update();
	}
	else 
	{
		return;
	}
}

/**
 * A SLOT callback activated when the copy Sketch 3 to Sketch 1 menu item is selected.
 * @param none.
 * @return none
 */
void MainMenuHandling::CopySketch3toSketch1MenuAction()
{
	QMessageBox msgBox;
	msgBox.setIcon(QMessageBox::Critical);
	msgBox.setWindowTitle("Warning");
	msgBox.setText("Are you sure you want to overide Sketch 1?");
	msgBox.setStandardButtons(QMessageBox::Yes);
	msgBox.addButton(QMessageBox::No);
	msgBox.setDefaultButton(QMessageBox::No);
	if (msgBox.exec() == QMessageBox::Yes) 
	{
		mod_synth_copy_sketch(_SKETCH_PROGRAM_3, _SKETCH_PROGRAM_1);
		MainWindow::getInstance()->update();
	}
	else 
	{
		return;
	}
}

/**
 * A SLOT callback activated when the copy Sketch 3 to Sketch 2 menu item is selected.
 * @param none.
 * @return none
 */
void MainMenuHandling::CopySketch3toSketch2MenuAction()
{
	QMessageBox msgBox;
	msgBox.setIcon(QMessageBox::Critical);
	msgBox.setWindowTitle("Warning");
	msgBox.setText("Are you sure you want to overide Sketch 2?");
	msgBox.setStandardButtons(QMessageBox::Yes);
	msgBox.addButton(QMessageBox::No);
	msgBox.setDefaultButton(QMessageBox::No);
	if (msgBox.exec() == QMessageBox::Yes) 
	{
		mod_synth_copy_sketch(_SKETCH_PROGRAM_3, _SKETCH_PROGRAM_2);
		MainWindow::getInstance()->update();
	}
	else 
	{
		return;
	}
}

/**
 * A SLOT callback activated when the Audio->Jack menu item is selected.
 * @param none.
 * @return none
 */
void MainMenuHandling::OpenJackSettingsDialog()
{
//	dialog_AudioSettings->update();
//	dialog_AudioSettings->show();
}

/**
 * A SLOT callback activated when the Audio->JACK Clients menu item is selected.
 * @param none.
 * @return none
 */
void MainMenuHandling::open_jack_clients_dialog()
{
	dialog_jack_clients->update();
	dialog_jack_clients->show();
	dialog_jack_clients->raise();
	dialog_jack_clients->activateWindow();
}

/**
 * A SLOT callback activated when the MIDI->Connections menu item is selected.
 * @param none.
 * @return none
 */
void MainMenuHandling::OpenMidiDevicesDialog()
{
	dialog_MidiClients->update();
	dialog_MidiClients->show();
	dialog_MidiClients->raise();
	dialog_MidiClients->activateWindow();
}


