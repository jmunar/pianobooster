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

#include "Cfg.h"

CfgCls Cfg;

bool lookupCColour(libconfig::Config &config, const char *path,
                   CColour &value)
{
    bool exists = config.exists(path);
    
    if(exists)
    {
        value = CColour(config.lookup(path));
    }
    
    return exists;
}

void CfgCls::readFile(std::string file)
{
    
    libconfig::Config config;

    config.readFile(file.c_str());
    
    config.lookupValue("app.quickstart", app_quickstart);
    config.lookupValue("app.swapinterval", app_swapinterval);
    config.lookupValue("app.silencetimeout", app_silencetimeout);
    config.lookupValue("app.tickrate", app_tickrate);
    
    config.lookupValue("log.level", log_level);
    config.lookupValue("log.usefile", log_usefile);
    config.lookupValue("log.file", log_file);
    config.lookupValue("log.mididump", log_mididump);
    
    config.lookupValue("play.channelkbdlights", play_channelkbdlights);
    config.lookupValue("play.chord_mingap", play_chord_mingap);
    config.lookupValue("play.chord_maxlength", play_chord_maxlength);
    config.lookupValue("play.show_note_length", play_show_note_length);
    
    lookupCColour(config, "style.accuracy_bar_color", accuracy_bar_color);
    lookupCColour(config, "style.marker_bar_color", marker_bar_color);
    lookupCColour(config, "style.marker_beat_color", marker_beat_color);
    config.lookupValue("style.marker_clef2stave", marker_clef2stave);
    config.lookupValue("style.marker_timesign2clef", marker_timesign2clef);
    config.lookupValue("style.marker_key2timesign", marker_key2timesign);
    config.lookupValue("style.marker_scroll2key", marker_scroll2key);
    lookupCColour(config, "style.note_color", note_color);
    lookupCColour(config, "style.note_colordim", note_colordim);
    lookupCColour(config, "style.note_good_color", note_good_color);
    lookupCColour(config, "style.note_bad_color", note_bad_color);
    lookupCColour(config, "style.note_unplayed_color", note_unplayed_color);
    lookupCColour(config, "style.note_name_color", note_name_color);
    lookupCColour(config, "style.piano_good_color", piano_good_color);
    lookupCColour(config, "style.piano_bad_color", piano_bad_color);
    lookupCColour(config, "style.playarea_bg_color", playarea_bg_color);
    lookupCColour(config, "style.playarea_text_color", playarea_text_color);
    config.lookupValue("style.playrect_wprev", playrect_wprev);
    config.lookupValue("style.playrect_wpast", playrect_wpast);
    config.lookupValue("style.playrect_relx", playrect_relx);
    lookupCColour(config, "style.playrect_bg_color", playrect_bg_color);
    lookupCColour(config, "style.playrect_line_color", playrect_line_color);
    lookupCColour(config, "style.playrect_border_color", playrect_border_color);
    lookupCColour(config, "style.stave_color", stave_color);
    lookupCColour(config, "style.stave_colordim", stave_colordim);
    config.lookupValue("style.stave_gap_left", stave_gap_left);
    config.lookupValue("style.stave_gap_right", stave_gap_right);
    config.lookupValue("style.stave_thickness", stave_thickness);
    
    // Variables depending on explicit parameters
    this->_marker_clef     = stave_gap_left + marker_clef2stave;
    this->_marker_timesign = marker_clef + marker_timesign2clef;
    this->_marker_key      = marker_timesign + marker_key2timesign;
    this->_marker_scroll   = marker_key + marker_scroll2key;
    
    experimentalTempo        = false;
    
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
