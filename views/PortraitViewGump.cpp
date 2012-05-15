/*
 *  PortraitViewGump.cpp
 *  Nuvie
 *
 *  Created by Eric Fry on Mon Apr 09 2012.
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
#include <cassert>
#include "nuvieDefs.h"
#include "U6misc.h"
#include "Event.h"
#include "GUI.h"
#include "GUI_button.h"

#include "Party.h"
#include "Actor.h"
#include "Portrait.h"
#include "ViewManager.h"

#include "ContainerWidgetGump.h"
#include "PortraitViewGump.h"


PortraitViewGump::PortraitViewGump(Configuration *cfg) : DraggableView(cfg)
{
	bg_image = NULL;
	font = NULL;
	portrait_data = NULL;
}

PortraitViewGump::~PortraitViewGump()
{
	if(bg_image)
		delete bg_image;
	if(font)
		delete font;
	if(portrait_data)
		free(portrait_data);
}

bool PortraitViewGump::init(Screen *tmp_screen, void *view_manager, uint16 x, uint16 y, Text *t, Party *p, TileManager *tm, ObjManager *om, Portrait *por, Actor *a)
{
	View::init(x,y,t,p,tm,om);

	SetRect(area.x, area.y, 188, 91);

	portrait = por;
	actor = a;
	portrait_data = portrait->get_portrait_data(actor);

	std::string datadir = GUI::get_gui()->get_data_dir();
	std::string imagefile;
	std::string path;

	build_path(datadir, "images", path);
	datadir = path;
	build_path(datadir, "gumps", path);
	datadir = path;

	gump_button = loadButton(datadir, "gump", 0, 67);

	build_path(datadir, "portrait_bg.bmp", imagefile);
	bg_image = SDL_LoadBMP(imagefile.c_str());

	SDL_SetColorKey(bg_image, SDL_SRCCOLORKEY, SDL_MapRGB(bg_image->format, 0, 0x70, 0xfc));

	font = new GUI_Font(GUI_FONT_GUMP);
	font->SetColoring( 0x08, 0x08, 0x08, 0x80, 0x58, 0x30, 0x00, 0x00, 0x00);

	return true;
}

void PortraitViewGump::Display(bool full_redraw)
{
 char buf[5]; //xxxx\n
 //display_level_text();
 //display_spell_list_text();
 SDL_Rect dst;
 dst = area;
 SDL_BlitSurface(bg_image, NULL, surface, &dst);

 DisplayChildren(full_redraw);
 screen->blit(area.x+25,area.y+17,portrait_data,8,PORTRAIT_WIDTH,PORTRAIT_HEIGHT,PORTRAIT_WIDTH,false);

 int w,h;
 font->TextExtent(actor->get_name(), &w, &h);

 if(w < 138)
  {
 	 w = (138 - w) / 2;
  }
  else
 	 w = 0;

 font->SetColoring( 0x08, 0x08, 0x08, 0x80, 0x58, 0x30, 0x00, 0x00, 0x00);

 font->TextOut(screen->get_sdl_surface(), area.x + 29 + w, area.y + 6, actor->get_name());

 snprintf(buf, 4, "%d", actor->get_strength());
 font->TextExtent(buf, &w, &h);
 font->TextOut(screen->get_sdl_surface(), area.x + 170 - w, area.y + 18, buf);

 snprintf(buf, 4, "%d", actor->get_dexterity());
 font->TextExtent(buf, &w, &h);
 font->TextOut(screen->get_sdl_surface(), area.x + 170 - w, area.y + 27, buf);

 snprintf(buf, 4, "%d", actor->get_intelligence());
 font->TextExtent(buf, &w, &h);
 font->TextOut(screen->get_sdl_surface(), area.x + 170 - w, area.y + 36, buf);

 font->SetColoring( 0x6c, 0x00, 0x00, 0xbc, 0x34, 0x00, 0x00, 0x00, 0x00);

 snprintf(buf, 4, "%d", actor->get_magic());
 font->TextExtent(buf, &w, &h);
 font->TextOut(screen->get_sdl_surface(), area.x + 142 - w, area.y + 55, buf);

 snprintf(buf, 4, "%d", actor->get_maxmagic());
 font->TextExtent(buf, &w, &h);
 font->TextOut(screen->get_sdl_surface(), area.x + 170 - w, area.y + 55, buf);

 font->SetColoring( 0x00, 0x3c, 0x70, 0x74, 0x74, 0x74, 0x00, 0x00, 0x00);

 snprintf(buf, 4, "%d", actor->get_hp());
 font->TextExtent(buf, &w, &h);
 font->TextOut(screen->get_sdl_surface(), area.x + 142 - w, area.y + 64, buf);

 snprintf(buf, 4, "%d", actor->get_maxhp());
 font->TextExtent(buf, &w, &h);
 font->TextOut(screen->get_sdl_surface(), area.x + 170 - w, area.y + 64, buf);

 font->SetColoring( 0xa8, 0x28, 0x00, 0xa8, 0x54, 0x00, 0x00, 0x00, 0x00);

 snprintf(buf, 4, "%d", actor->get_level());
 font->TextExtent(buf, &w, &h);
 font->TextOut(screen->get_sdl_surface(), area.x + 142 - w, area.y + 73, buf);

 snprintf(buf, 4, "%d", actor->get_exp());
 font->TextExtent(buf, &w, &h);
 font->TextOut(screen->get_sdl_surface(), area.x + 170 - w, area.y + 73, buf);

 update_display = false;
 screen->update(area.x, area.y, area.w, area.h);


 return;
}

GUI_status PortraitViewGump::callback(uint16 msg, GUI_CallBack *caller, void *data)
{
	//close gump and return control to Magic class for clean up.
	if(caller == gump_button)
	{
		Game::get_game()->get_view_manager()->close_gump(this);
		return GUI_YUM;
	}

    return GUI_PASS;
}