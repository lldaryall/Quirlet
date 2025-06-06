# Quirlet (C++)

As someone who is too cheap to pay for premium Quizlet when studying for my AWS certifications I made quirlet to study AWS certifications from the command line. 

## Features
- Flashcards, multiple-choice, written test, and full practice exam  
- 13 AWS certifications, including new AI Practitioner & SA Professional  
- Random order every run  
- Press **q** or **0** in any mode to exit early and see the answer key

## Build (macOS • Linux • WSL)

1. **Install g++ 11+**

```bash
# Ubuntu / Debian / WSL
sudo apt update && sudo apt install build-essential

# macOS (Apple CLI tools)
xcode-select --install

2. **Compile**
# build
g++ -std=c++17 -O2 src/*.cpp -o quirlet

# or use the pre‑built binary
./build/quirlet.exe

# run
./quirlet           # interactive menu
