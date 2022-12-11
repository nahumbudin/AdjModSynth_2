/**
* @file		Dialog_FluidSynthSelectProgram.h
*	@author		Nahum Budin
*	@date		26-Oct-2019
*	@version	1.0
*
*	@brief		Used for selecting a program from the available
*				programs in the loaded sounfonts banks.
*
*/

#ifndef _DIALOG_FS_SELPROG
#define _DIALOG_FS_SELPROG

#include <QDialog>
#include <QDialogButtonBox>


#include "NQgridWidget.h"

namespace Ui {
class Dialog_FluidSynthSelectProgram;
}

void soundFontSelectedWrapper(int *row, int *col);
void bankSelectedWrapper(int *row, int *col);
void programSelectedWrapper(int *row, int *col);

class Dialog_FluidSynthSelectProgram : public QDialog
{
	Q_OBJECT

public:
	explicit Dialog_FluidSynthSelectProgram(QWidget *parent = 0);
	~Dialog_FluidSynthSelectProgram();

	static Dialog_FluidSynthSelectProgram *getInstance();

	void closeEvent(QCloseEvent *event);
	
	void setOpenedBy(int ob);
	int getOpenedBy();

	void updateSoundfontsTable(std::vector<_sondfont_disp_data_t> *sf_names);
	void updateBanksTable();
	void updateBankPresetsTable(int bank, int soundfontid);
	
	void update();

	void soundFontSelected(int *row, int *col);
	void bankSelected(int *row, int *col);
	void programSelected(int *row, int *col);

protected slots:
	void programSelectionDone();
	void programSelectionCancell();
	void programSelectionOther(QAbstractButton *button);
	

private:
	Ui::Dialog_FluidSynthSelectProgram *ui;

	static Dialog_FluidSynthSelectProgram *dialog_FluidSynthSelectProgramInstance;

	NQgridWidget *fluidSelectProgramBanksSheet;
	NQgridWidget *fluidSelectSoundFontSheet;
	NQgridWidget *fluidBankPresetsSheet;

	std::vector<std::string> presetsTabaleHorizontalHeaders, presetsTabaleVerticalHeaders;
	std::vector<int> presetsTabaleRowsHeights, presetsTabaleColumnsWidth;

	int selected_soundfont_id;
	int selected_bank;
	int selected_program;
	
	int opened_by;
};


#endif

