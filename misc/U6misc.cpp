/*
 *  misc.cpp
 *  Nuvie
 *
 *  Created by Eric Fry on Sat Jun 14 2003.
 *  Copyright (c) 2003. All rights reserved.
 *
 */
#include <cstdio>

#include "nuvieDefs.h"

#include "U6misc.h"
#include "Configuration.h"

std::string config_get_game_key(Configuration *config)
{
 std::string game_key, game_name;
 
 config->value("config/GameName",game_name);
 
 game_key.assign("config/");
 game_key.append(game_name);
 
 return game_key;
}

void config_get_path(Configuration *config, std::string filename, std::string &path)
{
 std::string key, game_name;
 
 config->value("config/GameName",game_name);
 
 key.assign("config/");
 key.append(game_name);
 key.append("/gamedir");
    
 config->pathFromValue(key, filename, path);
 
 return;
}

//return the uint8 game_type from a char string
uint8 get_game_type(const char *string)
{
 if(string != NULL && strlen(string) >= 2)
   {
    if(strcmp("md",string) == 0 || strcmp("martian",string) == 0)
      return NUVIE_GAME_MD;
    if(strcmp("se",string) == 0 || strcmp("savage",string) == 0)
      return NUVIE_GAME_SE;
    if(strcmp("u6",string) == 0 || strcmp("ultima6",string) == 0)
      return NUVIE_GAME_U6;
   } 

 return NUVIE_GAME_NONE;
}

void print_b(uint8 num)
{
 sint8 i;
 
 for(i=7;i>=0;i--)
 {
  if(num & (1<<i))
    printf("1");
  else
    printf("0");
 }
 
 return;
}

void print_indent(uint8 indent)
{
 uint16 i;
 
 for(i=0;i < indent;i++)
  printf(" ");

 return;
}
