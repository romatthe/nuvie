#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../nuvieDefs.h"
#include "../files/U6Lzw.h"
#include "../files/U6Lib_n.h"
#include "../files/NuvieIOFile.h"

int main(int argc, char **argv)
{
 U6Lib_n library;
 unsigned char *data;
 string name;
 char gametype[3]; // 'xx\0'
 char outfile[8]; // 'nnn.dat\0'

 if(argc != 2)
 {
  fprintf(stderr,"Usage: %s file.lzc\n",argv[0]);
  exit(1);
 }

 std::string path(argv[1]);

   if(library.open(path, 4, NUVIE_GAME_SE) == false)
     exit(1);

 for(int i=0;i<library.get_num_items();i++)
{
   fprintf(stderr,"size: %ld\n",library.get_item_size(i));
   data = library.get_item(i, NULL);
   snprintf(outfile, 8, "%d.dat", i);
   FILE * filed = fopen(outfile,"w");
   fwrite(data,1,library.get_item_size(i), filed);
   fclose(filed);
   free(data);
}
   library.close();

   exit(0);

}

