INSTALL
=======

To install SMART-TPL you'll need the following dependencies

* lemon
* flex
* boost-regex
* openssl
* libjit
* timelib (as shared object file)

Both lemon and flex can usually be found in your distro repositories. Libjit however is often missing, you clone it from http://git.savannah.gnu.org/cgit/libjit.git/
Installing it however does require yacc (often packaged as bison), texi2html/texinfo. If libjit is in the repository of your distro you won't need these.
Although use of libjit from your distro repository is probably rather outdated so use of those is discouraged.

Timelib can be downloaded and installed from https://github.com/CopernicaMarketingSoftware/timelib, from which installing is done by `make` and `make install`.

After you have all the required dependencies a simple make and make install should be enough.
