
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *read_input() {
  char *file_name = "./src/input.txt";

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

// given lines of text, combine first and last number of each line and sum all
// of those combined numbers
int getSum(const char text[]) {
  // get one line at a time
  char *curr_line = strtok(text, "\n");

  int total = 0;

  while (curr_line != NULL) {
    // printf("curr_line: %s\n", curr_line);

    int first_num = 0;
    int last_num = 0;

    for (int i = 0; i < strlen(curr_line); i++) {
      char curr_char = curr_line[i];
      if (curr_char >= '0' && curr_char <= '9') {
        first_num = curr_char - '0';
        break;
      }
    }
    for (int i = strlen(curr_line) - 1; i >= 0; i--) {
      char curr_char = curr_line[i];
      if (curr_char >= '0' && curr_char <= '9') {
        last_num = curr_char - '0';
        break;
      }
    }

    // printf("first: %d\n", first_num);
    // printf("last: %d\n", last_num);

    // combine 1 and 9 to 19
    int combined;
    if (first_num > 0 && last_num > 0) {
      combined = first_num * 10 + last_num;
    } else {
      combined = first_num + last_num;
    }

    // printf("combined: %d\n", combined);
    total += combined;

    curr_line = strtok(NULL, "\n");
  }

  return total;
}

// helper: return number if the given string contains a number
int check_if_string_contains(char *substr) {
  if (strstr(substr, "one") != NULL) {
    return 1;
  }
  if (strstr(substr, "two") != NULL) {
    return 2;
  }
  if (strstr(substr, "three") != NULL) {
    return 3;
  }
  if (strstr(substr, "four") != NULL) {
    return 4;
  }
  if (strstr(substr, "five") != NULL) {
    return 5;
  }
  if (strstr(substr, "six") != NULL) {
    return 6;
  }
  if (strstr(substr, "seven") != NULL) {
    return 7;
  }
  if (strstr(substr, "eight") != NULL) {
    return 8;
  }
  if (strstr(substr, "nine") != NULL) {
    return 9;
  }

  return 0;
}

int get_sum_part_two(char *text) {
  // get one line at a time
  char *curr_line = strtok(text, "\n");

  int total = 0;

  while (curr_line != NULL) {
    // printf("curr_line: %s\n", curr_line);

    int first_num = 0;
    int last_num = 0;

    for (int i = 0; i < strlen(curr_line); i++) {
      char curr_char = curr_line[i];
      if (curr_char >= '0' && curr_char <= '9') {
        first_num = curr_char - '0';
        break;
      }
      char substr[i + 1];
      strncpy(substr, curr_line, i + 1);
      substr[i + 1] = '\0';
      // printf("substr: %s\n", substr);
      int num = check_if_string_contains(substr);
      if (num > 0) {
        first_num = num;
        break;
      }
    }
    for (int i = strlen(curr_line) - 1; i >= 0; i--) {
      char curr_char = curr_line[i];
      if (curr_char >= '0' && curr_char <= '9') {
        last_num = curr_char - '0';
        break;
      }

      int len = strlen(curr_line) - i;
      char substr[len];
      strncpy(substr, curr_line + i, len);
      substr[len] = '\0';
      // printf("ending substr: %s\n", substr);
      int num = check_if_string_contains(substr);
      if (num > 0) {
        // printf("found num: %d\n", num);
        last_num = num;
        break;
      }
    }

    // printf("first: %d\n", first_num);
    // printf("last: %d\n", last_num);

    // combine 1 and 9 to 19
    int combined;
    if (first_num > 0 && last_num > 0) {
      combined = first_num * 10 + last_num;
    } else {
      combined = first_num + last_num;
    }

    // printf("combined: %d\n", combined);
    total += combined;

    curr_line = strtok(NULL, "\n");
  }

  return total;
}

// returns 1 if test passes, 0 if test fails
int test() {
  char test_input[] = "1abc2\npqr3stu8vwx\na1b2c3d4e5f\ntreb7uchet";
  int total = getSum(test_input);

  if (total == 142) {
    return 1;
  } else {
    return 0;
  }
}

int test_part_two() {
  char test_input[] = "two1nine\neightwothree\nabcone2threexyz\nxtwone3four\n4n"
                      "ineeightseven2\nzoneight234\n7pqrstsixteen";
  int total = get_sum_part_two(test_input);
  return total == 281;
}

int main() {
  printf("Hello, world!\n");

  printf("running test");
  int test_result = test();
  printf("test result: %d\n", test_result);

  printf("reading input");
  const char *input = read_input();
  // printf("input: %s\n", input);

  int result = getSum(input);
  printf("result: %d\n", result);

  printf("running test part two");
  int test_result_part_two = test_part_two();
  printf("test result part two: %d\n", test_result_part_two);


  const char* input_part_two = read_input();
  int result_part_two = get_sum_part_two(input_part_two);
  printf("result part two: %d\n", result_part_two);

  return 0;
}
