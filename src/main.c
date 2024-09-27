#include "dir.h"
#include "log.h"
#include "stdheader.h"
#include "structs.h"
#include <stdio.h>

int main(int argc, char **argv) {
  /* Check for file arguments */
  if (argc < 2) {
    logerror(__func__, "Missing file argument");
    exit(1);
  }

  /* change working directory */
  if (move_directory(argv[1]) != 0) {
    logerror(__func__, "Error -> move_directory");
    exit(1);
  }

  /* Declaration */
  int i;
  struct dir_data *data;

  /* Initialization */
  data = get_directory_entries(argv[1]);
  if (data == NULL) {
    logerror(__func__, "Error: get_directory_entries");
    exit(1);
  }

  /* print the directory entries */
  for (i = 0; i < data->count; i++) {
    printf("%d %s %s\n", i, data->list[i]->type, data->list[i]->name);
  }

  /* loop to traverse directories */
  printf("Selected file: %s\n", argv[1]);
  while (1) {
    /* choose a file name and append path to that dir */
    scanf("%d", &i);
    if (i == -1) {
      printf("Quitting\n");
      break;
    }

    printf("Selected file:%s\n", data->list[i]->name);
    /* check if selected file is a directory */
    if (dir_check(data, i) == 0) {
      /* get new directory entries */
      data = change_directory(data, i);
      if (data == NULL) {
        logerror(__func__, "Error: change_directory");
        exit(1);
      }

      /* print the directory entries */
      for (i = 0; i < data->count; i++) {
        printf("%d %s %s\n", i, data->list[i]->type, data->list[i]->name);
      }
    }
  }

  free_dir(data);

  return 0;
}
