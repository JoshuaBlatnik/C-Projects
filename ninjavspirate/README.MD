# **Ninja vs Pirate Duel**  
### **Final Project Checkpoint — README.md**

## **Overview**
This project expands the original continuous “Ninja vs Pirate” assignment into a fully interactive C++ console game. The program demonstrates key programming concepts including:

- Object oriented design  
- Inheritance and polymorphism  
- Randomized turn based combat  
- Dynamic memory allocation (`new` and `delete`)  
- Pointer operations  
- Input validation and exception handling  
- Modular, multi file architecture  

This checkpoint submission represents the working foundation for the final project.

---

## **Core Features**

### **1. Object Oriented Game Design**
The game is built around a clean class hierarchy:

- **Character** — Base class  
- **Ninja** and **Pirate** — Derived classes with unique attacks, dialogue, and help text  
- **GameStructure** — Abstract interface enforcing `Help()`  

Each fighter implements its own combat behavior and personality through overridden functions.

---

### **2. Duel Combat System**
A complete turn based duel engine is implemented, featuring:

- Alternating attacker and defender turns  
- Randomized damage outcomes  
- Difficulty based damage scaling  
- Health bars for both fighters  
- Flavor text animations using a typewriter effect  
- End of match statistics including  
  - total damage dealt  
  - strongest single hit  
  - number of successful hits  
  - average damage  

The duel ends when one fighter reaches zero health.

---

### **3. Robust Input Handling with Exceptions**
To ensure a smooth user experience, the program includes:

- `try/catch` handling for invalid numbers  
- Out of range protections  
- Auto correction when both fighters share the same name  
- A cap on failed attempts before throwing a controlled `runtime_error`  

All error responses are clearly explained to the user.

---

### **4. Dynamic Memory and Pointer Demonstration**
Before gameplay begins, the user experiences a guided tutorial showing:

- Declaring pointer variables  
- Allocating five primitive values on the heap  
- Modifying heap data through pointers  
- Proper deallocation with `delete`  
- Resetting pointers to `nullptr`  

During the actual duel, fighters are allocated with `new` and cleaned up properly each round.

---

### **5. Utility Module**
The project includes a complete utility system that handles:

- Typewriter style animated output  
- Windows console color  
- Delays and timing  
- Safe string and integer input  
- Health bar creation  
- Text alignment helpers  

This keeps main gameplay logic clean and readable.

---

## **File Structure**
```
Character.h / Character.cpp  
Duel.h / Duel.cpp  
GameStructure.h  
Utilities.h / Utilities.cpp  
main.cpp  
```

---

## **How to Compile and Run**

### **Windows (MinGW or VS Developer Command Prompt)**
```bash
g++ *.cpp -o NinjaPirateDuel
NinjaPirateDuel.exe
```

### **Linux / MacOS**
```bash
g++ *.cpp -o NinjaPirateDuel
./NinjaPirateDuel
```

ANSI color compatible terminals recommended.

---

## **Gameplay Flow**
1. Intro animation  
2. Memory tutorial explaining `new` and `delete`  
3. Enter Ninja and Pirate names  
4. Names validated (auto rename if needed)  
5. Select difficulty  
6. Duel begins  
7. End of match summary  
8. Replay menu (rematch, new fighters, or exit)

---

## **Future Expansion (Final Project Goals)**
Planned improvements include:

- Additional fighter classes  
- Special abilities with cooldowns  
- Persisting stats  
- Improved ASCII UI  
- Item buff system  
- Smarter AI behavior  

---