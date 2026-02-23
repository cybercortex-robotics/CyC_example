# CyC_example: How to use CyberCortex.AI

<!-- markdownlint-disable first-line-h1 -->
<!-- markdownlint-disable html -->
<!-- markdownlint-disable no-duplicate-header -->

<div align="center">
  <img src="https://github.com/cybercortex-robotics/inference/blob/main/figures/cyc_logo.png?raw=true" width="60%" alt="CyberCortex.AI.inference" />
</div>
<hr>
<div align="center" style="line-height: 1;">
  <a href="https://www.cybercortex.ai/" target="_blank"><img alt="Homepage"
    src="https://github.com/cybercortex-robotics/inference/blob/main/figures/cyc_logo_badge.svg?raw=true"/>
  </a>
  <br>
  <a href="https://arxiv.org/abs/2409.01241"><b>Paper Link</b>👁️</a>
</div>

## Introduction

<a href="https://www.cybercortex.ai/" target="_blank">CyberCortex.AI</a> is a lightweight real-time AI operating system designed for autonomous robots and complex automation. It operates directly on embedded hardware, enabling robots to process sensory data, perform decision-making, and execute actions efficiently.

This repository illustrates how to use CyberCortex.AI in a straightforward robot vision application. The example uses the <a href="https://github.com/cybercortex-robotics/inference" target="_blank">CyberCortex.AI.inference</a> system, as a submodule in the current repository.

In this example, we use four filters:

| Component | License | Source | Notes |
| :--- | :---: | ----------: | :--- |
| **Filter_HW_Camera** | 🌐 open-source | local | Acquires images from an USB, or integrated camera. |
| **Filter_Vision_BinarySegmentation** | 🌐 open-source | local | Performs image segmentation on the input camera image. |
| **Filter_Visualization_Sensing** | 🔒 proprietary | <a href="https://www.cybercortex.ai/data/filters/Filter_Visualization_Sensing/linux-gcc-x64-ubuntu-24/Filter_Visualization_Sensing.zip" target="_blank">linux-gcc-x64 (ubuntu 24)</a> <br> linux-gcc-arm-x64 <br> <a href="https://www.cybercortex.ai/data/filters/Filter_Visualization_Sensing/win-msvc-x64/Filter_Visualization_Sensing.zip" target="_blank">win-msvc-x64</a> | Visualization of input and output filters results. |
| **Filter_Comm_DataChannel** | 🔒 proprietary | <a href="https://www.cybercortex.ai/data/filters/Filter_Comm_DataChannel/linux-gcc-x64-ubuntu-24/Filter_Comm_DataChannel.zip" target="_blank">linux-gcc-x64 (ubuntu 24)</a> <br> linux-gcc-arm-x64 <br> <a href="https://www.cybercortex.ai/data/filters/Filter_Comm_DataChannel/win-msvc-x64/Filter_Comm_DataChannel.zip" target="_blank">win-msvc-x64</a> | Communication between distributed DataBlocks (including CyberCortex.AI Droids). |

## Quick Start

### Running the binaries

Download the binaries from github Releases section.
Unzip the content and
```bash
cd CyC_example
```

#### Linux specific ####

Make the application executable:
```bash
chmod +x bin/App_CycCore
```

Install dependencies:
```bash
sudo apt install libopencv-dev libfmt-dev libconfig++-dev liboctomap-dev libopenh264-dev qtbase5-dev freeglut3 libqglviewer2-qt5
```

Go to the bin folder and run:
```bash
./run.sh
```


### Requirements ⚒️

CyberCortex.AI's requirements are the following libraries: Eigen, libconfig++, Msgpack, Octomap, OpenCV, SpdLog and Qt5.

#### Dependencies instalation (using apt) ####

```bash
sudo apt install libopencv-dev libeigen3-dev libspdlog-dev libfmt-dev libconfig++-dev libmsgpack-dev liboctomap-dev
```
QT libraries for visualization
```bash
sudo apt install qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools
```

#### Dependencies instalation (local) ####

For better controlling the distributions of the dependencies, one can installed them localy in a ```3rdParty``` folder.
Precompiled windows and linux dependencies are available for download:

| Library         | Download link                                                     |
|-----------------|-------------------------------------------------------------------|
| **Eigen**       | https://drive.google.com/file/d/1-1MQH4B1fxEOehrdhlKT7QtG4shKSW7_ |
| **libconfig++** | https://drive.google.com/file/d/1YtLF52m5gYgAU2kH8aKAvK5VP6x_C2Z2 |
| **Msgpack**     | https://drive.google.com/file/d/1l78Y2wOy3Z-l7m0gChnFCZn8retwfeIh |
| **Octomap**     | https://drive.google.com/file/d/1dFAx7jUxee-SYIMJihDT3ResKFOSiaym |
| **OpenCV**      | https://drive.google.com/file/d/1PUKKQ_l6ADCthnZLO7LvmejRrpGc409J |
| **SpdLog**      | https://drive.google.com/file/d/1w2M07evGCUo-6lrIs3M1G_vIiYWRxdXb |
| **Qt5**         | https://drive.google.com/file/d/1LCaccGxOxVzrR9IJiHB4AGg5bGR8RxRh |

Unzip all dependency files in a ```3rdParty``` folder.
The link to the ```3rdParty``` folder has to be specified in the root ```CMakeLists.txt``` file of the project.

When both local and system dependencies are installed, the local dependencies will be prefered.

### Installation

Install this repo in the following way:  
```bash
git clone https://github.com/cybercortex-robotics/CyC_example.git
cd CyC_example
```

Initialize the CyberCortex.AI.inference submodule:
```bash
git submodule update --remote --init
```

Configure the project in the cmake-gui utility. Enable the two local filters and the application inference core:

<div align="center">
  <img src="https://github.com/cybercortex-robotics/CyC_example/blob/main/figures/cmake_filters_enable.png?raw=true" width="40%" alt="cmake_filters_enable" />
</div>

Reconfigure and generate the project.

Download the binaries of the two proprietary filters using the links in the table above. Unzip and copy the binaries in the ``bin/filters`` folder (the two local filter should already be compiled there).

### Runtime

In command line, go to the ```bin``` folder of the project.

#### Windows specific ####

Add the bin folders of your Qt5, opencv and libconfig++ libraries to the environment variables system path.
Install the Qt5 dependencies by running:
```bash
windeployqt.exe App_CycCore.exe
```

#### Start the CyberCortex.AI DataBlock ####

Start the CyberCortex.AI inference core by executing ```App_CycCore```, having as argument a configured DataBlock.

```bash
./App_CycCore ../etc/datablocks/example.conf
```

In windows, start the datablock using the ```*.exe``` extension:
```bash
./App_CycCore.exe ../etc/datablocks/example.conf
```

The console will display the running datablock:

<div align="center">
  <img src="https://github.com/cybercortex-robotics/CyC_example/blob/main/figures/datablock_cmd.png?raw=true" width="60%" alt="cmake_filters_enable" />
</div>

The output of each data block can be inspected by typing the number of the filter in the command line and pressing enter (under windows, press enter twice).

## Citation
```
@article{CyberCortex_AI,
  author = {Grigorescu, Sorin and Zaha, Mihai},
  title = {CyberCortex.AI: An AI-based operating system for autonomous robotics and complex automation},
  journal = {Journal of Field Robotics},
  volume = {42},
  number = {2},
  pages = {474-492},
  doi = {https://doi.org/10.1002/rob.22426},
  url = {https://onlinelibrary.wiley.com/doi/abs/10.1002/rob.22426},
  year = {2025}
}
```
