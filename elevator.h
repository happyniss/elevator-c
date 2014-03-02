#define STOP 0
#define UP 1
#define DOWN 2

#include <stdbool.h>

typedef struct elevator_system_store {
  int floors;
  bool *requests_up;
  bool *requests_down;
} elevator_system;

typedef struct elevator_car_store {
  int direction;
  int current_floor; // last floor touched or passed
  bool *requests_car; // array of floors (0 to number of floors-1), if true, stop at that floor
  bool *requests_pending; // array of requests pending
  elevator_system *elv_sys;
} elevator_car;

elevator_system *new_system(int floors);
elevator_car *new_car(elevator_system *sys);

bool check_floor(int floor, elevator_system *sys); // is floor ok destination

void car_request_submit(int floor, elevator_car *car); // add to pending
void system_request_add(int floor, int direction, elevator_system *sys);

// update car requests with system requests and pending car requests
void car_request_update(elevator_car *car, elevator_system *sys);

// check if car should keep going
bool check_continue(elevator_car *car);

void next_floor(elevator_car *car);

void pause_maybe(elevator_car *car);
