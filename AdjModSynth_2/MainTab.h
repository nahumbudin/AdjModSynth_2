/**
* @file		MainTab.h
*	@author		Nahum Budin
*	@date		16-Jan-2021
*	@version	1.1 
*				1. Adding JACK parameters selection options |(Auto/Manual).
*	
*	Version	1.0		20-Oct-2019
*
*	@brief		Master Mixer ui handling.
*/

#ifndef _MAIN_TAB
#define _MAIN_TAB

#include <ui_MainWindow.h>

#include "Dialog_FluidSynthSelectProgram.h"

#include "libAdjHeartModSynth_2.h"

#include "NQgridWidget.h"
#include "NQgridWidgetItem.h"

void onRowDoubleClickWraper(int *row, int *col);

class MainTabUiHandling : public QMainWindow 
{
	Q_OBJECT

public:
	MainTabUiHandling(Ui_MainWindow *mainWind);
	
	static MainTabUiHandling *getInstance();
	
	std::vector<_soundfont_presets_data_t> *get_active_soundfont_presets();

	void setTrigers();

	void update();
	
	int initChannelsTableWidget();
	int refreshChannelsTableWidget();
	int channelSelected(int channel, int col);
	
	void onRowDoubleClick(int *raw, int *col);

	void getBanks(int sfid);

	static std::vector<_soundfont_presets_data_t> active_soundfont_presets;
	static std::vector<int> active_soundfont_bank_nums;
	static std::vector<int> loaded_soundfont_ids;
	
	int selected_channel;

	NQgridWidget *fluidChannelsSheet;

protected slots:
		
	void sketchModeClicked(bool val);
	void mapingModeClicked(bool val);
	
	void setAllChannelsToFluidSynthClicked(bool val);
	void setAllChannelsToAdjSynthClicked(bool val);
	
//	void ChannelsTableRefreshClicked(bool val);
	
	void Channel1SynthSelected(int synth);
	void Channel2SynthSelected(int synth);
	void Channel3SynthSelected(int synth);
	void Channel4SynthSelected(int synth);
	void Channel5SynthSelected(int synth);
	void Channel6SynthSelected(int synth);
	void Channel7SynthSelected(int synth);
	void Channel8SynthSelected(int synth);
	void Channel9SynthSelected(int synth);
	void Channel10SynthSelected(int synth);
	void Channel11SynthSelected(int synth);
	void Channel12SynthSelected(int synth);
	void Channel13SynthSelected(int synth);
	void Channel14SynthSelected(int synth);
	void Channel15SynthSelected(int synth);
	void Channel16SynthSelected(int synth);
	
	void savePresetClicked(bool val);
	void loadPresetClicked(bool val);
	
	void Preset1Selected(bool val);
	void Preset2Selected(bool val);
	void Preset3Selected(bool val);
	void Preset4Selected(bool val);
	void Preset5Selected(bool val);

private:
	Ui_MainWindow *mainWindow;
	
	Dialog_FluidSynthSelectProgram *dialog_FluidSynthSelectProgram;

	QComboBox* selectSynthCombo[16];

	std::vector<std::string> channelsTabHorizontableHeaders, channelsTabaleVerticalHeaders;
	std::vector<int> channelsTabRowsHeights, channelsTabaleColumnsWidth;
	
	static MainTabUiHandling *mainTabUiHandlingInstance;
	
	char mssg1[128] = { "" };
	
	int activePreset = 0;;

	QRadioButton *presetRadioButtons[_NUM_OF_PRESETS];
};



#endif
