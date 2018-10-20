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

### `src/main.cpp`
- [ ] :eyes: check all



## src/utils

### `Mouse`

### `LoopTimer`
- [ ] :warning: time not handled perfectly (see `this -> restart()` in `is_done()`)

### `Parameters`
- [ ] :eyes: check all

### `tools.*`
- [x] :flashlight: change `general.*` for `tools.*`
- [x] :eyes: check all
- [x] :flashlight: check dependecies for class using `tools.hpp`
- [ ] :flashlight: remove `parse_string()`



## src/geometry

### `Vector3d`
- [x] :eyes: check friend declarations

### `Segment3d`
- [x] :eyes: check friend declarations

### `Plane3d`
- [x] :eyes: check friend declarations
- [x] :eyes: check every `// others` methods

### `Solid3d`
- [ ] :eyes: check every `// other` methods
- [ ] :tada: remove `SOLID_TYPE` enum and constructor and create custom cube, sphere and other solid classes

### `Camera3d`
- [x] :eyes: check every `// other` methods
- [x] :eyes: check constructor



## :clipboard:
* `Mouse`
    - :clipboard: need to use `setPosition()` before using this class
* `LoopTimer`
    - :clipboard: `is_done()` relaunches the timer automatically
* `Vector3d`
    - :clipboard: arithmetic operations don't change color
    - :clipboard: `rotate()` theta in degrees
* `Plane3d`
    - :clipboard: `handle_intersection_of_segment_with_plane()` if `da = db = 0` return `false`



