# Door-Locker-Security-System
Dual Microcontroller-Based Door Locker Security System Using Password Authentication
The goal of this project is to develop a reliable and secure smart door control system utilizing two microcontrollers, HMI_ECU and Control_ECU, which communicate via UART. The system ensures password-protected access, stores authentication data in an external EEPROM, and incorporates a PIR sensor, an H-bridge motor driver, and a buzzer for enhanced functionality.

Project Overview:

This smart door system is designed with two microcontrollers: one serving as the Human-Machine Interface (HMI_ECU) and the other as the Control Unit (Control_ECU). Users interact with the system through an LCD and keypad, where they enter passwords for authentication. The password is securely stored in an external EEPROM and verified before granting access. The door operates using a motor controlled by an H-bridge circuit, while additional security features include a PIR sensor for motion detection and a buzzer for alert notifications. The system also allows users to update passwords and enforces a security lock after multiple failed attempts.



Key Features:

1)Password Authentication: Secure login system with password verification stored in external EEPROM.
2)User Interface: LCD and keypad provide an intuitive method for entering and managing passwords.
3)UART-Based Communication: Ensures seamless data exchange between HMI_ECU and Control_ECU.
4)EEPROM Data Storage: Safeguards passwords and system data for persistent security.
5)Motorized Door Operation: Uses an H-bridge-controlled motor for locking and unlocking the door.
6)Security Alerts: A buzzer activates on failed password attempts or system alerts.
7)Motion Detection: A PIR sensor detects movement and can trigger door operations.
8)Password Update Feature: Users can modify their password upon successful authentication.
9)Auto Lock Mechanism: The system locks access for one minute after three consecutive incorrect password attempts.
