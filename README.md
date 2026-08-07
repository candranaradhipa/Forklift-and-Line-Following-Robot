# Forklift-and-Line-Following-Robot

## Overview
This project develops a prototype line-following forklift robot designed for autonomous navigation along predefined paths. The experiment aims to integrate material handling capabilities with autonomous control and navigation technologies to support automated transportation tasks.

## Tools and Materials
> ### Tools <a name = 'Tools'></a>
- Arduino IDE 1.8.19
- Autodesk Inventor 2023
- Proteus 8.13
- RD Works Version 8

> ### Materials <a name = 'Mats'></a>

| Component | Quantity |
|-----------|---------:|
| Arduino Mega 2560 R3 | 1 |
| 25GA370 DC Motor | 4 |
| Servo Motor | 1 |
| L298N Motor Driver | 2 |
| LCD + Button Module | 1 |
| LM2596 Step-Down Converter | 1 |
| Lithium-Ion Battery | 1 |
| Mini Breadboard | 1 |
| Jumper Wires | 30 |
| 2KΩ Resistor | 1 |
| 10KΩ Resistor | 1 |
| Push ON/OFF Switch | 1 |
| TCRT5000 Line Sensor | 5 |
| Wheels + Shaft | 4 |
| Ball Caster | 1 |
| MG996R Servo Motor | 1 |
| 6 mm Bolts | 10 |
| 20 cm Aluminum Tube | 2 |
| 20 × 15 cm Aluminum Box | 2 |
| 1 m Cable | 1 |
| 5 mm Timing Pulley | 1 |
| Gear + Belt | 1 |
| 2 mm Nuts & Bolts | 10 |
| 3 mm Nuts & Bolts | 10 |
| 5 mm Nuts & Bolts | 10 |
| Hollow Connector | 4 |
| 3 mm Drill Bit | 2 |
| 10 cm Wire | 1 |
| Glue | 1 |
| Duct Tape | 1 |

## Robot 
> ### Specification <a name = 'specs'></a>

| Specification | Description |
|---------------|-------------|
| **Dimensions** | 19 cm × 17 cm × 23 cm |
| **Battery Voltage** | 11.97 V |
| **Battery Type** | Lithium-Ion |
| **Number of Motors** | 2 DC motors (wheel drive) and 1 DC motor (forklift mechanism) |
| **Motor Type** | 25GA370 DC Motor with Encoder |
| **Motor Driver** | L298N (2 units) |
| **Maximum Speed** | 100 RPM |
| **Controller** | Arduino Mega 2560 R3 |
| **Sensors** | TCRT5000 Line Sensor (5 units) |
| **Wheels** | • 25GA370 drive wheels (2 units)<br>• Caster wheel (1 unit) |

> ### Mechanical and Design <a name = 'mechs'></a>
The robot was designed using [Autodesk Inventor](https://www.autodesk.com/products/inventor/overview) as the primary 3D modeling software. The design process was divided into two main stages: the base design, which serves as the robot's main structure, and the forklift design, which functions as the material handling mechanism. Several small supporting components were obtained from [GrabCAD](https://grabcad.com/library) and integrated into the overall assembly to create a complete robotic system. After the design phase was completed, the robot's base was fabricated using laser cutting technology with the assistance of [RDWorks](https://www.rdacs.com/en/download?type=software) software. Finally, all components were assembled through the manufacturing process to produce a fully functional robot prototype.

The following images show the complete 3D model of the robot together with its engineering drawings, providing a detailed overview of the robot's mechanical design.

#### 3D Model Design and Real-World Implementation
<img width="520" height="455" alt="Screenshot 2026-08-06 223630" src="https://github.com/user-attachments/assets/d9ba39e1-dc96-40f1-b901-6e659064dc4e" />
<img width="520" height="693" alt="IMG-20240107-WA0009" src="https://github.com/user-attachments/assets/6f79878a-ac9f-428b-965a-b9018891a152" />


#### Engineering Drawing
<img width="520" height="240.2933985330073" alt="image" src="https://github.com/user-attachments/assets/5080fbaf-83a9-497a-84b2-dde6a51bf4e3" />


#### Laser Cutting
<img width="459.2" height="816" alt="20231120_145343" src="https://github.com/user-attachments/assets/7eff5077-ee79-4fad-95fa-be79ca7de579" />

Due to GitHub's file size limitations, the project files have been uploaded to [Google Drive](https://drive.google.com/drive/folders/1FPVimtD9b8ttk-RFd2ZUUYt0dnfM8Jfg) and can be accessed.

> ### Electrical <a name = 'elecs'></a>
The electrical design phase focused on integrating all electronic components through jumper-wire connections on a mini breadboard. The Arduino Uno served as the central controller, managing communication and data exchange between the system components. Before being implemented on the physical prototype, the electronic circuit was first validated using Proteus simulation software to verify the functionality, connectivity, and overall performance of each component. Once the simulation results were satisfactory, the circuit was assembled and integrated into the robot prototype.

The following figures present the design and simulation of the electronic circuit using Proteus, along with its physical implementation on the robot prototype, demonstrating the realization of the developed system design.

<img width="612.5" height="438" alt="image" src="https://github.com/user-attachments/assets/85763131-d28a-4967-9811-b0c5aae970bc" />
<img width="640" height="360" alt="IMG-20231009-WA0006" src="https://github.com/user-attachments/assets/03dcfd8b-c5ba-4046-983a-df07b1902784" />


#### Component Functions
- 12V Battery
  - Serves as the primary power supply for the DC motors, motor drivers, and servo motors. The battery is connected through a power switch and integrated with the system controlled by the Arduino Mega 2560.
- Power Switch
  - Functions as the main switch to connect or disconnect the battery power supply, allowing the robot to be turned on or off safely.
- L298N Motor Driver
  - Controls the DC motors by receiving control signals from the Arduino Mega 2560 to regulate motor speed and rotation direction.
- 25GA370 DC Motor
  - Acts as the primary actuator for driving the robot's wheels, enabling autonomous movement along the designated path.
- Motor Encoder
  - Integrated with the 25GA370 DC motors to measure motor rotation and speed, providing feedback for more accurate motion control.
- MG996R Servo Motor
  - Provides high-precision movement for the forklift mechanism. It controls the tilting motion of the forklift when lifting and lowering materials through an Arduino PWM signal.
- TCRT5000 Sensor
  - Functions as the line-following sensor by detecting the black line on the track, enabling autonomous navigation.
- 16×2 LCD and Keypad
  - The LCD displays the user interface, system menu, and battery percentage, while the keypad allows users to navigate the menu and execute robot commands.
- I²C Module
  - Provides communication between the LCD and the Arduino Mega 2560, reducing the number of required I/O pins and ensuring stable data transmission.
- 10 kΩ and 12 kΩ Resistors
  - Configured as a voltage divider to monitor the battery voltage, allowing the Arduino to calculate and display the battery percentage on the LCD.


> ### Software <a name = 'soft'></a>
The software development phase represents the final stage of the robot design process. After all mechanical and electronic components were fully assembled into a complete prototype, the control program was developed to enable the Arduino to coordinate all hardware components and facilitate communication between them. The program was written, compiled, and uploaded using the Arduino IDE. Finally, the firmware was transferred to the Arduino Mega 2560 via a USB connection between the laptop and the microcontroller, allowing the robot to execute all designed functionalities. 

The complete source code developed for this project is available in the [Source Code](https://github.com/candranaradhipa/Forklift-and-Line-Following-Robot/tree/main/Source%20Code) directory of this repository, providing the full implementation of the proposed system.

## Results
The following videos demonstrate the final result of the complete system integration. The first video shows the robot operating without the forklift mechanism, while the second video demonstrates the robot after the forklift mechanism has been integrated.

> ### Video Demo without Forklift <a name = 'no-fork'></a>
https://github.com/user-attachments/assets/dd95b45c-40da-4a4f-adf9-d42e022e0fd6

> ### Video Demo with  Forklift <a name = 'no-fork'></a>
https://github.com/user-attachments/assets/6198d68a-f7ee-4768-a3fc-842895fe6263


## Contributor
| Job Description | Name | Contact |
|---------------|-------------|-------------|
| **Team Leader** | [Safa Saviera Sulaiman](https://github.com/safasavieraa) ||
| **Electrical** | Klara Setyajati ||
| **Mechanical** | [Kyrieleison Charla Frans](https://github.com/KyrieleisonFrans) (Base)<br> [Alfa Noora Fithria](https://github.com/bluefrappucino) (Forklift)| <kyrieleison.frans@gmail.com> |
| **Software** | Sunan Sheva Teguh Setiadi |
| **Manufacture** | [Candra Naradhipa Cahyakusuma](https://github.com/candranaradhipa) | <candradhipa16@gmail.com> |

[Robotics and AI Engineering](https://ftmm.unair.ac.id/teknik-robotika-dan-kecerdasan-buatan-program-studi/), [Universitas Airlangga](https://unair.ac.id/)

