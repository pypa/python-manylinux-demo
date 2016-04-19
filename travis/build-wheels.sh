#!/bin/bash
PYTHON_VERSIONS="2.7 3.4 3.5"

# Install a system package required by our library
yum install -y atlas-devel

# Compile wheels
for PYTHON in ${PYTHON_VERSIONS}; do
    /opt/${PYTHON}/bin/pip install -r /io/dev-requirements.txt
    /opt/${PYTHON}/bin/pip wheel /io/ -w wheelhouse/
done

# Bundle external shared libraries into the wheels
for whl in wheelhouse/*.whl; do
    auditwheel repair $whl -w /io/wheelhouse/
done

# Install packages and test
for PYTHON in ${PYTHON_VERSIONS}; do
    /opt/${PYTHON}/bin/pip install python_manylinux_demo --no-index -f wheelhouse
    (cd $HOME; /opt/${PYTHON}/bin/nosetests pymanylinuxdemo)
done
