"""
@brief: Implements sweet C preprocessor
@file: preprocessor.py
@date: 03-27-2023
"""
import sys

if __name__ == "__main__":
    if len(sys.argv) < 2:
        raise "Invalid argument"

    out = []
    blank = [' ', '\r', '\n', '\t', 0]

    with open(sys.argv[1], 'r') as src:
        for line in src:
            prev_char = 0
            for char in line:
                if char == '#':
                    break
                elif (char in blank):
                    if not(prev_char in blank) and char != '\n':
                        out.append(' ')
                        prev_char = char
                else:
                    out.append(char)
                    prev_char = char

    with open('out.txt', 'w') as out_file:
        for c in out:
            out_file.write(c)


