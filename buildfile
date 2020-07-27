./: {*/ -build/} doc{README.md NEWS} legal{LICENSE AUTHORS} manifest

# Don't install tests.
#
tests/: install = false
