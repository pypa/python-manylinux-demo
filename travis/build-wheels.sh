# Install a system package required by our library
yum install -y atlas-devel

for PYVER in ${PY_VERS};

    PATH=/opt/${PYVER}/bin:$PATH
    pip wheel /io/
done

