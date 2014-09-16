#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include "json.h"

int main(int argc, char * argv[])
{
   struct stat statbuf;
   int fd;
   char * data;
   int i;
   json_value * jv;

   if ((fd = open("file.json", O_RDONLY)) == 0) {
      printf("Error: Cannot open file\n");
      return -1;
   }

   if (fstat(fd, &statbuf) == -1) {
      printf("Error: Failed to stat file");
      return -1;
   }

   printf("Bytes: %u\n", (uint32_t) statbuf.st_size);
  

   data = (char*)malloc(statbuf.st_size); 

   if (read(fd, data, statbuf.st_size) != statbuf.st_size) {
       printf("Error: Failed to read all of the file\n");
       return -1;
   }

   jv = json_parse(data, statbuf.st_size);

   printf("Type %d\n", jv->type);
   printf("Length %d\n", jv->u.object.length);

   for (i = 0; i < jv->u.object.length; i++) {
       printf("Name %s\n", jv->u.object.values[i].name);
       printf("Type %d\n", jv->u.object.values[i].value->type);
   }
 
   free(data);
   return 0;
}
