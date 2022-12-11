/**
* @file		AdjModSynth.cpp
*	@author		Nahum Budin
*	@Date		17-Jan-2021
*	@version	1.1 
*				1. Adding Control Widgets control through Knob and Slider
*				2. Adding local midi devices handling (not through jack connection kit)
*				3. Adding local JACK clients handling (not through jack connection kit)
*				4. Seperating JACK auto connection of audio and midi
*				5. Adding start/stop audio
*	
*	Version	1.0		16-Oct-2019
*
*	History:\n
*/

#include <QApplication>
#include <qprocess.h>

#include <unistd.h> // for nice()

#include "libAdjHeartModSynth_2.h"

#include "MainWindow.h"
#include "MainTab.h"
#include "OscilatorsTab.h"
#include "NoiseMsoTab.h"
#include "JackConfigurationFile.h"

#include "Dialog_MidiClients.h"

#include "Log.h"

using namespace std;


void exit_handler(void)
{
	//	int err;

	printf("Program terminated! Press any key to exit.");
	
	// Disable screen saver
	system("xset s blank");
	system("xset s on");
	system("xset -dpms");
	
	system("pactl unload-module module-jack-sink");
	system("pactl unload-module module-jack-source");
	
	//	err = errno;
	//	getchar();
}

int main(int argc, char *argv[])
{
	// Set clock control and priority	
	/*
	* https://github.com/DavidM42/rpi-cpu.gov
	*
	* install: wget https://raw.githubusercontent.com/DavidM42/rpi-cpu.gov/master/install.sh && sudo chmod +x ./install.sh && sudo ./install.sh --nochown && sudo rm install.sh
	*
	**/
	system("cpu.gov -g performance");
	// Disable screen saver
	system("xset s noblank");
	system("xset s off");
	system("xset -dpms");
	

	nice(20);

	setbuf(stderr, NULL);
	atexit(exit_handler);

	// Debuger
//	FILELog::ReportingLevel() = FILELog::FromString("DEBUG4");
	FILE* pFile = fopen("AdjHeartRaspiFlSynth2_0.log", "a");
	Output2FILE::Stream() = pFile;
//	FILE_LOG(logINFO) << "...";
	
    // Start QjackCtl
	QProcess process;
	QProcess processes[_MAX_NUM_OF_PROCESSES];
/*
	if ((mod_synth_get_audio_driver() == _AUDIO_JACK) && mod_synth_get_jack_auto_start_state())
	{
		process.start("qjackctl");
		system("pactl load-module module-jack-sink channels=2");
		system("pactl load-module module-jack-source");
		system("pacmd set-default-sink jack_out");
	}

	JackConfigurationFile *configFile = new JackConfigurationFile("/home/pi/AdjHeartModSynth_2/JackConfig.txt"); // TODO: get path from configuration
	configFile->executeConfiguration(processes);
*/
	mod_synth_init();
	mod_synth_start_audio();
	
	mod_synth_init_bt_services();

	mod_synth_init_serial_port_services(16);	// port 16 ttyUSB0

	mod_synth_init_midi_services();
	mod_synth_connect_bt_to_midi();

	// Do not change the order of this code		
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	w.update();
	return a.exec();
}
