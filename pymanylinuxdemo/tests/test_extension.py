from unittest import TestCase
from array import array
from pymanylinuxdemo.extension import dot


class TestExtension(TestCase):
    def test_1(self):
        self.assertAlmostEqual(dot([1,2,3], [2,3,4]), 20.0)

    def test_2(self):
        self.assertAlmostEqual(dot([1,1.5,2.5,4], [-1.0,-2.0,-3.0,4]), 4.5)

    def test_3(self):
        x = array('d', [1.0, 2.0, 3.14])
        self.assertAlmostEqual(dot(x, x), 14.8596)
