#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <unistd.h>

#include "elevator.h"

elevator_system *new_system(int floors) {
  elevator_system *result = (elevator_system *) malloc(sizeof(elevator_system));
  assert(result != NULL);

  result->floors=floors;
  result->requests_up = (bool *) calloc(floors, sizeof(bool));
  result->requests_down = (bool *) calloc(floors, sizeof(bool));

  return result;
}

elevator_car *new_car(elevator_system *sys) {
  elevator_car *result = (elevator_car *) malloc(sizeof(elevator_car));

  result->direction = UP;
  result->current_floor=0;
  result->requests_car = (bool *) calloc(sys->floors, sizeof(bool));
  result->requests_pending = (bool *) calloc(sys->floors, sizeof(bool));
  result->elv_sys = sys;

  return result;
}

bool check_floor(int floor, elevator_system *sys) {
  if (floor < sys->floors && floor >= 0)
    return true;
  else
    return false;
}

void car_request_submit(int floor, elevator_car *car) {
  if (check_floor(floor, car->elv_sys)==0)
    car->requests_pending[floor] = true;
}

void system_request_add(int floor, int direction, elevator_system *sys) {
  if (check_floor(floor,sys)==true) {
    if (direction==UP)
      sys->requests_up[floor]=true;
    else if (direction==DOWN)
      sys->requests_down[floor]=true;
    else
      printf("invalid request\n");
  }
}

void car_request_update(elevator_car *car, elevator_system *sys) {
  // add requests_pending (buttons pushed in elevator)
  int i;
  for(i=0;i<sys->floors;i++) {
    if (car->requests_pending[i]==true) {
      car->requests_car[i]=true; // add to requests
      car->requests_pending[i]=false; // remove from pending
    }
  }
  // add requests from floors
  i=car->current_floor+1;
  if (car->direction==UP) {
    while (i<sys->floors) {
      if (sys->requests_up[i]==true) {
	car->requests_car[i]=true;
	sys->requests_up[i]=false;
      }
      i++;
    }
  }
  else if (car->direction==DOWN) {
    while (i>=0) {
      if (sys->requests_down[i]==true) {
	car->requests_car[i]=true;
	sys->requests_down[i]=false;
      }
      i--;
    }
  }
}

bool check_continue(elevator_car *car) {
  int i = car->current_floor; 
  if (car->direction==UP) {
    i+=1; // start checking floor above current
    while(i<car->elv_sys->floors) {
      if (car->requests_car[i]==true)
	return true;
    }
    return false;
  }
  else if (car->direction==DOWN) {
    i-=1; // start checking floor below current
    while(i>=0) {
      if (car->requests_car[i]==true)
	return true;
    }
    return false;
  }
}

void next_floor(elevator_car *car) {
  if (car->direction==UP) {
    if (car->current_floor+1 < car->elv_sys->floors) {
      sleep(4);
      car->current_floor+=1;
      printf("Floor %d\n", car->current_floor);
      fflush(stdout);
    }
  }
  else if (car->direction==DOWN) {
    void car_down(elevator_car *car) {
      sleep(4);
      if (car->current_floor-1 >= 0) {
	car->current_floor-=1;
	printf("Floor %d\n", car->current_floor);
	fflush(stdout);
      }
    }
  }
}

void pause_maybe(elevator_car *car) {
  if (car->requests_car[car->current_floor]==true) {
    printf("Stopping at floor %d",car->current_floor);
    fflush(stdout);
    sleep(5);
    car->requests_car[car->current_floor]=false;
  }
}
