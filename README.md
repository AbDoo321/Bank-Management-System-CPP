# 🏦 Bank Management System (C++ Console Application)

A complete **console-based bank management system** developed in **C++** using **Object-Oriented Programming (OOP)** principles.

This project is built for learning purposes and demonstrates how a real banking system can be structured at a basic level.

---

## 🚀 Features

### 🔐 Authentication System
- User login system (bank employees)
- Login attempts limited to 3 tries
- Program terminates after 3 failed attempts
- Encrypted passwords stored in files
- Login activity logging (username, date, time)

---

### 🧑‍💼 Client Management
- View all bank clients
- Add new client
- Update client information
- Delete client
- Search for a specific client
- All client data stored in files

---

### 👨‍💼 User Management
- View all system users with full details
- Add new user
- Update user information
- Delete user
- Find/search for a specific user
- All user data stored in files
- Each user management feature implemented in a separate screen

---

### 💰 Transactions
- Deposit
- Withdraw
- Transfer between clients
- View short client list
- Full transaction history (date & time logged)

---

### 📊 Logs
- Login history screen
- Transaction history screen

---

## 🧭 Screens & Navigation System

- Each screen is implemented in a **separate class**
- All screens inherit from a base `Screen` class
- Shared features across all screens:
  - Display logged-in username
  - Display current date and time
  - Display screen title
  - Navigation options (Back / Main Menu / Logout)
  
- Every screen provides:
  - Return to its parent screen
  - Return to the main menu
  - Logout option

---

### 💱 Currency Exchange
- Display available currencies
- Simple currency conversion
- Fixed exchange rates stored in files (educational purpose)

---

## 🧠 Technical Details

- Language: **C++**
- Paradigm: **Object-Oriented Programming**
- IDE: **Visual Studio**
- Interface: **Console (Black Screen)**
- Data persistence using files
- Simple encryption algorithm (character shift)
- Role-based access control using bitwise permissions
- Clear separation between UI and backend logic
- Each screen implemented in a separate class for scalability

---

## 🧠 OOP Design Highlights

- Full Object-Oriented Design
- Clear separation between UI and backend logic
- Each screen represented by a separate class
- Base `Screen` class for shared behavior (Inheritance)
- Encapsulation of file operations
- Role-based permissions using bitwise operations
- Modular and scalable architecture
  
---

## 📚 Learning Source
This project was developed following the educational content of  
**Mohammed AbouHadhoud – Programming Advices**

---

## ⚠️ Disclaimer
This is an **educational project**, not intended for real banking use.

---

## 📌 Author
**Khellaf Mohamed Abd Elarouf**
