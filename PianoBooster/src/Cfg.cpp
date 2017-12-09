/*********************************************************************************/
/*!
@file           Cfg.cpp

@brief          xxx.

@author         L. J. Barman

    Copyright (c)   2008-2009, L. J. Barman, all rights reserved

    This file is part of the PianoBooster application

    PianoBooster is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    PianoBooster is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with PianoBooster.  If not, see <http://www.gnu.org/licenses/>.

*/
/*********************************************************************************/



#include <iostream>
#include "Cfg.h"

CfgCls Cfg;

void CfgCls::readFile(std::string file)
{
        
    libconfig::Config config;

    config.readFile(file.c_str());
    
    app_quickstart     = config.lookup("app.quickstart");
    app_swapinterval   = config.lookup("app.swapinterval");
    app_silencetimeout = config.lookup("app.silencetimeout");
    app_tickrate       = config.lookup("app.tickrate");
    
    log_level    = config.lookup("log.level");
    log_usefile  = config.lookup("log.usefile");
    log_file     = config.lookup("log.file").c_str();
    log_mididump = config.lookup("log.mididump");
    
    play_channelkbdlights = config.lookup("play.channelkbdlights");
    play_chord_mingap     = config.lookup("play.chord_mingap");
    play_chord_maxlength  = config.lookup("play.chord_maxlength");
    
    marker_bar_color     = CColour(config.lookup("style.marker_bar_color"));
    marker_beat_color    = CColour(config.lookup("style.marker_beat_color"));
    marker_clef2stave    = config.lookup("style.marker_clef2stave");
    marker_timesign2clef = config.lookup("style.marker_timesign2clef");
    marker_key2timesign  = config.lookup("style.marker_key2timesign");
    marker_scroll2key    = config.lookup("style.marker_scroll2key");
    note_color           = CColour(config.lookup("style.note_color"));
    note_colordim        = CColour(config.lookup("style.note_colordim"));
    note_good_color      = CColour(config.lookup("style.note_good_color"));
    note_bad_color       = CColour(config.lookup("style.note_bad_color"));
    note_unplayed_color  = CColour(config.lookup("style.note_unplayed_color"));
    note_name_color      = CColour(config.lookup("style.note_name_color"));
    piano_good_color     = CColour(config.lookup("style.piano_good_color"));
    piano_bad_color      = CColour(config.lookup("style.piano_bad_color"));
    playarea_bg_color    = CColour(config.lookup("style.playarea_bg_color"));
    playrect_wprev       = config.lookup("style.playrect_wprev");
    playrect_wpast       = config.lookup("style.playrect_wpast");
    playrect_relx        = config.lookup("style.playrect_relx");
    stave_color          = CColour(config.lookup("style.stave_color"));
    stave_colordim       = CColour(config.lookup("style.stave_colordim"));
    stave_gap_left       = config.lookup("style.stave_gap_left");
    stave_gap_right      = config.lookup("style.stave_gap_right");
    stave_thickness      = config.lookup("style.stave_thickness");
    
    this->_marker_clef     = stave_gap_left + marker_clef2stave;
    this->_marker_timesign = marker_clef + marker_timesign2clef;
    this->_marker_key      = marker_timesign + marker_key2timesign;
    this->_marker_scroll   = marker_key + marker_scroll2key;
    this->_play_rect       = (int) (marker_scroll
        + (app_pos_w - stave_gap_right - marker_scroll) * playrect_relx);
    
    experimentalTempo        = false;
    experimentalNoteLength   = false;
    
}

void CfgCls::setAppDimensions(int x, int y, int w, int h)
{
    this->_app_pos_x = x;
    this->_app_pos_y = y;
    this->_app_pos_w = w;
    this->_app_pos_h = h;
    this->_play_rect = (int) (marker_scroll
    + (app_pos_w - stave_gap_right - marker_scroll) * playrect_relx);
}
