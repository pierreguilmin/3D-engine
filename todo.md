# todo list

| emoji        | meaning                      | code           |
| :----------: | :--------------------------- | :------------- |
| :sos:        | critical bug                 | `:sos:`        |
| :warning:    | bug                          | `:warning:`    |
| :eyes:       | to check                     | `:eyes:`       |
| :flashlight: | simplification/clarification | `:flashlight:` |
| :clipboard:  | comment                      | `:clipboard:`  |
| :sparkles:   | typos & style                | `:sparkles:`   |
| :tada:       | new feature                  | `:tada:`       |
| :cloud:      | minor modification           | `:cloud:`      |


### Git/GitHub
- [ ] :tada: `README.md`: correct, improve and clarify
- [ ] :sparkles: edit old commit messages to match emoji commit code table
- [ ] :tada: Travis CI: add simulated GUI
- [ ] :tada: Travis CI: add Windows
- [ ] :flashlight: update `README.md` Windows SFML installation instructions


### General
- [x] :eyes: `makefile` flags: remove `-std=c++11`
- [x] :flashlight: handle dependencies
- [ ] :tada: setup matrix and vector multiplication and write every formula under a matrix form
- [ ] :tada: write test for every class
- [ ] :tada: add `constexpr` keyword

* `src/main.cpp`
    - [ ] :eyes: check all


### src/utils

* `Mouse`

* `LoopTimer`
    - [ ] :warning: time not handled perfectly (see `this -> restart()` in `is_done()`)

* `Parameters`
    - [x] :eyes: check all

* `tools.*`
    - [x] :flashlight: change `general.*` for `tools.*`
    - [x] :eyes: check all
    - [x] :flashlight: check dependecies for class using `tools.hpp`
    - [x] :flashlight: remove `parse_string()`


### src/geometry

* `Vector3d`
    - [x] :eyes: check friend declarations
    - [ ] :tada: pre-compute every rotation cos/sin

* `Segment3d`
    - [x] :eyes: check friend declarations
    - [x] :tada: references to Vector3d rather than holding objects

* `Plane3d`
    - [x] :eyes: check friend declarations
    - [x] :eyes: check every `// others` methods
    - [ ] :flashlight: rename `get_signed_distance_from_point_to_plane()` to vector

* `Solid3d`
    - [ ] :eyes: check every `// other` methods
    - [x] :tada: remove `SOLID_TYPE` enum and constructor and create custom cube, sphere and other solid classes
    - [x] :tada: add `max_size` object handling and improve rendering performances
    - [ ] :tada: make vector of Vector3d rather than holding Vector3d in Segment3d
    - [ ] :eyes: check if intersection with window is perfect

* `Camera3d`
    - [x] :eyes: check every `// other` methods
    - [x] :eyes: check constructor
    - [ ] :tada: pre-compute cos/sin of theta_x/y/z

* `geometry.*`
    - [x] :warning: pole point of the sphere repeated
    - [ ] :tada: add multiple kernels for asteroids creation (gaussian, cos, abs, ...)
    - [ ] :tada: work on the asteroids parameters range / adaptability with `nb_circles`, `nb_points_per_circle`


### :clipboard:
- [ ] :clipboard: comment everything

* `Mouse`
    - [ ] :clipboard: need to use `setPosition()` before using this class
* `LoopTimer`
    - [ ] :clipboard: `is_done()` relaunches the timer automatically
* `Vector3d`
    - [ ] :clipboard: arithmetic operations don't change color
    - [ ] :clipboard: `rotate()` theta in degrees
* `Plane3d`
    - [ ] :clipboard: `handle_intersection_of_segment_with_plane()` if `da = db = 0` return `false`
* `Solid3d`
    - [ ] :clipboard: in `rotate_around_vector()` don't pass `rotation_center` by reference: explain why
    - [ ] :clipboard: necessary to specify `max_size` to improve rendering performances
