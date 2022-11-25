#include <stdio.h>
#include <stdlib.h>

enum drink_type { COFFEE, TEA, JUICE, WATER };

struct drink {
  double price;
  char *name;
  enum drink_type type;
};

// Return the cheapest coffee drink price
enum drink_type type_of_cheapest_drink(int size, struct drink drinks[size]) {
  int i = 0;
  struct drink cheapest_drink = drinks[0];
  while (i < size) {
    if (drinks[i].price < cheapest_drink.price) {
      cheapest_drink = drinks[i];
    }
    i++;
  }

  return cheapest_drink.type;
}

// This is a simple main function which could be used
// to test your type_of_cheapest_drink function.
// It will not be marked.
// Only your type_of_cheapest_drink function will be marked.
#define TEST_ARRAY_SIZE 3

int main(void) {
  struct drink test_array[TEST_ARRAY_SIZE] = {
      {.price = 2.50, .type = COFFEE, .name = "Short Black"},
      {.price = 3.00, .type = JUICE, .name = "Orange Juice"},
      {.price = 1.50, .type = WATER, .name = "Mount Franklin"}};
  enum drink_type cheapest_drink_type =
      type_of_cheapest_drink(TEST_ARRAY_SIZE, test_array);

  if (cheapest_drink_type == COFFEE) {
    printf("coffee\n");
  } else if (cheapest_drink_type == TEA) {
    printf("tea\n");
  } else if (cheapest_drink_type == JUICE) {
    printf("juice\n");
  } else if (cheapest_drink_type == WATER) {
    printf("water\n");
  }

  return 0;
}