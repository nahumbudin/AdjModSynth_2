/**
* @file		Dialog_MidiClients.h
*	@author		Nahum Budin
*	@date		17-Feb-2021
*	@version	1.0
*
*	@brief		Used for connecting Midi clients
*
*/

#ifndef _DIALOG_MIDI_CLIENTS
#define _DIALOG_MIDI_CLIENTS

#include <QDialog>
#include <QDialogButtonBox>
#include <QTreeWidget>
#include <QString>

#include "libAdjHeartModSynth_2.h"

typedef struct midi_client_info
{
	midi_client_info(int c, int p)
		: client(c),
		 port(p) {}
	
	int client;
	int port;	
} midi_client_info_t;

typedef struct s_midi_connection_line
{
	int connected_line;
	int connecting_to_line;
} s_midi_connection_line_t;

namespace Ui
{
	class Dialog_MidiClients;
}



class Dialog_MidiClients : public QDialog
{
	Q_OBJECT

  public :
	explicit Dialog_MidiClients(QWidget *parent = 0);
	~Dialog_MidiClients();
	
	void update();

	
protected slots:
	
	void midi_input_client_selection_changed();
	void midi_output_client_selection_changed();
	void item_was_expanded(QTreeWidgetItem *item);
	void item_was_collapsed(QTreeWidgetItem *item);
	void connect_pushbutton_clicked(bool state);
	void disconnect_pushbutton_clicked(bool state);
	void disconnect_all_pushbutton_clicked(bool state);
	void refresh_data(bool state = true);
	void expand_all(bool state);

  private:
	Ui::Dialog_MidiClients *ui;
	
	void update_input_clients_tree();
	void update_output_clients_tree();
	int update_connections();

	void setup_connections_plot();
	void clear_connections_plot();
	void plot_connection_line(int input, int output, QColor color);

	int get_tree_line_num_coordinate(int client, int port, int type);
	
	QTreeWidgetItem *input_clients_tree_root_items[_MAX_NUM_OF_MIDI_DEVICES];
	QTreeWidgetItem *output_clients_tree_root_items[_MAX_NUM_OF_MIDI_DEVICES];
	
	QTreeWidgetItem *input_clients_tree_port_items[_MAX_NUM_OF_MIDI_DEVICES][_MAX_NUM_OF_MIDI_DEVICE_PORTS];
	QTreeWidgetItem *output_clients_tree_port_items[_MAX_NUM_OF_MIDI_DEVICES][_MAX_NUM_OF_MIDI_DEVICE_PORTS];
	
	bool input_clients_tree_updated, output_clients_tree_updated;

	map<QTreeWidgetItem *, midi_client_info_t* > input_clients_tree_map;
	map<QTreeWidgetItem*, midi_client_info_t* > output_clients_tree_map;
	
	int input_clients_selected_client, input_clients_selected_port;
	int output_clients_selected_client, output_clients_selected_port;

	vector<s_midi_connection_line_t> connections_plot_lines;
	int num_of_connections;

	int connection_lines_use_color;

	bool all_expanded, collapsing_expanding_all_in_progress;

	//	char selectedMidiDevString[64];
	
};




#endif
