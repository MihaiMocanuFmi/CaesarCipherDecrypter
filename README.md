# CaesarCipherDecrypter
This is a program that decrypts text which was encrypted using Caesar's Cipher.

## How it works
The program compares the usual distribution of letters that appear in english with the distribution of 
letters in the given encrypted text.

It repeats this process with all possible encryptions and chooses the distribution of letters which is 
closest to the one that naturally appears in english.

Therefore, in cases when the given text is too small to accurately compute the distribution, it might not be successful
in the first try.

## How to compile with CMake
- Using Make
  - `cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug`
  - `make`
  - `./CaesarCipherDecrypter`

## Dependencies
* CMake 
* C11 (recommended)

## Notes
This was only tested on linux, format of file paths might pose a problem in Windows.

To build this program in release mode, use instead:
* `cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release`