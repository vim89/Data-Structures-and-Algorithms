import unittest
from insertion_sort.insertion_sort import insertion_sort


class TestInsertionSort(unittest.TestCase):
    def test_insertion_sort(self):
        print("Test Insertion sort")
        input_array = [5, 2, 4, 6, 1, 3]
        print(f"Input = {input_array}")
        output_array = insertion_sort(_array=input_array)
        print(f"Output = {output_array}")

        print("Non-increasing order")
        input_array = [5, 2, 4, 6, 1, 3]
        print(f"Input = {input_array}")
        output_array = insertion_sort(_array=input_array, order='descending')
        print(f"Output = {output_array}")


if __name__ == '__main__':
    unittest.main()
