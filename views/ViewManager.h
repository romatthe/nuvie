#ifndef __ViewManager_h__
#define __ViewManager_h__

/*
 *  ViewManager.h
 *  Nuvie
 *
 *  Created by Eric Fry on Tue May 20 2003.
 *  Copyright (c) 2003. All rights reserved.
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

#include <SDL.h>

#include "U6def.h"
#include "Configuration.h"
#include "Screen.h"
#include "Text.h"
#include "TileManager.h"
#include "ObjManager.h"
#include "Party.h"
#include "Portrait.h"

#include "View.h"
#include "InventoryView.h"
#include "PortraitView.h"

class ViewManager
{
 protected:
 
 Configuration *config;
 int game_type;
 Screen *screen;
 Text *text;
 TileManager *tile_manager;
 ObjManager *obj_manager;
 Party *party;

 InventoryView *inventory_view;
 PortraitView *portrait_view;
 
 View *current_view;
 
 public:
 
 ViewManager(Configuration *cfg);
 virtual ~ViewManager();
 
 bool init(Screen *s, Text *t, Party *p, TileManager *tm, ObjManager *om, Portrait *portrait);
 
 void update_display();
 bool handle_input(SDLKey *input);

 void set_portrait_mode(uint8 actor_num, char *name);
 void set_inventory_mode(uint8 actor_num);
 void set_party_mode(); 
};

#endif /* __ViewManager_h__ */
