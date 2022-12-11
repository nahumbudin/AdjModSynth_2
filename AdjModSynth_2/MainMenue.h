/**
* @file		MainMenu.h
*	@author		Nahum Budin
*	@date		16-Jan-2021
*	@version	1.1 
*				1. Adding ALSA Midi connections handling
*				2. Adding Audio menue
*				3. Adding JACK parameters selection options |(Auto/Manual).
*	
*	Version	1.0		18-Oct-2019
*
*	@brief		main menu ui handling.
*/

#ifndef _MAIN_MENU
#define _MAIN_MENU

#include <QAction>

#include <ui_MainWindow.h>
#include "Dialog_AudioSettings.h"
#include "Dialog_MidiClients.h"
#include "Dialog_JackClients.h"

#include "../libAdjHeartModSynth_2.h"


class MainMenuHandling : public QMainWindow {

	Q_OBJECT

public :
	MainMenuHandling(Ui_MainWindow *mainWind);

	void setTrigers();

protected slots :

	void SaveFluidSynthSettingsMenuAction();
	void OpenFluidSynthSettingsMenuAction();
	
	void SaveAdjSynthPatchMenuAction();
	void OpenAdjSynthPatchMenuAction();
	
	void SaveAdjSynthSettingsMenuAction();
	void OpenAdjSynthSettingsMenuAction();

	void SaveModSynthGeneralSettingsMenuAction();
	void OpenModSynthGeneralSettingsMenuAction();

	void OpenSoundfontFileMenuAction();
	
	void CopySketch1toSketch2MenuAction();
	void CopySketch1toSketch3MenuAction();
	void CopySketch2toSketch1MenuAction();
	void CopySketch2toSketch3MenuAction();
	void CopySketch3toSketch1MenuAction();
	void CopySketch3toSketch2MenuAction();

	void OpenJackSettingsDialog();
	void open_jack_clients_dialog();

	void OpenMidiDevicesDialog();
	
//	void scan_midi_devices();
/*	
	void input_midi_devices_clicked_1();
	void input_midi_devices_clicked_2();
	void input_midi_devices_clicked_3();
	void input_midi_devices_clicked_4();
	void input_midi_devices_clicked_5();
	void input_midi_devices_clicked_6();
	void input_midi_devices_clicked_7();
	void input_midi_devices_clicked_8();
	
	void output_midi_devices_clicked_1();
	void output_midi_devices_clicked_2();
	void output_midi_devices_clicked_3();
	void output_midi_devices_clicked_4();
	void output_midi_devices_clicked_5();
	void output_midi_devices_clicked_6();
	void output_midi_devices_clicked_7();
	void output_midi_devices_clicked_8();
*/	
	void audio_driver_jack_selected();
	void audio_driver_alsa_selected();
	
	void sample_rate_44_selected();
	void sample_rate_48_selected();
	
	void block_size_256_selected();
	void block_size_512_selected();
	void block_size_1024_selected();
	
	void jack_server_auto_start_selected();
	void jack_server_auto_connect_selected();

private:
	Ui_MainWindow *mainWindow;

	Dialog_AudioSettings *dialog_AudioSettings;
	Dialog_MidiClients *dialog_MidiClients;
	Dialog_JackClients *dialog_jack_clients;
	
//	void build_midi_devices_menu();
	
//	void connect_midi_input_device_checked_action(int dev);
//	void connect_midi_output_device_checked_action(int dev);
	
//	void input_midi_device_cliked(int dev, bool checked);
//	void output_midi_device_cliked(int dev, bool checked);
	
	void update_audio_menu_params();
	void build_audio_menu();
	
//	int num_of_midi_devices;
	
//	char **midi_devices_names = NULL;
	
//	QAction **midi_input_devices_actions, **midi_output_devices_actions; 
//	QAction *midi_input_devices_action, *midi_output_devices_action;
//	QAction *midi_scan_devices_action;
//	bool input_midi_device_checked[_MAX_NUM_OF_MIDI_DEVICES] = { false };
//	bool output_midi_device_checked[_MAX_NUM_OF_MIDI_DEVICES] = { false };
	
	QAction *audio_driver_label, *audio_sample_rate_label, *audio_block_size_label;
	QAction *audio_select_driver_jack_action, *audio_select_driver_alsa_action;
	QAction *audio_select_sample_rate_44_action, *audio_select_sample_rate_48_action;
	QAction *audio_select_block_size_256_action, *audio_select_block_size_512_action, *audio_select_block_size_1024_action;
	QAction *jack_server_auto_start_action, *jack_server_auto_connect_audio_action;
	
	// Holds the input midi deviced menu item id
//	int input_devices[_MAX_NUM_OF_MIDI_DEVICES + 3] = { -1 }; // +3: Scan, Output Devices, Input Devices menu items
	// Holds the outnput midi deviced menu item id
//	int output_devices[_MAX_NUM_OF_MIDI_DEVICES + 3] = { -1 };

	bool audio_driver_selected_jack, audio_driver_selected_alsa;
	bool sample_rate_selected_44, sample_rate_selected_48;
	bool audio_block_size_256_selected, audio_block_size_512_selected, audio_block_size_1024_selected;
	bool jack_server_auto_start_state, jack_server_auto_connect_audio_state;

};

#endif
