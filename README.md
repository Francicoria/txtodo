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
- [x] Parser that is not hardcoded to the todo.txt guidelines, so that I can just add features i'd like.
- [ ] Live editor (add/modify/remove tasks) (won't use curses, i just don't like it).
	- [x] add, modify, remove tasks.
	- [ ] add, remove projects from tasks.
	- [ ] add, remove contexts from tasks.
	- [ ] add, remove 'finished' status to tasks.
- [ ] ~~Gui, in something like sdl or imgui or something else, have to decide which i prefer.~~ i won't create a gui, it's kinda out of scope for this project+it's kinda hard to write a gui in C, i'll just create a cli
