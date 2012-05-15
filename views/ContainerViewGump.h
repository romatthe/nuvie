#ifndef __ContainerViewGump_h__
#define __ContainerViewGump_h__

/*
 *  ContainerViewGump.h
 *  Nuvie
 *
 *  Created by Eric Fry on Sat Mar 24 2012.
 *  Copyright (c) 2012. All rights reserved.
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

#include "DraggableView.h"

class Configuration;
class TileManager;
class ObjManager;
class Screen;
class Actor;
class Text;
class U6Bmp;
class ContainerWidgetGump;

class ContainerViewGump : public DraggableView {

	SDL_Surface *bg_image;
	GUI_Button *gump_button;
	GUI_Button *up_arrow_button;
	GUI_Button *down_arrow_button;

	ContainerWidgetGump *container_widget;

	GUI_Font *font;

	Actor *actor;
	Obj *container_obj;

public:
 ContainerViewGump(Configuration *cfg);
 ~ContainerViewGump();

 bool init(Screen *tmp_screen, void *view_manager, uint16 x, uint16 y, Text *t, Party *p, TileManager *tm, ObjManager *om);

 void Display(bool full_redraw);

 void set_actor(Actor *a);
 void set_container_obj(Obj *o);

 virtual GUI_status MouseDown(int x, int y, int button);
 virtual GUI_status MouseUp(int x, int y, int button);
 virtual GUI_status MouseMotion(int x,int y,Uint8 state) { return DraggableView::MouseMotion(x, y, state); }
 virtual void MoveRelative(int dx,int dy) { return DraggableView::MoveRelative(dx, dy); }


 GUI_status callback(uint16 msg, GUI_CallBack *caller, void *data);
 protected:

};

#endif /* __ContainerViewGump_h__ */
