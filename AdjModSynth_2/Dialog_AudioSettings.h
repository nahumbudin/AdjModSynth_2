/**
* @file		Dialog_AudioSettings.h
*	@author		Nahum Budin
*	@date		17-Jan-2021
*	@version	1.0
*
*	@brief		Used for selecting JACK parameters
*
*/

#ifndef _DIALOG_AUDIO_SETTINGS
#define _DIALOG_AUDIO_SETTINGS

#include <QDialog>
#include <QDialogButtonBox>

namespace Ui
{
	class Dialog_AudioSettings;
}

class Dialog_AudioSettings : public QDialog
{
	Q_OBJECT

  public:
	explicit Dialog_AudioSettings(QWidget *parent = 0);
	~Dialog_AudioSettings();

	void closeEvent(QCloseEvent *event);

	void update();

  protected slots:
	void driverJackChanged(bool val);
	void driverAlsaChanged(bool val);
	void manualModeChanged(bool val);
	void autoModeChanged(bool val);
	void autoStartChanged(bool val);
	void autoConnectChanged(bool val);
	void sampleRateChanged(int val);
	void blockSizeChanged(int val);

	void audioSettingsAccepted();

	void audioSettingsCanceled();

  private:
	Ui::Dialog_AudioSettings *ui;

	int driver, mode, blockSize, sampleRate;
	bool autoStart, autoConnect;

	QList<QString> stringSamplRatesList;
	QList<QString> stringBlockSizeList;

	static Dialog_AudioSettings *dialog_AudioSettingsInstance;
};

#endif
