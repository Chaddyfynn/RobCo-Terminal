# RobCo Terminal
RobCo Terminal OS for Commodore 64

## Project Outline
This is a personal project with the aim of creating an OS similar
in aesthetic design to the RobCo terminals seen in the Fallout
franchise.

Currently the 'OS' is a standalone binary without additional libraries.

Please bear in mind I am a lowly theoretical phyics student, so all this
computer science stuff is just a hobby for me... I barely know what I'm doing.

## Limitations and Development
The application at this stage is limited to changing the screen colours and subsequently printing example text to the screen.

The development process is expected to look a little like this:
1. Example text printed to the screen (Done! Yay)
2. Simple CLI (Command Line Interface)
3. Navigable 'desktop' with a simple text editor
4. Navigable 'desktop' with multiple basic apps dependent on an OS library

## How to Build
You can compile this project on Windows using make and the cl65 compiler (get it here: https://cc65.github.io/).
The version of C used in this project is GNU89.

Once the /bin directory of the cc65 has been added to path, you can compile with
```bash
make
```
and that should be sufficient.  The output binary will be /bin/robco.

## How to Run
To run the binary you will need either a C64 emulator (I use VICE GTK3: https://vice-emu.sourceforge.io/index.html#download) or a Commodore 64.

Using VICE:
1. Run the x64sc.exe emulator.
2. Using the File option, smart attach the binary /bin/robco.
3. Using the BASIC CLI, type RUN to run the loaded binary.

## License and Acknowledgements
Naturally, this is based on the Fallout series, and many elements within the games (and now Amazon show).  With this in mind, all references to Fallout are in good taste, and I do not claim to own any references to the work of Bethesda Softworks LLC.

The user license can be found in the LICENSE file.  This version is licensed under an MIT license, so you can have at it really.  Give it a read.

## Developer Information
For info about my other, and academic, work please go to my website: https://server.westernelectronics.co.uk/charlie
