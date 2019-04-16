/* B.Shapr
 * Step Sequencer Effect Plugin
 *
 * Copyright (C) 2019 by Sven Jähnichen
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef BSHAPR_H_
#define BSHAPR_H_

#include <cmath>
#include <array>
#include <lv2/lv2plug.in/ns/lv2core/lv2.h>
#include <lv2/lv2plug.in/ns/ext/atom/atom.h>
#include <lv2/lv2plug.in/ns/ext/atom/util.h>
#include <lv2/lv2plug.in/ns/ext/atom/forge.h>
#include <lv2/lv2plug.in/ns/ext/urid/urid.h>
#include <lv2/lv2plug.in/ns/ext/time/time.h>
#include "StaticArrayList.hpp"
#include "definitions.h"
#include "ports.h"
#include "urids.h"
#include "Point.hpp"
#include "Node.hpp"
#include "Shape.hpp"

typedef struct
{
	int count;
	bool ready;
	double inputMin;
	double inputMax;
	double outputMin;
	double outputMax;
} BShaprMonitor_t;

BShaprMonitor_t defaultMonitorData = {0, false, 0.0, 0.0};

class BShapr
{
public:
	BShapr (double samplerate, const LV2_Feature* const* features);
	~BShapr();

	void connect_port (uint32_t port, void *data);
	void run (uint32_t n_samples);

	LV2_URID_Map* map;

private:
	void play(uint32_t start, uint32_t end);
	void notifyMonitorToGui();
	void notifyShapeToGui (int shapeNr);
	double getPositionFromBeats (double beats);
	double getPositionFromFrames (uint64_t frames);

	double rate;
	float bpm;
	float speed;
	uint64_t bar;
	float barBeat;
	float beatsPerBar;
	uint32_t beatUnit;

	double position;
	uint64_t refFrame;

	// Audio buffers
	float* audioInput1;
	float* audioInput2;
	float* audioOutput1;
	float* audioOutput2;

	// Controllers
	float* new_controllers[NR_CONTROLLERS];
	float controllers [NR_CONTROLLERS];

	// Nodes and Maps
	Shape<MAXNODES> shapes[MAXSHAPES];

	// Atom port
	BShaprURIDs urids;

	LV2_Atom_Sequence* controlPort;
	LV2_Atom_Sequence* notifyPort;

	LV2_Atom_Forge forge;
	LV2_Atom_Forge_Frame notify_frame;

	// Data buffers
	float nodeBuffer[7];
	float shapeBuffer[MAXNODES * 7];

	// Internals
	bool ui_on;
	int monitorpos;
	std::array<BShaprNotifications, NOTIFYBUFFERSIZE> notifications;
	std::array<BShaprMonitor_t, MONITORBUFFERSIZE> monitor;
	bool scheduleNotifyShapes[MAXSHAPES];

};

#endif /* BSHAPR_H_ */