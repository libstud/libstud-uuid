# libstud-uuid - UUID generation library for C++

A portable, dependency-free, MIT-licensed UUID generation library for C++ that
tries to make reasonably sure the generated IDs are unique.

Specifically, the implementation calls platform-specific APIs that were
carefully analyzed for uniqueness guarantees (good source of randomness, time
collision prevention, etc). If an API does not explicitly provide such
guarantees or if such guarantees are only provided for certain UUID versions,
then the implementation will refuse to return such a UUID if a strong
uniqueness was requested.

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
