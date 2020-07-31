python-manylinux-demo
=====================
Demo project for building Python wheels for Linux with Travis-CI

[![Build Status](https://travis-ci.org/pypa/python-manylinux-demo.svg?branch=master)](https://travis-ci.org/pypa/python-manylinux-demo)


This is an example of how to use Travis-CI to build
[PEP 513](https://www.python.org/dev/peps/pep-0513/)-compatible
wheels for Python. It supports

- manylinux1 for both Python 2 and 3 on 32 and 64 bit linux architectures.
- manylinux2010 for Python 2 and 3 on 64 bit linux architectures.

Because these wheels need to be compiled with a specific toolchain and support
libraries , this example uses Docker running on Travis-CI to compile (you don't
need to use docker at all to _use_ these wheels, it's just to compile them).
The docker-based build environment images are:

- 64-bit image for manylinux1 (x86-64): ``quay.io/pypa/manylinux1_x86_64`` [![Docker Repository on Quay](https://quay.io/repository/pypa/manylinux1_x86_64/status "Docker Repository on Quay")](https://quay.io/repository/pypa/manylinux1_x86_64)
- 32-bit image for manylinux1 (i686): ``quay.io/pypa/manylinux1_i686`` [![Docker Repository on Quay](https://quay.io/repository/pypa/manylinux1_i686/status "Docker Repository on Quay")](https://quay.io/repository/pypa/manylinux1_i686)
- 64-bit image for manylinux2010 (x86-64): ``quay.io/pypa/manylinux2010_x86_64`` [![Docker Repository on Quay](https://quay.io/repository/pypa/manylinux2010_x86_64/status "Docker Repository on Quay")](https://quay.io/repository/pypa/manylinux2010_x86_64)

This sample project contains a very simple C compile extension module that links
to an external library (ATLAS, a linear algebra library). The build is
configured via the `setup.py` file.

Continuous integration setup with Travis + Docker
-------------------------------------------------

The `.travis.yml` file in this repository sets up the build environment. The
resulting build logs can be found at

  https://travis-ci.org/pypa/python-manylinux-demo

The `.travis.yml` file instructs Travis to run the script
`travis/build-wheels.sh` inside of the various docker build environments. This
script builds the package using `pip`. But these wheels link against an
external library. So to create self-contained wheels, the build script runs the
wheels through [`auditwheel`](https://pypi.python.org/pypi/auditwheel), which
copies the external library into the wheel itself, so that users won't need to
install any extra non-PyPI dependencies.

Code of Conduct
---------------

Everyone interacting in the python-manylinux-demo project's codebases, issue trackers,
chat rooms, and mailing lists is expected to follow the
[PSF Code of Conduct](https://github.com/pypa/.github/blob/main/CODE_OF_CONDUCT.md).

License
-------

<p xmlns:dct="http://purl.org/dc/terms/" xmlns:vcard="http://www.w3.org/2001/vcard-rdf/3.0#">
  <a rel="license"
     href="https://creativecommons.org/publicdomain/zero/1.0/">
    <img src="https://i.creativecommons.org/p/zero/1.0/88x31.png" style="border-style: none;" alt="CC0" />
  </a>
  <br />
  To the extent possible under law,
  <a rel="dct:publisher"
     href="https://github.com/rmcgibbo">
    <span property="dct:title">Robert T. McGibbon</span></a>
  has waived all copyright and related or neighboring rights to
  <span property="dct:title">python-manylinux-demo</span>.
This work is published from:
<span property="vcard:Country" datatype="dct:ISO3166"
      content="US" about="https://github.com/pypa/python-manylinux-demo">
  United States of America</span>.
</p>
