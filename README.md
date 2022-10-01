### A simple todo.txt implementation in C.

Build on linux (GCC)
```console
$ ./build.sh
```
and on windows (MSYS2 MinGW64)
```console
$ ./build.cmd
```

As I go, i will add sane features like:
- [ ] Parser that is not hardcoded to the todo.txt guidelines, so that I can just add features i'd like.
- [ ] Live editor (add/modify/remove tasks) (won't use curses, i just don't like it).
	- [ ] add, modify, remove tasks.
	- [ ] add, remove tasks to projects.
	- [ ] add, remove tasks to contexts.
	- [ ] add, remove 'finished' status to tasks.
- [ ] Gui, in something like sdl or imgui or something else, have to decide which i prefer.
