/*********************************************************************************/
/*!
@file           Tempo.cpp

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


#include "Tempo.h"

int CTempo::m_cfg_followTempoAmount = 0;
int CTempo::m_cfg_maxJumpAhead = 0;

CTempo::CTempo()
{
    m_savedWantedChord = 0;
    reset();
}

void CTempo::setSavedWantedChord(CChord * savedWantedChord)
{
    m_savedWantedChord = savedWantedChord;
}

void CTempo::reset()
{
    // 120 beats per minute is the default
    setMidiTempo(static_cast<int>(( 60 * MICRO_SECOND ) / 120 ));
    m_jumpAheadDelta = 0;
}

// Tempo, microseconds-per-MIDI-quarter-note
void CTempo::setMidiTempo(int tempo)
{
    m_midiTempo = (static_cast<float>(tempo) * DEFAULT_PPQN) / CMidiFile::getPulsesPerQuarterNote();
    ppLogWarn("Midi Tempo %f  ppqn %d %d", m_midiTempo, CMidiFile::getPulsesPerQuarterNote(), tempo);
}

float CTempo::getBPM()
{
    return (60000000.0 * m_userSpeed * DEFAULT_PPQN
            / (m_midiTempo * CMidiFile::getPulsesPerQuarterNote()));
}

void CTempo::setSpeed(float speed)
{
    // limit the allowed speed
    if (speed > 2.0f)
        speed = 2.0f;
    if (speed < 0.1f)
        speed = 0.1f;
    m_userSpeed = speed;
}

float CTempo::getSpeed()
{
    return m_userSpeed;
}

int CTempo::mSecToTicks(int mSec)
{
    return static_cast<int>(mSec * m_userSpeed * (100.0 * MICRO_SECOND) /m_midiTempo);
}

void CTempo::insertPlayingTicks(int ticks)
{
    m_jumpAheadDelta -= ticks;
    if (m_jumpAheadDelta < CMidiFile::ppqnAdjust(-10)*SPEED_ADJUST_FACTOR)
        m_jumpAheadDelta = CMidiFile::ppqnAdjust(-10)*SPEED_ADJUST_FACTOR;
}

void CTempo::removePlayingTicks(int ticks)
{
    if (m_cfg_maxJumpAhead != 0)
        m_jumpAheadDelta = ticks;
}
void CTempo::clearPlayingTicks()
{
    m_jumpAheadDelta = 0;
}


void CTempo::enableFollowTempo(bool enable)
{
    if (enable)
    {
        m_cfg_maxJumpAhead = 1;
        m_cfg_followTempoAmount = 1;
    }
    else
    {
        m_cfg_maxJumpAhead = 0;
        m_cfg_followTempoAmount = 0;
    }
}

void CTempo::adjustTempo(int * ticks)
{
    if (m_jumpAheadDelta && m_cfg_maxJumpAhead && m_savedWantedChord)
    {
        if (m_jumpAheadDelta > 0)
            *ticks += m_jumpAheadDelta;

        // Automatically adjust the speed
        m_userSpeed = m_userSpeed + m_userSpeed * m_jumpAheadDelta * 0.00002;

        if (m_userSpeed> 2.0) m_userSpeed = 2.0;
        if (m_userSpeed < 0.2) m_userSpeed = 0.2;
        printf("%03.0f  %5d\r",m_userSpeed *100, m_jumpAheadDelta );
        fflush(stdout);

        m_jumpAheadDelta = 0;
    }
}




