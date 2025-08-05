Plugin support
=================

Interface to plugins is very simple and requires just one function to be exported from the plugin DLL, the uidgen_install_plugin function. The uidgen.exe application loads all *.uidgen DLLs at start up and tries to initialize the plugin by using ths function.

Since plugins cannot be dynamically unloaded, plugin unloading happens only when the uidgen.exe application is terminated.

The uidgen_install_plugin accepts pointer to the uidgen context object and is supposed to install generator(s) and/or formatter(s) by calling context functions.
