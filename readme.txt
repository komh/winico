===============================================================================
2005/01/01

WINICO had been released as Open Souce under the GNU GPL License.

The source code had been included on this file (source.zip) and it is compiled
used VACC 4.0.

Special Thanks to Leonardo Pino for releasing the source code of this program.

2015/01/28

The source code can be compiled with kLIBC and GNU Make.
===============================================================================



This program is to convert icons from the Win32 format into the OS/2 format
(v1.2).
Multiple images are supported. In cases of 16x16 and/or 32x32 sizes, 
respectively, 20x20 and/or 40x40 sizes are generated additionally.

Usage:

winico <win file> <OS/2 file> (*.ico extension is expected)

or 

winico -d <dir name> (here the program grabs all *.ico files it finds in the 
directory and converts them into the OS/2 format placing the files with the 
same name under a directory that is created at the place where winico was 
executed)

History

0.94 ( 2015/04/25 )
- Some 32-bits icons cannot be loaded by ICONEDIT. Fixed by converting 32-bits
  icons to 24-bits icons
- There are some gliches of 24-bits icons converted from 32-bits icons when
  icons are inverted by selecting them. Fixed by considering AND map

0.93 ( 2015/01/28 )
- Support kLIBC and GNU Make build system
- Support arbitrary image sizes
- Print out some informational messages
- Fixed that an icon file whose name contained multiple dots were recgonized 
  as 'Wrong file format'.

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
