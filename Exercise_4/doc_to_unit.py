import unittest
import doctest
import main as mod


def load_tests(loader, tests, ignore):
    tests.addTests(doctest.DocTestSuite(mod))
    return tests

if __name__ == '__main__':
    unittest.main()