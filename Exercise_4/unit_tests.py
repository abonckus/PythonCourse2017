import unittest

class TestMethods(unittest.TestCase):

    def test_string_to_list(self):
        self.assertEqual(list('abcd'), ['a', 'b', 'c', 'd'])

    def test_string_to_int(self):
        self.assertEqual(int('5'), 5)
        with self.assertRaises(ValueError):
            int('a')

if __name__ == '__main__':
    unittest.main()