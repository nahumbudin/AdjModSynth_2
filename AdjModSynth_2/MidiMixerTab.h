/**
* @file		MidiMixerTab.h
*	@author		Nahum Budin
*	@date		16-Jan-2021
*	@version	1.1 
*				1. Adding Control Widgets control through Knob and Slider
*	
*	Version	1.0		10-Jan-2020
*
*	@brief		Midi Mixer ui handling.
*/

#ifndef _MIDI_MIXER_TAB
#define _MIDI_MIXER_TAB

#include <ui_MainWindow.h>

class MidiMixerTabUiHandling : public QMainWindow 
{
	Q_OBJECT

public :
	MidiMixerTabUiHandling(Ui_MainWindow *mainWind);
	
	static MidiMixerTabUiHandling *getInstance();
	
	void setTrigers();

	void setWidgetsInfoMap();

	void update();
	
	void enableChannelKnobs(int chan, bool enLev, bool enPan, bool enSnd);
	
protected slots :
	void levelChangedChannel_1(int lev);
	void levelChangedChannel_2(int lev);
	void levelChangedChannel_3(int lev);
	void levelChangedChannel_4(int lev);
	void levelChangedChannel_5(int lev);
	void levelChangedChannel_6(int lev);
	void levelChangedChannel_7(int lev);
	void levelChangedChannel_8(int lev);
	void levelChangedChannel_9(int lev);
	void levelChangedChannel_10(int lev);
	void levelChangedChannel_11(int lev);
	void levelChangedChannel_12(int lev);
	void levelChangedChannel_13(int lev);
	void levelChangedChannel_14(int lev);
	void levelChangedChannel_15(int lev);
	void levelChangedChannel_16(int lev);
	void levelChangedAll(int lev);
	
	void panChangedChannel_1(int pan);
	void panChangedChannel_2(int pan);
	void panChangedChannel_3(int pan);
	void panChangedChannel_4(int pan);
	void panChangedChannel_5(int pan);
	void panChangedChannel_6(int pan);
	void panChangedChannel_7(int pan);
	void panChangedChannel_8(int pan);
	void panChangedChannel_9(int pan);
	void panChangedChannel_10(int pan);
	void panChangedChannel_11(int pan);
	void panChangedChannel_12(int pan);
	void panChangedChannel_13(int pan);
	void panChangedChannel_14(int pan);
	void panChangedChannel_15(int pan);
	void panChangedChannel_16(int pan);
	void panChangedAll(int pan);
	
	void sendChangedChannel_1(int snd);
	void sendChangedChannel_2(int snd);
	void sendChangedChannel_3(int snd);
	void sendChangedChannel_4(int snd);
	void sendChangedChannel_5(int snd);
	void sendChangedChannel_6(int snd);
	void sendChangedChannel_7(int snd);
	void sendChangedChannel_8(int snd);
	void sendChangedChannel_9(int snd);
	void sendChangedChannel_10(int snd);
	void sendChangedChannel_11(int snd);
	void sendChangedChannel_12(int snd);
	void sendChangedChannel_13(int snd);
	void sendChangedChannel_14(int snd);
	void sendChangedChannel_15(int snd);
	void sendChangedChannel_16(int snd);
	void sendChangedAll(int snd);
	
	
private :
	Ui_MainWindow *mainWindow;	
	
	static MidiMixerTabUiHandling *midiMixerTabUiHandlingInstance;
	
	char mssg1[128] = { "" };	
};


#endif

