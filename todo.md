# todo list

| emoji       | meaning                      |
| :---------: | :--------------------------- |
| :sos:       | critical bug                 |
| :warning:   | bug                          |
| :eyes:      | to check                     |
| :flashlight:| simplification/clarification |
| :clipboard: | comment                      |
| :sparkles:  | typos and style              |
| :tada:      | new feature                  |


## General
- [x] :eyes: `makefile` flags: remove `-std=c++11`
- [x] :flashlight: handle dependencies
- [ ] :clipboard: comment everything
- [ ] :tada: `README.md`: correct, improve and clarify
- [ ] :tada: setup matrix and vector multiplication and write every formula under a matrix form
- [ ] :tada: write test for every class
- [ ] :flashlight: change `general.*` for `tools.*`



## utils

### `Mouse`
- [ ] :clipboard: need to use `setPosition()` before using this class

### `LoopTimer`
- [ ] :warning: time not handled perfectly (see `this -> restart()` in `is_done()`)
- [ ] :clipboard: `is_done()` relaunches the timer automatically

### `tools.*`
- [ ] :eyes: check all



## geometry

### `Vector3d`
- [ ] :eyes: check friend declarations
- [ ] :clipboard: arithmetic operations don't change color
- [ ] :clipboard: `rotate()`theta in degrees

### `Segment3d`
- [ ] :eyes: check friend declarations

### `Plane3d`
- [ ] :eyes: check friend declarations
- [ ] :eyes: check every `// other` methods
- [ ] :flashlight: clarify `handle_intersection_of_segment_with_plane()`
- [ ] :flashlight: clarify `get_projection_on_plane()`

### `Solid3d`
- [ ] :eyes: check every `// other` methods
- [ ] :tada: remove `SOLID_TYPE` enum and constructor and create custom cube, sphere and other solid classes
- [ ] :flashlight: remove `set_center()`, automatize it

### `Camera3d`
- [ ] :eyes: check every `// other` methods
- [ ] :eyes: check constructor
