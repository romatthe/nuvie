/*
 *  GUI_TextToggleButton.h
 *  Nuvie
 *
 *  Copyright (c) 2013. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */

#ifndef _GUI_TextToggleButton_h
#define _GUI_TextToggleButton_h

#include "GUI_button.h"

// A button that cycles through a set of captions when clicked

class GUI_TextToggleButton : public GUI_Button {
public:
	/* Passed the button data, position, width, height,
	   captions, number of captions, initial selection,
	   a font, an alignment (see GUI_Button),
	   the callback and a flag if it should be 2D (1) or 3D (0).

	   The captions are copied into the class. */
	GUI_TextToggleButton(void *data, int x, int y, int w, int h,
	                     const char* const* texts, int count, int selection,
	                     GUI_Font *font, int alignment,
	                     GUI_CallBack *callback, int flat = 0);

	~GUI_TextToggleButton();

	virtual int GetSelection() const;

	virtual GUI_status MouseUp(int x, int y, int button);
	virtual GUI_status Activate_button(int x = 0,int y = 0,int button = 1);

protected:
	int selection;
	char** texts;
	int count;
	int alignment;
};

#endif
