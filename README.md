UIDgen - UUID generator, GUI and console versions.
========================================================

Author: ![https://github.com/duox] (https://github.com/duox)
Project page: ![https://github.com/duox/uidgen] (https://github.com/duox/uidgen/)
License: MIT
Supported platforms: Windows only

UIDgen is a small utility that extends functionality of the standard WinWDK uidgen utility.
Besides of the standard functionality of the UUID generation, following features are implemented:
- both GUI and console versions selected automatically or manualy on startup;
- extended number of UUID formatters;
- user-supplied format string that allows any kind of UUID formats;
- allows re-formatting of user supplied UUID (manual generator);
- multiple UUIDs can be generated and copied to clipboard or saved to a file;
- configurable behaviour (related to the UUID generation and main window behaviour);
- the Windows version uses only standard Windows DLLs, while the standard MSVS/SDK uidgen.exe uses MFC dll;
- global key hook that allows for background UUID(s) generation;
- resizeable dialog windows allow for better user experience.

Contents
-----------------

[Screenshots](#Screenshots)
[UID generators] (./docs/generators.md)
[UID formatters] (./docs/formatters.md)
[Plugin interface] (./docs/plugins.md)
[Use in MSVS] (./docs/use-msvs.md)
[Alternatives] (./docs/alternatives.md)

Screenshots
-----------------

* Default window state:<br/>
![Default window](./docs/images/gui-main.png)

* List of available UUID generators:<br/>
![UUID generators](./docs/images/gui-types.png)

* List of available UUID formats:<br/>
![UUID formats](./docs/images/gui-formats.png)

* Drop box with results:<br/>
![Results](./docs/images/gui-results.png)

* Internal help:<br/>
![Help window](./docs/images/help-wnd.png)

* Command line utility help:<br/>
![Help window](./docs/images/console-help.png)

