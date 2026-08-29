# Nios V Experiments

This repository contains Nios V/m RISC-V processor experiments
implemented on an Intel FPGA using Quartus Prime, Platform Designer, the
Nios V Command Shell, and RiscFree IDE.

The workflow used for each experiment is:

``` text
Quartus Project
      │
      ▼
Platform Designer
      │
      ├── Nios V/m Processor
      ├── On-Chip Memory
      └── JTAG UART
      │
      ▼
Generate HDL
      │
      ▼
Quartus Pin Assignment + Compilation
      │
      ▼
.sopcinfo
      │
      ▼
Generate HAL BSP
      │
      ▼
Create Nios V Application
      │
      ▼
Build Application → app.elf
      │
      ▼
Program FPGA with .sof
      │
      ▼
JTAG UART (juart-terminal)
      │
      ▼
RiscFree IDE
      │
      ▼
Run using Ashling RISC-V Hardware Debugging
      │
      ▼
Application Output
```

------------------------------------------------------------------------

## 1. Tools Used

-   Intel Quartus Prime
-   Platform Designer (Qsys)
-   Nios V Command Shell
-   RiscFree IDE
-   JTAG / USB-Blaster connection
-   Intel FPGA development board

------------------------------------------------------------------------

## 2. Project Structure

Each experiment is maintained as a separate directory.

``` text
Nios-V-Experiments/
│
├── helloworld/
│   ├── <Quartus project files>
│   ├── <Platform Designer system>
│   ├── <generated system files>
│   ├── simulation/
│   └── software/
│       ├── bsp/
│       └── app/
│
├── ledswitch/
│   ├── <Quartus project files>
│   ├── <Platform Designer system>
│   ├── <generated system files>
│   ├── simulation/
│   └── software/
│       ├── bsp/
│       └── app/
│
├── pushbutton/
│   └── ...
│
└── .gitignore
```

Important project-definition and reproducibility files such as `.qpf`,
`.qsf`, `.qsys`, `.sopcinfo`, `.qip`, HDL, constraints, application
source, and required BSP files are retained.

Generated build/cache files, IDE metadata, logs, and ZIP archives are
excluded using `.gitignore`.

------------------------------------------------------------------------

# 3. Hardware Design

## 3.1 Create a Quartus Project

1.  Open Quartus Prime.
2.  Select **File → New Project Wizard**.
3.  Specify the project directory and project name.
4.  Create an empty project.
5.  Select the target FPGA device.
6.  Complete the project creation.

------------------------------------------------------------------------

## 3.2 Create the Platform Designer System

Open Platform Designer from Quartus:

``` text
Tools → Platform Designer
```

Create a new Qsys/Platform Designer system.

The default system contains a Clock Source.

------------------------------------------------------------------------

## 3.3 Add Nios V/m Processor

From the IP Catalog:

``` text
Processors and Peripherals
→ Embedded Processors
→ Nios V/m Processor
```

Add the Nios V/m Processor and leave the processor at its default
settings.

------------------------------------------------------------------------

## 3.4 Add On-Chip Memory

From the IP Catalog:

``` text
Basic Functions
→ On-Chip Memory
→ On-Chip Memory (RAM or ROM)
```

Configure:

``` text
Total Memory Size = 131072 Bytes (128 KB)
```

Then instantiate the memory.

------------------------------------------------------------------------

## 3.5 Add JTAG UART

From the IP Catalog:

``` text
Interface Protocols
→ Serial
→ JTAG UART
```

Add the JTAG UART using the default settings.

------------------------------------------------------------------------

## 3.6 Connect the System

Connect the Clock Source to the Nios V processor, On-Chip Memory, and
JTAG UART.

The required connections include:

``` text
Clock Source
 ├── Nios V clock
 ├── On-Chip Memory clock
 └── JTAG UART clock

Clock Reset
 ├── Nios V reset
 ├── On-Chip Memory reset
 └── JTAG UART reset

Nios V
 ├── instruction_manager → On-Chip Memory
 ├── data_manager        → On-Chip Memory
 └── platform_irq_rx     → JTAG UART IRQ

JTAG UART
 └── avalon_jtag_slave → Nios V data interface
```

Use:

``` text
System → Assign Base Addresses
```

to assign the required base addresses and clear address-related
warnings.

------------------------------------------------------------------------

## 3.7 Configure the Reset Vector

Open the Nios V/m Processor parameter editor and navigate to the
**Vectors** section.

Configure:

``` text
Reset Agent = onchip_memory2_0.s1
Reset Offset = 0x00000000
```

------------------------------------------------------------------------

## 3.8 Generate HDL

Save the Platform Designer system.

Select:

``` text
Generate HDL
```

Leave the generation settings at their required/default values and
generate the system.

Verify that HDL generation completes successfully.

The generated system directory contains the files required by the
Quartus project.

------------------------------------------------------------------------

# 4. Quartus Hardware Configuration

## 4.1 Add Generated Files

Return to Quartus Prime.

Navigate to:

``` text
Assignments → Settings → Files
```

Verify that the Platform Designer/Qsys system and generated IP files are
included in the project.

Generated `.qip` files and the associated generated HDL are retained in
this repository because they are part of the project reconstruction
flow.

------------------------------------------------------------------------

## 4.2 Pin Assignment

Run:

``` text
Processing → Start → Start Analysis & Elaboration
```

Then open:

``` text
Assignments → Pin Planner
```

Assign the required FPGA pins for the experiment.

Pin assignments depend on the hardware used and the peripherals included
in the individual experiment.

------------------------------------------------------------------------

## 4.3 Compile the Hardware

Start compilation:

``` text
Processing → Start Compilation
```

Verify that the Quartus project compiles successfully.

The resulting FPGA programming file is:

``` text
<project>.sof
```

------------------------------------------------------------------------

# 5. Software Development

The software portion uses the Nios V Command Shell and RiscFree IDE.

Each experiment contains:

``` text
software/
├── bsp/
└── app/
```

------------------------------------------------------------------------

## 5.1 Generate the HAL BSP

Open the **Nios V Command Shell**.

The BSP settings file is located at:

``` text
software/bsp/settings.bsp
```

Generate the BSP using the Platform Designer `.sopcinfo` file:

``` bash
niosv-bsp -c -t=hal --sopcinfo=<system>.sopcinfo software/bsp/settings.bsp
```

Example:

``` bash
niosv-bsp -c -t=hal --sopcinfo=niosv_helloworld_2.sopcinfo software/bsp/settings.bsp
```

Verify that BSP generation completes successfully.

------------------------------------------------------------------------

## 5.2 Create the Application

Place the application source file inside:

``` text
software/app/
```

For example:

``` text
software/app/hello.c
```

The application source depends on the individual experiment.

------------------------------------------------------------------------

## 5.3 Generate the Application CMake Project

Use the Nios V Command Shell:

``` bash
niosv-app -a=software/app -b=software/bsp -s=software/app/hello.c
```

This generates the application `CMakeLists.txt` file in the application
directory.

Verify that generation completes successfully.

------------------------------------------------------------------------

## 5.4 Open the Application in RiscFree

Open **RiscFree IDE**.

Locate the application project in the Project Explorer.

The application is built using the generated CMake project.

------------------------------------------------------------------------

## 5.5 Build the Application

Build the application from RiscFree:

``` text
Right-click app
→ Build Project
```

A successful build produces the application executable:

``` text
app.elf
```

The generated build directory is not required in the repository and is
excluded by `.gitignore`.

------------------------------------------------------------------------

# 6. Program the FPGA

Before executing the software, program the hardware design into the
FPGA.

Open Quartus Programmer:

``` text
Tools → Programmer
```

1.  Connect the FPGA board through the JTAG/USB-Blaster connection.
2.  Detect the hardware.
3.  Select the generated `.sof` file.
4.  Start programming.
5.  Verify successful programming.

The programming operation should report successful completion before
proceeding.

------------------------------------------------------------------------

# 7. Open JTAG UART

Open the Nios V Command Shell and execute:

``` bash
juart-terminal
```

Verify that the terminal is connected to the hardware target using JTAG
UART.

Keep the terminal open while executing the application.

------------------------------------------------------------------------

# 8. Run the Nios V Application

Open RiscFree IDE.

In the Project Explorer:

``` text
Right-click app
→ Run As
→ Ashling RISC-V Hardware Debugging
```

For the first execution, configure the C local application.

Select:

``` text
app.elf
```

as the application.

In the debugger configuration:

``` text
Debugger → Auto-detect Scan Chain
```

Select the appropriate FPGA device/TAP.

For the target used in the supplied procedure, select:

``` text
5CSE(BAS|MAS)
```

The Nios V core should then be detected.

Click:

``` text
Run
```

------------------------------------------------------------------------

# 9. Observe the Output

The application executes on the Nios V processor.

Console output is observed through the JTAG UART in the Nios V Command
Shell:

``` text
Nios V Application
        │
        ▼
     JTAG UART
        │
        ▼
  juart-terminal
```

For the Hello World experiment, the final application output is
displayed in the Nios V Command Shell.

------------------------------------------------------------------------

# 10. Experiment Workflow Summary

For each new Nios V experiment, follow this sequence:

### Hardware

``` text
1. Create Quartus Project
2. Open Platform Designer
3. Add Nios V/m
4. Add On-Chip Memory
5. Add required peripherals
6. Connect interfaces
7. Assign Base Addresses
8. Configure Reset Vector
9. Generate HDL
10. Add generated files to Quartus
11. Assign FPGA pins
12. Compile
```

### Software

``` text
13. Generate HAL BSP
14. Add application source
15. Generate CMake project
16. Open/build in RiscFree
17. Generate app.elf
```

### Execution

``` text
18. Program FPGA with .sof
19. Start juart-terminal
20. Run app.elf using RISC-V hardware debugging
21. Observe application output
```

------------------------------------------------------------------------


------------------------------------------------------------------------

# 12. Experiments

  Experiment     Description
  -------------- --------------------------------------------------
  `helloworld`   Basic Nios V application with JTAG UART output
  `ledswitch`    Nios V system with LED/switch peripheral control
  `pushbutton`   Nios V system using pushbutton input
  `...`          Additional experiments can be added here

## //ADD URL LINK TO .C file later

------------------------------------------------------------------------


The Nios V/m processor system is successfully created in Platform
Designer, compiled into an FPGA hardware image, provided with a HAL BSP
and CMake-based application, and executed through RiscFree using RISC-V
hardware debugging. Application output is verified through the JTAG UART
terminal.
