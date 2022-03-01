# libstud-uuid - UUID generation library for C++

A portable, dependency-free, MIT-licensed UUID generation library for C++ that
makes sure the generated IDs are actually unique.

Typical usage:

```
#include <string>
#include <iostream>

#include <libstud/uuid.hxx>

int main ()
{
  using stud::uuid;
  using namespace std;

  uuid u (uuid::generate ()); // Make strong ID using system generator.
  string s (u.string ());     // xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx
  cout << u << endl;          // Print string representation.
}
```

See the [`libstud/uuid/uuid.hxx`][uuid.hxx] and
[`libstud/uuid/uuid-io.hxx`][uuid-io.hxx] headers for interface details and
the [`NEWS`][news] file for changes. See the [`cppget.org/libstud-uuid`][pkg]
package page for build status.


[news]:     https://github.com/libstud/libstud-uuid/blob/master/NEWS
[uuid.hxx]: https://github.com/libstud/libstud-uuid/blob/master/libstud/uuid/uuid.hxx
[uuid-io.hxx]: https://github.com/libstud/libstud-uuid/blob/master/libstud/uuid/uuid-io.hxx
[pkg]:      https://cppget.org/libstud-uuid
