elevator-c
==========

Simulate an Elevator

I am currently trying to figure out pthreads and mutex so that I can get input, but I will update the code once I do. The logic I want to implement is to continue in the same direction if there are requests in that direction to let passengers off, or to pick up passengers who want to continue in that direction (as per wikipedia's elevator logic). If there are no more requests in the same direction, it picks up the furthest request to go the opposite direction in the same direction (if you were on floor 4 going up, you might pick up a person on floor 9 going down, then start going down).

It should also be possible to implement multiple elevators into this system (with mutex).
