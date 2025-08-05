Internally supported GUID formatters
=====================================

A GUID generator creates a GUID which is sent to the selected formatter.

List of supported GUID generators:
- random GUID (implemented via CoCreateGuid),
- null GUID (all bytes are zero),
- invalid GUID (all bytes are 0xFF's),
- manual GUID (allows to manually give a GUID in the standard registry format and reformat it using one of formatters).

Generator plugin interface
----------------------------

Please refer to `plugins.md'.
