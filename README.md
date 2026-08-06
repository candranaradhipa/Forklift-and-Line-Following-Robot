# Forklift-and-Line-Following-Robot

## Overview
This project develops a prototype line-following forklift robot designed for autonomous navigation along predefined paths. The experiment aims to integrate material handling capabilities with autonomous control and navigation technologies to support automated transportation tasks.

## Tools and Materials
### Tools
- Arduino IDE 1.8.19
- Autodesk Inventor 2023
- Proteus 8.13
- RD Works Version 8

### Materials
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
| Korean Glue | 1 |
| Duct Tape | 1 |

## Robot 
### Specification
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

### Mechanical and Design
The robot was designed using [Autodesk Inventor](https://www.autodesk.com/products/inventor/overview) as the primary 3D modeling software. The design process was divided into two main stages: the base design, which serves as the robot's main structure, and the forklift design, which functions as the material handling mechanism. Several small supporting components were obtained from [GrabCAD](https://grabcad.com/library) and integrated into the overall assembly to create a complete robotic system. After the design phase was completed, the robot's base was fabricated using laser cutting technology with the assistance of [RDWorks](https://www.rdacs.com/en/download?type=software) software. Finally, all components were assembled through the manufacturing process to produce a fully functional robot prototype.

The following images show the complete 3D model of the robot together with its engineering drawings, providing a detailed overview of the robot's mechanical design.

- 3D Model Design and Real-World Implementation
<img width="520" height="455" alt="Screenshot 2026-08-06 223630" src="https://github.com/user-attachments/assets/d9ba39e1-dc96-40f1-b901-6e659064dc4e" />
<img width="3120" height="4160" alt="IMG-20240107-WA0009" src="https://github.com/user-attachments/assets/6f79878a-ac9f-428b-965a-b9018891a152" />

- Engineering Drawing
<img width="2048" height="947" alt="image" src="https://github.com/user-attachments/assets/5080fbaf-83a9-497a-84b2-dde6a51bf4e3" />

- Laser Cutting
<img width="2296" height="4080" alt="20231120_145343" src="https://github.com/user-attachments/assets/7eff5077-ee79-4fad-95fa-be79ca7de579" />

### Electrical 
The electrical design phase focused on integrating all electronic components through jumper-wire connections on a mini breadboard. The Arduino Uno served as the central controller, managing communication and data exchange between the system components. Before being implemented on the physical prototype, the electronic circuit was first validated using Proteus simulation software to verify the functionality, connectivity, and overall performance of each component. Once the simulation results were satisfactory, the circuit was assembled and integrated into the robot prototype.

The following figures present the design and simulation of the electronic circuit using Proteus, along with its physical implementation on the robot prototype, demonstrating the realization of the developed system design.
<img width="1225" height="876" alt="image" src="https://github.com/user-attachments/assets/85763131-d28a-4967-9811-b0c5aae970bc" />
<img width="3840" height="2160" alt="IMG-20231009-WA0006" src="https://github.com/user-attachments/assets/03dcfd8b-c5ba-4046-983a-df07b1902784" />



