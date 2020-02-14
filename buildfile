./: {*/ -build/} doc{README.md NEWS LICENSE COPYRIGHT} manifest

# Don't install tests.
#
tests/: install = false
