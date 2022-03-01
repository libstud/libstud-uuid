#pragma once

#include <array>
#include <string>
#include <cstdint>
#include <functional> // hash

#include <libstud/uuid/export.hxx>
#include <libstud/uuid/version.hxx>

#ifdef _WIN32
struct _GUID; // GUID and UUID.
#endif

namespace stud
{
  //-
  // Universally-unique identifier (UUID).
  //
  // See RFC4122[1] for background.
  //
  // [1]: https://tools.ietf.org/html/rfc4122
  //-

  //- #uuid_variant `uuid_variant`
  //
  // UUID variant (type). Nil UUID is DCE.
  //
  enum class uuid_variant
  {
    ncs,       // NCS backward compatibility.
    dce,       // DCE 1.1/RFC4122.
    microsoft, // Microsoft backward compatibility.
    other      // Currently reserved for possible future definition.
  };
  //-

  //- #uuid_version `uuid_version`
  //
  // DCE UUID version (sub-type). Nil UUID is random.
  //
  enum class uuid_version
  {
    time     = 1, // Time-based.
    security = 2, // DCE Security with embedded POSIX UIDs.
    md5      = 3, // Name-based with MD5 hashing.
    random   = 4, // Randomly or pseudo-randomly generated.
    sha1     = 5  // Name-based with SHA1 hashing.
  };
  //-

  class LIBSTUD_UUID_SYMEXPORT uuid_system_generator;

  //- #uuid `uuid`
  //
  // UUID value type. Typical usage:
  //
  //     #include <string>
  //     #include <iostream>
  //
  //     #include <libstud/uuid/uuid.hxx>
  //     #include <libstud/uuid/uuid-io.hxx>
  //
  //     int main ()
  //     {
  //       using stud::uuid;
  //       using namespace std;
  //
  //       uuid u (uuid::generate ()); // Generate using system generator.
  //       string s (u.string ());     // xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx
  //       cout << u << endl;          // Print string representation.
  //     }
  //
  struct LIBSTUD_UUID_SYMEXPORT uuid
  //-
  {
    //-
    // Data members are normally not accessed directly (see RFC4122, Section
    // 4.1.2).
    //
    std::uint32_t time_low = 0;
    std::uint16_t time_mid = 0;
    std::uint16_t time_hiv = 0;      // hi_and_version
    std::uint8_t  clock_seq_hir = 0; // hi_and_reserved
    std::uint8_t  clock_seq_low = 0;
    std::uint8_t  node[6] = {0, 0, 0, 0, 0, 0};
    //-

    //-
    // System UUID generator. See the `uuid_generator` interface for details.
    //
    //| System generator cannot be called during static initialization.
    //
    static uuid_system_generator system_generator;

    static uuid
    generate (bool strong = true);
    //-

    //-
    // Create a nil UUID (all data members are 0).
    //
    uuid () = default;

    bool
    nil () const;

    explicit operator bool () const;
    //-

    //-
    // Create a UUID from a 16-octet binary representation with the sizes and
    // order of the fields as defined in RFC4122, Section 4.1.2 and with each
    // field encoded with the most significant byte first (also known as
    // big-endian or network byte order).
    //
    //| The C array constructor is compatible with the `uuid_t` type from
    //| `libuuid`.
    //
    using binary_type = std::array<std::uint8_t, 16>;

    explicit
    uuid (const binary_type&);

    explicit
    uuid (const std::uint8_t (&)[16]);

    void
    assign (const binary_type&);

    void
    assign (const std::uint8_t (&)[16]);

    binary_type
    binary () const noexcept;
    //-

#ifdef _WIN32
    //-
    // Create a UUID from Win32 `GUID`.
    //
    uuid (const _GUID&);

    void
    assign (const _GUID&);

    template <typename G = _GUID>
    G
    guid () const;
    //-
#endif

    //-
    // Create a UUID from a 36-character upper or lower case string
    // representation in the following form:
    //`
    //   xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx
    //`
    // Throw `std::invalid_argument` if the representation is invalid. The
    // returned string representation is by default in the lower case.
    //
    explicit
    uuid (const std::string&);

    explicit
    uuid (const char*);

    void
    assign (const std::string&);

    void
    assign (const char*);

    std::string
    string (bool upper = false) const;

    std::array<char, 37>
    c_string (bool upper = false) const;
    //-

    //-
    // Query UUID variant (type) and version (sub-type).
    //
    using variant_type = uuid_variant;
    using version_type = uuid_version;

    variant_type
    variant () const;

    version_type
    version () const;
    //-

    //-
    // UUID comparison.
    //
    int
    compare (const uuid&) const;
    //-

    //-
    // Swapping and moving. Note that a moved-from instance is made nil.
    //
    void
    swap (uuid&);

    uuid (uuid&&);
    uuid (const uuid&) = default;

    uuid& operator= (uuid&&);
    uuid& operator= (const uuid&) = default;
    //-
  };

  //-
  // Comparison operators.
  //
  bool operator== (const uuid&, const uuid&);
  bool operator!= (const uuid&, const uuid&);
  bool operator<  (const uuid&, const uuid&);
  bool operator>  (const uuid&, const uuid&);
  bool operator<= (const uuid&, const uuid&);
  bool operator>= (const uuid&, const uuid&);
  //-

  //-
  // Note: for `iostream` operators see `uuid-io.hxx`.
  //-

  //- #uuid_generator `uuid_generator`
  //
  // UUID generator interface.
  //
  class LIBSTUD_UUID_SYMEXPORT uuid_generator
  //-
  {
  public:
    //-
    // Generate a UUID. If strong is `true` (default), generate a
    // strongly-unique UUID. Throw `std::runtime_error` to report errors,
    // including if strong uniqueness cannot be guaranteed.
    //
    // A weak UUID is not guaranteed to be unique, neither universialy nor
    // locally (that is, on the machine it has been generated).
    //
    virtual uuid
    generate (bool strong = true) = 0;
    //-

    virtual
    ~uuid_generator () = default;
  };

  //- #uuid_generator `uuid_generator`
  //
  // System UUID generator.
  //
  class LIBSTUD_UUID_SYMEXPORT uuid_system_generator: public uuid_generator
  //-
  {
  public:
    //-
    // Throw `std::system_error` with the generic category and `ENOTSUP` error
    // code if strong uniqueness cannot be guaranteed.
    //
    virtual uuid
    generate (bool strong = true) override;
    //-

    //-
    // Optional explicit initialization and termination. Note that it is not
    // thread-safe and must only be performed once (normally from `main()`)
    // before/after any calls to `generate()`, respectively. Both functions
    // may throw `std::runtime_error` to report errors.
    //
    static void
    initialize ();

    static void
    terminate ();
    //-
  };
}

namespace std
{
  template <>
  struct hash<stud::uuid>
  {
    using argument_type = stud::uuid;
    using result_type = size_t;

    size_t
    operator() (const stud::uuid&) const noexcept;
  };
}

#include <libstud/uuid/uuid.ixx>
