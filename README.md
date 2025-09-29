# CyC_example

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
  <img src="https://github.com/cybercortex-robotics/CyC_example/figures/cmake_filters_enable.png?raw=true" width="60%" alt="cmake_filters_enable" />
</div>

