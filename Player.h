#ifndef __Player_h__
#define __Player_h__

/*
 *  player.h
 *  Nuive
 *
 *  Created by Eric Fry on Sun Mar 23 2003.
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

#include "U6def.h"
#include "Configuration.h"
#include "GameClock.h"

#include "Actor.h"
#include "ActorManager.h"
#include "MapWindow.h"

class Player
{
 Configuration *config;
 GameClock *clock;
 
 bool party_mode;
 Actor *actor;
 ActorManager *actor_manager;
 
 uint8 karma;
 
 MapWindow *map_window;
 
 public:
 
 Player(Configuration *cfg);
 
 bool init(Actor *a, ActorManager *am, MapWindow *mw, GameClock *c);
 
 Actor *get_actor();
 void get_location(uint16 *ret_x, uint16 *ret_y, uint8 *ret_level);
 
 void moveRelative(sint16 rel_x, sint16 rel_y);
 void Player::move(sint16 new_x, sint16 new_y, uint8 new_level);
 void moveLeft();
 void moveRight();
 void moveUp();
 void moveDown();
 void pass();
 
 protected:
 
 bool loadObjlistData();
};

#endif /* __Player_h__ */
