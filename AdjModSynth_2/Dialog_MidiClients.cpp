/**
* @file		Dialog_MidiClientss.cpp
*	@author		Nahum Budin
*	@date		17-Feb-2021
*	@version	1.0
*
*	@brief		Used for connecting to Midi clients
*
*/

#include <QDialog>
#include <QString>
#include <QTreeWidget>
#include <QFont>
#include <QPen>

#include "Dialog_MidiClients.h"
#include "ui_Dialog_MidiClients.h"

#include "libAdjHeartModSynth_2.h"

Dialog_MidiClients::Dialog_MidiClients(QWidget *parent)
	: QDialog(parent), 
	ui(new Ui::Dialog_MidiClients)
{
	QFont font;
	
	ui->setupUi(this);
	
	input_clients_tree_updated = false;
	output_clients_tree_updated = false;

	all_expanded = false;
	collapsing_expanding_all_in_progress = false;

	input_clients_selected_client = -1;  // nothing selected
	input_clients_selected_port = -1;
	
	output_clients_selected_client = -1; 
	output_clients_selected_port = -1;
	
	ui->treeWidget_inputClients->setColumnCount(1);
	ui->treeWidget_inputClients->setHeaderLabel(tr("Input Clients (Kbds)"));
	font = ui->treeWidget_inputClients->font();
	font.setPointSize(12);
	ui->treeWidget_inputClients->headerItem()->setFont(0, font);
	
	ui->treeWidget_outputClients->setColumnCount(1);
	ui->treeWidget_outputClients->setHeaderLabel(tr("Output Clients (Synth)"));
	ui->treeWidget_outputClients->headerItem()->setFont(0, font);

	connect(ui->treeWidget_inputClients,
		SIGNAL(itemSelectionChanged()),
		this,
		SLOT(midi_input_client_selection_changed()));
	
	connect(ui->treeWidget_outputClients,
		SIGNAL(itemSelectionChanged()),
		this,
		SLOT(midi_output_client_selection_changed()));

	connect(ui->treeWidget_inputClients,
			SIGNAL(itemCollapsed(QTreeWidgetItem *)),
			this,
			SLOT(item_was_collapsed(QTreeWidgetItem *)));

	connect(ui->treeWidget_inputClients,
			SIGNAL(itemExpanded(QTreeWidgetItem *)),
			this,
			SLOT(item_was_expanded(QTreeWidgetItem *)));
	
	connect(ui->treeWidget_outputClients,
			SIGNAL(itemCollapsed(QTreeWidgetItem*)),
			this,
			SLOT(item_was_collapsed(QTreeWidgetItem*)));

	connect(ui->treeWidget_outputClients,
			SIGNAL(itemExpanded(QTreeWidgetItem *)),
			this,
			SLOT(item_was_expanded(QTreeWidgetItem *)));
	
	connect(ui->pushButton_midiConnectionsConnect,
		SIGNAL(clicked(bool)),
		this,
		SLOT(connect_pushbutton_clicked(bool)));
	
	connect(ui->pushButton_midiConnectionsDisconnect,
		SIGNAL(clicked(bool)),
		this,
		SLOT(disconnect_pushbutton_clicked(bool)));

	connect(ui->pushButton_midiConnectionsDisconnectAll,
			SIGNAL(clicked(bool)),
			this,
			SLOT(disconnect_all_pushbutton_clicked(bool)));
	
	connect(ui->pushButton_midiConnectionsRefresh,
		SIGNAL(clicked(bool)),
		this,
		SLOT(refresh_data(bool)));
	
	connect(ui->pushButton_midiConnectionsExpandAll,
		SIGNAL(clicked(bool)),
		this,
		SLOT(expand_all(bool)));
	
	update();
	setup_connections_plot();
	
}

Dialog_MidiClients::~Dialog_MidiClients()
{
	
}

/**
*   @brief  Refresh and update all connections data and display.
*   @param  none.
*   @return void
*/
void Dialog_MidiClients::update()
{
	refresh_data();
}

/**
*   @brief  Update the input clients tree widget.
*   @param  none.
*   @return void
*/
void Dialog_MidiClients::update_input_clients_tree()
{
	int cln;
	std::string cln_name, port_name;
	int num_of_input_clients;
	int num_of_ports, port;
	
	if (!input_clients_tree_updated)
	{
		input_clients_tree_updated = true;
		num_of_input_clients = mod_synth_get_num_of_input_midi_clients();
		if (num_of_input_clients > _MAX_NUM_OF_MIDI_DEVICES)
		{
			num_of_input_clients = _MAX_NUM_OF_MIDI_DEVICES;
		}
		
		if (num_of_input_clients > 0)
		{		
			for (cln = 0; cln < num_of_input_clients; cln++)
			{
				mod_synth_get_midi_input_client_name_string(cln, &cln_name);
				input_clients_tree_root_items[cln] = new QTreeWidgetItem(ui->treeWidget_inputClients);
				input_clients_tree_root_items[cln]->setText(0, QString::fromLocal8Bit(cln_name.c_str()));
				input_clients_tree_map[input_clients_tree_root_items[cln]] = new midi_client_info_t(cln, -1);   // -1 indicates root
				
				num_of_ports = mod_synth_get_num_of_input_midi_client_ports(cln);
				if (num_of_ports > 0)
				{
					for (port = 0; port < num_of_ports; port++)
					{
						mod_synth_get_midi_input_client_port_name_string(cln, port, &port_name);
						input_clients_tree_port_items[cln][port] = new QTreeWidgetItem();
						input_clients_tree_port_items[cln][port]->setText(0, QString::fromLocal8Bit(port_name.c_str()));
						input_clients_tree_root_items[cln]->addChild(input_clients_tree_port_items[cln][port]);
						input_clients_tree_map[input_clients_tree_port_items[cln][port]] = new midi_client_info_t(cln, port);
					}
				}

			}

			get_tree_line_num_coordinate(130, 0, _MIDI_DEVICE_INPUT);
		}
	}
}

/**
*   @brief  Update the output clients tree widget.
*   @param  none.
*   @return void
*/
void Dialog_MidiClients::update_output_clients_tree()
{
	int cln;
	std::string cln_name, port_name;
	int num_of_output_clients;
	int num_of_ports, port;
	
	if (!output_clients_tree_updated)
	{
		output_clients_tree_updated = true;
		num_of_output_clients = mod_synth_get_num_of_output_midi_clients();
		if (num_of_output_clients > _MAX_NUM_OF_MIDI_DEVICES)
		{
			num_of_output_clients = _MAX_NUM_OF_MIDI_DEVICES;
		}
		
		if (num_of_output_clients > 0)
		{		
			for (cln = 0; cln < num_of_output_clients; cln++)
			{
				mod_synth_get_midi_output_client_name_string(cln, &cln_name);
				output_clients_tree_root_items[cln] = new QTreeWidgetItem(ui->treeWidget_outputClients);
				output_clients_tree_root_items[cln]->setText(0, QString::fromLocal8Bit(cln_name.c_str()));
				output_clients_tree_map[output_clients_tree_root_items[cln]] = new midi_client_info_t(cln, -1);    // -1 indicates root
				
				num_of_ports = mod_synth_get_num_of_output_midi_client_ports(cln);
				if (num_of_ports > 0)
				{
					for (port = 0; port < num_of_ports; port++)
					{
						mod_synth_get_midi_output_client_port_name_string(cln, port, &port_name);
						output_clients_tree_port_items[cln][port] = new QTreeWidgetItem();
						output_clients_tree_port_items[cln][port]->setText(0, QString::fromLocal8Bit(port_name.c_str()));
						output_clients_tree_root_items[cln]->addChild(output_clients_tree_port_items[cln][port]);
						output_clients_tree_map[output_clients_tree_port_items[cln][port]] = new midi_client_info_t(cln, port);
					}
				}
			}
		}
	}
}

/**
*   @brief  Update active connection data and plot connecting lines.
*   @param  none.
*   @return void
*/
int Dialog_MidiClients::update_connections()
{
	int c, in_client, in_port, out_client, out_port, in_line, out_line;
	s_midi_connection_line_t connection;

	static const QColor line_colors[] = {Qt::blue, Qt::green, Qt::yellow, Qt::red};

	connections_plot_lines.clear();
	clear_connections_plot();
	connection_lines_use_color = 0;

	mod_synth_refresh_alsa_midi_clients_data();
	num_of_connections = mod_synth_get_num_of_midi_clients_connections();

	for (c = 0; c < num_of_connections; c++)
	{
		in_client = mod_synth_get_midi_client_connection_connected_client_num(c);
		in_port = mod_synth_get_midi_client_connection_connected_port_num(c);
		out_client = mod_synth_get_midi_client_connection_connecting_to_client_num(c);
		out_port = mod_synth_get_midi_client_connection_connecting_to_port_num(c);

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
*   @brief  Intialize connections plot widget.
*   @param  none.
*   @return void
*/
void Dialog_MidiClients::setup_connections_plot()
{
	QPen pen;
	pen.setStyle(Qt::SolidLine);
	pen.setWidth(2);
	pen.setColor(QColor("#FFFFFF"));

	clear_connections_plot();

	ui->widget_midi_connection_lines->addGraph();
	ui->widget_midi_connection_lines->graph(0)->setPen(pen);
	ui->widget_midi_connection_lines->addGraph();

	ui->widget_midi_connection_lines->xAxis->setVisible(false);
	ui->widget_midi_connection_lines->xAxis->setTickLabels(false);
	ui->widget_midi_connection_lines->yAxis->setVisible(false);
	ui->widget_midi_connection_lines->yAxis->setTickLabels(false);

	ui->widget_midi_connection_lines->yAxis->setRange(0, 200);
	ui->widget_midi_connection_lines->xAxis->setRange(0, 50);

	ui->widget_midi_connection_lines->setBackground(QBrush(QColor("#1f1f1f")));
}

/**
*   @brief  Clear (erase) connections plot widget.
*   @param  none.
*   @return void
*/
void Dialog_MidiClients::clear_connections_plot()
{
	ui->widget_midi_connection_lines->clearItems();
	ui->widget_midi_connection_lines->replot();
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
void Dialog_MidiClients::plot_connection_line(int input, int output,QColor color)
{
	QCPItemLine *connection_line1 = new QCPItemLine(ui->widget_midi_connection_lines);
	connection_line1->start->setCoords(0, 200 - (int )(input * 10.5));
	connection_line1->end->setCoords(10, 200 - (int)(input * 10.5));
	connection_line1->setPen(QPen(color));

	QCPItemLine *connection_line2 = new QCPItemLine(ui->widget_midi_connection_lines);
	connection_line2->start->setCoords(40, 200 - (int)(output * 10.5));
	connection_line2->end->setCoords(50, 200 - (int)(output * 10.5));
	connection_line2->setPen(QPen(color));

	QCPItemLine *connection_line3 = new QCPItemLine(ui->widget_midi_connection_lines);
	connection_line3->start->setCoords(10, 200 - (int)(input * 10.5));
	connection_line3->end->setCoords(40, 200 - (int)(output * 10.5));
	connection_line3->setPen(QPen(color));

	ui->widget_midi_connection_lines->replot();
}

/**
*   @brief  Get the tree-widget connection-line Y level.
*   @param  client	client number.
*	@param	port	port number
*	@param	type	tree-widget: _MIDI_DEVICE_INPUT/_MIDI_DEVICE_OUTPUT
*   @return the tree-widget connection-line Y level
*/
int Dialog_MidiClients::get_tree_line_num_coordinate(int client, int port, int type)
{
	int i, c, line = 0;
	QTreeWidgetItem *item;
	string client_str, port_str, item_str;
	int pos, num_of_items;
	bool found = false;

	// Get num of root items
	if (type == _MIDI_DEVICE_INPUT)
	{
		num_of_items = mod_synth_get_num_of_input_midi_clients();
	}
	else if (type == _MIDI_DEVICE_OUTPUT)
	{
		num_of_items = mod_synth_get_num_of_output_midi_clients();
	}
	else
	{
		return -1;
	}

	// Serched client number: string
	client_str = std::to_string(client) + ":";
	// Serched port :number string
	port_str = std::to_string(port) + ":";

	// look for the client item
	for (i = 0; i < num_of_items ; i++)
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
		pos = item_str.find(client_str);
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
					pos = item_str.find(port_str);
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
			// item not found
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


void Dialog_MidiClients::midi_input_client_selection_changed()
{
	map<QTreeWidgetItem *, midi_client_info_t* >::iterator it;
	int client, port;
	
	QList<QTreeWidgetItem*> selected_items_list =
		ui->treeWidget_inputClients->selectedItems();
	
	if (selected_items_list.length() > 0)
	{
		it = input_clients_tree_map.find(selected_items_list.at(0));
		if (it != input_clients_tree_map.end())
		{
			client = it->second->client;
			if (client == -1)
			{
				input_clients_selected_client = 0;     	// root selected
			}
			else
			{
				input_clients_selected_client = client;
			}

			port = it->second->port;
			input_clients_selected_port = port;
		}
	}
	else
	{
		input_clients_selected_client = -1;
		input_clients_selected_port = -1;
	}
}

void Dialog_MidiClients::midi_output_client_selection_changed()
{
	map<QTreeWidgetItem *, midi_client_info_t* >::iterator it;
	int client, port;
	
	QList<QTreeWidgetItem*> selected_items_list =
		ui->treeWidget_outputClients->selectedItems();
	
	if (selected_items_list.length() > 0)
	{
		it = output_clients_tree_map.find(selected_items_list.at(0));
		if (it != input_clients_tree_map.end())
		{
			client = it->second->client;
			if (client == -1)
			{
				output_clients_selected_client = 0;      	// root selected
			}
			else
			{
				output_clients_selected_client = client;
			}
			
			port = it->second->port;
			output_clients_selected_port = port;
		}
	}
	else
	{
		output_clients_selected_client = -1;
		output_clients_selected_port = -1;
	}
}

void Dialog_MidiClients::item_was_expanded(QTreeWidgetItem *item)
{
	if (!collapsing_expanding_all_in_progress)
	{
		update_connections();
	}
}

void Dialog_MidiClients::item_was_collapsed(QTreeWidgetItem *item)
{
	if (!collapsing_expanding_all_in_progress)
	{
		update_connections();
	}
}

void Dialog_MidiClients::connect_pushbutton_clicked(bool state)
{	
	int in_port = input_clients_selected_port;
	
	if (in_port == -1)
	{
		// Root selected
		in_port = 0;
	}
	
	int out_port = output_clients_selected_port;
	
	if (out_port == -1)
	{
		// Root selected
		out_port = 0;
	}
	
	mod_synth_connect_midi_clients(
		input_clients_selected_client, 
		in_port,
		output_clients_selected_client, 
		out_port);

	update_connections();
}

void Dialog_MidiClients::disconnect_pushbutton_clicked(bool state)
{
	int in_port = input_clients_selected_port;
	
	if (in_port == -1)
	{
		// Root selected
		in_port = 0;
	}
	
	int out_port = output_clients_selected_port;
	
	if (out_port == -1)
	{
		// Root selected
		out_port = 0;
	}
	
	mod_synth_disconnect_midi_clients(
		input_clients_selected_client, 
		in_port,
		output_clients_selected_client, 
		out_port);

	update_connections();
}

void Dialog_MidiClients::disconnect_all_pushbutton_clicked(bool state)
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
		mod_synth_disconnect_all_midi_clients();
		update_connections();
	}
}

void Dialog_MidiClients::refresh_data(bool state)
{
	mod_synth_refresh_alsa_midi_clients_data();
	
	input_clients_tree_updated = false;
	output_clients_tree_updated = false;
	
	ui->treeWidget_inputClients->clear();
	ui->treeWidget_outputClients->clear();

	all_expanded = false;
	ui->pushButton_midiConnectionsExpandAll->setText(tr("Expand All"));
	
	update_input_clients_tree();
	update_output_clients_tree();

	update_connections();
}

void Dialog_MidiClients::expand_all(bool state)
{
	collapsing_expanding_all_in_progress = true;
	
	if (!all_expanded)
	{
		ui->treeWidget_inputClients->expandAll();
		ui->treeWidget_outputClients->expandAll();
		ui->pushButton_midiConnectionsExpandAll->setText(tr("Collapse All"));
		all_expanded = true;
	}
	else
	{
		ui->treeWidget_inputClients->collapseAll();
		ui->treeWidget_outputClients->collapseAll();
		ui->pushButton_midiConnectionsExpandAll->setText(tr("Expand All"));
		all_expanded = false;
	}

	collapsing_expanding_all_in_progress = false;

	update_connections();
}

