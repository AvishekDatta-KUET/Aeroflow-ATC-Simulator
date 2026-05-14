# ✈️ AeroFlow: Air Traffic Control Simulator

A comprehensive, terminal-based Air Traffic Control (ATC) and airspace management system built entirely in C++. This project was developed as a comprehensive Object-Oriented Programming (OOP) Lab project at Khulna University of Engineering & Technology (KUET). 

AeroFlow simulates a real-time airspace environment, allowing operators to track, manage, and coordinate both commercial planes and drones via a 2D radar grid and database system.

---

## 🌟 Key Features

* **🔐 Secure User Authentication:** Role-based access control requiring users to register and log in before accessing the main ATC terminal.
* **📡 2D Live Radar Map:** A visual coordinate grid system that dynamically maps the X and Y positions of all active aircraft in the sector.
* **✈️ Multi-Vehicle Management:** Distinct handling and data structures for different types of aircraft (Planes vs. Drones).
* **📊 Dynamic Database View:** Tabular, real-time tracking of critical flight telemetry including ID, Coordinates, Altitude, Fuel Level, and Flight Status.
* **🌤️ Weather Simulation:** An integrated weather generation system that simulates conditions (Clear, Cloudy, Rainy, Stormy) affecting airspace visibility and safety.
* **🚨 Emergency Protocols:** Dedicated emergency landing procedures for flights in distress or low on fuel.

---

## 💻 Visual Showcase

### Main Menu Interface
<img width="406" height="350" alt="image" src="https://github.com/user-attachments/assets/60a0f365-963f-4ac2-ab4b-a3388c0aa500" />


### Live Radar Tracking
<img width="881" height="682" alt="image" src="https://github.com/user-attachments/assets/9a6ad41e-faaf-413b-83dd-df4acb93e7ae" />


### Airspace Database
<img width="782" height="228" alt="image" src="https://github.com/user-attachments/assets/1d0ddf4b-2aba-44b5-b6f1-6ccf9ae67007" />


### Weather Generation
<img width="223" height="111" alt="image" src="https://github.com/user-attachments/assets/ebfa1589-5a87-4713-9f0e-53097c01e3ae" />


### Critical Warning
<img width="975" height="684" alt="image" src="https://github.com/user-attachments/assets/c89af98c-76c8-4b65-9735-d1e6f5731754" />


### Emergency Queue
<img width="424" height="187" alt="image" src="https://github.com/user-attachments/assets/934ec875-7dc6-4b0c-96e8-644f4d45effb" />


---

## 🛠️ Technical Stack

* **Language:** C++
* **Paradigm:** Object-Oriented Programming (OOP)
* **Environment:** Command-Line Interface (CLI) / Terminal
* **Core Concepts Demonstrated:** Encapsulation, Inheritance, Polymorphism, File I/O (for user authentication/data persistence), and dynamic data structures.

---

## 🚀 How to Run Locally

To run this simulator on your local machine, you will need a standard C++ compiler (like GCC/MinGW) installed.

1. **Clone the repository:**
   ```bash
   git clone [https://github.com/AvishekDatta-KUET/Aeroflow-ATC-Simulator.git](https://github.com/AvishekDatta-KUET/Aeroflow-ATC-Simulator.git)

---

### Navigate to the directory
cd Aeroflow-ATC-Simulator

---

### Compile the source code
g++ main.cpp -o aeroflow

---

### Run the executable
./aeroflow

---

###👨‍💻 Author
Avishek Datta

Computer Science and Engineering (CSE)

Khulna University of Engineering & Technology (KUET)
