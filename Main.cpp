#include <stdio.h>
#include <stdlib.h>

//wchar_t list[30];
//fread( list, sizeof(wchar_t), 25, girl );

int main(int argc, char* argv[])
{
  if (argc != 2) {
    fprintf(stderr, "Error: wrong number of arguments");
    return -1;
  }
  printf("read %s\n", argv[1]);
  return 0;
}

