/*********************************************************************************/
/*!
@file           Score.cpp

@brief          xxxx.

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

#include <stdarg.h>
#include "Cfg.h"
#include "Draw.h"
#include "Score.h"

CScore::CScore(CSettings* settings) : CDraw(settings)
{
    size_t i;
    m_piano = new CPiano(settings);
    m_rating = 0;
    for (i=0; i< arraySize(m_scroll); i++)
    {
        m_scroll[i] = new CScroll(i, settings);
        m_scroll[i]->setChannel(i);
    }

    m_activeScroll = -1;
    m_stavesDisplayListId = 0;
    m_scoreDisplayListId = 0;//glGenLists (1);
}

CScore::~CScore()
{
    delete m_piano;
    size_t i;
    for (i=0; i< arraySize(m_scroll); i++)
        delete m_scroll[i];

    if (m_scoreDisplayListId != 0)
        glDeleteLists(m_scoreDisplayListId, 1);
    m_scoreDisplayListId = 0;

    if (m_stavesDisplayListId != 0)
        glDeleteLists(m_stavesDisplayListId, 1);
    m_stavesDisplayListId = 0;
}

void CScore::init()
{
}

void CScore::drawScroll(bool refresh)
{
    if (refresh == false)
    {
        float topY = CStavePos(PB_PART_right, MAX_STAVE_INDEX).getPosY();
        float bottomY = CStavePos(PB_PART_left, MIN_STAVE_INDEX).getPosY();
        drColour (Cfg.playarea_bg_color);
        glRectf(Cfg.marker_scroll, topY, Cfg.app_pos_w, bottomY);
    }

    if (m_stavesDisplayListId == 0)
        m_stavesDisplayListId = glGenLists (1);

    if (getCompileRedrawCount())
    {

        glNewList (m_stavesDisplayListId, GL_COMPILE_AND_EXECUTE);
            drawSymbol(CSymbol(PB_SYMBOL_playingZone,  CStavePos(PB_PART_both, 0)), Cfg.play_rect);
            drawStaves(Cfg.marker_scroll, Cfg.app_pos_w - Cfg.stave_gap_right);
        glEndList ();
                // decrement the compile count until is reaches zero
        forceCompileRedraw(0);

    }
    else
        glCallList(m_stavesDisplayListId);

    drawScrollingSymbols(true);
    m_piano->drawPianoInput();
}

void CScore::drawScore()
{
    if (getCompileRedrawCount())
    {
        if (m_scoreDisplayListId == 0)
            m_scoreDisplayListId = glGenLists (1);

        glNewList (m_scoreDisplayListId, GL_COMPILE_AND_EXECUTE);
            drColour (Cfg.stave_color);

            drawSymbol(CSymbol(PB_SYMBOL_gClef, CStavePos(PB_PART_right, -1)), Cfg.marker_clef); // The Treble Clef
            drawSymbol(CSymbol(PB_SYMBOL_fClef, CStavePos(PB_PART_left, 1)), Cfg.marker_clef);
            drawKeySignature(CStavePos::getKeySignature());
            drawStaves(Cfg.stave_gap_left, Cfg.marker_scroll);
        glEndList ();
    }
    else
        glCallList(m_scoreDisplayListId);
}



