# todo list

| emoji       | meaning      |
| :---------: | :----------- |
| :sos:       | critical bug |
| :warning:   | bug          |
| :eyes:      | to check     |
| :clipboard: | comment      |
| :tada:      | new feature  |

## General
- [x] :eyes: `makefile` flags: remove `-std=c++11`
- [ ] :clipboard: comment everything
- [ ] :tada: `README.md`: correct, improve and clarify
- [ ] :tada: setup matrix and vector multiplication and write every formula under a matrix form


## utils

### `Mouse`
- [ ] :clipboard: need to use `setPosition()` before using this class


### `LoopTimer`
- [ ] :warning: time not handled perfectly (see `this -> restart()` in `is_done()`)
- [ ] :clipboard: `is_done()` relaunches the timer automatically

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