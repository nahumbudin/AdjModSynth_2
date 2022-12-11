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

#include "MainWindow.h"
#include "MainTab.h"
#include "libAdjHeartModSynth_2.h"

#include <QFileDialog>
#include <QMessageBox>

MainTabUiHandling *MainTabUiHandling::mainTabUiHandlingInstance = NULL;

/* Holds al the active soundfonts presets data */
std::vector<_soundfont_presets_data_t> MainTabUiHandling::active_soundfont_presets;
/* Holds the active soundfont banks numbers */
std::vector<int> MainTabUiHandling::active_soundfont_bank_nums;
/* Holds the loaded soundfonts id numbers */
std::vector<int> MainTabUiHandling::loaded_soundfont_ids;
/* Holds the soundfont names and associated id numbers */
std::vector<_sondfont_disp_data_t> sound_fonts_names_dispaly_data;

/* Holds the names of the FluidSynth channels selected programs */
std::vector<std::string> fluid_synth_channels_programs;
/* Holds the names of the AdjSynth channels selected patches */
std::vector<std::string> fluid_synth_channels_patches;

/**
*   @brief  A wrapper used far callback activation of the onRowDoubleClick function.
*   @param  row a pointer to an integer varaiable holding the selected row number
*   @param  col a pointer to an integer varaiable holding the selected column number
*   @return 0 if OK -1 otherwise
*/
void onRowDoubleClickWraper(int *row, int *col)
{
	MainTabUiHandling::getInstance()->onRowDoubleClick(row, col);
}

MainTabUiHandling::MainTabUiHandling(Ui_MainWindow *mainWind)
{
	mainWindow = mainWind;
	
	// Init channels grid widget
	initChannelsTableWidget();
	mainWindow->groupBox_fluidTab_channels->setDisabled(true);

	dialog_FluidSynthSelectProgram = new Dialog_FluidSynthSelectProgram(this);
	dialog_FluidSynthSelectProgram->move(10, 150);

	mainWindow->groupBox_MainTab_presets->setDisabled(true);
	
	mainTabUiHandlingInstance = this;
	
	presetRadioButtons[0] = mainWindow->radioButton_mainTab_preset_0;
	presetRadioButtons[1] = mainWindow->radioButton_mainTab_preset_1;
	presetRadioButtons[2] = mainWindow->radioButton_mainTab_preset_2;
	presetRadioButtons[3] = mainWindow->radioButton_mainTab_preset_3;
	presetRadioButtons[4] = mainWindow->radioButton_mainTab_preset_4;
	
	presetRadioButtons[0]->setToolTip(tr("Preset 1: not loaded."));
	presetRadioButtons[1]->setToolTip(tr("Preset 2: not loaded."));
	presetRadioButtons[2]->setToolTip(tr("Preset 3: not loaded."));
	presetRadioButtons[3]->setToolTip(tr("Preset 4: not loaded."));
	presetRadioButtons[4]->setToolTip(tr("Preset 5: not loaded."));
}

/**
*   @brief  Returns the instance of this class.
*   @param  none
*   @return the instance of this class
*/
MainTabUiHandling *MainTabUiHandling::getInstance()
{
	return mainTabUiHandlingInstance;
}

void MainTabUiHandling::setTrigers()
{
	connect(mainWindow->radioButton_midiModeMapping,
		SIGNAL(clicked(bool)),
		this,
		SLOT(mapingModeClicked(bool)));

	connect(mainWindow->radioButton_midiModeSketch,
		SIGNAL(clicked(bool)),
		this,
		SLOT(sketchModeClicked(bool)));
	
	connect(mainWindow->pushButton_setAllChannelsFluidSynth,
		SIGNAL(clicked(bool)),
		this,
		SLOT(setAllChannelsToFluidSynthClicked(bool)));
	
	connect(mainWindow->pushButton_setAllChannelsAdjSynth,
		SIGNAL(clicked(bool)),
		this,
		SLOT(setAllChannelsToAdjSynthClicked(bool)));
	
	connect(mainWindow->pushButton_mainTab_savePreset,
		SIGNAL(clicked(bool)),
		this,
		SLOT(savePresetClicked(bool)));
	
	connect(mainWindow->pushButton_mainTab_loadPreset,
		SIGNAL(clicked(bool)),
		this,
		SLOT(loadPresetClicked(bool)));
	
	connect(mainWindow->radioButton_mainTab_preset_0,
		SIGNAL(clicked(bool)),
		this,
		SLOT(Preset1Selected(bool)));
	
	connect(mainWindow->radioButton_mainTab_preset_1,
		SIGNAL(clicked(bool)),
		this,
		SLOT(Preset2Selected(bool)));
	
	connect(mainWindow->radioButton_mainTab_preset_2,
		SIGNAL(clicked(bool)),
		this,
		SLOT(Preset3Selected(bool)));
	
	connect(mainWindow->radioButton_mainTab_preset_3,
		SIGNAL(clicked(bool)),
		this,
		SLOT(Preset4Selected(bool)));
	
	connect(mainWindow->radioButton_mainTab_preset_4,
		SIGNAL(clicked(bool)),
		this,
		SLOT(Preset5Selected(bool)));
}

void MainTabUiHandling::update()
{
	
}

/**
*   @brief  Returns a pointer to the vector of _soundfont_presets_data_t elements holding presets data.
*   @param  none
*   @return a pointer to the vector of _soundfont_presets_data_t elements holding presets data.
*/
std::vector<_soundfont_presets_data_t> *MainTabUiHandling::get_active_soundfont_presets()
{
	return &active_soundfont_presets;
}

/**
*   @brief  Init the channels table.
*   @param  none
*   @return 0
*/
int MainTabUiHandling::initChannelsTableWidget()
{
	int width;
	
	channelsTabHorizontableHeaders.push_back("Channel");
	channelsTabHorizontableHeaders.push_back("Synth");
	channelsTabHorizontableHeaders.push_back("Bank");
	channelsTabHorizontableHeaders.push_back("Prog");
	channelsTabHorizontableHeaders.push_back("Name");
	channelsTabHorizontableHeaders.push_back("SFID");
	channelsTabHorizontableHeaders.push_back("SoundFont");

	for (int i = 0; i < 16; i++)
	{
		channelsTabaleVerticalHeaders.push_back("");
		channelsTabRowsHeights.push_back(14);
	}

	channelsTabaleColumnsWidth.push_back(75);
	channelsTabaleColumnsWidth.push_back(95);
	channelsTabaleColumnsWidth.push_back(50);
	channelsTabaleColumnsWidth.push_back(50);
	channelsTabaleColumnsWidth.push_back(220);
	channelsTabaleColumnsWidth.push_back(50);
	channelsTabaleColumnsWidth.push_back(150);

	fluidChannelsSheet = new NQgridWidget(16, 7);
//	fluidChannelsSheet->getTableWidget()->setToolTip("FluidSynth active preset");
	fluidChannelsSheet->getTableWidget()->setFont(QFont("Helvetica", 10));
	fluidChannelsSheet->getTableWidget()->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
	fluidChannelsSheet->getTableWidget()->setSizeAdjustPolicy(QTableWidget::AdjustToContents);
	fluidChannelsSheet->getTableWidget()->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	fluidChannelsSheet->getTableWidget()->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

	fluidChannelsSheet->setHorizontalHeaders(&channelsTabHorizontableHeaders);
	fluidChannelsSheet->setVerticalHeaders(&channelsTabaleVerticalHeaders);
	fluidChannelsSheet->setRowColsSize(&channelsTabRowsHeights, &channelsTabaleColumnsWidth);
	
	fluidChannelsSheet->getTableWidget()->setEditTriggers(QAbstractItemView::NoEditTriggers);
	
	// Set all cells not editable
	QTableWidgetItem *item;
	for (int r = 0; r <= fluidChannelsSheet->getTableWidget()->rowCount(); r++)
	{
//		for (int c = 0; c <= fluidChannelsSheet->getTableWidget()->columnCount(); c++)
//		{
//			item = fluidChannelsSheet->getTableWidget()->item(r, c);
//			if (item)
//			{
//				item->setBackgroundColor(QColor(255, 236, 23));
//			}
//		}
		
		selectSynthCombo[r] = new QComboBox();
		width = channelsTabaleColumnsWidth.at(1);
		selectSynthCombo[r]->view()->setMinimumWidth(width - 2);
		selectSynthCombo[r]->addItem("None");
		selectSynthCombo[r]->addItem("FluidSynth");
		selectSynthCombo[r]->addItem("AdjSynth");
		fluidChannelsSheet->getTableWidget()->setCellWidget(r, 1, selectSynthCombo[r]);
		switch (r)
		{
			case (0):
				QObject::connect(selectSynthCombo[r], SIGNAL(currentIndexChanged(int)), this, SLOT(Channel1SynthSelected(int)));
				break;
				
			case (1):
				QObject::connect(selectSynthCombo[r], SIGNAL(currentIndexChanged(int)), this, SLOT(Channel2SynthSelected(int)));
				break;
				
			case (2):
				QObject::connect(selectSynthCombo[r], SIGNAL(currentIndexChanged(int)), this, SLOT(Channel3SynthSelected(int)));
				break;
				
			case (3):
				QObject::connect(selectSynthCombo[r], SIGNAL(currentIndexChanged(int)), this, SLOT(Channel4SynthSelected(int)));
				break;
				
			case (4):
				QObject::connect(selectSynthCombo[r], SIGNAL(currentIndexChanged(int)), this, SLOT(Channel5SynthSelected(int)));
				break;
				
			case (5):
				QObject::connect(selectSynthCombo[r], SIGNAL(currentIndexChanged(int)), this, SLOT(Channel6SynthSelected(int)));
				break;
				
			case (6):
				QObject::connect(selectSynthCombo[r], SIGNAL(currentIndexChanged(int)), this, SLOT(Channel7SynthSelected(int)));
				break;
				
			case (7):
				QObject::connect(selectSynthCombo[r], SIGNAL(currentIndexChanged(int)), this, SLOT(Channel8SynthSelected(int)));
				break;
				
			case (8):
				QObject::connect(selectSynthCombo[r], SIGNAL(currentIndexChanged(int)), this, SLOT(Channel9SynthSelected(int)));
				break;
				
			case (9):
				QObject::connect(selectSynthCombo[r], SIGNAL(currentIndexChanged(int)), this, SLOT(Channel10SynthSelected(int)));
				break;
				
			case (10):
				QObject::connect(selectSynthCombo[r], SIGNAL(currentIndexChanged(int)), this, SLOT(Channel11SynthSelected(int)));
				break;
				
			case (11):
				QObject::connect(selectSynthCombo[r], SIGNAL(currentIndexChanged(int)), this, SLOT(Channel12SynthSelected(int)));
				break;
				
			case (12):
				QObject::connect(selectSynthCombo[r], SIGNAL(currentIndexChanged(int)), this, SLOT(Channel13SynthSelected(int)));
				break;
				
			case (13):
				QObject::connect(selectSynthCombo[r], SIGNAL(currentIndexChanged(int)), this, SLOT(Channel14SynthSelected(int)));
				break;
				
			case (14):
				QObject::connect(selectSynthCombo[r], SIGNAL(currentIndexChanged(int)), this, SLOT(Channel15SynthSelected(int)));
				break;
				
			case (15):
				QObject::connect(selectSynthCombo[r], SIGNAL(currentIndexChanged(int)), this, SLOT(Channel16SynthSelected(int)));
				break;
			}

//			selectSynthCombo[r]->blockSignals(true);
	}

	fluidChannelsSheet->registerOnDoubleClickEvent(&onRowDoubleClickWraper);

	mainWindow->scrollArea_fluidTab_programSelect->setWidget(fluidChannelsSheet);
	
	// Set Channels current presets  data
	refreshChannelsTableWidget();

	fluidChannelsSheet->show();

	return 0;
}

/**
*   @brief  refresh the channels table.
*   @param  none
*   @return 0
*/
int MainTabUiHandling::refreshChannelsTableWidget()
{	
	QComboBox *comboSynthType;
	int type, row_count;

	row_count = fluidChannelsSheet->getTableWidget()->rowCount();

	// Set Channels current presets  data
	for(int i = 0 ; i < row_count ; i++)
	{
		fluidChannelsSheet->setTabItemIntegerValue(i, 0, i + 1);
		type = mod_synth_get_midi_channel_synth(i);
		selectSynthCombo[i]->blockSignals(true);
		selectSynthCombo[i]->setCurrentIndex(type);
		if (type == _MIDI_CHAN_ASSIGNED_SYNTH_FLUID)
		{
			fluidChannelsSheet->setTabItemIntegerValue(i, 2, mod_synth_get_fluid_synth_channel_bank(i));
			fluidChannelsSheet->setTabItemIntegerValue(i, 3, mod_synth_get_fluid_synth_channel_program(i) + 1);
			fluidChannelsSheet->setTabItemStringValue(i, 4, QString::fromStdString(mod_synth_get_fluid_synth_channel_preset_name(i)));
			fluidChannelsSheet->setTabItemIntegerValue(i, 5, mod_synth_get_fluid_synth_channel_sfont_id(i));
			fluidChannelsSheet->setTabItemStringValue(i, 6, QString::fromStdString(mod_synth_get_fluid_synth_channel_preset_soundfont_name(i)));
		}
		else if (type == _MIDI_CHAN_ASSIGNED_SYNTH_ADJ)
		{
			fluidChannelsSheet->setTabItemStringValue(i, 2, "");
			fluidChannelsSheet->setTabItemStringValue(i, 3, "");		
			
			fluidChannelsSheet->setTabItemStringValue(i, 4, 
				QString::fromStdString(mod_synth_get_program_patch_name(i))); 
			
			fluidChannelsSheet->setTabItemStringValue(i, 5, "");
			fluidChannelsSheet->setTabItemStringValue(i, 6, "");
		}
		else
		{
			fluidChannelsSheet->setTabItemStringValue(i, 2, "");
			fluidChannelsSheet->setTabItemStringValue(i, 3, "");					
			fluidChannelsSheet->setTabItemStringValue(i, 4, "");			
			fluidChannelsSheet->setTabItemStringValue(i, 5, "");
			fluidChannelsSheet->setTabItemStringValue(i, 6, "");
		}
		
		selectSynthCombo[i]->blockSignals(false);
	}	

	fluidChannelsSheet->show();

	return 0;
}

/**
*   @brief  called when a channel was selected.
*   @param  channel selected channel
*   @return 0
*/
int MainTabUiHandling::channelSelected(int channel, int col)
{
	int num_of_loaded_soundFonts, res, count, i, j;
	bool bank_exist = false;
	bool sfid_exist = false;
	_sondfont_disp_data_t soundfonts_name_dat;

	selected_channel = channel;

	if (col == 1)
	{
		// Set assigned synthesizer		
		
	}
	else
	{
		// Not synth allocation selected - select program
		if(mod_synth_get_midi_channel_synth(selected_channel) == _MIDI_CHAN_ASSIGNED_SYNTH_FLUID)
		{
			// FluidSynth - select program
			loaded_soundfont_ids.clear();
			active_soundfont_bank_nums.clear();
			active_soundfont_presets.clear();
			sound_fonts_names_dispaly_data.clear();
			// Get the presets of all fluid soundfont files
			res = mod_synth_get_fluid_synth_loaded_soundfonts_presets(&MainTabUiHandling::active_soundfont_presets);

			// Look for soundfonts ids
			loaded_soundfont_ids.push_back(active_soundfont_presets.at(0).soundFontId);
			soundfonts_name_dat.sfid = active_soundfont_presets.at(0).soundFontId;
			soundfonts_name_dat.name = mod_synth_get_fluid_synth_soundfont_id_name(soundfonts_name_dat.sfid);
			sound_fonts_names_dispaly_data.push_back(soundfonts_name_dat);
			for (i = 1; i < active_soundfont_presets.size(); i++)
			{
				// Go over all loaded sounfonts - load only once
				sfid_exist = false;
				for (j = 0; j < loaded_soundfont_ids.size() && !sfid_exist; j++)
				{
//					sfid_exist = false;
					if (active_soundfont_presets.at(i).soundFontId == loaded_soundfont_ids.at(j))
					{
						// Already loaded
						sfid_exist = true;
					}
				}

				if (!sfid_exist)
				{
					loaded_soundfont_ids.push_back(active_soundfont_presets.at(i).soundFontId);
					soundfonts_name_dat.sfid = active_soundfont_presets.at(i).soundFontId;
					soundfonts_name_dat.name = mod_synth_get_fluid_synth_soundfont_id_name(soundfonts_name_dat.sfid);
					sound_fonts_names_dispaly_data.push_back(soundfonts_name_dat);
				}
			}
			
			dialog_FluidSynthSelectProgram->show();

			dialog_FluidSynthSelectProgram->updateSoundfontsTable(&sound_fonts_names_dispaly_data);
		}
		else if(mod_synth_get_midi_channel_synth(selected_channel) == _MIDI_CHAN_ASSIGNED_SYNTH_ADJ)
		{
			// AdjSynth - select patch
			dialog_FluidSynthSelectProgram->setOpenedBy(selected_channel);
			QString fileName = QFileDialog::getOpenFileName(this,
				tr("Open Patch File"),
				_ADJ_DEFAULT_PATCHES_DIR,
				tr("Settings (*.xml *.XML);;All Files (*)"));

			if (!fileName.isEmpty())
			{
				res = mod_synth_open_adj_synth_patch_file(fileName.toStdString(), selected_channel);
				if (res == 0)
				{
					// Patch file selected
					fluidChannelsSheet->setTabItemStringValue(selected_channel, 4, 
						QString::fromStdString(MainWindow::getInstance()->removeFileExtention
						(MainWindow::getInstance()->getFileName(fileName.toStdString()))));
				}
			}
			
			refreshChannelsTableWidget();
//			MainWindow::getInstance()->update();
		}
	}

	//	dialog_FluidSynthSelectProgram->show();

	//	dialog_FluidSynthSelectProgram->updateSoundfontsTable(&sound_fonts_names_dispaly_data);

		fluidChannelsSheet->getTableWidget()->clearSelection();
	
	return 0;
}

/**
*   @brief  Activated when a cell is doubleclicked.
*   @param  none
*   @return void
*/
void MainTabUiHandling::onRowDoubleClick(int *raw, int *col)
{
	channelSelected(*raw, *col);
}

/**
*   @brief  Get the bank of the provided soundfont id and push tham into 
*	 the active _soundfont_bank_nums vector.
*   @param  sfid soundfont id number
*   @return void
*/
void MainTabUiHandling::getBanks(int sfid)
{
	int i, j;
	bool bank_exist = false;

	active_soundfont_bank_nums.clear();
	
	for (i = 0; i < active_soundfont_presets.size(); i++)
	{
		// Look for the 1st apperance of preset of the given soundfont id.
		if(active_soundfont_presets.at(i).soundFontId == sfid)
		{
			active_soundfont_bank_nums.push_back(active_soundfont_presets.at(i).banknum);
			break;
		}
	}

	if (active_soundfont_bank_nums.size() == 0)
	{
		// No bank found.
		return;
	}
	// Start from the next element
	i++;
	
	for (i; i < active_soundfont_presets.size(); i++)
	{
		if (active_soundfont_presets.at(i).soundFontId == sfid)
		{
			// Refer only to the selected soundfont id banks.
			for(j = 0 ; j < active_soundfont_bank_nums.size() ; j++)
			{
				bank_exist = false;
				if (active_soundfont_presets.at(i).banknum == active_soundfont_bank_nums.at(j))
				{
					// This bank number was alreaddy registered.
					bank_exist = true;
				}
			}

			if (!bank_exist)
			{
				// Push a new bank number
				active_soundfont_bank_nums.push_back(active_soundfont_presets.at(i).banknum);
			}
		}
	}
}

/**
 * A SLOT callback activated when the set midi-mode non-mapping is selected.
 * @param val radio-button status.
 * @return none
 */
void MainTabUiHandling::sketchModeClicked(bool val)
{  
	if (val)
	{
		mainWindow->groupBox_fluidTab_channels->setEnabled(false);
		mainWindow->actionOpen_AdjSyntPatch->setEnabled(true);
		mainWindow->actionSave_AdjSynthPatch->setEnabled(true);
		mainWindow->actionOpen_AdjSynthSettings->setEnabled(true);
		mainWindow->actionSave_AdjSynthSettings->setEnabled(true);
		mainWindow->menuSketch->setEnabled(true);
		mainWindow->label_mainTab_Sketch_1->setEnabled(true);
		mainWindow->lineEdit_MainTab_SketchName_1->setEnabled(true);
		mainWindow->label_mainTab_Sketch_2->setEnabled(true);
		mainWindow->lineEdit_MainTab_SketchName_2->setEnabled(true);
		mainWindow->label_mainTab_Sketch_3->setEnabled(true);
		mainWindow->lineEdit_MainTab_SketchName_3->setEnabled(true);
		mainWindow->pushButton_setAllChannelsAdjSynth->setEnabled(false);
		mainWindow->pushButton_setAllChannelsFluidSynth->setEnabled(false);
		mainWindow->pushButton_mainTab_savePreset->setEnabled(false);
		mainWindow->pushButton_mainTab_loadPreset->setEnabled(false);
		mainWindow->groupBox_MainTab_presets->setEnabled(false);
		mod_synth_set_active_midi_mapping_mode(_MIDI_MAPPING_MODE_SKETCH);
		
		MainWindow::getInstance()->setSketchRadiobuttonsEnable(true);
	}
}

/**
 * A SLOT callback activated when the set midi-mode mapping is selected.
 * @param val radio-button status.
 * @return none
 */
void MainTabUiHandling::mapingModeClicked(bool val)
{
	if (val)
	{
		mainWindow->groupBox_fluidTab_channels->setEnabled(true);
		mainWindow->actionOpen_AdjSyntPatch->setEnabled(false);
		mainWindow->actionSave_AdjSynthPatch->setEnabled(false);
		mainWindow->actionOpen_AdjSynthSettings->setEnabled(false);
		mainWindow->actionSave_AdjSynthSettings->setEnabled(false);
		mainWindow->menuSketch->setEnabled(false);
		mainWindow->label_mainTab_Sketch_1->setEnabled(false);
		mainWindow->lineEdit_MainTab_SketchName_1->setEnabled(false);
		mainWindow->label_mainTab_Sketch_2->setEnabled(false);
		mainWindow->lineEdit_MainTab_SketchName_2->setEnabled(false);
		mainWindow->label_mainTab_Sketch_3->setEnabled(false);
		mainWindow->lineEdit_MainTab_SketchName_3->setEnabled(false);
		mainWindow->pushButton_setAllChannelsAdjSynth->setEnabled(true);
		mainWindow->pushButton_setAllChannelsFluidSynth->setEnabled(true);
		mainWindow->pushButton_mainTab_savePreset->setEnabled(true);
		mainWindow->pushButton_mainTab_loadPreset->setEnabled(true);
		mainWindow->groupBox_MainTab_presets->setEnabled(true);
		//		ui->pushButton_midiPatchProg_1->setEnabled(true);
		mod_synth_set_active_midi_mapping_mode(_MIDI_MAPPING_MODE_MAPPING);
		
		MainWindow::getInstance()->setSketchRadiobuttonsEnable(false);
	}
}

/**
* A SLOT callback activated when the Set All Channels to FluidSynth buton is pressed.
* @param the new push botton value.
* @return void
*/
void MainTabUiHandling::setAllChannelsToFluidSynthClicked(bool val)
{
	int channel;
	
	mainWindow->pushButton_setAllChannelsFluidSynth->blockSignals(true);
	mainWindow->pushButton_setAllChannelsFluidSynth->setChecked(false);
	mainWindow->pushButton_setAllChannelsFluidSynth->blockSignals(false);
	
	for (channel = 0; channel < 16; channel++)
	{
		selectSynthCombo[channel]->setCurrentIndex(_MIDI_CHAN_ASSIGNED_SYNTH_FLUID);			
	}
	
	refreshChannelsTableWidget();
}

/**
* A SLOT callback activated when the Set All Channels to AdjSynth buton is pressed.
* @param the new push botton value.
* @return void
*/
void MainTabUiHandling::setAllChannelsToAdjSynthClicked(bool val)
{
	int channel;
	
	mainWindow->pushButton_setAllChannelsAdjSynth->blockSignals(true);
	mainWindow->pushButton_setAllChannelsAdjSynth->setChecked(false);
	mainWindow->pushButton_setAllChannelsAdjSynth->blockSignals(false);
	
	for (channel = 0; channel < 16; channel++)
	{
		selectSynthCombo[channel]->setCurrentIndex(_MIDI_CHAN_ASSIGNED_SYNTH_ADJ);			
	}
	
	refreshChannelsTableWidget();
}

/**
* A SLOT callback activated when the fluid_synth channels table refresh buton is pressed.
* @param the new checkbox value.
* @return none
*/
/*
void MainTabUiHandling::ChannelsTableRefreshClicked(bool val)
{
	if (val)
	{
		mainWindow->pushButton_fluidTab_refersh->blockSignals(true);
		mainWindow->pushButton_fluidTab_refersh->setChecked(false);
		mainWindow->pushButton_fluidTab_refersh->blockSignals(false);

		refreshChannelsTableWidget();
	}
}
*/
/**
 * A SLOT callback activated when  channel 1 associated selected synth is changed.
 * @param synth	synthesizer type id.
 * @return none
 */
void MainTabUiHandling::Channel1SynthSelected(int synth)
{
	mod_synth_set_midi_channel_synth(0, synth);
	refreshChannelsTableWidget();
	MidiMixerTabUiHandling::getInstance()->update();
}

/**
 * A SLOT callback activated when  channel 2 associated selected synth is changed.
 * @param synth	synthesizer type id.
 * @return none
 */
void MainTabUiHandling::Channel2SynthSelected(int synth)
{
	mod_synth_set_midi_channel_synth(1, synth);
	refreshChannelsTableWidget();
	MidiMixerTabUiHandling::getInstance()->update();
}

/**
 * A SLOT callback activated when  channel 3 associated selected synth is changed.
 * @param synth	synthesizer type id.
 * @return none
 */
void MainTabUiHandling::Channel3SynthSelected(int synth)
{
	mod_synth_set_midi_channel_synth(2, synth);
	refreshChannelsTableWidget();
	MidiMixerTabUiHandling::getInstance()->update();
}

/**
 * A SLOT callback activated when  channel 4 associated selected synth is changed.
 * @param synth	synthesizer type id.
 * @return none
 */
void MainTabUiHandling::Channel4SynthSelected(int synth)
{
	mod_synth_set_midi_channel_synth(3, synth);
	refreshChannelsTableWidget();
	MidiMixerTabUiHandling::getInstance()->update();
}

/**
 * A SLOT callback activated when  channel 5 associated selected synth is changed.
 * @param synth	synthesizer type id.
 * @return none
 */
void MainTabUiHandling::Channel5SynthSelected(int synth)
{
	mod_synth_set_midi_channel_synth(4, synth);
	refreshChannelsTableWidget();
	MidiMixerTabUiHandling::getInstance()->update();
}

/**
 * A SLOT callback activated when  channel 6 associated selected synth is changed.
 * @param synth	synthesizer type id.
 * @return none
 */
void MainTabUiHandling::Channel6SynthSelected(int synth)
{
	mod_synth_set_midi_channel_synth(5, synth);
	refreshChannelsTableWidget();
	MidiMixerTabUiHandling::getInstance()->update();
}

/**
 * A SLOT callback activated when  channel 7 associated selected synth is changed.
 * @param synth	synthesizer type id.
 * @return none
 */
void MainTabUiHandling::Channel7SynthSelected(int synth)
{
	mod_synth_set_midi_channel_synth(6, synth);
	refreshChannelsTableWidget();
	MidiMixerTabUiHandling::getInstance()->update();
}

/**
 * A SLOT callback activated when  channel 8 associated selected synth is changed.
 * @param synth	synthesizer type id.
 * @return none
 */
void MainTabUiHandling::Channel8SynthSelected(int synth)
{
	mod_synth_set_midi_channel_synth(7, synth);
	refreshChannelsTableWidget();
	MidiMixerTabUiHandling::getInstance()->update();
}

/**
 * A SLOT callback activated when  channel 9 associated selected synth is changed.
 * @param synth	synthesizer type id.
 * @return none
 */
void MainTabUiHandling::Channel9SynthSelected(int synth)
{
	mod_synth_set_midi_channel_synth(8, synth);
	refreshChannelsTableWidget();
	MidiMixerTabUiHandling::getInstance()->update();
}

/**
 * A SLOT callback activated when  channel 10 associated selected synth is changed.
 * @param synth	synthesizer type id.
 * @return none
 */
void MainTabUiHandling::Channel10SynthSelected(int synth)
{
	mod_synth_set_midi_channel_synth(9, synth);
	refreshChannelsTableWidget();
	MidiMixerTabUiHandling::getInstance()->update();
}

/**
 * A SLOT callback activated when  channel 11 associated selected synth is changed.
 * @param thesynth	synthesizer type id.
 * @return none
 */
void MainTabUiHandling::Channel11SynthSelected(int synth)
{
	mod_synth_set_midi_channel_synth(10, synth);
	refreshChannelsTableWidget();
	MidiMixerTabUiHandling::getInstance()->update();
}

/**
 * A SLOT callback activated when  channel 12 associated selected synth is changed.
 * @param synth	synthesizer type id.
 * @return none
 */
void MainTabUiHandling::Channel12SynthSelected(int synth)
{
	mod_synth_set_midi_channel_synth(11, synth);
	refreshChannelsTableWidget();
	MidiMixerTabUiHandling::getInstance()->update();
}

/**
 * A SLOT callback activated when  channel 13 associated selected synth is changed.
 * @param synth	synthesizer type id.
 * @return none
 */
void MainTabUiHandling::Channel13SynthSelected(int synth)
{
	mod_synth_set_midi_channel_synth(12, synth);
	refreshChannelsTableWidget();
	MidiMixerTabUiHandling::getInstance()->update();
}

/**
 * A SLOT callback activated when  channel 14 associated selected synth is changed.
 * @param synth	synthesizer type id.
 * @return none
 */
void MainTabUiHandling::Channel14SynthSelected(int synth)
{
	mod_synth_set_midi_channel_synth(13, synth);
	refreshChannelsTableWidget();
	MidiMixerTabUiHandling::getInstance()->update();
}

/**
 * A SLOT callback activated when  channel 15 associated selected synth is changed.
 * @param synth	synthesizer type id.
 * @return none
 */
void MainTabUiHandling::Channel15SynthSelected(int synth)
{
	mod_synth_set_midi_channel_synth(14, synth);
	refreshChannelsTableWidget();
	MidiMixerTabUiHandling::getInstance()->update();
}

/**
 * A SLOT callback activated when  channel 16 associated selected synth is changed.
 * @param synth	synthesizer type id.
 * @return none
 */
void MainTabUiHandling::Channel16SynthSelected(int synth)
{
	mod_synth_set_midi_channel_synth(15, synth);
	refreshChannelsTableWidget();
	MidiMixerTabUiHandling::getInstance()->update();
}

/**
 * A SLOT callback activated when the save preset push button is clicked.
 * @param the new checkbox state.
 * @return none
 */
void MainTabUiHandling::savePresetClicked(bool val)
{	
	if (val)
	{
		QString presetName = QFileDialog::getSaveFileName(this,
			tr("Save Preset File"),
			"/home/pi/AdjHeartModSynth/Presets",
			tr("Presets (*.xml *.XML);;All Files (*)"));

		if (!presetName.isEmpty())
		{
			mod_synth_save_mod_synth_preset_file(presetName.toStdString());
		}
		
		mainWindow->pushButton_mainTab_savePreset->setEnabled(false);
		mainWindow->pushButton_mainTab_savePreset->setChecked(false);
		mainWindow->pushButton_mainTab_savePreset->setEnabled(true);
	}
}

/**
 * A SLOT callback activated when the load preset push button is clicked.
 * @param the new checkbox state.
 * @return none
 */
void MainTabUiHandling::loadPresetClicked(bool val)
{
	if (val)
	{
		QString presetName = QFileDialog::getOpenFileName(this,
			tr("Load Preset ") + QString::number(activePreset+1),
			"/home/pi/AdjHeartModSynth/Presets",
			tr("Presets (*.xml *.XML);;All Files (*)"));

		if (!presetName.isEmpty())
		{
			mod_synth_open_mod_synth_preset_file(presetName.toStdString(), activePreset);
		}
		
		presetRadioButtons[activePreset]->setToolTip(QString::fromStdString(*mod_synth_get_preset_summary_string(activePreset)));
		
		refreshChannelsTableWidget();
		MidiMixerTabUiHandling::getInstance()->update();
		FluidSynthUiHandling::getInstance()->update();
		EffectsTabUiHandling::getInstance()->update();
		
		
		mainWindow->pushButton_mainTab_loadPreset->setEnabled(false);
		mainWindow->pushButton_mainTab_loadPreset->setChecked(false);
		mainWindow->pushButton_mainTab_loadPreset->setEnabled(true);
	}
}

/**
 * A SLOT callback activated when the Preset 1 radio button is clicked.
 * @param the new radio button state.
 * @return none
 */
void MainTabUiHandling::Preset1Selected(bool val)
{
	if (val)
	{
		activePreset = 0;
		mod_synth_set_mod_synth_active_preset_num(0);
		
		mainWindow->radioButton_mainTab_preset_0->setToolTip(QString::fromStdString(*mod_synth_get_preset_summary_string(0)));
		
		refreshChannelsTableWidget();
		MidiMixerTabUiHandling::getInstance()->update();
		FluidSynthUiHandling::getInstance()->update();
		EffectsTabUiHandling::getInstance()->update();
	}
}

/**
 * A SLOT callback activated when the Preset 2 radio button is clicked.
 * @param the new radio button state.
 * @return none
 */
void MainTabUiHandling::Preset2Selected(bool val)
{
	if (val)
	{
		activePreset = 1;
		mod_synth_set_mod_synth_active_preset_num(1);
		refreshChannelsTableWidget();
		
		mainWindow->radioButton_mainTab_preset_1->setToolTip(QString::fromStdString(*mod_synth_get_preset_summary_string(1)));
		
		MidiMixerTabUiHandling::getInstance()->update();
		FluidSynthUiHandling::getInstance()->update();
		EffectsTabUiHandling::getInstance()->update();
	}
}

/**
 * A SLOT callback activated when the Preset 3 radio button is clicked.
 * @param the new radio button state.
 * @return none
 */
void MainTabUiHandling::Preset3Selected(bool val)
{
	if (val)
	{
		activePreset = 2;
		mod_synth_set_mod_synth_active_preset_num(2);
		refreshChannelsTableWidget();
		
		mainWindow->radioButton_mainTab_preset_2->setToolTip(QString::fromStdString(*mod_synth_get_preset_summary_string(2)));
		
		MidiMixerTabUiHandling::getInstance()->update();
		FluidSynthUiHandling::getInstance()->update();
		EffectsTabUiHandling::getInstance()->update();
	}
}

/**
 * A SLOT callback activated when the Preset 4 radio button is clicked.
 * @param the new radio button state.
 * @return none
 */
void MainTabUiHandling::Preset4Selected(bool val)
{
	if (val)
	{
		activePreset = 3;
		mod_synth_set_mod_synth_active_preset_num(3);
		refreshChannelsTableWidget();
		
		mainWindow->radioButton_mainTab_preset_3->setToolTip(QString::fromStdString(*mod_synth_get_preset_summary_string(3)));
		
		MidiMixerTabUiHandling::getInstance()->update();
		FluidSynthUiHandling::getInstance()->update();
		EffectsTabUiHandling::getInstance()->update();
	}
}
	
	/**
 * A SLOT callback activated when the Preset 5 radio button is clicked.
 * @param the new radio button state.
 * @return none
 */
void MainTabUiHandling::Preset5Selected(bool val)
{
	if (val)
	{
		activePreset = 4;
		mod_synth_set_mod_synth_active_preset_num(4);
		refreshChannelsTableWidget();
		
		mainWindow->radioButton_mainTab_preset_4->setToolTip(QString::fromStdString(*mod_synth_get_preset_summary_string(4)));
		
		MidiMixerTabUiHandling::getInstance()->update();
		FluidSynthUiHandling::getInstance()->update();
		EffectsTabUiHandling::getInstance()->update();
	}
}

