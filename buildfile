./: {*/ -build/} doc{README.md NEWS LICENSE AUTHORS} manifest

# Don't install tests.
#
tests/: install = false
