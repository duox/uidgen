TODO:
+ keyboard hook to generate GUIDs in background (e.g. Ctrl+Alt+G), use RegisterHotKey
+ minimize to tray option
+ Esc to minimize option
+ option for ignore new-lines in user format field
+ implement upper/lower case
+ plugin support: formatters and generators
+ command line interface
+ advanced help window
+ uuidgen wrapper utility
+ avoid using of libc version (platfrom folder required)
+ change license to MIT or something less restrictive than LGPL
+ new Guid("xxxx...xxxx")
+ rename project and UI to uidgen

+ Options
	x braces
	+ uppercase
	x hypens
	+ swap bytes (LE <-> BE)
	x prefix
	x suffix

+ Group generation
	+ list
	+ set count
	+ generate button
	+ save to file

- UID generators
	- ULID? (https://github.com/ulid/spec)
	- CUID? (https://github.com/ericelliott/cuid)

- complete all TODOs in source code

TODO rejected:
x use local INI file (for portability)
