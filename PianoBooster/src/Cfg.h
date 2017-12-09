/*********************************************************************************/
/*!
@file           Cfg.h

@brief          Contains all the configuration Information.

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

#ifndef __CFG_H__
#define __CFG_H__

#include <libconfig.h++>

#define OPTION_BENCHMARK_TEST     0
#if OPTION_BENCHMARK_TEST
#define BENCHMARK_INIT()        benchMarkInit()
#define BENCHMARK(id,mesg)      benchMark(id,mesg)
#define BENCHMARK_RESULTS()     benchMarkResults()
#else
#define BENCHMARK_INIT()
#define BENCHMARK(id,mesg)
#define BENCHMARK_RESULTS()
#endif

class CColour
{
public:
    CColour() { red = green = blue = 0; }
    
    CColour(libconfig::Setting& setting)
    {
        red   = setting[0];
        green = setting[1];
        blue  = setting[2];
    }

    CColour(double r, double g, double b)
    {
        red   = static_cast<float>(r);
        green = static_cast<float>(g);
        blue  = static_cast<float>(b);
    }
    float red, green, blue;

    bool operator==(CColour colour)
    {
        if (red == colour.red && green == colour.green && blue == colour.blue)
            return true;
        return false;
    }
};

/*!
 * @brief   Contains all the configuration Information.
 */
class CfgCls
{
    // Current window position
    int _app_pos_x,
        _app_pos_y,
        _app_pos_w,
        _app_pos_h,
        _marker_clef,
        _marker_timesign,
        _marker_key,
        _marker_scroll,
        _play_rect;
    
public:
    
    // Bind public (constant) and private variables,
    // to make them read-only
    CfgCls() : app_pos_x(_app_pos_x),
               app_pos_y(_app_pos_y),
               app_pos_w(_app_pos_w),
               app_pos_h(_app_pos_h),
               marker_clef(_marker_clef),
               marker_timesign(_marker_timesign),
               marker_key(_marker_key),
               marker_scroll(_marker_scroll),
               play_rect(_play_rect)
    {
    }
    
    void readFile(std::string);
    
    void setAppDimensions(int x, int y,int w, int h);
    
    const int   &app_pos_x,
                &app_pos_y,
                &app_pos_w,
                &app_pos_h,
                &marker_clef,
                &marker_timesign,
                &marker_key,
                &marker_scroll,
                &play_rect;
    bool        app_quickstart,
                log_mididump,
                log_usefile;
    CColour     marker_bar_color,
                marker_beat_color,
                note_color,
                note_colordim,
                note_good_color,
                note_bad_color,
                note_unplayed_color,
                note_name_color,
                piano_good_color,
                piano_bad_color,
                playarea_bg_color,
                stave_color,
                stave_colordim;
    int         app_silencetimeout,
                app_swapinterval,
                app_tickrate,
                log_level,
                marker_clef2stave,
                marker_timesign2clef,
                marker_key2timesign,
                marker_scroll2key,
                play_channelkbdlights,
                play_chord_mingap,
                play_chord_maxlength,
                playrect_wpast,
                playrect_wprev,
                stave_gap_left,
                stave_gap_right;
    float       playrect_relx,
                stave_thickness;
    std::string log_file;
    
    int defaultWrongPatch() {return 7;} // Starts at 1
    int defaultRightPatch() {return 1;} // Starts at 1

    bool experimentalTempo;
    bool experimentalNoteLength;
};

extern CfgCls Cfg;

#endif //__CFG_H__
