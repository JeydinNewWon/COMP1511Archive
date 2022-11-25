// 
// Written 22/06/2022
// By Jayden Nguyen z5362408
//
// Takes in results of a car race and prints them out.
//

#include <stdio.h>


#define MAX_CARS 20

struct race_result {
    int car_number;
    double race_time;
};


// Prints the race result in the correct format.
void print_result(int car_number, double race_time);

int main(void) {

    int number_of_cars;
    printf("How many cars in the race? ");
    // TODO: scan in number of cars in the race
    scanf("%i", &number_of_cars);

    struct race_result results_roster[number_of_cars];

    printf("Enter results: \n");
    int i = 0;
    while (i < number_of_cars) {
        int new_car_number;
        double new_car_race_time;

        scanf("%d %lf", &new_car_number, &new_car_race_time);
        struct race_result new_car = {  .car_number = new_car_number, 
                                        .race_time = new_car_race_time};

        results_roster[i] = new_car;
        i++;
    }

    printf("Results:\n");
    i = 0;
    while (i < number_of_cars) {
        print_result(results_roster[i].car_number, results_roster[i].race_time);
        i++;
    }

    return 0;
}


//  Prints the race result in the correct format.
//
// Parameters:
// - `car_number` -- The car number of the result
// - `race_time` -- The time the car took to finish the race.
//
// Returns: nothing.
void print_result(int car_number, double race_time) {
    
    printf("%2d: %.2lf\n", car_number, race_time);
}