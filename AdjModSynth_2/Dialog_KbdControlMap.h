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

#ifndef _DIALOG_KBDCONMAP
#define _DIALOG_KBDCONMAP

#include <QDialog>

namespace Ui {
	class Dialog_KbdControlMap;
}

void updateMidiControlSequencesDataWrapper(int ch, int contNum, int val);
void updateSynthControlsDataWrapper(int module, int contId, int val);

class Dialog_KbdControlMap : public QDialog
{
	Q_OBJECT
		
public:
	explicit Dialog_KbdControlMap(QWidget *parent = 0);
	~Dialog_KbdControlMap();
	
	static Dialog_KbdControlMap *getInstance();

	void closeEvent(QCloseEvent *event);
	
	void updateMappingDisplay();
	
	void updateMidiControlSequencesData(int ch, int contNum, int val);
	void updateSynthControlsData(int module, int contId, int val);
	
	QString midiControlSequenceChannelStr;
	QString midiControlSequenceControlNumStr;
	QString midiControlSequenceValueStr;
	
	QString synthControlsModuleStr;
	QString synthControlsControlIdtr;
	QString synthControlsValueStr;
	
protected slots :
	void trainPushButtonPressed(bool val);
	void mapPushButtonPressed(bool val);
	void savePushButtonPressed(bool val);
	void openPushButtonPressed(bool val);
	void ignoreChannelChanged(int val);

  private:
	Ui::Dialog_KbdControlMap *ui;
	
	static Dialog_KbdControlMap *dialog_KbdControlMapInstance;
	
		
		
		
		
};


#endif
