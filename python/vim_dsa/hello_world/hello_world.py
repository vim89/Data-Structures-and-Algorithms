"""
This module contains functions to process input files and print "Hello, World!" to the console.
"""

import sys

from vim_dsa.hello_world import hello_world_logger

"""Main module for the program."""


def process_input_file(input_file: str, output_file: str) -> None:
	"""
	Reads code from input_file, executes it, and writes the output to output_file.
	"""
	global input_array
	with open(input_file) as file:
		input_array = file.read()
		input_array = str(input).split("\n")
		print(input_array)
	# Redirect stdout to the output file
	original_stdout = sys.stdout
	with open(output_file, "w") as file:
		sys.stdout = file
		try:
			exec(input_array)
		except Exception as e:
			print(f"Error executing code: {e}")
		finally:
			sys.stdout = original_stdout


def main() -> None:
	"""
	Main function that prints "Hello, World!" to the console.
	This is the entry point of the program.
	"""
	print("Hello, World!")
	hello_world_logger.info("Hello, World!")
	process_input_file("input.txt", "output.txt")


if __name__ == "__main__":
	main()
