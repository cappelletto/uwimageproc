# uwimageproc
# Underwater Image Processing Toolbox

Toolbox of underwater video and image processing that can be employed in applications such as: SLAM, seafloor mosaics, Structure-from-Motion, 3D reconstruction of shipwrecks, coral colonies and reefs, fish census, etc.

**uwimageproc** if a free and open source software licensed under the [GNU GPLv3.0 License](https://en.wikipedia.org/wiki/GNU_General_Public_License), unless otherwise specified in particular modules or libraries (see LICENSE and README.md).

## Table of Contents
- [Modules list](#modules-list)
- [Requirements](#requirements)
- [Getting Started](#getting-started)
- [Directory Layout](#software-details)
- [License](#license)

## Modules list
- [videostrip](https://github.com/MecatronicaUSB/uwimageproc/tree/master/modules/videostrip) Automatic frame extraction for 2D mosaic and/or 3D reconstruction 
- [bgdehaze](https://github.com/MecatronicaUSB/uwimageproc/tree/master/modules/bgdehaze) BG Haze removal for UW images
- [aclahe](https://github.com/MecatronicaUSB/uwimageproc/tree/master/modules/aclahe) Automatic Clip-Limit AHE (CLAHE)
- [histretch](https://github.com/MecatronicaUSB/uwimageproc/tree/master/modules/histretch) Histogram stretch w/channel selection
- Automatic 2D mosaic generation > to be moved to [mosaic](https://github.com/MecatronicaUSB/mosaic)
- 3D sparse and dense reconstruction > to be moved to [uw-slam](https://github.com/MecatronicaUSB/uw-slam)

Each module or script contains information describing its usage, with (usually) some useful README file. Code documentation is expected to be provided in Doxygen-compatible format. The current release contains C/C++, Python and/or Matlab implementations.

## Requirements

The current release has been developed and tested in Ubuntu 16.04 LTS 64 bits

- [OpenCV 3.2+](http://opencv.org) and extra modules (OpenCV contrib).
- [CUDA]().
- [cmake 2.8](https://cmake.org/) - cmake making it happen again

## Getting Started

This repository provides an (increasing) collection of compatible, yet independent, underwater oriented modules for image and video. To start using this toolbox, proceed to the standard *clone* procedure:

```bash
cd <some_directory>
git clone https://github.com/MecatronicaUSB/uwimageproc.git
```

## Software Details

- Implementation done in C++, Python or Matlab/Octave.

## License

Copyright (c) 2017-2018 Grupo de Investigación y Desarrollo en Mecatrónica (<mecatronica@usb.ve>).
Released under the [GPL-3.0 License](LICENSE). 

