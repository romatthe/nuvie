/*
 *  BMPFont.cpp
 *  Nuvie
 *
 *  Created by Eric Fry on Sat Feb 09 2013.
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

#include <stdio.h>

#include <string>
#include <cctype>

#include "nuvieDefs.h"
#include "NuvieIOFile.h"
#include "Configuration.h"

#include "Screen.h"

#include "BMPFont.h"

BMPFont::BMPFont()
{
 num_chars = 0;
 offset = 0;
 char_w = 0;
 char_h = 0;
 font_width_data = NULL;
 sdl_font_data = NULL;
 rune_mode = false;
 dual_font_mode = false;
}

BMPFont::~BMPFont()
{
  if(sdl_font_data)
  {
    SDL_FreeSurface(sdl_font_data);
  }

	if(font_width_data)
	{
		free(font_width_data);
	}
}

bool BMPFont::init(std::string bmp_filename, bool dual_fontmap)
{
	dual_font_mode = dual_fontmap;
	num_chars = 256;

	std::string full_filename = bmp_filename;

	full_filename += ".bmp";

	sdl_font_data = SDL_LoadBMP(full_filename.c_str());

	SDL_SetColorKey(sdl_font_data, SDL_TRUE, SDL_MapRGB(sdl_font_data->format, 0, 0x70, 0xfc));

	char_w = sdl_font_data->w / 16;
	char_h = sdl_font_data->h / 16;

	//read font width data. For variable width fonts.
	full_filename = bmp_filename;
	full_filename += ".dat";

	NuvieIOFileRead font_width_data_file;
	if(font_width_data_file.open(full_filename))
	{
		font_width_data = font_width_data_file.readAll();
		font_width_data_file.close();
	}

	return true;
}

uint16 BMPFont::getStringWidth(const char *str, uint16 string_len)
{
	uint16 i;
	uint16 w=0;

	for(i=0;i<string_len;i++)
	{
		if(dual_font_mode && str[i] == '<')
		{
			offset = 128;
		}
		else if(dual_font_mode && str[i] == '>')
		{
			offset = 0;
		}
		else
		{
			w += getCharWidth(str[i]+offset);
		}
	}

	return w;


}
uint16 BMPFont::getCharWidth(uint8 c)
{
	if(font_width_data)
	{
		return font_width_data[c];
	}

	return char_w;
}

uint16 BMPFont::drawChar(Screen *screen, uint8 char_num, uint16 x, uint16 y,
                    uint8 color)
{
	SDL_Rect src;
	SDL_Rect dst;

	if(dual_font_mode)
	{
		if(char_num == '<')
		{
			rune_mode = true;
			return 0;
		}
		else if(char_num == '>')
		{
			rune_mode = false;
			return 0;
		}
	}

	if(rune_mode)
	{
		char_num += 128;
	}

	src.w = char_w;
	src.h = char_h;
	src.x = (char_num % 16) * char_w;
	src.y = (char_num / 16) * char_h;

	dst.w = char_w;
	dst.h = char_h;
	dst.x = x;
	dst.y = y;

	SDL_BlitSurface(sdl_font_data, &src, screen->get_sdl_surface(), &dst);

	return getCharWidth(char_num);
}
