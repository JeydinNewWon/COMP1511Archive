#include <stdio.h>

/*
enum weather { sunny, rainy, cloudy, windy };

struct today { 
    enum weather weather_today;
    double temp; 
    double wind_strength;

};*/

#define NUM_DAYS_A_WEEK 7

int main(void) {
    /*
    struct today wednesday = { .weather_today = cloudy, .temp = 17.25, .wind_strength = 50};

    printf("%i", wednesday.weather_today);

    if (wednesday.weather_today == cloudy) {
        printf("Cloudy today! at %lf degrees and %f knots", wednesday.temp, wednesday.wind_strength);
    }*/
    int temperatures[NUM_DAYS_A_WEEK] = {32, 12, 20, 21, 25, 33, 30};

    int i = 0;
    while (i < NUM_DAYS_A_WEEK) {
        if (i != NUM_DAYS_A_WEEK - 1) {
            printf("%d, ", temperatures[i]);
        } else {
            printf("%d\n", temperatures[i]);
        }

        i++;
    }

    return 0;
    
}