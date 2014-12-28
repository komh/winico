=======================================================================================
2005/01/01

WINICO had been released as Open Souce under the GNU GPL License.

The source code had been included on this file (source.zip) and it is compiled used VACC 4.0.

Special Thanks to Leonardo Pino for releasing the source code of this program.


=======================================================================================



This program is to convert icons from the Win32 format into the OS/2 format (v 1.2). 
Multiples images are supported but only on 16x16 and/or 32x32 sizes.

Usage:

winico <win file> <OS/2 file> (*.ico extension is expected)

or 

winico -d <dir name> (here the program grabs all *.ico files it finds in the directory and converts them into the OS/2 format placing the files with the same name under a directory that is created at the place where winico was executed)

History

0.92
- Rewrote the code using C++ (VAC++ 4.0)
- The program creates images for 20x20 and 40x40 sizes (centering the image)
- Flexible design to make easier developing new features
- Some exception handling

0.91
- Fix some minor bugs

0.9
- Inicial public release

To do

- Find an easy algorithm to scale images.
- Support for OS/2 icon format 2.0
