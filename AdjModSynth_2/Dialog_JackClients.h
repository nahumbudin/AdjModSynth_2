/**
* @file		Dialog_JackClients.h
*	@author		Nahum Budin
*	@date		28-3-2021
*	@version	1.0
*
*	@brief		Used for connecting JACK Audio clients
*
*/

#ifndef _DIALOG_JACK_CLIENTS
#define _DIALOG_JACK_CLIENTS

#include <QDialog>
#include <QDialogButtonBox>
#include <QString>
#include <QTreeWidget>

#include "libAdjHeartModSynth_2.h"

namespace Ui
{
	class Dialog_JackClients;
}

typedef struct s_jack_connection_line
{
	int connected_line;
	int connecting_to_line;
} s_jack_connection_line_t;

typedef struct jack_client_info
{
	jack_client_info(int c, int p)
		: client(c),
		  port(p) {}

	int client;
	int port;
} jack_client_info_t;

class Dialog_JackClients : public QDialog
{
	Q_OBJECT

  public:
	explicit Dialog_JackClients(QWidget *parent = 0);
	~Dialog_JackClients();

	void update();

  protected slots:

	void jack_input_client_selection_changed();
	void jack_output_client_selection_changed();
	void item_was_expanded(QTreeWidgetItem *item);
	void item_was_collapsed(QTreeWidgetItem *item);
	void connect_pushbutton_clicked(bool state);
	void disconnect_pushbutton_clicked(bool state);
	void disconnect_all_pushbutton_clicked(bool state);
	void auto_connect_jack_ports_changed(bool state);

	void refresh_data(bool state = true);
	void expand_all(bool state = false);

  private:
	Ui::Dialog_JackClients *ui;

	void update_input_clients_tree();
	void update_output_clients_tree();
	int update_connections();
	void clear_connections_plot();
	
	void setup_connections_plot();

	void plot_connection_line(int input, int output, QColor color);

	int get_tree_line_num_coordinate(std::string client, std::string port, int type);

	std::string input_clients_selected_client, input_clients_selected_port;
	std::string output_clients_selected_client, output_clients_selected_port;
	// True if client was selected; false if a port was selected.
	bool input_client_selected, output_client_selected;

	bool input_clients_tree_updated, output_clients_tree_updated;
	bool all_expanded, collapsing_expanding_all_in_progress;
	bool auto_connect_ports;

	int connection_lines_use_color;
	int num_of_connections;

	QTreeWidgetItem *input_clients_tree_root_items[_MAX_NUM_OF_JACK_CLIENTS];
	QTreeWidgetItem *output_clients_tree_root_items[_MAX_NUM_OF_JACK_CLIENTS];

	QTreeWidgetItem *input_clients_tree_port_items[_MAX_NUM_OF_JACK_CLIENTS][_MAX_NUM_OF_JACK_CLIENT_PORTS];
	QTreeWidgetItem *output_clients_tree_port_items[_MAX_NUM_OF_JACK_CLIENTS][_MAX_NUM_OF_JACK_CLIENT_PORTS];

	map<QTreeWidgetItem *, jack_client_info_t *> input_clients_tree_map;
	map<QTreeWidgetItem *, jack_client_info_t *> output_clients_tree_map;

	vector<s_jack_connection_line_t> connections_plot_lines;
	
	
};

#endif
