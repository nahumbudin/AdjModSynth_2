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

#include "MainWindow.h"
#include "MidiMixerTab.h"
#include "libAdjHeartModSynth_2.h"

MidiMixerTabUiHandling *MidiMixerTabUiHandling::midiMixerTabUiHandlingInstance = NULL;

MidiMixerTabUiHandling::MidiMixerTabUiHandling(Ui_MainWindow *mainWind)
{
	mainWindow = mainWind;
	
	midiMixerTabUiHandlingInstance = this;
}

/**
*   @brief  Returns the instance of this class.
*   @param  none
*   @return the instance of this class
*/
MidiMixerTabUiHandling *MidiMixerTabUiHandling::getInstance()
{
	return midiMixerTabUiHandlingInstance;
}

void MidiMixerTabUiHandling::setTrigers()
{
	connect(mainWindow->dial_MidiMixerLevelChan_1,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(levelChangedChannel_1(int)));
	
	connect(mainWindow->dial_MidiMixerLevelChan_2,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(levelChangedChannel_2(int)));
	
	connect(mainWindow->dial_MidiMixerLevelChan_3,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(levelChangedChannel_3(int)));
	
	connect(mainWindow->dial_MidiMixerLevelChan_4,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(levelChangedChannel_4(int)));
	
	connect(mainWindow->dial_MidiMixerLevelChan_5,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(levelChangedChannel_5(int)));
	
	connect(mainWindow->dial_MidiMixerLevelChan_6,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(levelChangedChannel_6(int)));
	
	connect(mainWindow->dial_MidiMixerLevelChan_7,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(levelChangedChannel_7(int)));
	
	connect(mainWindow->dial_MidiMixerLevelChan_8,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(levelChangedChannel_8(int)));
	
	connect(mainWindow->dial_MidiMixerLevelChan_9,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(levelChangedChannel_9(int)));
	
	connect(mainWindow->dial_MidiMixerLevelChan_10,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(levelChangedChannel_10(int)));
	
	connect(mainWindow->dial_MidiMixerLevelChan_11,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(levelChangedChannel_11(int)));
	
	connect(mainWindow->dial_MidiMixerLevelChan_12,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(levelChangedChannel_12(int)));
	
	connect(mainWindow->dial_MidiMixerLevelChan_13,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(levelChangedChannel_13(int)));
	
	connect(mainWindow->dial_MidiMixerLevelChan_14,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(levelChangedChannel_14(int)));
	
	connect(mainWindow->dial_MidiMixerLevelChan_15,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(levelChangedChannel_15(int)));
	
	connect(mainWindow->dial_MidiMixerLevelChan_16,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(levelChangedChannel_16(int)));
	
	connect(mainWindow->dial_MidiMixerLevelSetAll,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(levelChangedAll(int)));
	
	
	connect(mainWindow->dial_MidiMixerPanChan_1,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(panChangedChannel_1(int)));
	
	connect(mainWindow->dial_MidiMixerPanChan_2,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(panChangedChannel_2(int)));
	
	connect(mainWindow->dial_MidiMixerPanChan_3,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(panChangedChannel_3(int)));
	
	connect(mainWindow->dial_MidiMixerPanChan_4,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(panChangedChannel_4(int)));
	
	connect(mainWindow->dial_MidiMixerPanChan_5,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(panChangedChannel_5(int)));
	
	connect(mainWindow->dial_MidiMixerPanChan_6,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(panChangedChannel_6(int)));
	
	connect(mainWindow->dial_MidiMixerPanChan_7,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(panChangedChannel_7(int)));
	
	connect(mainWindow->dial_MidiMixerPanChan_8,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(panChangedChannel_8(int)));
	
	connect(mainWindow->dial_MidiMixerPanChan_9,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(panChangedChannel_9(int)));
	
	connect(mainWindow->dial_MidiMixerPanChan_10,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(panChangedChannel_10(int)));
	
	connect(mainWindow->dial_MidiMixerPanChan_11,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(panChangedChannel_11(int)));
	
	connect(mainWindow->dial_MidiMixerPanChan_12,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(panChangedChannel_12(int)));
	
	connect(mainWindow->dial_MidiMixerPanChan_13,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(panChangedChannel_13(int)));
	
	connect(mainWindow->dial_MidiMixerPanChan_14,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(panChangedChannel_14(int)));
	
	connect(mainWindow->dial_MidiMixerPanChan_15,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(panChangedChannel_15(int)));
	
	connect(mainWindow->dial_MidiMixerPanChan_16,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(panChangedChannel_16(int)));
	
	connect(mainWindow->dial_MidiMixerPanSetAll,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(panChangedAll(int)));
	
	
	connect(mainWindow->dial_MidiMixerSendChan_1,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(sendChangedChannel_1(int)));
	
	connect(mainWindow->dial_MidiMixerSendChan_2,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(sendChangedChannel_2(int)));
	
	connect(mainWindow->dial_MidiMixerSendChan_3,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(sendChangedChannel_3(int)));
	
	connect(mainWindow->dial_MidiMixerSendChan_4,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(sendChangedChannel_4(int)));
	
	connect(mainWindow->dial_MidiMixerSendChan_5,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(sendChangedChannel_5(int)));
	
	connect(mainWindow->dial_MidiMixerSendChan_6,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(sendChangedChannel_6(int)));
	
	connect(mainWindow->dial_MidiMixerSendChan_7,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(sendChangedChannel_7(int)));
	
	connect(mainWindow->dial_MidiMixerSendChan_8,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(sendChangedChannel_8(int)));
	
	connect(mainWindow->dial_MidiMixerSendChan_9,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(sendChangedChannel_9(int)));
	
	connect(mainWindow->dial_MidiMixerSendChan_10,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(sendChangedChannel_10(int)));
	
	connect(mainWindow->dial_MidiMixerSendChan_11,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(sendChangedChannel_11(int)));
	
	connect(mainWindow->dial_MidiMixerSendChan_12,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(sendChangedChannel_12(int)));
	
	connect(mainWindow->dial_MidiMixerSendChan_13,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(sendChangedChannel_13(int)));
	
	connect(mainWindow->dial_MidiMixerSendChan_14,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(sendChangedChannel_14(int)));
	
	connect(mainWindow->dial_MidiMixerSendChan_15,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(sendChangedChannel_15(int)));
	
	connect(mainWindow->dial_MidiMixerSendChan_16,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(sendChangedChannel_16(int)));	
	
	connect(mainWindow->dial_MidiMixerSendSetAll,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(sendChangedAll(int)));	
	
	
}

void MidiMixerTabUiHandling::setWidgetsInfoMap()
{
	// Widgets Ids
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MidiMixerLevelChan_1, _MIDI_MIXER_1_EVENT * 10000 + _MIXER_CHAN_1_LEVEL);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MidiMixerLevelChan_2, _MIDI_MIXER_1_EVENT * 10000 + _MIXER_CHAN_2_LEVEL);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MidiMixerLevelChan_3, _MIDI_MIXER_1_EVENT * 10000 + _MIXER_CHAN_3_LEVEL);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MidiMixerLevelChan_4, _MIDI_MIXER_1_EVENT * 10000 + _MIXER_CHAN_4_LEVEL);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MidiMixerLevelChan_5, _MIDI_MIXER_1_EVENT * 10000 + _MIXER_CHAN_5_LEVEL);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MidiMixerLevelChan_6, _MIDI_MIXER_1_EVENT * 10000 + _MIXER_CHAN_6_LEVEL);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MidiMixerLevelChan_7, _MIDI_MIXER_1_EVENT * 10000 + _MIXER_CHAN_7_LEVEL);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MidiMixerLevelChan_8, _MIDI_MIXER_1_EVENT * 10000 + _MIXER_CHAN_8_LEVEL);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MidiMixerLevelChan_9, _MIDI_MIXER_1_EVENT * 10000 + _MIXER_CHAN_9_LEVEL);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MidiMixerLevelChan_10, _MIDI_MIXER_1_EVENT * 10000 + _MIXER_CHAN_10_LEVEL);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MidiMixerLevelChan_11, _MIDI_MIXER_1_EVENT * 10000 + _MIXER_CHAN_11_LEVEL);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MidiMixerLevelChan_12, _MIDI_MIXER_1_EVENT * 10000 + _MIXER_CHAN_12_LEVEL);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MidiMixerLevelChan_13, _MIDI_MIXER_1_EVENT * 10000 + _MIXER_CHAN_13_LEVEL);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MidiMixerLevelChan_14, _MIDI_MIXER_1_EVENT * 10000 + _MIXER_CHAN_14_LEVEL);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MidiMixerLevelChan_15, _MIDI_MIXER_1_EVENT * 10000 + _MIXER_CHAN_15_LEVEL);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MidiMixerLevelChan_16, _MIDI_MIXER_1_EVENT * 10000 + _MIXER_CHAN_16_LEVEL);

	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MidiMixerPanChan_1, _MIDI_MIXER_1_EVENT * 10000 + _MIXER_CHAN_1_PAN);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MidiMixerPanChan_2, _MIDI_MIXER_1_EVENT * 10000 + _MIXER_CHAN_2_PAN);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MidiMixerPanChan_3, _MIDI_MIXER_1_EVENT * 10000 + _MIXER_CHAN_3_PAN);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MidiMixerPanChan_4, _MIDI_MIXER_1_EVENT * 10000 + _MIXER_CHAN_4_PAN);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MidiMixerPanChan_5, _MIDI_MIXER_1_EVENT * 10000 + _MIXER_CHAN_5_PAN);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MidiMixerPanChan_6, _MIDI_MIXER_1_EVENT * 10000 + _MIXER_CHAN_6_PAN);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MidiMixerPanChan_7, _MIDI_MIXER_1_EVENT * 10000 + _MIXER_CHAN_7_PAN);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MidiMixerPanChan_8, _MIDI_MIXER_1_EVENT * 10000 + _MIXER_CHAN_8_PAN);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MidiMixerPanChan_9, _MIDI_MIXER_1_EVENT * 10000 + _MIXER_CHAN_9_PAN);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MidiMixerPanChan_10, _MIDI_MIXER_1_EVENT * 10000 + _MIXER_CHAN_10_PAN);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MidiMixerPanChan_11, _MIDI_MIXER_1_EVENT * 10000 + _MIXER_CHAN_11_PAN);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MidiMixerPanChan_12, _MIDI_MIXER_1_EVENT * 10000 + _MIXER_CHAN_12_PAN);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MidiMixerPanChan_13, _MIDI_MIXER_1_EVENT * 10000 + _MIXER_CHAN_13_PAN);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MidiMixerPanChan_14, _MIDI_MIXER_1_EVENT * 10000 + _MIXER_CHAN_14_PAN);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MidiMixerPanChan_15, _MIDI_MIXER_1_EVENT * 10000 + _MIXER_CHAN_15_PAN);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MidiMixerPanChan_16, _MIDI_MIXER_1_EVENT * 10000 + _MIXER_CHAN_16_PAN);

	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MidiMixerSendChan_1, _MIDI_MIXER_1_EVENT * 10000 + _MIXER_CHAN_1_SEND);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MidiMixerSendChan_2, _MIDI_MIXER_1_EVENT * 10000 + _MIXER_CHAN_2_SEND);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MidiMixerSendChan_3, _MIDI_MIXER_1_EVENT * 10000 + _MIXER_CHAN_3_SEND);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MidiMixerSendChan_4, _MIDI_MIXER_1_EVENT * 10000 + _MIXER_CHAN_4_SEND);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MidiMixerSendChan_5, _MIDI_MIXER_1_EVENT * 10000 + _MIXER_CHAN_5_SEND);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MidiMixerSendChan_6, _MIDI_MIXER_1_EVENT * 10000 + _MIXER_CHAN_6_SEND);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MidiMixerSendChan_7, _MIDI_MIXER_1_EVENT * 10000 + _MIXER_CHAN_7_SEND);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MidiMixerSendChan_8, _MIDI_MIXER_1_EVENT * 10000 + _MIXER_CHAN_8_SEND);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MidiMixerSendChan_9, _MIDI_MIXER_1_EVENT * 10000 + _MIXER_CHAN_9_SEND);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MidiMixerSendChan_10, _MIDI_MIXER_1_EVENT * 10000 + _MIXER_CHAN_10_SEND);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MidiMixerSendChan_11, _MIDI_MIXER_1_EVENT * 10000 + _MIXER_CHAN_11_SEND);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MidiMixerSendChan_12, _MIDI_MIXER_1_EVENT * 10000 + _MIXER_CHAN_12_SEND);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MidiMixerSendChan_13, _MIDI_MIXER_1_EVENT * 10000 + _MIXER_CHAN_13_SEND);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MidiMixerSendChan_14, _MIDI_MIXER_1_EVENT * 10000 + _MIXER_CHAN_14_SEND);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MidiMixerSendChan_15, _MIDI_MIXER_1_EVENT * 10000 + _MIXER_CHAN_15_SEND);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MidiMixerSendChan_16, _MIDI_MIXER_1_EVENT * 10000 + _MIXER_CHAN_16_SEND);

	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MidiMixerLevelSetAll, _MIDI_MIXER_1_EVENT * 10000 + _MIXER_ALL_LEVEL);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MidiMixerPanSetAll, _MIDI_MIXER_1_EVENT * 10000 + _MIXER_ALL_PAN);
	MainWindow::getInstance()->m_widgetsIdsMap.insert(mainWindow->dial_MidiMixerSendSetAll, _MIDI_MIXER_1_EVENT * 10000 + _MIXER_ALL_SEND);

	// Widgets types
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MidiMixerLevelChan_1, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MidiMixerLevelChan_2, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MidiMixerLevelChan_3, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MidiMixerLevelChan_4, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MidiMixerLevelChan_5, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MidiMixerLevelChan_6, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MidiMixerLevelChan_7, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MidiMixerLevelChan_8, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MidiMixerLevelChan_9, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MidiMixerLevelChan_10, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MidiMixerLevelChan_11, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MidiMixerLevelChan_12, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MidiMixerLevelChan_13, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MidiMixerLevelChan_14, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MidiMixerLevelChan_15, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MidiMixerLevelChan_16, _CONTROL_TYPE_DIAL);

	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MidiMixerPanChan_1, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MidiMixerPanChan_2, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MidiMixerPanChan_3, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MidiMixerPanChan_4, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MidiMixerPanChan_5, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MidiMixerPanChan_6, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MidiMixerPanChan_7, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MidiMixerPanChan_8, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MidiMixerPanChan_9, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MidiMixerPanChan_10, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MidiMixerPanChan_11, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MidiMixerPanChan_12, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MidiMixerPanChan_13, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MidiMixerPanChan_14, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MidiMixerPanChan_15, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MidiMixerPanChan_16, _CONTROL_TYPE_DIAL);

	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MidiMixerSendChan_1, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MidiMixerSendChan_2, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MidiMixerSendChan_3, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MidiMixerSendChan_4, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MidiMixerSendChan_5, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MidiMixerSendChan_6, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MidiMixerSendChan_7, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MidiMixerSendChan_8, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MidiMixerSendChan_9, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MidiMixerSendChan_10, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MidiMixerSendChan_11, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MidiMixerSendChan_12, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MidiMixerSendChan_13, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MidiMixerSendChan_14, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MidiMixerSendChan_15, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MidiMixerSendChan_16, _CONTROL_TYPE_DIAL);

	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MidiMixerLevelSetAll, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MidiMixerPanSetAll, _CONTROL_TYPE_DIAL);
	MainWindow::getInstance()->m_widgetsTypesMap.insert(mainWindow->dial_MidiMixerSendSetAll, _CONTROL_TYPE_DIAL);
}

void MidiMixerTabUiHandling::update()
{
	mainWindow->dial_MidiMixerLevelChan_1->blockSignals(true);
	mainWindow->dial_MidiMixerLevelChan_1->setValue(mod_synth_get_active_midi_mixer_setting_param(_MIXER_CHAN_1_LEVEL));
	mainWindow->dial_MidiMixerLevelChan_1->blockSignals(false);
	
	mainWindow->dial_MidiMixerLevelChan_2->blockSignals(true);
	mainWindow->dial_MidiMixerLevelChan_2->setValue(mod_synth_get_active_midi_mixer_setting_param(_MIXER_CHAN_2_LEVEL));
	mainWindow->dial_MidiMixerLevelChan_2->blockSignals(false);
	
	mainWindow->dial_MidiMixerLevelChan_3->blockSignals(true);
	mainWindow->dial_MidiMixerLevelChan_3->setValue(mod_synth_get_active_midi_mixer_setting_param(_MIXER_CHAN_3_LEVEL));
	mainWindow->dial_MidiMixerLevelChan_3->blockSignals(false);
	
	mainWindow->dial_MidiMixerLevelChan_4->blockSignals(true);
	mainWindow->dial_MidiMixerLevelChan_4->setValue(mod_synth_get_active_midi_mixer_setting_param(_MIXER_CHAN_4_LEVEL));
	mainWindow->dial_MidiMixerLevelChan_4->blockSignals(false);
	
	mainWindow->dial_MidiMixerLevelChan_5->blockSignals(true);
	mainWindow->dial_MidiMixerLevelChan_5->setValue(mod_synth_get_active_midi_mixer_setting_param(_MIXER_CHAN_5_LEVEL));
	mainWindow->dial_MidiMixerLevelChan_5->blockSignals(false);
	
	mainWindow->dial_MidiMixerLevelChan_6->blockSignals(true);
	mainWindow->dial_MidiMixerLevelChan_6->setValue(mod_synth_get_active_midi_mixer_setting_param(_MIXER_CHAN_6_LEVEL));
	mainWindow->dial_MidiMixerLevelChan_6->blockSignals(false);
	
	mainWindow->dial_MidiMixerLevelChan_7->blockSignals(true);
	mainWindow->dial_MidiMixerLevelChan_7->setValue(mod_synth_get_active_midi_mixer_setting_param(_MIXER_CHAN_7_LEVEL));
	mainWindow->dial_MidiMixerLevelChan_7->blockSignals(false);
	
	mainWindow->dial_MidiMixerLevelChan_8->blockSignals(true);
	mainWindow->dial_MidiMixerLevelChan_8->setValue(mod_synth_get_active_midi_mixer_setting_param(_MIXER_CHAN_8_LEVEL));
	mainWindow->dial_MidiMixerLevelChan_8->blockSignals(false);
	
	mainWindow->dial_MidiMixerLevelChan_9->blockSignals(true);
	mainWindow->dial_MidiMixerLevelChan_9->setValue(mod_synth_get_active_midi_mixer_setting_param(_MIXER_CHAN_9_LEVEL));
	mainWindow->dial_MidiMixerLevelChan_9->blockSignals(false);
	
	mainWindow->dial_MidiMixerLevelChan_10->blockSignals(true);
	mainWindow->dial_MidiMixerLevelChan_10->setValue(mod_synth_get_active_midi_mixer_setting_param(_MIXER_CHAN_10_LEVEL));
	mainWindow->dial_MidiMixerLevelChan_10->blockSignals(false);
	
	mainWindow->dial_MidiMixerLevelChan_11->blockSignals(true);
	mainWindow->dial_MidiMixerLevelChan_11->setValue(mod_synth_get_active_midi_mixer_setting_param(_MIXER_CHAN_11_LEVEL));
	mainWindow->dial_MidiMixerLevelChan_11->blockSignals(false);
	
	mainWindow->dial_MidiMixerLevelChan_12->blockSignals(true);
	mainWindow->dial_MidiMixerLevelChan_12->setValue(mod_synth_get_active_midi_mixer_setting_param(_MIXER_CHAN_12_LEVEL));
	mainWindow->dial_MidiMixerLevelChan_12->blockSignals(false);
	
	mainWindow->dial_MidiMixerLevelChan_13->blockSignals(true);
	mainWindow->dial_MidiMixerLevelChan_13->setValue(mod_synth_get_active_midi_mixer_setting_param(_MIXER_CHAN_13_LEVEL));
	mainWindow->dial_MidiMixerLevelChan_13->blockSignals(false);
	
	mainWindow->dial_MidiMixerLevelChan_14->blockSignals(true);
	mainWindow->dial_MidiMixerLevelChan_14->setValue(mod_synth_get_active_midi_mixer_setting_param(_MIXER_CHAN_14_LEVEL));
	mainWindow->dial_MidiMixerLevelChan_14->blockSignals(false);
	
	mainWindow->dial_MidiMixerLevelChan_15->blockSignals(true);
	mainWindow->dial_MidiMixerLevelChan_15->setValue(mod_synth_get_active_midi_mixer_setting_param(_MIXER_CHAN_15_LEVEL));
	mainWindow->dial_MidiMixerLevelChan_15->blockSignals(false);
	
	mainWindow->dial_MidiMixerLevelChan_16->blockSignals(true);
	mainWindow->dial_MidiMixerLevelChan_16->setValue(mod_synth_get_active_midi_mixer_setting_param(_MIXER_CHAN_16_LEVEL));
	mainWindow->dial_MidiMixerLevelChan_16->blockSignals(false);
	
	
	mainWindow->dial_MidiMixerPanChan_1->blockSignals(true);
	mainWindow->dial_MidiMixerPanChan_1->setValue(mod_synth_get_active_midi_mixer_setting_param(_MIXER_CHAN_1_PAN));
	mainWindow->dial_MidiMixerPanChan_1->blockSignals(false);
	
	mainWindow->dial_MidiMixerPanChan_2->blockSignals(true);
	mainWindow->dial_MidiMixerPanChan_2->setValue(mod_synth_get_active_midi_mixer_setting_param(_MIXER_CHAN_2_PAN));
	mainWindow->dial_MidiMixerPanChan_2->blockSignals(false);
	
	mainWindow->dial_MidiMixerPanChan_3->blockSignals(true);
	mainWindow->dial_MidiMixerPanChan_3->setValue(mod_synth_get_active_midi_mixer_setting_param(_MIXER_CHAN_3_PAN));
	mainWindow->dial_MidiMixerPanChan_3->blockSignals(false);
	
	mainWindow->dial_MidiMixerPanChan_4->blockSignals(true);
	mainWindow->dial_MidiMixerPanChan_4->setValue(mod_synth_get_active_midi_mixer_setting_param(_MIXER_CHAN_4_PAN));
	mainWindow->dial_MidiMixerPanChan_4->blockSignals(false);
	
	mainWindow->dial_MidiMixerPanChan_5->blockSignals(true);
	mainWindow->dial_MidiMixerPanChan_5->setValue(mod_synth_get_active_midi_mixer_setting_param(_MIXER_CHAN_5_PAN));
	mainWindow->dial_MidiMixerPanChan_5->blockSignals(false);
	
	mainWindow->dial_MidiMixerPanChan_6->blockSignals(true);
	mainWindow->dial_MidiMixerPanChan_6->setValue(mod_synth_get_active_midi_mixer_setting_param(_MIXER_CHAN_6_PAN));
	mainWindow->dial_MidiMixerPanChan_6->blockSignals(false);
	
	mainWindow->dial_MidiMixerPanChan_7->blockSignals(true);
	mainWindow->dial_MidiMixerPanChan_7->setValue(mod_synth_get_active_midi_mixer_setting_param(_MIXER_CHAN_7_PAN));
	mainWindow->dial_MidiMixerPanChan_7->blockSignals(false);
	
	mainWindow->dial_MidiMixerPanChan_8->blockSignals(true);
	mainWindow->dial_MidiMixerPanChan_8->setValue(mod_synth_get_active_midi_mixer_setting_param(_MIXER_CHAN_8_PAN));
	mainWindow->dial_MidiMixerPanChan_8->blockSignals(false);
	
	mainWindow->dial_MidiMixerPanChan_9->blockSignals(true);
	mainWindow->dial_MidiMixerPanChan_9->setValue(mod_synth_get_active_midi_mixer_setting_param(_MIXER_CHAN_9_PAN));
	mainWindow->dial_MidiMixerPanChan_9->blockSignals(false);
	
	mainWindow->dial_MidiMixerPanChan_10->blockSignals(true);
	mainWindow->dial_MidiMixerPanChan_10->setValue(mod_synth_get_active_midi_mixer_setting_param(_MIXER_CHAN_10_PAN));
	mainWindow->dial_MidiMixerPanChan_10->blockSignals(false);
	
	mainWindow->dial_MidiMixerPanChan_11->blockSignals(true);
	mainWindow->dial_MidiMixerPanChan_11->setValue(mod_synth_get_active_midi_mixer_setting_param(_MIXER_CHAN_11_PAN));
	mainWindow->dial_MidiMixerPanChan_11->blockSignals(false);
	
	mainWindow->dial_MidiMixerPanChan_12->blockSignals(true);
	mainWindow->dial_MidiMixerPanChan_12->setValue(mod_synth_get_active_midi_mixer_setting_param(_MIXER_CHAN_12_PAN));
	mainWindow->dial_MidiMixerPanChan_12->blockSignals(false);
	
	mainWindow->dial_MidiMixerPanChan_13->blockSignals(true);
	mainWindow->dial_MidiMixerPanChan_13->setValue(mod_synth_get_active_midi_mixer_setting_param(_MIXER_CHAN_13_PAN));
	mainWindow->dial_MidiMixerPanChan_13->blockSignals(false);
	
	mainWindow->dial_MidiMixerPanChan_14->blockSignals(true);
	mainWindow->dial_MidiMixerPanChan_14->setValue(mod_synth_get_active_midi_mixer_setting_param(_MIXER_CHAN_14_PAN));
	mainWindow->dial_MidiMixerPanChan_14->blockSignals(false);
	
	mainWindow->dial_MidiMixerPanChan_15->blockSignals(true);
	mainWindow->dial_MidiMixerPanChan_15->setValue(mod_synth_get_active_midi_mixer_setting_param(_MIXER_CHAN_15_PAN));
	mainWindow->dial_MidiMixerPanChan_15->blockSignals(false);
	
	mainWindow->dial_MidiMixerPanChan_16->blockSignals(true);
	mainWindow->dial_MidiMixerPanChan_16->setValue(mod_synth_get_active_midi_mixer_setting_param(_MIXER_CHAN_16_PAN));
	mainWindow->dial_MidiMixerPanChan_16->blockSignals(false);
	
	
	mainWindow->dial_MidiMixerSendChan_1->blockSignals(true);
	mainWindow->dial_MidiMixerSendChan_1->setValue(mod_synth_get_active_midi_mixer_setting_param(_MIXER_CHAN_1_SEND));
	mainWindow->dial_MidiMixerSendChan_1->blockSignals(false);
	
	mainWindow->dial_MidiMixerSendChan_2->blockSignals(true);
	mainWindow->dial_MidiMixerSendChan_2->setValue(mod_synth_get_active_midi_mixer_setting_param(_MIXER_CHAN_2_SEND));
	mainWindow->dial_MidiMixerSendChan_2->blockSignals(false);
	
	mainWindow->dial_MidiMixerSendChan_3->blockSignals(true);
	mainWindow->dial_MidiMixerSendChan_3->setValue(mod_synth_get_active_midi_mixer_setting_param(_MIXER_CHAN_3_SEND));
	mainWindow->dial_MidiMixerSendChan_3->blockSignals(false);
	
	mainWindow->dial_MidiMixerSendChan_4->blockSignals(true);
	mainWindow->dial_MidiMixerSendChan_4->setValue(mod_synth_get_active_midi_mixer_setting_param(_MIXER_CHAN_4_SEND));
	mainWindow->dial_MidiMixerSendChan_4->blockSignals(false);
	
	mainWindow->dial_MidiMixerSendChan_5->blockSignals(true);
	mainWindow->dial_MidiMixerSendChan_5->setValue(mod_synth_get_active_midi_mixer_setting_param(_MIXER_CHAN_5_SEND));
	mainWindow->dial_MidiMixerSendChan_5->blockSignals(false);
	
	mainWindow->dial_MidiMixerSendChan_6->blockSignals(true);
	mainWindow->dial_MidiMixerSendChan_6->setValue(mod_synth_get_active_midi_mixer_setting_param(_MIXER_CHAN_6_SEND));
	mainWindow->dial_MidiMixerSendChan_6->blockSignals(false);
	
	mainWindow->dial_MidiMixerSendChan_7->blockSignals(true);
	mainWindow->dial_MidiMixerSendChan_7->setValue(mod_synth_get_active_midi_mixer_setting_param(_MIXER_CHAN_7_SEND));
	mainWindow->dial_MidiMixerSendChan_7->blockSignals(false);
	
	mainWindow->dial_MidiMixerSendChan_8->blockSignals(true);
	mainWindow->dial_MidiMixerSendChan_8->setValue(mod_synth_get_active_midi_mixer_setting_param(_MIXER_CHAN_8_SEND));
	mainWindow->dial_MidiMixerSendChan_8->blockSignals(false);
	
	mainWindow->dial_MidiMixerSendChan_9->blockSignals(true);
	mainWindow->dial_MidiMixerSendChan_9->setValue(mod_synth_get_active_midi_mixer_setting_param(_MIXER_CHAN_9_SEND));
	mainWindow->dial_MidiMixerSendChan_9->blockSignals(false);
	
	mainWindow->dial_MidiMixerSendChan_10->blockSignals(true);
	mainWindow->dial_MidiMixerSendChan_10->setValue(mod_synth_get_active_midi_mixer_setting_param(_MIXER_CHAN_10_SEND));
	mainWindow->dial_MidiMixerSendChan_10->blockSignals(false);
	
	mainWindow->dial_MidiMixerSendChan_11->blockSignals(true);
	mainWindow->dial_MidiMixerSendChan_11->setValue(mod_synth_get_active_midi_mixer_setting_param(_MIXER_CHAN_11_SEND));
	mainWindow->dial_MidiMixerSendChan_11->blockSignals(false);
	
	mainWindow->dial_MidiMixerSendChan_12->blockSignals(true);
	mainWindow->dial_MidiMixerSendChan_12->setValue(mod_synth_get_active_midi_mixer_setting_param(_MIXER_CHAN_12_SEND));
	mainWindow->dial_MidiMixerSendChan_12->blockSignals(false);
	
	mainWindow->dial_MidiMixerSendChan_13->blockSignals(true);
	mainWindow->dial_MidiMixerSendChan_13->setValue(mod_synth_get_active_midi_mixer_setting_param(_MIXER_CHAN_13_SEND));
	mainWindow->dial_MidiMixerSendChan_13->blockSignals(false);
	
	mainWindow->dial_MidiMixerSendChan_14->blockSignals(true);
	mainWindow->dial_MidiMixerSendChan_14->setValue(mod_synth_get_active_midi_mixer_setting_param(_MIXER_CHAN_14_SEND));
	mainWindow->dial_MidiMixerSendChan_14->blockSignals(false);
	
	mainWindow->dial_MidiMixerSendChan_15->blockSignals(true);
	mainWindow->dial_MidiMixerSendChan_15->setValue(mod_synth_get_active_midi_mixer_setting_param(_MIXER_CHAN_15_SEND));
	mainWindow->dial_MidiMixerSendChan_15->blockSignals(false);
	
	mainWindow->dial_MidiMixerSendChan_16->blockSignals(true);
	mainWindow->dial_MidiMixerSendChan_16->setValue(mod_synth_get_active_midi_mixer_setting_param(_MIXER_CHAN_16_SEND));
	mainWindow->dial_MidiMixerSendChan_16->blockSignals(false);
	
	for (int i = 0; i < 16; i++)
	{
		if (mod_synth_get_midi_channel_synth(i) == _MIDI_CHAN_ASSIGNED_SYNTH_FLUID)
		{
			// Disable Pan and Se
			enableChannelKnobs(i, true, false, false);
		}
		else
		{
			enableChannelKnobs(i, true, true, true);
		}
	}
}

void MidiMixerTabUiHandling::enableChannelKnobs(int chan, bool enLev, bool enPan, bool enSnd)
{
	switch (chan)
	{
		case 0:
			mainWindow->dial_MidiMixerLevelChan_1->setEnabled(enLev);
			mainWindow->dial_MidiMixerPanChan_1->setEnabled(enPan);
			mainWindow->dial_MidiMixerSendChan_1->setEnabled(enSnd);
			break;
			
		case 1:
			mainWindow->dial_MidiMixerLevelChan_2->setEnabled(enLev);
			mainWindow->dial_MidiMixerPanChan_2->setEnabled(enPan);
			mainWindow->dial_MidiMixerSendChan_2->setEnabled(enSnd);
			break;
		case 2:
			mainWindow->dial_MidiMixerLevelChan_3->setEnabled(enLev);
			mainWindow->dial_MidiMixerPanChan_3->setEnabled(enPan);
			mainWindow->dial_MidiMixerSendChan_3->setEnabled(enSnd);
			break;
		case 3:
			mainWindow->dial_MidiMixerLevelChan_4->setEnabled(enLev);
			mainWindow->dial_MidiMixerPanChan_4->setEnabled(enPan);
			mainWindow->dial_MidiMixerSendChan_4->setEnabled(enSnd);
			break;
		case 4:
			mainWindow->dial_MidiMixerLevelChan_5->setEnabled(enLev);
			mainWindow->dial_MidiMixerPanChan_5->setEnabled(enPan);
			mainWindow->dial_MidiMixerSendChan_5->setEnabled(enSnd);
			break;
		case 5:
			mainWindow->dial_MidiMixerLevelChan_6->setEnabled(enLev);
			mainWindow->dial_MidiMixerPanChan_6->setEnabled(enPan);
			mainWindow->dial_MidiMixerSendChan_6->setEnabled(enSnd);
			break;
		case 6:
			mainWindow->dial_MidiMixerLevelChan_7->setEnabled(enLev);
			mainWindow->dial_MidiMixerPanChan_7->setEnabled(enPan);
			mainWindow->dial_MidiMixerSendChan_7->setEnabled(enSnd);
			break;
		case 7:
			mainWindow->dial_MidiMixerLevelChan_8->setEnabled(enLev);
			mainWindow->dial_MidiMixerPanChan_8->setEnabled(enPan);
			mainWindow->dial_MidiMixerSendChan_8->setEnabled(enSnd);
			break;
		case 8:
			mainWindow->dial_MidiMixerLevelChan_9->setEnabled(enLev);
			mainWindow->dial_MidiMixerPanChan_9->setEnabled(enPan);
			mainWindow->dial_MidiMixerSendChan_9->setEnabled(enSnd);
			break;
		case 9:
			mainWindow->dial_MidiMixerLevelChan_10->setEnabled(enLev);
			mainWindow->dial_MidiMixerPanChan_10->setEnabled(enPan);
			mainWindow->dial_MidiMixerSendChan_10->setEnabled(enSnd);
			break;
		case 10:
			mainWindow->dial_MidiMixerLevelChan_11->setEnabled(enLev);
			mainWindow->dial_MidiMixerPanChan_11->setEnabled(enPan);
			mainWindow->dial_MidiMixerSendChan_11->setEnabled(enSnd);
			break;
		case 11:
			mainWindow->dial_MidiMixerLevelChan_12->setEnabled(enLev);
			mainWindow->dial_MidiMixerPanChan_12->setEnabled(enPan);
			mainWindow->dial_MidiMixerSendChan_12->setEnabled(enSnd);
			break;
		case 12:
			mainWindow->dial_MidiMixerLevelChan_13->setEnabled(enLev);
			mainWindow->dial_MidiMixerPanChan_13->setEnabled(enPan);
			mainWindow->dial_MidiMixerSendChan_13->setEnabled(enSnd);
			break;
		case 13:
			mainWindow->dial_MidiMixerLevelChan_14->setEnabled(enLev);
			mainWindow->dial_MidiMixerPanChan_14->setEnabled(enPan);
			mainWindow->dial_MidiMixerSendChan_14->setEnabled(enSnd);
			break;
		case 14:
			mainWindow->dial_MidiMixerLevelChan_15->setEnabled(enLev);
			mainWindow->dial_MidiMixerPanChan_15->setEnabled(enPan);
			mainWindow->dial_MidiMixerSendChan_15->setEnabled(enSnd);
			break;
		case 15:
			mainWindow->dial_MidiMixerLevelChan_16->setEnabled(enLev);
			mainWindow->dial_MidiMixerPanChan_16->setEnabled(enPan);
			mainWindow->dial_MidiMixerSendChan_16->setEnabled(enSnd);
			break;		
	}
}

/**
 * A SLOT callback activated when the set level of midi channel 1 is changed.
 * @param lev	level value.
 * @return none
 */
void MidiMixerTabUiHandling::levelChangedChannel_1(int lev)
{
	mod_synth_midi_mixer_event(_MIDI_MIXER_1_EVENT, _MIXER_CHAN_1_LEVEL, lev);
	sprintf(mssg1, "Mixer Channel 1 Level: %.2f", (float)lev / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

/**
 * A SLOT callback activated when the set level of midi channel 2 is changed.
 * @param lev	level value.
 * @return none
 */
void MidiMixerTabUiHandling::levelChangedChannel_2(int lev)
{
	mod_synth_midi_mixer_event(_MIDI_MIXER_1_EVENT, _MIXER_CHAN_2_LEVEL, lev);
	sprintf(mssg1, "Mixer Channel 2 Level: %.2f", (float)lev / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

/**
 * A SLOT callback activated when the set level of midi channel 3 is changed.
 * @param lev	level value.
 * @return none
 */
void MidiMixerTabUiHandling::levelChangedChannel_3(int lev)
{
	mod_synth_midi_mixer_event(_MIDI_MIXER_1_EVENT, _MIXER_CHAN_3_LEVEL, lev);
	sprintf(mssg1, "Mixer Channel 3 Level: %.2f", (float)lev / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

/**
 * A SLOT callback activated when the set level of midi channel 4 is changed.
 * @param lev	level value.
 * @return none
 */
void MidiMixerTabUiHandling::levelChangedChannel_4(int lev)
{
	mod_synth_midi_mixer_event(_MIDI_MIXER_1_EVENT, _MIXER_CHAN_4_LEVEL, lev);
	sprintf(mssg1, "Mixer Channel 4 Level: %.2f", (float)lev / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

/**
 * A SLOT callback activated when the set level of midi channel 5 is changed.
 * @param lev	level value.
 * @return none
 */
void MidiMixerTabUiHandling::levelChangedChannel_5(int lev)
{
	mod_synth_midi_mixer_event(_MIDI_MIXER_1_EVENT, _MIXER_CHAN_5_LEVEL, lev);
	sprintf(mssg1, "Mixer Channel 5 Level: %.2f", (float)lev / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

/**
 * A SLOT callback activated when the set level of midi channel 6 is changed.
 * @param lev	level value.
 * @return none
 */
void MidiMixerTabUiHandling::levelChangedChannel_6(int lev)
{
	mod_synth_midi_mixer_event(_MIDI_MIXER_1_EVENT, _MIXER_CHAN_6_LEVEL, lev);
	sprintf(mssg1, "Mixer Channel 6 Level: %.2f", (float)lev / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

/**
 * A SLOT callback activated when the set level of midi channel 7 is changed.
 * @param lev	level value.
 * @return none
 */
void MidiMixerTabUiHandling::levelChangedChannel_7(int lev)
{
	mod_synth_midi_mixer_event(_MIDI_MIXER_1_EVENT, _MIXER_CHAN_7_LEVEL, lev);
	sprintf(mssg1, "Mixer Channel 7 Level: %.2f", (float)lev / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

/**
 * A SLOT callback activated when the set level of midi channel 8 is changed.
 * @param lev	level value.
 * @return none
 */
void MidiMixerTabUiHandling::levelChangedChannel_8(int lev)
{
	mod_synth_midi_mixer_event(_MIDI_MIXER_1_EVENT, _MIXER_CHAN_8_LEVEL, lev);
	sprintf(mssg1, "Mixer Channel 8 Level: %.2f", (float)lev / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

/**
 * A SLOT callback activated when the set level of midi channel 9 is changed.
 * @param lev	level value.
 * @return none
 */
void MidiMixerTabUiHandling::levelChangedChannel_9(int lev)
{
	mod_synth_midi_mixer_event(_MIDI_MIXER_1_EVENT, _MIXER_CHAN_9_LEVEL, lev);
	sprintf(mssg1, "Mixer Channel 9 Level: %.2f", (float)lev / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

/**
 * A SLOT callback activated when the set level of midi channel 10 is changed.
 * @param lev	level value.
 * @return none
 */
void MidiMixerTabUiHandling::levelChangedChannel_10(int lev)
{
	mod_synth_midi_mixer_event(_MIDI_MIXER_1_EVENT, _MIXER_CHAN_10_LEVEL, lev);
	sprintf(mssg1, "Mixer Channel 10 Level: %.2f", (float)lev / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

/**
 * A SLOT callback activated when the set level of midi channel 11 is changed.
 * @param lev	level value.
 * @return none
 */
void MidiMixerTabUiHandling::levelChangedChannel_11(int lev)
{
	mod_synth_midi_mixer_event(_MIDI_MIXER_1_EVENT, _MIXER_CHAN_11_LEVEL, lev);
	sprintf(mssg1, "Mixer Channel 11 Level: %.2f", (float)lev / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

/**
 * A SLOT callback activated when the set level of midi channel 12 is changed.
 * @param lev	level value.
 * @return none
 */
void MidiMixerTabUiHandling::levelChangedChannel_12(int lev)
{
	mod_synth_midi_mixer_event(_MIDI_MIXER_1_EVENT, _MIXER_CHAN_12_LEVEL, lev);
	sprintf(mssg1, "Mixer Channel 12 Level: %.2f", (float)lev / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

/**
 * A SLOT callback activated when the set level of midi channel 13 is changed.
 * @param lev	level value.
 * @return none
 */
void MidiMixerTabUiHandling::levelChangedChannel_13(int lev)
{
	mod_synth_midi_mixer_event(_MIDI_MIXER_1_EVENT, _MIXER_CHAN_13_LEVEL, lev);
	sprintf(mssg1, "Mixer Channel 13 Level: %.2f", (float)lev / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

/**
 * A SLOT callback activated when the set level of midi channel 14 is changed.
 * @param lev	level value.
 * @return none
 */
void MidiMixerTabUiHandling::levelChangedChannel_14(int lev)
{
	mod_synth_midi_mixer_event(_MIDI_MIXER_1_EVENT, _MIXER_CHAN_14_LEVEL, lev);
	sprintf(mssg1, "Mixer Channel 14 Level: %.2f", (float)lev / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

/**
 * A SLOT callback activated when the set level of midi channel 15 is changed.
 * @param lev	level value.
 * @return none
 */
void MidiMixerTabUiHandling::levelChangedChannel_15(int lev)
{
	mod_synth_midi_mixer_event(_MIDI_MIXER_1_EVENT, _MIXER_CHAN_15_LEVEL, lev);
	sprintf(mssg1, "Mixer Channel 15 Level: %.2f", (float)lev / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

/**
 * A SLOT callback activated when the set level of midi channel 16 is changed.
 * @param lev	level value.
 * @return none
 */
void MidiMixerTabUiHandling::levelChangedChannel_16(int lev)
{
	mod_synth_midi_mixer_event(_MIDI_MIXER_1_EVENT, _MIXER_CHAN_16_LEVEL, lev);
	sprintf(mssg1, "Mixer Channel 16 Level: %.2f", (float)lev / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

/**
 * A SLOT callback activated when the set level of midi all channels is changed.
 * @param lev	level value.
 * @return none
 */
void MidiMixerTabUiHandling::levelChangedAll(int lev)
{
	
	
	mainWindow->dial_MidiMixerLevelChan_1->setValue(lev);
	mainWindow->dial_MidiMixerLevelChan_2->setValue(lev);
	mainWindow->dial_MidiMixerLevelChan_3->setValue(lev);
	mainWindow->dial_MidiMixerLevelChan_4->setValue(lev);
	mainWindow->dial_MidiMixerLevelChan_5->setValue(lev);
	mainWindow->dial_MidiMixerLevelChan_6->setValue(lev);
	mainWindow->dial_MidiMixerLevelChan_7->setValue(lev);
	mainWindow->dial_MidiMixerLevelChan_8->setValue(lev);
	mainWindow->dial_MidiMixerLevelChan_9->setValue(lev);
	mainWindow->dial_MidiMixerLevelChan_10->setValue(lev);
	mainWindow->dial_MidiMixerLevelChan_11->setValue(lev);
	mainWindow->dial_MidiMixerLevelChan_12->setValue(lev);
	mainWindow->dial_MidiMixerLevelChan_13->setValue(lev);
	mainWindow->dial_MidiMixerLevelChan_14->setValue(lev);
	mainWindow->dial_MidiMixerLevelChan_15->setValue(lev);
	mainWindow->dial_MidiMixerLevelChan_16->setValue(lev);
	
	sprintf(mssg1, "Mixer All Channels Level: %.2f", (float)lev / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}


/**
 * A SLOT callback activated when the set pan of midi channel 1 is changed.
 * @param lev	level value.
 * @return none
 */
void MidiMixerTabUiHandling::panChangedChannel_1(int pan)
{
	mod_synth_midi_mixer_event(_MIDI_MIXER_1_EVENT, _MIXER_CHAN_1_PAN, pan);
	sprintf(mssg1, "Mixer Channel 1 Pan: %.2f", (float)(pan -50) / 50.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

/**
 * A SLOT callback activated when the set pan of midi channel 2 is changed.
 * @param lev	level value.
 * @return none
 */
void MidiMixerTabUiHandling::panChangedChannel_2(int pan)
{
	mod_synth_midi_mixer_event(_MIDI_MIXER_1_EVENT, _MIXER_CHAN_2_PAN, pan);
	sprintf(mssg1, "Mixer Channel 2 Pan: %.2f", (float)(pan - 50) / 50.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

/**
 * A SLOT callback activated when the set pan of midi channel 3 is changed.
 * @param lev	level value.
 * @return none
 */
void MidiMixerTabUiHandling::panChangedChannel_3(int pan)
{
	mod_synth_midi_mixer_event(_MIDI_MIXER_1_EVENT, _MIXER_CHAN_3_PAN, pan);
	sprintf(mssg1, "Mixer Channel 3 Pan: %.2f", (float)(pan - 50) / 50.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

/**
 * A SLOT callback activated when the set pan of midi channel 4 is changed.
 * @param lev	level value.
 * @return none
 */
void MidiMixerTabUiHandling::panChangedChannel_4(int pan)
{
	mod_synth_midi_mixer_event(_MIDI_MIXER_1_EVENT, _MIXER_CHAN_4_PAN, pan);
	sprintf(mssg1, "Mixer Channel 4 Pan: %.2f", (float)(pan - 50) / 50.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

/**
 * A SLOT callback activated when the set pan of midi channel 5 is changed.
 * @param lev	level value.
 * @return none
 */
void MidiMixerTabUiHandling::panChangedChannel_5(int pan)
{
	mod_synth_midi_mixer_event(_MIDI_MIXER_1_EVENT, _MIXER_CHAN_5_PAN, pan);
	sprintf(mssg1, "Mixer Channel 5 Pan: %.2f", (float)(pan - 50) / 50.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

/**
 * A SLOT callback activated when the set pan of midi channel 6 is changed.
 * @param lev	level value.
 * @return none
 */
void MidiMixerTabUiHandling::panChangedChannel_6(int pan)
{
	mod_synth_midi_mixer_event(_MIDI_MIXER_1_EVENT, _MIXER_CHAN_6_PAN, pan);
	sprintf(mssg1, "Mixer Channel 6 Pan: %.2f", (float)(pan - 50) / 50.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

/**
 * A SLOT callback activated when the set pan of midi channel 7 is changed.
 * @param lev	level value.
 * @return none
 */
void MidiMixerTabUiHandling::panChangedChannel_7(int pan)
{
	mod_synth_midi_mixer_event(_MIDI_MIXER_1_EVENT, _MIXER_CHAN_7_PAN, pan);
	sprintf(mssg1, "Mixer Channel 7 Pan: %.2f", (float)(pan - 50) / 50.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

/**
 * A SLOT callback activated when the set pan of midi channel 8 is changed.
 * @param lev	level value.
 * @return none
 */
void MidiMixerTabUiHandling::panChangedChannel_8(int pan)
{
	mod_synth_midi_mixer_event(_MIDI_MIXER_1_EVENT, _MIXER_CHAN_8_PAN, pan);
	sprintf(mssg1, "Mixer Channel 8 Pan: %.2f", (float)(pan - 50) / 50.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

/**
 * A SLOT callback activated when the set pan of midi channel 9 is changed.
 * @param lev	level value.
 * @return none
 */
void MidiMixerTabUiHandling::panChangedChannel_9(int pan)
{
	mod_synth_midi_mixer_event(_MIDI_MIXER_1_EVENT, _MIXER_CHAN_9_PAN, pan);
	sprintf(mssg1, "Mixer Channel 9 Pan: %.2f", (float)(pan - 50) / 50.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

/**
 * A SLOT callback activated when the set pan of midi channel 10 is changed.
 * @param lev	level value.
 * @return none
 */
void MidiMixerTabUiHandling::panChangedChannel_10(int pan)
{
	mod_synth_midi_mixer_event(_MIDI_MIXER_1_EVENT, _MIXER_CHAN_10_PAN, pan);
	sprintf(mssg1, "Mixer Channel 10 Pan: %.2f", (float)(pan - 50) / 50.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

/**
 * A SLOT callback activated when the set pan of midi channel 11 is changed.
 * @param lev	level value.
 * @return none
 */
void MidiMixerTabUiHandling::panChangedChannel_11(int pan)
{
	mod_synth_midi_mixer_event(_MIDI_MIXER_1_EVENT, _MIXER_CHAN_11_PAN, pan);
	sprintf(mssg1, "Mixer Channel 11 Pan: %.2f", (float)(pan - 50) / 50.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

/**
 * A SLOT callback activated when the set pan of midi channel 12 is changed.
 * @param lev	level value.
 * @return none
 */
void MidiMixerTabUiHandling::panChangedChannel_12(int pan)
{
	mod_synth_midi_mixer_event(_MIDI_MIXER_1_EVENT, _MIXER_CHAN_12_PAN, pan);
	sprintf(mssg1, "Mixer Channel 12 Pan: %.2f", (float)(pan - 50) / 50.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

/**
 * A SLOT callback activated when the set pan of midi channel 13 is changed.
 * @param lev	level value.
 * @return none
 */
void MidiMixerTabUiHandling::panChangedChannel_13(int pan)
{
	mod_synth_midi_mixer_event(_MIDI_MIXER_1_EVENT, _MIXER_CHAN_13_PAN, pan);
	sprintf(mssg1, "Mixer Channel 13 Pan: %.2f", (float)(pan - 50) / 50.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

/**
 * A SLOT callback activated when the set pan of midi channel 14 is changed.
 * @param lev	level value.
 * @return none
 */
void MidiMixerTabUiHandling::panChangedChannel_14(int pan)
{
	mod_synth_midi_mixer_event(_MIDI_MIXER_1_EVENT, _MIXER_CHAN_14_PAN, pan);
	sprintf(mssg1, "Mixer Channel 14 Pan: %.2f", (float)(pan - 50) / 50.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

/**
 * A SLOT callback activated when the set pan of midi channel 15 is changed.
 * @param lev	level value.
 * @return none
 */
void MidiMixerTabUiHandling::panChangedChannel_15(int pan)
{
	mod_synth_midi_mixer_event(_MIDI_MIXER_1_EVENT, _MIXER_CHAN_15_PAN, pan);
	sprintf(mssg1, "Mixer Channel 15 Pan: %.2f", (float)(pan - 50) / 50.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

/**
 * A SLOT callback activated when the set pan of midi channel 16 is changed.
 * @param lev	level value.
 * @return none
 */
void MidiMixerTabUiHandling::panChangedChannel_16(int pan)
{
	mod_synth_midi_mixer_event(_MIDI_MIXER_1_EVENT, _MIXER_CHAN_1_PAN, pan);
	sprintf(mssg1, "Mixer Channel 16 pan: %.2f", (float)(pan - 50) / 50.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

/**
 * A SLOT callback activated when the set pan of midi all channels is changed.
 * @param pan	pan value.
 * @return none
 */
void MidiMixerTabUiHandling::panChangedAll(int pan)
{
	mainWindow->dial_MidiMixerPanChan_1->setValue(pan);
	mainWindow->dial_MidiMixerPanChan_2->setValue(pan);
	mainWindow->dial_MidiMixerPanChan_3->setValue(pan);
	mainWindow->dial_MidiMixerPanChan_4->setValue(pan);
	mainWindow->dial_MidiMixerPanChan_5->setValue(pan);
	mainWindow->dial_MidiMixerPanChan_6->setValue(pan);
	mainWindow->dial_MidiMixerPanChan_7->setValue(pan);
	mainWindow->dial_MidiMixerPanChan_8->setValue(pan);
	mainWindow->dial_MidiMixerPanChan_9->setValue(pan);
	mainWindow->dial_MidiMixerPanChan_10->setValue(pan);
	mainWindow->dial_MidiMixerPanChan_11->setValue(pan);
	mainWindow->dial_MidiMixerPanChan_12->setValue(pan);
	mainWindow->dial_MidiMixerPanChan_13->setValue(pan);
	mainWindow->dial_MidiMixerPanChan_14->setValue(pan);
	mainWindow->dial_MidiMixerPanChan_15->setValue(pan);
	mainWindow->dial_MidiMixerPanChan_16->setValue(pan);
	
	
	sprintf(mssg1, "Mixer All Channels Pan: %.2f", (float)(pan - 50) / 50.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

/**
 * A SLOT callback activated when the set send of midi channel 1 is changed.
 * @param lev	level value.
 * @return none
 */
void MidiMixerTabUiHandling::sendChangedChannel_1(int snd)
{
	mod_synth_midi_mixer_event(_MIDI_MIXER_1_EVENT, _MIXER_CHAN_1_SEND, snd);
	sprintf(mssg1, "Mixer Channel 1 Send: %.2f", (float)snd / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

/**
 * A SLOT callback activated when the set send of midi channel 2 is changed.
 * @param lev	level value.
 * @return none
 */
void MidiMixerTabUiHandling::sendChangedChannel_2(int snd)
{
	mod_synth_midi_mixer_event(_MIDI_MIXER_1_EVENT, _MIXER_CHAN_2_SEND, snd);
	sprintf(mssg1, "Mixer Channel 2 Send: %.2f", (float)snd / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

/**
 * A SLOT callback activated when the set send of midi channel 3 is changed.
 * @param lev	level value.
 * @return none
 */
void MidiMixerTabUiHandling::sendChangedChannel_3(int snd)
{
	mod_synth_midi_mixer_event(_MIDI_MIXER_1_EVENT, _MIXER_CHAN_3_SEND, snd);
	sprintf(mssg1, "Mixer Channel 3 Send: %.2f", (float)snd / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

/**
 * A SLOT callback activated when the set send of midi channel 4 is changed.
 * @param lev	level value.
 * @return none
 */
void MidiMixerTabUiHandling::sendChangedChannel_4(int snd)
{
	mod_synth_midi_mixer_event(_MIDI_MIXER_1_EVENT, _MIXER_CHAN_4_SEND, snd);
	sprintf(mssg1, "Mixer Channel 4 Send: %.2f", (float)snd / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

/**
 * A SLOT callback activated when the set send of midi channel 5 is changed.
 * @param lev	level value.
 * @return none
 */
void MidiMixerTabUiHandling::sendChangedChannel_5(int snd)
{
	mod_synth_midi_mixer_event(_MIDI_MIXER_1_EVENT, _MIXER_CHAN_5_SEND, snd);
	sprintf(mssg1, "Mixer Channel 5 Send: %.2f", (float)snd / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

/**
 * A SLOT callback activated when the set send of midi channel 6 is changed.
 * @param lev	level value.
 * @return none
 */
void MidiMixerTabUiHandling::sendChangedChannel_6(int snd)
{
	mod_synth_midi_mixer_event(_MIDI_MIXER_1_EVENT, _MIXER_CHAN_6_SEND, snd);
	sprintf(mssg1, "Mixer Channel 6 Send: %.2f", (float)snd / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

/**
 * A SLOT callback activated when the set send of midi channel 7 is changed.
 * @param lev	level value.
 * @return none
 */
void MidiMixerTabUiHandling::sendChangedChannel_7(int snd)
{
	mod_synth_midi_mixer_event(_MIDI_MIXER_1_EVENT, _MIXER_CHAN_7_SEND, snd);
	sprintf(mssg1, "Mixer Channel 7 Send: %.2f", (float)snd / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

/**
 * A SLOT callback activated when the set send of midi channel 8 is changed.
 * @param lev	level value.
 * @return none
 */
void MidiMixerTabUiHandling::sendChangedChannel_8(int snd)
{
	mod_synth_midi_mixer_event(_MIDI_MIXER_1_EVENT, _MIXER_CHAN_8_SEND, snd);
	sprintf(mssg1, "Mixer Channel 8 Send: %.2f", (float)snd / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

/**
 * A SLOT callback activated when the set send of midi channel 9 is changed.
 * @param lev	level value.
 * @return none
 */
void MidiMixerTabUiHandling::sendChangedChannel_9(int snd)
{
	mod_synth_midi_mixer_event(_MIDI_MIXER_1_EVENT, _MIXER_CHAN_9_SEND, snd);
	sprintf(mssg1, "Mixer Channel 9 Send: %.2f", (float)snd / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

/**
 * A SLOT callback activated when the set send of midi channel 10 is changed.
 * @param lev	level value.
 * @return none
 */
void MidiMixerTabUiHandling::sendChangedChannel_10(int snd)
{
	mod_synth_midi_mixer_event(_MIDI_MIXER_1_EVENT, _MIXER_CHAN_10_SEND, snd);
	sprintf(mssg1, "Mixer Channel 10 Send: %.2f", (float)snd / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

/**
 * A SLOT callback activated when the set send of midi channel 11 is changed.
 * @param lev	level value.
 * @return none
 */
void MidiMixerTabUiHandling::sendChangedChannel_11(int snd)
{
	mod_synth_midi_mixer_event(_MIDI_MIXER_1_EVENT, _MIXER_CHAN_11_SEND, snd);
	sprintf(mssg1, "Mixer Channel 11 Send: %.2f", (float)snd / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

/**
 * A SLOT callback activated when the set send of midi channel 12 is changed.
 * @param lev	level value.
 * @return none
 */
void MidiMixerTabUiHandling::sendChangedChannel_12(int snd)
{
	mod_synth_midi_mixer_event(_MIDI_MIXER_1_EVENT, _MIXER_CHAN_12_SEND, snd);
	sprintf(mssg1, "Mixer Channel 12 Send: %.2f", (float)snd / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

/**
 * A SLOT callback activated when the set send of midi channel 13 is changed.
 * @param lev	level value.
 * @return none
 */
void MidiMixerTabUiHandling::sendChangedChannel_13(int snd)
{
	mod_synth_midi_mixer_event(_MIDI_MIXER_1_EVENT, _MIXER_CHAN_13_SEND, snd);
	sprintf(mssg1, "Mixer Channel 13 Send: %.2f", (float)snd / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

/**
 * A SLOT callback activated when the set send of midi channel 14 is changed.
 * @param lev	level value.
 * @return none
 */
void MidiMixerTabUiHandling::sendChangedChannel_14(int snd)
{
	mod_synth_midi_mixer_event(_MIDI_MIXER_1_EVENT, _MIXER_CHAN_14_SEND, snd);
	sprintf(mssg1, "Mixer Channel 14 Send: %.2f", (float)snd / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

/**
 * A SLOT callback activated when the set send of midi channel 15 is changed.
 * @param lev	level value.
 * @return none
 */
void MidiMixerTabUiHandling::sendChangedChannel_15(int snd)
{
	mod_synth_midi_mixer_event(_MIDI_MIXER_1_EVENT, _MIXER_CHAN_15_SEND, snd);
	sprintf(mssg1, "Mixer Channel 15 Send: %.2f", (float)snd / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

/**
 * A SLOT callback activated when the set send of midi channel 16 is changed.
 * @param lev	level value.
 * @return none
 */
void MidiMixerTabUiHandling::sendChangedChannel_16(int snd)
{
	mod_synth_midi_mixer_event(_MIDI_MIXER_1_EVENT, _MIXER_CHAN_16_SEND, snd);
	sprintf(mssg1, "Mixer Channel 16 Send: %.2f", (float)snd / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

/**
 * A SLOT callback activated when the set send level of all channels is changed.
 * @param lev	level value.
 * @return none
 */
void MidiMixerTabUiHandling::sendChangedAll(int snd)
{
	mainWindow->dial_MidiMixerSendChan_1->setValue(snd);
	mainWindow->dial_MidiMixerSendChan_2->setValue(snd);
	mainWindow->dial_MidiMixerSendChan_3->setValue(snd);
	mainWindow->dial_MidiMixerSendChan_4->setValue(snd);
	mainWindow->dial_MidiMixerSendChan_5->setValue(snd);
	mainWindow->dial_MidiMixerSendChan_6->setValue(snd);
	mainWindow->dial_MidiMixerSendChan_7->setValue(snd);
	mainWindow->dial_MidiMixerSendChan_8->setValue(snd);
	mainWindow->dial_MidiMixerSendChan_9->setValue(snd);
	mainWindow->dial_MidiMixerSendChan_10->setValue(snd);
	mainWindow->dial_MidiMixerSendChan_11->setValue(snd);
	mainWindow->dial_MidiMixerSendChan_12->setValue(snd);
	mainWindow->dial_MidiMixerSendChan_13->setValue(snd);
	mainWindow->dial_MidiMixerSendChan_14->setValue(snd);
	mainWindow->dial_MidiMixerSendChan_15->setValue(snd);
	mainWindow->dial_MidiMixerSendChan_16->setValue(snd);
	
	sprintf(mssg1, "Mixer All Channels Send: %.2f", (float)snd / 100.0f);
	MainWindow::getInstance()->updateStatusDisplayText(std::string(mssg1));
}

