"""
This module contains unit tests for the `program` module.

Classes:
    TestHelloWorld: A unittest.TestCase subclass to test the functionality of the `program` module.

Methods:
    test_main: Tests the `main` function of the `program` module by checking the output written to a file.
    test_process_input_file: Tests the `process_input_file` function of the `program` module by checking the output written to a file after processing an input file.
"""

import unittest
from pathlib import Path

from vim_dsa.hello_world import hello_world


class TestHelloWorld(unittest.TestCase):
	"""
	Test suite for the hello_world module.

	This test suite contains two test cases:
	1. test_main: Tests the main function of the hello_world module by writing its output to a file and comparing it to the expected output.
	2. test_process_input_file: Tests the process_input_file function of the hello_world module by writing a sample input to a file, processing it, and comparing the output to the expected result.
	"""

	def test_main(self) -> None:
		"""
		Test the main function of the hello_world module.
		"""
		with Path.open("output.txt", "w") as file:
			hello_world.main()
		with Path.open("output.txt") as file:
			assert file.read() == "1\n2\n3\n4\n5\n6\n7\n8\n9\n10"

	def test_process_input_file(self) -> None:
		"""
		Test the process_input_file function of the hello_world module.
		"""
		with Path.open("input.txt", "w") as file:
			file.write("1\n2\n3\n4\n5\n6\n7\n8\n9\n10")
			hello_world.process_input_file("input.txt", "output.txt")
		with Path.open("output.txt") as file:
			assert file.read() == "1\n2\n3\n4\n5\n6\n7\n8\n9\n10"
