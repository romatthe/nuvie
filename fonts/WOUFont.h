#ifndef __WOUFont_h__
#define __WOUFont_h__

/*
 *  WOUFont.h
 *  Nuvie
 *
 *  Created by Eric Fry on Mon Nov 25 2013.
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

#include "Font.h"

class Configuration;
class Screen;
class U6Shape;

class WOUFont : public Font
{
private:
 unsigned char *font_data;
 unsigned char *char_buf;
 uint16 height;
 uint8 pixel_char;

 public:

   WOUFont();
   virtual ~WOUFont();

   bool init(const char *filename);
   bool initWithBuffer(unsigned char *buffer, uint32 buffer_len);


   virtual uint16 drawChar(Screen *screen, uint8 char_num, uint16 x, uint16 y,
                 uint8 color);

   uint16 drawStringToShape(U6Shape *shp, const char *str, uint16 x, uint16 y, uint8 color);
   uint8 drawCharToShape(U6Shape *shp, uint8 char_num, uint16 x, uint16 y, uint8 color);

   virtual uint16 getCharWidth(uint8 c);
   virtual uint16 getCharHeight() { return height; }
 private:
   bool initCharBuf();
};

#endif /* __WOUFont_h__ */
