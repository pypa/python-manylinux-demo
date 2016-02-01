python-manylinux-demo
=====================
Demo project for building Python wheels for Linux with Travis-CI

[![Build Status](https://travis-ci.org/pypa/python-manylinux-demo.svg?branch=master)](https://travis-ci.org/pypa/python-manylinux-demo)


This is an example of how to use Travis-CI to build
[PEP 513](https://www.python.org/dev/peps/pep-0513/)-compatible manylinux1
wheels for Python. It supports both Python 2 and 3 on 32 and 64 bit linux
architectures.

Because these wheels need to be compiled on CentOS 5, this example uses Docker
running on Travis-CI to compile (you don't need to use docker at all to _use_
these wheels, it's just to compile them). The docker-based build environment
images are:

- 64-bit image (x86-64): ``quay.io/pypa/manylinux1_x86_64`` [![Docker Repository on Quay](https://quay.io/repository/pypa/manylinux1_x86_64/status "Docker Repository on Quay")](https://quay.io/repository/pypa/manylinux1_x86_64)
- 32-bit image (i686): ``quay.io/pypa/manylinux1_i686`` [![Docker Repository on Quay](https://quay.io/repository/pypa/manylinux1_i686/status "Docker Repository on Quay")](https://quay.io/repository/pypa/manylinux1_i686)

This sample project contains a very simple C compile extension module that links
to an external library (ATLAS, a linear algebra library). The build is
configured via the `setup.py` file.

Continuous integration setup with Travis + Docker
-------------------------------------------------

The `.travis.yml` file in this repository sets up the build environment. The
resulting build logs can be found at

  https://travis-ci.org/pypa/python-manylinux-demo

The `.travis.yml` file instructs Travis to run the script
`travis/build-wheels.sh` inside of the 32-bit and 64-bit manylinux1 docker
build environments. This script builds the package using `pip`. But these
wheels link against an external library. So to create self-contained libraries,
the build script runs the wheels through
[`auditwheel`](https://pypi.python.org/pypi/auditwheel).

Code of Conduct
---------------

Everyone interacting in the python-manylinux-demo project's codebases, issue trackers,
chat rooms, and mailing lists is expected to follow the
[PyPA Code of Conduct](https://www.pypa.io/en/latest/code-of-conduct/).
