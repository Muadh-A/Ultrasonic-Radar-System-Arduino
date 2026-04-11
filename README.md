
(In collaboration with Taha Sohail)

Autonomous Ultrasonic Radar System with Real-Time Web Visualization

Software: Custom browser-based radar interface built from scratch in C++ using the Web Serial API for real-time serial communication between the hardware and browser, and HTML5 Canvas for live 2D rendering. Features an independent sweep animation running on requestAnimationFrame, a fading dot plot system with timestamp-based alpha decay, serial stream parsing, and configurable detection range and sweep speed — no frontend frameworks or external libraries used.

Hardware: Elegoo Uno R3, HC-SR04 ultrasonic sensor, SG90 servo motor, and 16x2 LCD display performing continuous 180° angular sweeps with acoustic echo-based distance measurement over UART serial at 9600 baud.
