/*
 *  FontManager.cpp
 *  Nuvie
 *
 *  Created by Eric Fry on Wed Jan 28 2004.
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

#include <stdlib.h>

#include "nuvieDefs.h"
#include "Configuration.h"

#include "GUI.h"
#include "NuvieIOFile.h"
#include "U6Lib_n.h"
#include "NuvieBmpFile.h"
#include "FontManager.h"
#include "Font.h"
#include "ConvFont.h"
#include "U6Font.h"
#include "WOUFont.h"
#include "U6misc.h"

FontManager::FontManager(Configuration *cfg)
{
 config = cfg;
 num_fonts = 0;

 conv_font = NULL;
 conv_garg_font = NULL;
 conv_font_data = NULL;
 conv_font_widths = NULL;
}

FontManager::~FontManager()
{
 std::vector<Font *>::iterator font;

 for(font = fonts.begin(); font != fonts.end();)
   {
    delete *font;
    font++;
   }
 if(conv_font)
 {
   delete conv_font;
 }
 if(conv_garg_font)
 {
   delete conv_garg_font;
 }
 if(conv_font_data)
 {
   free(conv_font_data);
 }
 if(conv_font_widths)
 {
   free(conv_font_widths);
 }
}

bool FontManager::init(nuvie_game_t game_type)
{
  initConvFonts(game_type);

	if(game_type == NUVIE_GAME_U6)
		return initU6();

	return initWOUSystemFont();
}

bool FontManager::initU6()
{
 U6Font *font;
 unsigned char *font_data;
 std::string filename;
 NuvieIOFileRead u6_ch;

 config_get_path(config,"u6.ch",filename);

 if(u6_ch.open(filename) == false)
   return false;

 font_data = u6_ch.readAll();
 if(font_data == NULL)
   return false;

 // english font
 font = new U6Font();
 font->init(font_data,128,0);
 fonts.push_back(font);
 num_fonts++;

 // runic & gargoyle font
 font = new U6Font();
 font->init(&font_data[128 * 8], 128, 0);
 fonts.push_back(font);
 num_fonts++;

 free(font_data);
 return true;
}

bool FontManager::initWOU(std::string filename)
{
	 WOUFont *font;
	 std::string path;
	 U6Lib_n lib_file;

	 config_get_path(config, filename, path);

	 lib_file.open(path,4,NUVIE_GAME_MD); //can be either SE or MD just as long as it isn't set to U6 type.

	 font = new WOUFont();
	 unsigned char *buf = lib_file.get_item(0);
	 font->initWithBuffer(buf, lib_file.get_item_size(0)); //buf will be freed by ~Font()
	 fonts.push_back(font);
	 num_fonts++;
/*
	 font = new Font();
	 font->init(path.c_str());
	 fonts.push_back(font);
	 num_fonts++;
*/
	 return true;
}

bool FontManager::initWOUSystemFont()
{
  U6Font *font;
  std::string path;
  U6Lib_n lib_file;

  config_get_path(config, "system.lzc", path);

  lib_file.open(path,4,NUVIE_GAME_MD);

  font = new U6Font();
  unsigned char *buf = lib_file.get_item(3);
  font->init(buf, 128, 0);
  font->setDefaultColor(FONT_COLOR_WOU_NORMAL);
  font->setDefaultHighlightColor(FONT_COLOR_WOU_HIGHLIGHT);
  free(buf);
  fonts.push_back(font);
  num_fonts++;

  return true;
}

bool FontManager::initConvFonts(nuvie_game_t game_type)
{
  char filename[7]; // u6.bmp\0 or u6.dat\0
  std::string datadir = GUI::get_gui()->get_data_dir();
  std::string path;

  build_path(datadir, "images", path);
  datadir = path;
  build_path(datadir, "gumps", path);
  datadir = path;
  build_path(datadir, "fonts", path);
  datadir = path;

  std::string imagefile;
  sprintf(filename, "%s.bmp", get_game_tag(Game::get_game()->get_game_type()));

  build_path(datadir, filename, imagefile);

  NuvieBmpFile bmp;

  bmp.load(imagefile);

  conv_font_data = bmp.getRawIndexedDataCopy();

  std::string widthfile;
  sprintf(filename, "%s.dat", get_game_tag(Game::get_game()->get_game_type()));

  build_path(datadir, filename, widthfile);

  NuvieIOFileRead datfile;
  datfile.open(widthfile);
  uint32 bytes_read;
  conv_font_widths = datfile.readBuf(256, &bytes_read);
  datfile.close();

  conv_font = new ConvFont();
  ((ConvFont *)conv_font)->init(conv_font_data, conv_font_widths, 256, 0);

  if(game_type == NUVIE_GAME_U6)
  {
    conv_garg_font = new ConvFont();
    ((ConvFont *)conv_garg_font)->init(conv_font_data, conv_font_widths, 256, 128);
  }

  return true;
}

Font *FontManager::get_font(uint16 font_number)
{
 if(num_fonts > 0 && font_number < num_fonts)
   return fonts[font_number]; //fonts.at(font_number);

 return NULL;
}
