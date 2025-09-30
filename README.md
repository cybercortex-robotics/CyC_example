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

## 1. Introduction

<a href="https://www.cybercortex.ai/" target="_blank">CyberCortex.AI</a> is a lightweight real-time AI operating system designed for autonomous robots and complex automation. It operates directly on embedded hardware, enabling robots to process sensory data, perform decision-making, and execute actions efficiently.

This repository illustrates how to use CyberCortex.AI in a straightforward robot vision application. The example uses the <a href="https://github.com/cybercortex-robotics/inference" target="_blank">CyberCortex.AI.inference</a> system, as a submodule in the current repository.

In this example, we use four filters:

| Component | License | Source | Notes |
| :--- | :---: | ---: | :--- |
| **Filter_HW_Camera** | 🌐 open-source | local | Acquires images from an USB, or integrated camera. |
| **Filter_Vision_BinarySegmentation** | 🌐 open-source | local | Performs image segmentation on the input camera image. |
| **Filter_Visualization_Sensing** | 🔒 proprietary | linux-gcc-x64 <br> linux-gcc-arm-x64 <br> <a href="https://www.cybercortex.ai/data/filters/Filter_Visualization_Sensing/win-msvc-x64/Filter_Visualization_Sensing.zip" target="_blank">win-msvc-x64</a> | Visualization of input and output filters results. |
| **Filter_Comm_DataChannel** | 🔒 proprietary | linux-gcc-x64 <br> linux-gcc-arm-x64 <br> <a href="https://www.cybercortex.ai/data/filters/Filter_Comm_DataChannel/win-msvc-x64/Filter_Comm_DataChannel.zip" target="_blank">win-msvc-x64</a> | Communication between distributed DataBlocks and CyberCortex.AI Droids. |

## Quick Start

### Requirements⚒️

CyberCortex.AI's requirements are the following libraries: Eigen, libconfig++, Msgpack, Octomap, OpenCV, SpdLog and Qt5.

#### Dependencies instalation (using apt) ####

```bash
sudo apt install libopencv-dev libeigen3-dev libspdlog-dev libfmt-dev libconfig++-dev libmsgpack-dev liboctomap-dev
sudo apt install qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools
```

#### Dependencies instalation (local) ####

For better controlling the distributions of the dependencies, one can installed them localy in a ```3rdParty``` folder.
Precompiled windows and linux dependencies are available for download:

| Library         | Download link                        |
|-----------------|--------------------------------------|
| **Eigen**       | Linear algebra, matrix & vector math |
| **libconfig++** | C++ configuration file parser      |
| **Msgpack**     | Efficient binary serialization       |
| **Octomap**     | 3D occupancy mapping                 |
| **OpenCV**      | Computer vision & image processing   |
| **SpdLog**      | Fast C++ logging library             |
| **Qt5**         | GUI toolkit and application framework|


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

