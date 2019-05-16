# libstud-uuid - UUID generation library for C++

This `build2` package contains a portable, dependency-free, MIT-licensed UUID
generation library for C++ that makes sure the generated IDs are actually
unique.

Typical usage:

```
#include <string>
#include <iostream>

#include <libstud/uuid/uuid.hxx>
#include <libstud/uuid/uuid-io.hxx>

int main ()
{
  using stud::uuid;
  using namespace std;

  uuid u (uuid::generate ()); // Generate strong ID using system generator.
  string s (u.string ());     // xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx
  cout << u << endl;          // Print string representation.
}
```

See the [`libstud/uuid/uuid.hxx`][uuid.hxx] header for interface details. See
the [`NEWS`][news] file for changes.

Supported platforms:

* Linux
* Windows
* Mac OS
* FreeBSD

Supported compilers:

* GCC 4.9 or later
* Clang 3.8 or later
* MSVC  14.3 or later

[news]:     https://github.com/libstud/libstud-uuid/blob/master/NEWS
[uuid.hxx]: https://github.com/libstud/libstud-uuid/blob/master/libstud/uuid/uuid.hxx
