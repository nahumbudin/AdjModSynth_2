/**
* @file		Dialog_JackClients.cpp
*	@author		Nahum Budin
*	@date		28-3-2021
*	@version	1.0
*
*	@brief		Used for connecting JACK Audio clients
*
*/

#include <QDialog>
#include <QFont>
#include <QPen>
#include <QString>
#include <QTreeWidget>

#include "Dialog_JackClients.h"
#include "ui_Dialog_JackClients.h"

#include "libAdjHeartModSynth_2.h"

Dialog_JackClients::Dialog_JackClients(QWidget *parent)
	: QDialog(parent),
	  ui(new Ui::Dialog_JackClients)
{
	QFont font;

	ui->setupUi(this);

	input_clients_tree_updated = false;
	output_clients_tree_updated = false;

	all_expanded = false;
	collapsing_expanding_all_in_progress = false;

	auto_connect_ports = true;

	input_clients_selected_client = ""; // nothing selected
	input_clients_selected_port = "";

	output_clients_selected_client = "";
	output_clients_selected_port = "";

	input_client_selected = false;
	output_client_selected = false;

	ui->tree_widget_jack_input_clients->setColumnCount(1);
	ui->tree_widget_jack_input_clients->setHeaderLabel(tr("Input Clients"));
	font = ui->tree_widget_jack_input_clients->font();
	font.setPointSize(12);
	ui->tree_widget_jack_input_clients->headerItem()->setFont(0, font);

	ui->tree_widget_jack_output_clients->setColumnCount(1);
	ui->tree_widget_jack_output_clients->setHeaderLabel(tr("Output Clients"));
	ui->tree_widget_jack_output_clients->headerItem()->setFont(0, font);

	connect(ui->tree_widget_jack_input_clients,
			SIGNAL(itemSelectionChanged()),
			this,
			SLOT(jack_input_client_selection_changed()));

	connect(ui->tree_widget_jack_output_clients,
			SIGNAL(itemSelectionChanged()),
			this,
			SLOT(jack_output_client_selection_changed()));

	connect(ui->tree_widget_jack_input_clients,
			SIGNAL(itemCollapsed(QTreeWidgetItem *)),
			this,
			SLOT(item_was_collapsed(QTreeWidgetItem *)));

	connect(ui->tree_widget_jack_output_clients,
			SIGNAL(itemExpanded(QTreeWidgetItem *)),
			this,
			SLOT(item_was_expanded(QTreeWidgetItem *)));

	connect(ui->tree_widget_jack_output_clients,
			SIGNAL(itemCollapsed(QTreeWidgetItem *)),
			this,
			SLOT(item_was_collapsed(QTreeWidgetItem *)));

	connect(ui->tree_widget_jack_input_clients,
			SIGNAL(itemExpanded(QTreeWidgetItem *)),
			this,
			SLOT(item_was_expanded(QTreeWidgetItem *)));

	connect(ui->push_button_jack_connections_connect,
			SIGNAL(clicked(bool)),
			this,
			SLOT(connect_pushbutton_clicked(bool)));

	connect(ui->push_button_jack_connections_disconnect,
			SIGNAL(clicked(bool)),
			this,
			SLOT(disconnect_pushbutton_clicked(bool)));

	connect(ui->push_button_jack_connections_dDisconnect_all,
			SIGNAL(clicked(bool)),
			this,
			SLOT(disconnect_all_pushbutton_clicked(bool)));
	
	connect(ui->push_button_jack_connections_refresh,
			SIGNAL(clicked(bool)),
			this,
			SLOT(update()));

	connect(ui->push_button_jack_connections_expand_all,
			SIGNAL(clicked(bool)),
			this,
			SLOT(expand_all(bool)));

	connect(ui->check_box_auto_connect_all_jack_ports,
			SIGNAL(clicked(bool)),
			this,
			SLOT(auto_connect_jack_ports_changed(bool)));
	

	update();
	setup_connections_plot();	
}

Dialog_JackClients::~Dialog_JackClients()
{
	
}

/**
*   @brief  Refresh and update all connections data and display.
*   @param  none.
*   @return void
*/
void Dialog_JackClients::update()
{
	refresh_data();
	if (all_expanded)
	{
		expand_all();
	}
}

/**
*   @brief  Update the input clients tree widget.
*   @param  none.
*   @return void
*/
void Dialog_JackClients::update_input_clients_tree()
{
	int cln;
	std::string cln_name, port_name;
	int num_of_input_clients;
	int num_of_ports, port;

	if (!input_clients_tree_updated)
	{
		input_clients_tree_updated = true;
		num_of_input_clients = mod_synth_get_num_of_input_jack_clients();
		if (num_of_input_clients > _MAX_NUM_OF_JACK_CLIENTS)
		{
			num_of_input_clients = _MAX_NUM_OF_JACK_CLIENTS;
		}

		if (num_of_input_clients > 0)
		{
			for (cln = 0; cln < num_of_input_clients; cln++)
			{
				cln_name = mod_synth_get_jack_input_client_name(cln);
				input_clients_tree_root_items[cln] = new QTreeWidgetItem(ui->tree_widget_jack_input_clients);
				input_clients_tree_root_items[cln]->setText(0, QString::fromLocal8Bit(cln_name.c_str()));
				input_clients_tree_map[input_clients_tree_root_items[cln]] = new jack_client_info_t(cln, -1); // -1 indicates root

				num_of_ports = mod_synth_get_num_of_jack_input_client_ports(cln);
				if (num_of_ports > 0)
				{
					for (port = 0; port < num_of_ports; port++)
					{
						port_name = mod_synth_get_jack_input_client_port_name(cln, port);
						input_clients_tree_port_items[cln][port] = new QTreeWidgetItem();
						input_clients_tree_port_items[cln][port]->setText(0, QString::fromLocal8Bit(port_name.c_str()));
						input_clients_tree_root_items[cln]->addChild(input_clients_tree_port_items[cln][port]);
						input_clients_tree_map[input_clients_tree_port_items[cln][port]] = new jack_client_info_t(cln, port);
					}
				}
			}

//			get_tree_line_num_coordinate(130, 0, _MIDI_DEVICE_INPUT);
		}
	}
}

/**
*   @brief  Update the output clients tree widget.
*   @param  none.
*   @return void
*/
void Dialog_JackClients::update_output_clients_tree()
{
	int cln;
	std::string cln_name, port_name;
	int num_of_output_clients;
	int num_of_ports, port;

	if (!output_clients_tree_updated)
	{
		output_clients_tree_updated = true;
		num_of_output_clients = mod_synth_get_num_of_output_jack_clients();
		if (num_of_output_clients > _MAX_NUM_OF_JACK_CLIENTS)
		{
			num_of_output_clients = _MAX_NUM_OF_JACK_CLIENTS;
		}

		if (num_of_output_clients > 0)
		{
			for (cln = 0; cln < num_of_output_clients; cln++)
			{
				cln_name = mod_synth_get_jack_output_client_name(cln);
				output_clients_tree_root_items[cln] = new QTreeWidgetItem(ui->tree_widget_jack_output_clients);
				output_clients_tree_root_items[cln]->setText(0, QString::fromLocal8Bit(cln_name.c_str()));
				output_clients_tree_map[output_clients_tree_root_items[cln]] = new jack_client_info_t(cln, -1); // -1 indicates root

				num_of_ports = mod_synth_get_num_of_jack_output_client_ports(cln);
				if (num_of_ports > 0)
				{
					for (port = 0; port < num_of_ports; port++)
					{
						port_name = mod_synth_get_jack_output_client_port_name(cln, port);
						output_clients_tree_port_items[cln][port] = new QTreeWidgetItem();
						output_clients_tree_port_items[cln][port]->setText(0, QString::fromLocal8Bit(port_name.c_str()));
						output_clients_tree_root_items[cln]->addChild(output_clients_tree_port_items[cln][port]);
						output_clients_tree_map[output_clients_tree_port_items[cln][port]] = new jack_client_info_t(cln, port);
					}
				}
			}

			//			get_tree_line_num_coordinate(130, 0, _MIDI_DEVICE_INPUT);
		}
	}
}

void Dialog_JackClients::refresh_data(bool state)
{
	mod_synth_refresh_jack_clients_data();

	input_clients_tree_updated = false;
	output_clients_tree_updated = false;

	ui->tree_widget_jack_input_clients->clear();
	ui->tree_widget_jack_output_clients->clear();

	ui->push_button_jack_connections_expand_all->setText(tr("Expand All"));

	update_input_clients_tree();
	update_output_clients_tree();

	update_connections();
}

void Dialog_JackClients::expand_all(bool state)
{
	collapsing_expanding_all_in_progress = true;

	if (!all_expanded)
	{
		ui->tree_widget_jack_input_clients->expandAll();
		ui->tree_widget_jack_output_clients->expandAll();
		ui->push_button_jack_connections_expand_all->setText(tr("Collapse All"));
		all_expanded = true;
	}
	else
	{
		ui->tree_widget_jack_input_clients->collapseAll();
		ui->tree_widget_jack_output_clients->collapseAll();
		ui->push_button_jack_connections_expand_all->setText(tr("Expand All"));
		all_expanded = false;
	}

	collapsing_expanding_all_in_progress = false;

	update_connections();
}

/**
*   @brief  Intialize connections plot widget.
*   @param  none.
*   @return void
*/
void Dialog_JackClients::setup_connections_plot()
{
	QPen pen;
	pen.setStyle(Qt::SolidLine);
	pen.setWidth(2);
	pen.setColor(QColor("#FFFFFF"));

	clear_connections_plot();

	ui->widget_jack_connection_lines->addGraph();
	ui->widget_jack_connection_lines->graph(0)->setPen(pen);
	ui->widget_jack_connection_lines->addGraph();

	ui->widget_jack_connection_lines->xAxis->setVisible(false);
	ui->widget_jack_connection_lines->xAxis->setTickLabels(false);
	ui->widget_jack_connection_lines->yAxis->setVisible(false);
	ui->widget_jack_connection_lines->yAxis->setTickLabels(false);

	ui->widget_jack_connection_lines->yAxis->setRange(0, 200);
	ui->widget_jack_connection_lines->xAxis->setRange(0, 50);

	ui->widget_jack_connection_lines->setBackground(QBrush(QColor("#1f1f1f")));
}

/**
*   @brief  Clear (erase) connections plot widget.
*   @param  none.
*   @return void
*/
void Dialog_JackClients::clear_connections_plot()
{
	ui->widget_jack_connection_lines->clearItems();
	ui->widget_jack_connection_lines->replot();
}

/**
*   @brief  Plot a connection line between input client:port to output:port.
*					input level --
*								  \
*								   -- output level
*								   
*   @param  input	input level.
*   @param	output	output level
*   @return void
*/
void Dialog_JackClients::plot_connection_line(int input, int output, QColor color)
{
	QCPItemLine *connection_line1 = new QCPItemLine(ui->widget_jack_connection_lines);
	connection_line1->start->setCoords(0, 200 - (int)(output * 10.5));
	connection_line1->end->setCoords(10, 200 - (int)(output * 10.5));
	connection_line1->setPen(QPen(color));

	QCPItemLine *connection_line2 = new QCPItemLine(ui->widget_jack_connection_lines);
	connection_line2->start->setCoords(40, 200 - (int)(input * 10.5));
	connection_line2->end->setCoords(50, 200 - (int)(input * 10.5));
	connection_line2->setPen(QPen(color));

	QCPItemLine *connection_line3 = new QCPItemLine(ui->widget_jack_connection_lines);
	connection_line3->start->setCoords(10, 200 - (int)(output * 10.5));
	connection_line3->end->setCoords(40, 200 - (int)(input * 10.5));
	connection_line3->setPen(QPen(color));

	ui->widget_jack_connection_lines->replot();
}

/**
*   @brief  Update active connection data and plot connecting lines.
*   @param  none.
*   @return void
*/
int Dialog_JackClients::update_connections()
{
	int c, in_line, out_line;
	s_jack_connection_line_t connection;
	std::string in_client, in_port, out_client, out_port;

	static const QColor line_colors[] = {Qt::blue, Qt::green, Qt::yellow, Qt::red};

	connections_plot_lines.clear();
	clear_connections_plot();
	connection_lines_use_color = 0;

	mod_synth_refresh_alsa_midi_clients_data();
	num_of_connections = mod_synth_get_num_of_jack_clients_connections();

	for (c = 0; c < num_of_connections; c++)
	{
		in_client = mod_synth_get_jack_connection_in_client_name(c);
		in_port = mod_synth_get_jack_connection_in_client_port_name(c);
		out_client = mod_synth_get_jack_connection_out_client_name(c);
		out_port = mod_synth_get_jack_connection_out_client_port_name(c);

		out_line = get_tree_line_num_coordinate(out_client, out_port, _MIDI_DEVICE_OUTPUT);
		in_line = get_tree_line_num_coordinate(in_client, in_port, _MIDI_DEVICE_INPUT);

		if ((out_line >= 0) && (in_line >= 0))
		{
			connection.connected_line = in_line;
			connection.connecting_to_line = out_line;
			connections_plot_lines.push_back(connection);

			plot_connection_line(in_line + 1, out_line + 1, line_colors[connection_lines_use_color]);
			connection_lines_use_color = (connection_lines_use_color + 1) % 4;
		}
	}

	return num_of_connections;
}

/**
*   @brief  Get the tree-widget connection-line Y level.
*   @param  client	client name string.
*	@param	port	port name string
*	@param	type	tree-widget: _MIDI_DEVICE_INPUT/_MIDI_DEVICE_OUTPUT
*   @return the tree-widget connection-line Y level
*/
int Dialog_JackClients::get_tree_line_num_coordinate(std::string client, std::string port, int type)
{
	int num_of_items, i, c, pos, line = 0;
	QTreeWidgetItem *item;
	string item_str;
	bool found = false;
	
	// Get num of root items
	if (type == _JACK_CLIENT_INPUT)
	{
		num_of_items = mod_synth_get_num_of_input_jack_clients();
	}
	else if (type == _JACK_CLIENT_OUTPUT)
	{
		num_of_items = mod_synth_get_num_of_output_jack_clients();
	}
	else
	{
		return -1;
	}

	// look for the client item
	for (i = 0; i < num_of_items; i++)
	{
		if (type == _MIDI_DEVICE_INPUT)
		{
			item = input_clients_tree_root_items[i];
		}
		else if (type == _MIDI_DEVICE_OUTPUT)
		{
			item = output_clients_tree_root_items[i];
		}
		else
		{
			return -1;
		}

		item_str = item->text(0).toStdString();
		pos = item_str.find(client);

		if (pos == 0)
		{
			// client item found
			if (!item->isExpanded())
			{
				// Not epanded - this is it
				found = true;
				goto finish;
			}
			else
			{
				// Expanded - look for client port ":n"
				for (c = 0; c < item->childCount(); c++)
				{
					item_str = item->child(c)->text(0).toStdString();
					pos = item_str.find(port);
					if (pos >= 0)
					{
						// port found
						line++;
						found = true;
						goto finish;
					}
					else
					{
						// Port not found
						line++;
					}
				}
			}
		}
		else
		{
			// item not found - goto next item
			line++;
			if (item->isExpanded())
			{
				// If expanded, add childs (ports)
				line += item->childCount();
			}
		}
		
	}

finish:

	if (found)
	{
		return line;
	}
	else
	{
		return -1;
	}
}

void Dialog_JackClients::jack_input_client_selection_changed()
{
	QList<QTreeWidgetItem *> selected_items_list =
		ui->tree_widget_jack_input_clients->selectedItems();

	if (selected_items_list.length() > 0)
	{
		if (selected_items_list.at(0)->childCount() > 0)
		{
			// Parent (Top client level selected)
			input_clients_selected_client = selected_items_list.at(0)->text(0).toStdString();
			input_clients_selected_port = selected_items_list.at(0)->child(0)->text(0).toStdString();
			input_client_selected = true;
		}
		else
		{
			// Child (port level selected)
			input_clients_selected_client = selected_items_list.at(0)->parent()->text(0).toStdString();
			input_clients_selected_port = selected_items_list.at(0)->text(0).toStdString();
			input_client_selected = false;
		}
	}
	else
	{
		input_clients_selected_client = "";
		input_clients_selected_port = "";
	}
}

void Dialog_JackClients::jack_output_client_selection_changed()
{
	QList<QTreeWidgetItem *> selected_items_list =
		ui->tree_widget_jack_output_clients->selectedItems();

	if (selected_items_list.length() > 0)
	{
		if (selected_items_list.at(0)->childCount() > 0)
		{
			// Parent (Top client level selected)
			output_clients_selected_client = selected_items_list.at(0)->text(0).toStdString();
			output_clients_selected_port = selected_items_list.at(0)->child(0)->text(0).toStdString();
			output_client_selected = true;
		}
		else
		{
			// Child (port level selected)
			output_clients_selected_client = selected_items_list.at(0)->parent()->text(0).toStdString();
			output_clients_selected_port = selected_items_list.at(0)->text(0).toStdString();
			output_client_selected = false;
		}
	}
	else
	{
		output_clients_selected_client = "";
		output_clients_selected_port = "";
	}
}

void Dialog_JackClients::item_was_expanded(QTreeWidgetItem *item)
{
	if (!collapsing_expanding_all_in_progress)
	{
		update_connections();
	}
}

void Dialog_JackClients::item_was_collapsed(QTreeWidgetItem *item)
{
	if (!collapsing_expanding_all_in_progress)
	{
		update_connections();
	}
}

void Dialog_JackClients::connect_pushbutton_clicked(bool state)
{
	int p;

	QList<QTreeWidgetItem *> selected_output_items_list, selected_input_items_list;

	if (input_client_selected || output_client_selected)
	{
		// Client level selected or either in or out - connect all ports
		selected_output_items_list =
			ui->tree_widget_jack_output_clients->selectedItems();

		selected_input_items_list =
			ui->tree_widget_jack_input_clients->selectedItems();

		if (selected_output_items_list.length() > 0)
		{
			for (p = 0; p < selected_output_items_list.at(0)->childCount(); p++)
			{
				// Go over all ports
				mod_synth_connect_jack_connection(
					input_clients_selected_client,
					selected_input_items_list.at(0)->child(p)->text(0).toStdString(),
					output_clients_selected_client,
					selected_output_items_list.at(0)->child(p)->text(0).toStdString());
			}
		}
	}
	else
	{
		// Port level selected on both sides - connect only selected ports
		mod_synth_connect_jack_connection(
			input_clients_selected_client,
			input_clients_selected_port,
			output_clients_selected_client,
			output_clients_selected_port);
	}

	update();
}

void Dialog_JackClients::disconnect_pushbutton_clicked(bool state)
{
	if (input_client_selected || output_client_selected)
	{
		// Client level selected or either in or out - disconnect all ports
	}
	else
	{
		// Port level selected on both sides - disconnect only selected ports
		mod_synth_disconnect_jack_connection(
			input_clients_selected_client,
			input_clients_selected_port,
			output_clients_selected_client,
			output_clients_selected_port);
	}

	update();
}

void Dialog_JackClients::disconnect_all_pushbutton_clicked(bool state)
{
	QMessageBox msgBox;
	msgBox.setIcon(QMessageBox::Critical);
	msgBox.setWindowTitle("Warning?");
	msgBox.setText("Are you sure you want to disconnect all connections?");
	msgBox.setStandardButtons(QMessageBox::Yes);
	msgBox.addButton(QMessageBox::No);
	msgBox.setDefaultButton(QMessageBox::No);
	if (msgBox.exec() == QMessageBox::Yes)
	{
		mod_synth_disconnect_all_jack_connections();
		update();
	}
}

void Dialog_JackClients::auto_connect_jack_ports_changed(bool state)
{
	auto_connect_ports = state;
}
