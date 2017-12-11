/*********************************************************************************/
/*!
@file           Tempo.h

@brief          Tries to automatically calculate the tempo.

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

#ifndef __TEMPO_H__
#define __TEMPO_H__

#include "MidiEvent.h"
#include "MidiFile.h"
#include "Chord.h"

#define MICRO_SECOND 1000000.0

// Define a chord
class CTempo
{
public:
    
    CTempo();
    
    void setSavedWantedChord(CChord * savedWantedChord);
    
    void reset();

    // Tempo, microseconds-per-MIDI-quarter-note
    void setMidiTempo(int tempo);
    
    // Beats per minute
    float getBPM();

    void setSpeed(float speed);
    float getSpeed();

    int mSecToTicks(int mSec);

    void insertPlayingTicks(int ticks);
    void removePlayingTicks(int ticks);
    void clearPlayingTicks();

    void adjustTempo(int * ticks);
    
    static void enableFollowTempo(bool enable);
    
private:
    float m_userSpeed; // controls the speed of the piece playing
    float m_midiTempo; // controls the speed of the piece playing
    int m_jumpAheadDelta;
    static int m_cfg_maxJumpAhead;
    static int m_cfg_followTempoAmount;
    CChord *m_savedWantedChord; // A copy of the wanted chord complete with both left and right parts


};

#endif  // __TEMPO_H__

