
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *read_input(const char *file_name) {
  FILE *fileptr;

  fileptr = fopen(file_name, "r");

  if (fileptr) {
    // read entire file into a buffer on heap
    char *buffer = 0;
    long length;
    fseek(fileptr, 0, SEEK_END);
    length = ftell(fileptr);
    fseek(fileptr, 0, SEEK_SET);
    buffer = malloc(length);
    if (buffer) {
      fread(buffer, 1, length, fileptr);
    }
    fclose(fileptr);

    return buffer;
  } else {
    printf("not able to open file");
  }

  fclose(fileptr);

  return "";
}

struct Game {
  int id;
  // the max number of each color for any one turn
  int max_red;
  int max_green;
  int max_blue;
};

struct Game parse_game(const char *game) {
  char *token;
  char *saveptr = NULL;

  token = strtok_r(game, ":", &saveptr);
  int gameId = atoi(token + 5);

  int max_red = 0, max_green = 0, max_blue = 0;

  token = strtok_r(NULL, ";", &saveptr);
  while (token != NULL) {
    // printf("Token: %s\n", token);

    char *colorToken = token;
    // Find the position of the first non-digit character
    while (*colorToken && isdigit(*colorToken)) {
      colorToken++;
    }

    // Check if a non-digit character was found
    if (*colorToken) {
      // Trim any leading whitespace after the number
      while (*colorToken == ' ') {
        colorToken++;
      }

      // Get the number
      int num = atoi(token);

      // Get the color
      char *color = colorToken;
      // printf("Num: %d\n", num);
      // printf("Color: %s\n", color);

      if (strcmp(color, "red") == 0) {
        if (num > max_red) {
          max_red = num;
        }
      } else if (strcmp(color, "green") == 0) {
        if (num > max_green) {
          max_green = num;
        }
      } else if (strcmp(color, "blue") == 0) {
        if (num > max_blue) {
          max_blue = num;
        }
      }
    }

    token = strtok_r(NULL, ";", &saveptr);
  }

  return (struct Game){gameId, max_red, max_green, max_blue};
}

const int MAX_GREEN = 13;
const int MAX_BLUE = 14;
const int MAX_RED = 12;
// if the game is possible, then it returns the id of the game
// otherwise returns 0
int is_game_possible(const char *game) {
  struct Game gameNumbers = parse_game(game);

  if (gameNumbers.max_red > MAX_RED) {
    return 0;
  }

  if (gameNumbers.max_green > MAX_GREEN) {
    return 0;
  }

  if (gameNumbers.max_blue > MAX_BLUE) {
    return 0;
  }

  return gameNumbers.id;
}

int test() {
  char *input = read_input("./src/test_input.txt");

  // go through each line
  char *saveptr = NULL;
  char *curr_line = strtok_r(input, "\n", &saveptr);
  int total = 0;

  while (curr_line != NULL) {
    printf("curr_line: %s\n", curr_line);

    char *copy;
    strcpy(copy, curr_line);

    int game_id = is_game_possible(copy);
    printf("game_id: %d\n", game_id);

    total += game_id;

    curr_line = strtok_r(NULL, "\n", &saveptr);
  }

  printf("total: %d\n", total);

  return total == 8;
}

int main() {
  printf("Hello, world!\n");

  const char *input = read_input("./src/input.txt");

  int test_result = test();
  printf("test result: %d\n", test_result);

  return 0;
}
