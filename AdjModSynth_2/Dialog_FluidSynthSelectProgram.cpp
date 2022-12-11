/**
* @file		FluidSynthSelectProgramDialog.cpp
*	@author		Nahum Budin
*	@date		26-Oct-2019
*	@version	1.0
*
*	@brief		Used for selecting a program from the available
*				programs in the loaded sounfonts banks.
*
*/

#include <QDialog>
#include <QString>
#include "libAdjHeartModSynth_2.h"
#include "MainTab.h"
#include "ui_Dialog_FluidSynthSelectProgram.h"
#include "Dialog_FluidSynthSelectProgram.h"

#include "defs.h"

Dialog_FluidSynthSelectProgram *Dialog_FluidSynthSelectProgram::dialog_FluidSynthSelectProgramInstance = NULL;

/**
*   @brief  A wrapper used far callback activation of the soundFontSelected function.
*   @param  row a pointer to an integer varaiable holding the selected row number
*   @param  col a pointer to an integer varaiable holding the selected column number
*   @return 0 if OK -1 otherwise
*/
void soundFontSelectedWrapper(int *row, int *col)
{
	Dialog_FluidSynthSelectProgram::getInstance()->soundFontSelected(row, col);
}

/**
*   @brief  A wrapper used far callback activation of the bankSelected function.
*   @param  row a pointer to an integer varaiable holding the selected row number
*   @param  col a pointer to an integer varaiable holding the selected column number
*   @return 0 if OK -1 otherwise
*/
void bankSelectedWrapper(int *row, int *col)
{
	Dialog_FluidSynthSelectProgram::getInstance()->bankSelected(row, col);
}

/**
*   @brief  A wrapper used far callback activation of the programSelected function.
*   @param  row a pointer to an integer varaiable holding the selected row number
*   @param  col a pointer to an integer varaiable holding the selected column number
*   @return 0 if OK -1 otherwise
*/
void programSelectedWrapper(int *row, int *col)
{
	Dialog_FluidSynthSelectProgram::getInstance()->programSelected(row, col);
}

/** Constructor */
Dialog_FluidSynthSelectProgram::Dialog_FluidSynthSelectProgram(QWidget *parent)
	: QDialog(parent),
	 ui(new Ui::Dialog_FluidSynthSelectProgram)
{
	ui->setupUi(this);
	dialog_FluidSynthSelectProgramInstance = this;
	fluidSelectSoundFontSheet = NULL;
	
	setOpenedBy(_SET_PATCH_DIALOG_OPEND_BY_NONE);

	connect(ui->buttonBox_dialog_selectProgram, 
			SIGNAL(accepted()), 
			this, 
			SLOT(programSelectionDone()));

	connect(ui->buttonBox_dialog_selectProgram, 
			SIGNAL(rejected()), 
			this, 
			SLOT(programSelectionCancell()));
	
	connect(ui->buttonBox_dialog_selectProgram, 
			SIGNAL(clicked(QAbstractButton*)), 
			this, 
			SLOT(programSelectionOther(QAbstractButton*)));
}

Dialog_FluidSynthSelectProgram::~Dialog_FluidSynthSelectProgram()
{

}

/**
*   @brief  Returns a pointer to the Dialog_FluidSynthSelectProgram object instance.
*   @param  none
*   @return a pointer to the Dialog_FluidSynthSelectProgram object instance
*/
Dialog_FluidSynthSelectProgram *Dialog_FluidSynthSelectProgram::getInstance()
{
	return dialog_FluidSynthSelectProgramInstance;
}

void Dialog_FluidSynthSelectProgram::closeEvent(QCloseEvent *event)
{

}

/**
*   @brief  Set the Id of who opened the dialog.
*   @param  ob	Id of who opened the dialog _SET_PATCH_DIALOG_OPEND_BY_NONE,
*   _SET_PATCH_DIALOG_OPEND_BY_MAIN, _SET_PATCH_DIALOG_OPEND_BY_PROGRAM_1 - 
*   _SET_PATCH_DIALOG_OPEND_BY_PROGRAM_16
*   @return a pointer to the Dialog_FluidSynthSelectProgram object instance
*/
void Dialog_FluidSynthSelectProgram::setOpenedBy(int ob)
{
	opened_by = ob;
}

/**
*   @brief  Return the Id of who opened the dialog.
*   @param  none
*   @return Id of who opened the dialog _SET_PATCH_DIALOG_OPEND_BY_NONE,
*   _SET_PATCH_DIALOG_OPEND_BY_MAIN, _SET_PATCH_DIALOG_OPEND_BY_PROGRAM_1 - 
*   _SET_PATCH_DIALOG_OPEND_BY_PROGRAM_16
*/
int Dialog_FluidSynthSelectProgram::getOpenedBy()
{
	return opened_by;
}

/**
*   @brief  Updates the SoundFonts table.
*   @param  sf_names a pointer to a vector of _sondfont_disp_data_t data elements
*   @return void
*/
void Dialog_FluidSynthSelectProgram::updateSoundfontsTable(std::vector<_sondfont_disp_data_t> *sf_names)
{
	QTableWidgetItem *item;
	std::vector<std::string> sondFontsTabaleHorizontalHeaders, soundFontsTabaleVerticalHeaders;
	std::vector<int> soundFontsTabaleRowsHeights, soundFontsTabaleColumnsWidth;

	if (sf_names == NULL)
	{
		return;
	}

	// Create a banks table - columns headers
	sondFontsTabaleHorizontalHeaders.push_back("SoundFont");
	sondFontsTabaleHorizontalHeaders.push_back("SFID");
	soundFontsTabaleColumnsWidth.push_back(165);
	soundFontsTabaleColumnsWidth.push_back(50);

	// Clear the rows headers and set rows height
	for (int i = 0; i < sf_names->size(); i++)
	{
		soundFontsTabaleVerticalHeaders.push_back("");
		soundFontsTabaleRowsHeights.push_back(18);
	}

	fluidSelectSoundFontSheet = new NQgridWidget(sf_names->size(), 2);

	fluidSelectSoundFontSheet->registerOnClickEvent(&soundFontSelectedWrapper);

	fluidSelectSoundFontSheet->getTableWidget()->setToolTip("Loaded SoundFonts");
	fluidSelectSoundFontSheet->getTableWidget()->setFont(QFont("Helvetica", 11));
	fluidSelectSoundFontSheet->getTableWidget()->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
	// Set table headers and cells sizes
	fluidSelectSoundFontSheet->setHorizontalHeaders(&sondFontsTabaleHorizontalHeaders);
	fluidSelectSoundFontSheet->setVerticalHeaders(&soundFontsTabaleVerticalHeaders);
	fluidSelectSoundFontSheet->setRowColsSize(&soundFontsTabaleRowsHeights, &soundFontsTabaleColumnsWidth);

	for (int r = 0; r < sf_names->size(); r++)
	{
		// Fill table data
		fluidSelectSoundFontSheet->setTabItemStringValue(r, 0, QString::fromStdString(sf_names->at(r).name));
		fluidSelectSoundFontSheet->setTabItemIntegerValue(r, 1, sf_names->at(r).sfid);
		
		fluidSelectSoundFontSheet->getTableWidget()->setEditTriggers(QAbstractItemView::NoEditTriggers);
		
//		item = fluidSelectSoundFontSheet->getTableWidget()->item(r, 0);
		// Make cells not editable.
//		if (item)
//		{
//			item->setFlags(item->flags() & ~Qt::ItemIsEditable);
//		}
	}
	// Make the table scrollable
	ui->scrollArea_dialogFluidSelectProgram_soundfonts->setWidget(fluidSelectSoundFontSheet);

	fluidSelectSoundFontSheet->show();
}

/**
*   @brief  Updates the soundfont banks table.
*   @param  none
*   @return void
*/
void Dialog_FluidSynthSelectProgram::updateBanksTable()
{
	QTableWidgetItem *item;
	std::vector<std::string> banksTabaleHorizontalHeaders, banksTabaleVerticalHeaders;
	std::vector<int> banksTabaleRowsHeights, banksTabaleColumnsWidth;

	// Create banks table
	banksTabaleHorizontalHeaders.push_back("Bank");
	banksTabaleColumnsWidth.push_back(60);

	for (int i = 0; i < MainTabUiHandling::active_soundfont_bank_nums.size(); i++)
	{
		banksTabaleVerticalHeaders.push_back("");
		banksTabaleRowsHeights.push_back(18);
	}

	fluidSelectProgramBanksSheet = new NQgridWidget(MainTabUiHandling::active_soundfont_bank_nums.size(), 1);
	fluidSelectProgramBanksSheet->registerOnClickEvent(&bankSelectedWrapper);
	fluidSelectProgramBanksSheet->getTableWidget()->setToolTip("SoundFont Banks");
	fluidSelectProgramBanksSheet->getTableWidget()->setFont(QFont("Helvetica", 11));
	fluidSelectProgramBanksSheet->getTableWidget()->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

	//	fluidSelectProgramBanksSheet->setParent(ui->widget_dialogFluidSelectProgram_banks);
	fluidSelectProgramBanksSheet->setHorizontalHeaders(&banksTabaleHorizontalHeaders);
	fluidSelectProgramBanksSheet->setVerticalHeaders(&banksTabaleVerticalHeaders);
	fluidSelectProgramBanksSheet->setRowColsSize(&banksTabaleRowsHeights, &banksTabaleColumnsWidth);

	fluidSelectProgramBanksSheet->getTableWidget()->setEditTriggers(QAbstractItemView::NoEditTriggers);
	
	for (int r = 0; r < MainTabUiHandling::active_soundfont_bank_nums.size(); r++)
	{
		fluidSelectProgramBanksSheet->setTabItemIntegerValue(r, 0, MainTabUiHandling::active_soundfont_bank_nums.at(r));
//		item = fluidSelectProgramBanksSheet->getTableWidget()->item(r, 0);
//		if (item)
//		{
//			item->setFlags(item->flags() & ~Qt::ItemIsEditable);
//		}
	}

	ui->scrollArea_dialogFluidSelectProgram_banks->setWidget(fluidSelectProgramBanksSheet);

	fluidSelectProgramBanksSheet->show();
}

/**
*   @brief  Updates selected soundfont bank presets table.
*   @param  bank bank number
*	@param	soundfontid soundfont id number
*   @return void
*/
void Dialog_FluidSynthSelectProgram::updateBankPresetsTable(int bank, int soundfontid)
{
	std::vector<std::string> bankPresetsTabaleHorizontalHeaders, bankPresetsTabaleVerticalHeaders;
	std::vector<int> bankPresetsTabaleRowsHeights, bankPresetsTabaleColumnsWidth;
	std::vector<_soundfont_presets_data_t> active_soundfont_presets;
	QTableWidgetItem item;

	// Build a vector of all the presets that belongs to the selected soundfont and bank
	for(int i = 0 ; i < MainTabUiHandling::getInstance()->get_active_soundfont_presets()->size() ; i++)
	{
		if ((MainTabUiHandling::getInstance()->get_active_soundfont_presets()->at(i).banknum == bank) &&
			(MainTabUiHandling::getInstance()->get_active_soundfont_presets()->at(i).soundFontId == soundfontid))
		{
			active_soundfont_presets.push_back(MainTabUiHandling::getInstance()->get_active_soundfont_presets()->at(i));
		}
	}

	bankPresetsTabaleHorizontalHeaders.push_back("Prog");
	bankPresetsTabaleHorizontalHeaders.push_back("Name");
	bankPresetsTabaleHorizontalHeaders.push_back("SFID");
	bankPresetsTabaleHorizontalHeaders.push_back("SoundFont");

	for (int i = 0; i < active_soundfont_presets.size(); i++)
	{
		bankPresetsTabaleVerticalHeaders.push_back("");
		bankPresetsTabaleRowsHeights.push_back(16);
	}

	bankPresetsTabaleColumnsWidth.push_back(50);
	bankPresetsTabaleColumnsWidth.push_back(200);
	bankPresetsTabaleColumnsWidth.push_back(50);
	bankPresetsTabaleColumnsWidth.push_back(150);
	
	fluidBankPresetsSheet = new NQgridWidget(active_soundfont_presets.size(), 4);
	fluidBankPresetsSheet->registerOnClickEvent(&programSelectedWrapper);
	fluidBankPresetsSheet->getTableWidget()->setToolTip("FluidSynth selected sound font and bank presets");
	fluidBankPresetsSheet->getTableWidget()->setFont(QFont("Helvetica", 10));
	fluidBankPresetsSheet->getTableWidget()->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
	fluidBankPresetsSheet->getTableWidget()->setSizeAdjustPolicy(QTableWidget::AdjustToContents);
	fluidBankPresetsSheet->getTableWidget()->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	fluidBankPresetsSheet->getTableWidget()->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

	fluidBankPresetsSheet->setHorizontalHeaders(&bankPresetsTabaleHorizontalHeaders);
	fluidBankPresetsSheet->setVerticalHeaders(&bankPresetsTabaleVerticalHeaders);
	fluidBankPresetsSheet->setRowColsSize(&bankPresetsTabaleRowsHeights, &bankPresetsTabaleColumnsWidth);
	
	fluidBankPresetsSheet->getTableWidget()->setEditTriggers(QAbstractItemView::NoEditTriggers);

	for (int i = 0; i < active_soundfont_presets.size(); i++)
	{
		fluidBankPresetsSheet->setTabItemIntegerValue(i, 0, active_soundfont_presets.at(i).program);
		fluidBankPresetsSheet->setTabItemStringValue(i, 1, active_soundfont_presets.at(i).presetname);
		fluidBankPresetsSheet->setTabItemIntegerValue(i, 2, active_soundfont_presets.at(i).soundFontId);
		fluidBankPresetsSheet->setTabItemStringValue(i, 3, 
			QString::fromStdString(mod_synth_get_fluid_synth_soundfont_id_name(active_soundfont_presets.at(i).soundFontId)));
	}
	   
	ui->scrollArea_dialogFluidSelectProgram_presets->setWidget(fluidBankPresetsSheet);
	fluidBankPresetsSheet->show();

}

/**
*   @brief  Called when the user cliks the OK button.
*   @param  bank bank number
*	@param	soundfontid soundfont id number
*   @return void
*/
void Dialog_FluidSynthSelectProgram::programSelectionDone()
{
	// Select and close the dialog
	this->close();
	mod_synth_set_fluid_synth_program_select(MainTabUiHandling::getInstance()->selected_channel,
		selected_soundfont_id,
		selected_bank,
		selected_program);
	MainTabUiHandling::getInstance()->refreshChannelsTableWidget();
}

/**
*   @brief  Called when the user cliks the Cancel button.
*   @param  none
*   @return void
*/
void Dialog_FluidSynthSelectProgram::programSelectionCancell()
{
	// Close the dialog
	this->close();
}

/**
*   @brief  Called when the user cliks the Apply button.
*   @param  button pressed button
*   @return void
*/
void Dialog_FluidSynthSelectProgram::programSelectionOther(QAbstractButton *button)
{
	if (button == ui->buttonBox_dialog_selectProgram->button(QDialogButtonBox::Apply))
	{
		// Select and do not close the dialog
		mod_synth_set_fluid_synth_program_select(MainTabUiHandling::getInstance()->selected_channel, // 0-15
			selected_soundfont_id,
			selected_bank,
			selected_program);
		MainTabUiHandling::getInstance()->refreshChannelsTableWidget();
	}
}

void Dialog_FluidSynthSelectProgram::update()
{
	
}

/**
*   @brief  Called when a soundfont is selectes.
*   @param  row a pointer to an integer varaiable holding the selected row number
*   @param  col a pointer to an integer varaiable holding the selected column number
*   @return void
*/
void Dialog_FluidSynthSelectProgram::soundFontSelected(int *row, int *col)
{
	selected_soundfont_id = fluidSelectSoundFontSheet->getTableWidget()->item(*row, 1)->text().toInt();
	
	MainTabUiHandling::getInstance()->getBanks(selected_soundfont_id);
	updateBanksTable();	
}

/**
*   @brief  Called when a bank is selectes.
*   @param  row a pointer to an integer varaiable holding the selected row number
*   @param  col a pointer to an integer varaiable holding the selected column number
*   @return void
*/
void Dialog_FluidSynthSelectProgram::bankSelected(int *row, int *col)
{
	selected_bank = fluidSelectProgramBanksSheet->getTableWidget()->item(*row, 0)->text().toInt();

	updateBankPresetsTable(selected_bank, selected_soundfont_id);
}

/**
*   @brief  Called when a program is selectes.
*   @param  row a pointer to an integer varaiable holding the selected row number
*   @param  col a pointer to an integer varaiable holding the selected column number
*   @return void
*/
void Dialog_FluidSynthSelectProgram::programSelected(int *row, int *col)
{
	selected_program = fluidBankPresetsSheet->getTableWidget()->item(*row, 0)->text().toInt();
}

