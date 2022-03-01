#ifdef _WIN32
#  include <rpc.h> // GUID
#endif

#include <sstream>
#include <iostream>

#include <libstud/uuid.hxx>

#undef NDEBUG
#include <cassert>

using namespace std;
using namespace stud;

int main ()
{
  // Nil.
  //
  uuid un;
  assert (un.nil () && !un);

  // System generator.
  //
  uuid u1 (uuid::generate ());
  uuid u2 (uuid::generate ());

  assert (u1 && u2);
  assert (u1 != u2);

  // Binary.
  //
  assert (uuid (u1.binary ()) == u1);

  // GUID.
  //
#ifdef _WIN32
  assert (uuid (u1.guid ()) == u1);
#endif

  // String.
  //
  assert (uuid (u1.string ())                == u1);
  assert (uuid (u2.c_string (false).data ()) == u2);

  try {uuid ("123");                                  assert (false);} catch (const invalid_argument&) {}
  try {uuid ("2cfX28ff-1a9a-451d-b953-1bb4622e810f"); assert (false);} catch (const invalid_argument&) {}

  // Variant and version.
  //
  uuid ur ("2cf228ff-1a9a-451d-b953-1bb4622e810f");
  uuid ut ("027bf5e8-a471-11e8-aa3f-1f0a5c55c825");

  assert (ur.variant () == uuid_variant::dce &&
          ur.version () == uuid_version::random);

  assert (ut.variant () == uuid_variant::dce &&
          ut.version () == uuid_version::time);

  // Comparion.
  //
  assert (u1 != u2 && u1 == u1 && ur > ut);

  // Input/output.
  //
  {
    stringstream ss;
    uuid u;
    assert (ss << u1 && ss >> u && u == u1);
  }

  // Swap and move.
  //
  {
    uuid un, uc (u1);
    uc.swap (un);
    assert (uc.nil () && un == u1);
  }

  {
    uuid uc (u1), um (move (uc));
    assert (uc.nil () && um == u1);
  }

  {
    uuid uc (u1), um (u2);
    um = move (uc);
    assert (uc.nil () && um == u1);
  }

  // Hash.
  //
  assert (hash<uuid> () (ur) != hash<uuid> () (ut));
}
