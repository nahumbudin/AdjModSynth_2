/**
* @file		MainMenu_Audio.cpp
*	@author		Nahum Budin
*	@date		16-Jan-2021
*	@version	1.0 
*
*	@brief		Main Menu Audio actions handling.
*/

#include "MainMenue.h"

#include "../libAdjHeartModSynth_2.h"

void MainMenuHandling::update_audio_menu_params()
{
	int audio_driver = mod_synth_get_audio_driver();
	int sample_rate = mod_synth_get_audio_sample_rate();
	int block_size = mod_synth_get_audio_block_size();
	jack_server_auto_start_state = mod_synth_get_jack_auto_start_state();
	jack_server_auto_connect_audio_state = mod_synth_get_jack_auto_connect_audio_state();
	
	if (audio_driver == _AUDIO_ALSA)
	{
		audio_driver_selected_alsa = true;
		audio_driver_selected_jack = false;
	}
	else
	{
		// Fefault jack
		audio_driver_selected_alsa = false;
		audio_driver_selected_jack = true;
	}
	
	if (sample_rate == _SAMPLE_RATE_48)
	{
		sample_rate_selected_44 = false;
		sample_rate_selected_48 = true;
	}
	else
	{
		// Default 44
		sample_rate_selected_44 = true;
		sample_rate_selected_48 = false;
	}
	
	if (block_size == _AUDIO_BLOCK_SIZE_256)
	{
		audio_block_size_256_selected = true;
		audio_block_size_512_selected = false;
		audio_block_size_1024_selected = false;
	}
	else if (block_size == _AUDIO_BLOCK_SIZE_1024)
	{
		audio_block_size_256_selected = false;
		audio_block_size_512_selected = false;
		audio_block_size_1024_selected = true;
	}
	else
	{
		// Default 512
		audio_block_size_256_selected = false;
		audio_block_size_512_selected = true;
		audio_block_size_1024_selected = false;
	}
}

void MainMenuHandling::build_audio_menu()
{
	QFont font;

	return; // <<<<<<<<<<<<

	// Clear all previous content
	mainWindow->menu_Audio->clear();
	
	// Add Select audio driver label
	audio_driver_label = new QAction(tr("Audio Driver"), this);
	mainWindow->menu_Audio->addAction(audio_driver_label);
	font = audio_driver_label->font();
	font.setPointSize(14);	
	audio_driver_label->setFont(font);
	
	// Add select Jack action
	audio_select_driver_jack_action = new QAction(tr("   JACK"), this);
	mainWindow->menu_Audio->addAction(audio_select_driver_jack_action);
	audio_select_driver_jack_action->setCheckable(true);
	audio_select_driver_jack_action->setChecked(audio_driver_selected_jack);
	audio_select_driver_jack_action->setFont(font);
	connect(audio_select_driver_jack_action,
		SIGNAL(triggered()),
		this,
		SLOT(audio_driver_jack_selected()));
	
	// Add select ALSA action
	audio_select_driver_alsa_action = new QAction(tr("   ALSA"), this);
	mainWindow->menu_Audio->addAction(audio_select_driver_alsa_action);
	audio_select_driver_alsa_action->setCheckable(true);
	audio_select_driver_alsa_action->setChecked(audio_driver_selected_alsa);
	audio_select_driver_alsa_action->setFont(font);
	connect(audio_select_driver_alsa_action,
		SIGNAL(triggered()),
		this,
		SLOT(audio_driver_alsa_selected()));
	audio_select_driver_alsa_action->setEnabled(false);
	
	// Seperator
	mainWindow->menu_Audio->addSeparator();
	
	// Add Select sample-rate label
	audio_sample_rate_label = new QAction(tr("Sample Rate"), this);
	mainWindow->menu_Audio->addAction(audio_sample_rate_label);
	audio_sample_rate_label->setFont(font);
	
	// Add select 44100 action
	audio_select_sample_rate_44_action = new QAction(tr("   44.1KHz"), this);
	mainWindow->menu_Audio->addAction(audio_select_sample_rate_44_action);
	audio_select_sample_rate_44_action->setCheckable(true);
	audio_select_sample_rate_44_action->setChecked(sample_rate_selected_44);
	audio_select_sample_rate_44_action->setFont(font);
	connect(audio_select_sample_rate_44_action,
		SIGNAL(triggered()),
		this,
		SLOT(sample_rate_44_selected()));
	
	// Add select 48000 action
	audio_select_sample_rate_48_action = new QAction(tr("   48KHz"), this);
	mainWindow->menu_Audio->addAction(audio_select_sample_rate_48_action);
	audio_select_sample_rate_48_action->setCheckable(true);
	audio_select_sample_rate_48_action->setChecked(sample_rate_selected_48);
	audio_select_sample_rate_48_action->setFont(font);
	connect(audio_select_sample_rate_48_action,
		SIGNAL(triggered()),
		this,
		SLOT(sample_rate_48_selected()));
	
	
	// Seperator
	mainWindow->menu_Audio->addSeparator();
	
	// Add Select audio-block-size label
	audio_block_size_label = new QAction(tr("Block Size"), this);
	mainWindow->menu_Audio->addAction(audio_block_size_label);
	audio_block_size_label->setFont(font);
	
	// Add select 256 samples action
	audio_select_block_size_256_action = new QAction(tr("   256"), this);
	mainWindow->menu_Audio->addAction(audio_select_block_size_256_action);
	audio_select_block_size_256_action->setCheckable(true);
	audio_select_block_size_256_action->setChecked(audio_block_size_256_selected);
	audio_select_block_size_256_action->setFont(font);
	connect(audio_select_block_size_256_action,
		SIGNAL(triggered()),
		this,
		SLOT(block_size_256_selected()));
	
	// Add select 512 samples action
	audio_select_block_size_512_action = new QAction(tr("   512"), this);
	mainWindow->menu_Audio->addAction(audio_select_block_size_512_action);
	audio_select_block_size_512_action->setCheckable(true);
	audio_select_block_size_512_action->setChecked(audio_block_size_512_selected);
	audio_select_block_size_512_action->setFont(font);
	connect(audio_select_block_size_512_action,
		SIGNAL(triggered()),
		this,
		SLOT(block_size_512_selected()));
	
	// Add select 1024 samples action
	audio_select_block_size_1024_action = new QAction(tr("   1024"), this);
	mainWindow->menu_Audio->addAction(audio_select_block_size_1024_action);
	audio_select_block_size_1024_action->setCheckable(true);
	audio_select_block_size_1024_action->setChecked(audio_block_size_1024_selected);
	audio_select_block_size_1024_action->setFont(font);
	connect(audio_select_block_size_1024_action,
		SIGNAL(triggered()),
		this,
		SLOT(block_size_1024_selected()));
	
	// Add JACK server section
	if(audio_driver_selected_jack)
	{
		// Seperator
		mainWindow->menu_Audio->addSeparator();
	
		// Add JACK server label
		audio_block_size_label = new QAction(tr("JACK Server"), this);
		mainWindow->menu_Audio->addAction(audio_block_size_label);
		audio_block_size_label->setFont(font);
		
		// Add auto start action
		jack_server_auto_start_action = new QAction(tr("   Auto Start"), this);
		mainWindow->menu_Audio->addAction(jack_server_auto_start_action);
		jack_server_auto_start_action->setCheckable(true);
		jack_server_auto_start_action->setChecked(jack_server_auto_start_state);
		jack_server_auto_start_action->setFont(font);
		connect(jack_server_auto_start_action,
			SIGNAL(triggered()),
			this,
			SLOT(jack_server_auto_start_selected()));
		
		// Add auto connect action
		jack_server_auto_connect_audio_action = new QAction(tr("   Auto Connect Audio"), this);
		mainWindow->menu_Audio->addAction(jack_server_auto_connect_audio_action);
		jack_server_auto_connect_audio_action->setCheckable(true);
		jack_server_auto_connect_audio_action->setChecked(jack_server_auto_connect_audio_action);
		jack_server_auto_connect_audio_action->setFont(font);
		connect(jack_server_auto_connect_audio_action,
			SIGNAL(triggered()),
			this,
			SLOT(jack_server_auto_connect_selected()));
	}
	
}


void MainMenuHandling::audio_driver_jack_selected()
{
	mod_synth_set_audio_driver(_AUDIO_JACK);
	update_audio_menu_params();
	build_audio_menu();
	// Keep menu open
	mainWindow->menu_Audio->show();
}

void MainMenuHandling::audio_driver_alsa_selected()
{
	mod_synth_set_audio_driver(_AUDIO_ALSA);
	update_audio_menu_params();
	build_audio_menu();
	// Keep menu open
	mainWindow->menu_Audio->show();	
}

void MainMenuHandling::sample_rate_44_selected()
{
	mod_synth_set_audio_sample_rate(_SAMPLE_RATE_44);
	
	update_audio_menu_params();
	build_audio_menu();
	// Keep menu open
	mainWindow->menu_Audio->show();
	
}

void MainMenuHandling::sample_rate_48_selected()
{
	mod_synth_set_audio_sample_rate(_SAMPLE_RATE_48);
	
	update_audio_menu_params();
	build_audio_menu();
	// Keep menu open
	mainWindow->menu_Audio->show();
	
}


void MainMenuHandling::block_size_256_selected()
{
	mod_synth_set_audio_block_size(_AUDIO_BLOCK_SIZE_256);
	
	update_audio_menu_params();
	build_audio_menu();
	// Keep menu open
	mainWindow->menu_Audio->show();
	
}

void MainMenuHandling::block_size_512_selected()
{
	mod_synth_set_audio_block_size(_AUDIO_BLOCK_SIZE_512);
	
	update_audio_menu_params();
	build_audio_menu();
	// Keep menu open
	mainWindow->menu_Audio->show();
	
}

void MainMenuHandling::block_size_1024_selected()
{
	mod_synth_set_audio_block_size(_AUDIO_BLOCK_SIZE_1024);	
	
	update_audio_menu_params();
	build_audio_menu();
	// Keep menu open
	mainWindow->menu_Audio->show();
}


void MainMenuHandling::jack_server_auto_start_selected()
{
	mod_synth_set_jack_auto_start_state(jack_server_auto_start_action->isChecked());
	
	update_audio_menu_params();
	build_audio_menu();
	// Keep menu open
	mainWindow->menu_Audio->show();
}

void MainMenuHandling::jack_server_auto_connect_selected()
{
	mod_synth_set_jack_auto_connect_audio_state(jack_server_auto_connect_audio_action->isChecked());
	
	update_audio_menu_params();
	build_audio_menu();
	// Keep menu open
	mainWindow->menu_Audio->show();
}