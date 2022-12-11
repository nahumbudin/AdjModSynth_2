/**
* @file		MainMenu_Midi.cpp
*	@author		Nahum Budin
*	@date		16-Jan-2021
*	@version	1.1 
*				1. Adding ALSA Midi connections handling
*	
*	Version	1.0		18-Oct-2019
*
*	@brief		Main Menu Midi connections actions handling.
*/

#include "MainMenue.h"

void MainMenuHandling::build_midi_devices_menu()
{
	int dev, out_index, in_index;
	QFont font;
	// Get midi devices list
	num_of_midi_devices = mod_synth_get_num_of_midi_devices();
	if (mod_synth_get_num_of_midi_devices() <= 0)
	{
		return;
	}
	/*	
		if (midi_devices_names != NULL)
		{
			for (dev = 0; (dev < _MAX_NUM_OF_MIDI_DEVICES) && (dev < num_of_midi_devices); dev++)
			{
				if (*midi_devices_names[dev] != NULL)
				{
					delete[] midi_devices_names[dev];
		}
}
		
delete[] midi_devices_names;
}
*/	
	// Get all devices names
	midi_devices_names = new char*[num_of_midi_devices];
	for (dev = 0; (dev < num_of_midi_devices && (dev < _MAX_NUM_OF_MIDI_DEVICES)); dev++)
	{
		midi_devices_names[dev] = new char[128];
		mod_synth_get_midi_device_string(dev, midi_devices_names[dev]);
		input_devices[dev] = -1;
		output_devices[dev] = -1;
	}
	
	// Clear all previous content
	mainWindow->menu_MIDI->clear();
	
	// Add scan action
	midi_scan_devices_action = new QAction(tr("Scan"), this);
	mainWindow->menu_MIDI->addAction(midi_scan_devices_action);
	font = midi_scan_devices_action->font();
	font.setPointSize(14);	
	midi_scan_devices_action->setFont(font);
	connect(midi_scan_devices_action,
		SIGNAL(triggered()),
		this,
		SLOT(scan_midi_devices()));
	
	// Seperator
	mainWindow->menu_MIDI->addSeparator();
	
	// Add output devices Label(Kbds)
	midi_output_devices_action = new QAction(tr("Output Devices (Kbds)"), this);
	mainWindow->menu_MIDI->addAction(midi_output_devices_action);
	midi_output_devices_action->setFont(font);
		
	out_index = 0;	
	midi_output_devices_actions = new QAction*[num_of_midi_devices];	
	for (dev = 0; (dev < num_of_midi_devices && (dev < _MAX_NUM_OF_MIDI_DEVICES)); dev++)
	{
		if (((midi_devices_names[dev][0] == 'O') || (midi_devices_names[dev][1] == 'O')) && 
			!((midi_devices_names[dev][0] == 'I') || (midi_devices_names[dev][1] == 'I')))
		{
			// Output device
			output_devices[2 + out_index] = dev;      // 2+ : scan 0, out dev 1
			// Add as menu actions
			midi_output_devices_actions[out_index] = new QAction(tr(midi_devices_names[dev]), this);
			mainWindow->menu_MIDI->addAction(midi_output_devices_actions[out_index]);
			midi_output_devices_actions[out_index]->setCheckable(true);
			midi_output_devices_actions[out_index]->setChecked(output_midi_device_checked[dev]);        // TODO: get status from engine
			midi_output_devices_actions[out_index]->setFont(font);
			// connect signals
			connect_midi_output_device_checked_action(out_index);
			out_index++;
		}	
		else
		{
			output_devices[2 + out_index] = -1;
		}
	}
	
	// Seperator
	mainWindow->menu_MIDI->addSeparator();
	
	// Add input devices (Synths)
	midi_input_devices_action = new QAction(tr("Input Devices (Synth)"), this);
	mainWindow->menu_MIDI->addAction(midi_input_devices_action);
	midi_input_devices_action->setFont(font);
	
	in_index = 0;
	midi_input_devices_actions = new QAction*[num_of_midi_devices];
	for (dev = 0; (dev < num_of_midi_devices) && (dev < _MAX_NUM_OF_MIDI_DEVICES); dev++)
	{
		if (((midi_devices_names[dev][0] == 'I') || (midi_devices_names[dev][1] == 'I')) &&
			!((midi_devices_names[dev][0] == 'O') || (midi_devices_names[dev][1] == 'O')))
		{
			// Input devices
			input_devices[3 + in_index] = dev;       // 2+ : scan 0, out dev 1, in dev 2
			// Add as menu actions
			midi_input_devices_actions[in_index] = new QAction(tr(midi_devices_names[dev]), this);
			mainWindow->menu_MIDI->addAction(midi_input_devices_actions[in_index]);
			midi_input_devices_actions[in_index]->setCheckable(true);
			midi_input_devices_actions[in_index]->setChecked(output_midi_device_checked[dev]);         // TODO: get status from engine
			midi_input_devices_actions[in_index]->setFont(font);
			// connect signals
			connect_midi_input_device_checked_action(in_index);
			in_index++;
		}
		else
		{
			input_devices[3 + in_index] = -1;
		}
	}	
	
	// Keep menu open
	mainWindow->menu_MIDI->show();
}


void MainMenuHandling::connect_midi_output_device_checked_action(int dev)
{
	if (dev < _MAX_NUM_OF_MIDI_DEVICES)
	{
		switch (dev)
		{
		case 0:
			connect(midi_output_devices_actions[0],
				SIGNAL(triggered()),
				this,
				SLOT(output_midi_devices_clicked_1()));
			break;
					
		case 1:
			connect(midi_output_devices_actions[1],
				SIGNAL(triggered()),
				this,
				SLOT(output_midi_devices_clicked_2()));
			break;
					
		case 2:
			connect(midi_output_devices_actions[2],
				SIGNAL(triggered()),
				this,
				SLOT(output_midi_devices_clicked_3()));
			break;
					
		case 3:
			connect(midi_output_devices_actions[3],
				SIGNAL(triggered()),
				this,
				SLOT(output_midi_devices_clicked_4()));
			break;
					
		case 4:
			connect(midi_output_devices_actions[4],
				SIGNAL(triggered()),
				this,
				SLOT(output_midi_devices_clicked_5()));
			break;
					
		case 5:
			connect(midi_output_devices_actions[5],
				SIGNAL(triggered()),
				this,
				SLOT(output_midi_devices_clicked_6()));
			break;
		case 6:
			connect(midi_output_devices_actions[6],
				SIGNAL(triggered()),
				this,
				SLOT(output_midi_devices_clicked_7()));
			break;
		case 7:
			connect(midi_output_devices_actions[7],
				SIGNAL(triggered()),
				this,
				SLOT(output_midi_devices_clicked_8()));
			break;		
		}
	}
}

void MainMenuHandling::connect_midi_input_device_checked_action(int dev)
{
	if (dev < _MAX_NUM_OF_MIDI_DEVICES)
	{
		switch (dev)
		{
		case 0:
			connect(midi_input_devices_actions[0],
				SIGNAL(triggered()),
				this,
				SLOT(input_midi_devices_clicked_1()));
			break;
					
		case 1:
			connect(midi_input_devices_actions[1],
				SIGNAL(triggered()),
				this,
				SLOT(input_midi_devices_clicked_2()));
			break;
					
		case 2:
			connect(midi_input_devices_actions[2],
				SIGNAL(triggered()),
				this,
				SLOT(input_midi_devices_clicked_3()));
			break;
					
		case 3:
			connect(midi_input_devices_actions[3],
				SIGNAL(triggered()),
				this,
				SLOT(input_midi_devices_clicked_4()));
			break;
					
		case 4:
			connect(midi_input_devices_actions[4],
				SIGNAL(triggered()),
				this,
				SLOT(input_midi_devices_clicked_5()));
			break;
					
		case 5:
			connect(midi_input_devices_actions[5],
				SIGNAL(triggered()),
				this,
				SLOT(input_midi_devices_clicked_6()));
			break;
		case 6:
			connect(midi_input_devices_actions[6],
				SIGNAL(triggered()),
				this,
				SLOT(input_midi_devices_clicked_7()));
			break;
		case 7:
			connect(midi_input_devices_actions[7],
				SIGNAL(triggered()),
				this,
				SLOT(input_midi_devices_clicked_8()));
			break;		
		}
	}
}

void MainMenuHandling::input_midi_device_cliked(int dev, bool checked)
{
	int res;
	
	if (dev < _MAX_NUM_OF_MIDI_DEVICES)
	{
		input_midi_device_checked[dev] = checked;
		if (checked)
		{
			res = mod_synth_connect_midi_device(dev, _MIDI_DEVICE_INPUT);
		}
		else
		{
			res = mod_synth_disconnect_midi_device(dev, _MIDI_DEVICE_INPUT);
		}
		
	}
}
	
void MainMenuHandling::output_midi_device_cliked(int dev, bool checked)
{
	int res;
	
	if (dev < _MAX_NUM_OF_MIDI_DEVICES)
	{
		output_midi_device_checked[dev] = checked;
		if (checked)
		{
			res = mod_synth_connect_midi_device(dev, _MIDI_DEVICE_OUTPUT);
		}
		else
		{
			res = mod_synth_disconnect_midi_device(dev, _MIDI_DEVICE_OUTPUT);
		}
	}
}

/**
 * A SLOT callback activated when the MIDI menu item is selected.
 * @param none.
 * @return none
 */
void MainMenuHandling::scan_midi_devices()
{
	QMessageBox msgBox;
	int ret;
	
	msgBox.setIcon(QMessageBox::Critical);
	msgBox.setText("Scan MIDI Devices Will Disconnect all MIDI Devices!");
	msgBox.setInformativeText("Are you sure you want to disconnect all?");
	msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
	msgBox.setDefaultButton(QMessageBox::Cancel);
	ret = msgBox.exec();

	if (ret == QMessageBox::Yes)
	{
		// Call disconnect all or scan will do it?
		mod_synth_scan_midi_ports();
		build_midi_devices_menu();
	}	
}

/**
 * A SLOT callback activated when an input MIDI device item is clicked.
 * @param none.
 * @return none
 */
void MainMenuHandling::input_midi_devices_clicked_1()
{
	int device = input_devices[3];
	if (device < 0)
	{
		// not in use - this should not happen.
		fprintf(stderr, "MIDI input device not in use selected - 1");
		return;
	}
	
	input_midi_device_cliked(device, midi_input_devices_actions[0]->isChecked()); 	// [3]: 0 + 																							// skip scan and output label-action +
																					// skip scan and input label-action
	// Keep menu opened
	mainWindow->menu_MIDI->show();
}
void MainMenuHandling::input_midi_devices_clicked_2()
{
	int device = input_devices[4];
	if (device < 0)
	{
		// not in use - this should not happen.
		fprintf(stderr, "MIDI input device not in use selected - 2");
		return;
	}
	
	input_midi_device_cliked(device, midi_input_devices_actions[1]->isChecked());
	mainWindow->menu_MIDI->show();
}
void MainMenuHandling::input_midi_devices_clicked_3()
{
	int device = input_devices[5];
	if (device < 0)
	{
		// not in use - this should not happen.
		fprintf(stderr, "MIDI input device not in use selected - 3");
		return;
	}
	
	input_midi_device_cliked(device, midi_input_devices_actions[2]->isChecked());
	mainWindow->menu_MIDI->show();
}
void MainMenuHandling::input_midi_devices_clicked_4()
{
	int device = input_devices[6];
	if (device < 0)
	{
		// not in use - this should not happen.
		fprintf(stderr, "MIDI input device not in use selected - 4");
		return;
	}
	
	input_midi_device_cliked(device, midi_input_devices_actions[3]->isChecked());
	mainWindow->menu_MIDI->show();
}
void MainMenuHandling::input_midi_devices_clicked_5()
{
	int device = input_devices[7];
	if (device < 0)
	{
		// not in use - this should not happen.
		fprintf(stderr, "MIDI input device not in use selected - 5");
		return;
	}
	
	input_midi_device_cliked(device, midi_input_devices_actions[4]->isChecked());
	mainWindow->menu_MIDI->show();
}
void MainMenuHandling::input_midi_devices_clicked_6()
{
	int device = input_devices[8];
	if (device < 0)
	{
		// not in use - this should not happen.
		fprintf(stderr, "MIDI input device not in use selected - 6");
		return;
	}
	
	input_midi_device_cliked(device, midi_input_devices_actions[5]->isChecked());
	mainWindow->menu_MIDI->show();
}
void MainMenuHandling::input_midi_devices_clicked_7()
{
	int device = input_devices[9];
	if (device < 0)
	{
		// not in use - this should not happen.
		fprintf(stderr, "MIDI input device not in use selected - 7");
		return;
	}
	
	input_midi_device_cliked(device, midi_input_devices_actions[6]->isChecked());
	mainWindow->menu_MIDI->show();
}
void MainMenuHandling::input_midi_devices_clicked_8()
{
	int device = input_devices[10];
	if (device < 0)
	{
		// not in use - this should not happen.
		fprintf(stderr, "MIDI input device not in use selected - 8");
		return;
	}
	
	input_midi_device_cliked(input_devices[10], midi_input_devices_actions[7]->isChecked());
	mainWindow->menu_MIDI->show();
}


/**
 * A SLOT callback activated when an output MIDI device item is clicked.
 * @param none.
 * @return none
 */
void MainMenuHandling::output_midi_devices_clicked_1()
{
	int device = output_devices[2];
	if (device < 0)
	{
		// not in use - this should not happen.
		fprintf(stderr, "MIDI output device not in use selected - 1");
		return;
	}
	
	output_midi_device_cliked(device, midi_output_devices_actions[0]->isChecked());  	// [3]: 0 + skip scan and output label-action + 
	mainWindow->menu_MIDI->show();
}

void MainMenuHandling::output_midi_devices_clicked_2()
{
	int device = output_devices[3];
	if (device < 0)
	{
		// not in use - this should not happen.
		fprintf(stderr, "MIDI output device not in use selected - 2");
		return;
	}
	
	output_midi_device_cliked(device, midi_output_devices_actions[1]->isChecked());
	mainWindow->menu_MIDI->show();
}
void MainMenuHandling::output_midi_devices_clicked_3()
{
	int device = output_devices[4];
	if (device < 0)
	{
		// not in use - this should not happen.
		fprintf(stderr, "MIDI output device not in use selected - 3");
		return;
	}
	
	output_midi_device_cliked(device, midi_output_devices_actions[2]->isChecked());
	mainWindow->menu_MIDI->show();
}
void MainMenuHandling::output_midi_devices_clicked_4()
{
	int device = output_devices[5];
	if (device < 0)
	{
		// not in use - this should not happen.
		fprintf(stderr, "MIDI output device not in use selected - 4");
		return;
	}
	
	output_midi_device_cliked(device, midi_output_devices_actions[3]->isChecked());
	mainWindow->menu_MIDI->show();
}
void MainMenuHandling::output_midi_devices_clicked_5()
{
	int device = output_devices[6];
	if (device < 0)
	{
		// not in use - this should not happen.
		fprintf(stderr, "MIDI output device not in use selected - 5");
		return;
	}
	
	output_midi_device_cliked(device, midi_output_devices_actions[4]->isChecked());
	mainWindow->menu_MIDI->show();
}
void MainMenuHandling::output_midi_devices_clicked_6()
{
	int device = output_devices[7];
	if (device < 0)
	{
		// not in use - this should not happen.
		fprintf(stderr, "MIDI output device not in use selected - 6");
		return;
	}
	
	output_midi_device_cliked(device, midi_output_devices_actions[5]->isChecked());
	mainWindow->menu_MIDI->show();
}
void MainMenuHandling::output_midi_devices_clicked_7()
{
	int device = output_devices[8];
	if (device < 0)
	{
		// not in use - this should not happen.
		fprintf(stderr, "MIDI output device not in use selected - 7");
		return;
	}
	
	output_midi_device_cliked(device, midi_output_devices_actions[6]->isChecked());
	mainWindow->menu_MIDI->show();
}
void MainMenuHandling::output_midi_devices_clicked_8()
{
	int device = output_devices[9];
	if (device < 0)
	{
		// not in use - this should not happen.
		fprintf(stderr, "MIDI output device not in use selected - 8");
		return;
	}
	
	output_midi_device_cliked(device, midi_output_devices_actions[7]->isChecked());
	mainWindow->menu_MIDI->show();
}
