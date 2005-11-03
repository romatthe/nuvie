#ifndef __GUI_CALLBACK_H__
#define __GUI_CALLBACK_H__

/*
 *  GUI_CallBack.h
 *  Nuvie
 *
 *  Created by Eric Fry on Sat May 01 2004.
 *  Copyright (c) 2004. All rights reserved.
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

#include "GUI_status.h"

class GUI_CallBack
{

 public:

 GUI_CallBack() { return; }
 virtual ~GUI_CallBack() { return; }
 virtual GUI_status callback(uint16 msg, GUI_CallBack *caller, void *data) { printf("Warning! Unhandled callback. msg (%x)\n", msg); return GUI_PASS; }

};

#endif /* __GUI_CALLBACK_H__ */
