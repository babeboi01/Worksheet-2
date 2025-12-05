# 🚀 Operating Systems – Worksheet 2  
## 🎹 Inputs, Interrupts & Terminal System  
*A fully detailed, professionally written README with emojis*

---

## 📘 Overview  
This project extends our simple OS kernel by adding **keyboard input**, **interrupt handling**, and a **mini terminal (shell)**.  
We move from a framebuffer-only system to a kernel that interacts with hardware using:

- 🖥️ I/O Ports  
- ⚡ Programmable Interrupt Controller (PIC)  
- 🧱 Interrupt Descriptor Table (IDT)  
- ⌨️ Keyboard Interrupts  
- 🔤 Scan-code → ASCII conversion  
- 📦 Input buffer (`getc`, `readline`)  
- 💻 A basic shell with commands  

This README includes all required explanation and references to code files implemented in this worksheet.

---

# 🧩 1. Understanding Hardware Interrupts  
Interrupts allow external devices (like the keyboard) to signal the CPU.  
When a key is pressed:

1. The keyboard hardware sends a **scan code** to port `0x60`
2. PIC signals IRQ1
3. CPU jumps into interrupt vector `33` (0x21)
4. Our assembly interrupt handler runs
5. C-level handler processes the scan code
6. Character is converted to ASCII and stored/displayed

This mechanism builds our foundation for terminal input.

---

# 💾 2. I/O Port Access (`inb`, `outb`)  
We use assembly routines to read/write bytes to I/O ports — an essential low-level operation.

These functions allow:
- Reading the keyboard controller
- Remapping the PIC
- Accessing device buffers

---

# 🧱 3. Types (`types.h`)  
To ensure portability, we use fixed-size data types:

- `u8int` → 8-bit unsigned  
- `u16int` → 16-bit unsigned  
- `u32int` → 32-bit unsigned  

These types make it easy to define IDT entries and hardware structures.

---

# ⚙️ 4. PIC Remapping  
The Programmable Interrupt Controller originally maps IRQ0–IRQ15 to CPU interrupts 0–15, which conflict with CPU exceptions.

To prevent this, we **remap the PIC** to:

- Master PIC → offset `0x20` (32)
- Slave PIC → offset `0x28` (40)

Thus, **keyboard IRQ1** becomes **interrupt 33**.

We also unmask IRQ1 so keyboard input is enabled.

---

# 📜 5. The Interrupt Descriptor Table (IDT)  
The IDT is a table where each entry stores:

- Address of interrupt handler  
- Code segment selector  
- Attributes  

Our IDT contains 256 entries.  
We configure entry **33** to point to our keyboard interrupt stub.

---

# 🧵 6. Assembly Interrupt Stubs  
These stubs do important work:

- Save CPU registers  
- Push interrupt numbers  
- Call our C-level handler  
- Restore registers  
- Execute `iret`  

They form the “bridge” between CPU hardware and C code.

---

# 🎹 7. Keyboard Input System  
The keyboard sends *scan codes* for every key press or release.  
Our driver:

1. Reads scan codes from port `0x60`  
2. Ignores key-release codes  
3. Converts scan codes to ASCII  
4. Supports letters, numbers, space, enter, backspace  
5. Sends characters to:
   - Framebuffer (display)
   - Input buffer (for terminal commands)

---

# 📥 8. Input Buffer (`getc`, `readline`)  
We implement a **circular buffer**:

- `buffer_push(c)` — Called from the interrupt handler
- `getc()` — Blocks until a character is available
- `readline()` — Reads full lines until enter (newline)

This layer decouples interrupt-level input from terminal-level processing.

---

# 🖥️ 9. Terminal (Shell)  
We implement a *very small* shell similar to Unix:

Supported commands:

### 📢 `echo <text>`  
Prints text to screen.

### 🧽 `clear`  
Clears the framebuffer.

### ❓ `help`  
Lists available commands.

The shell supports:

- Prompt: `myos> `
- Line input
- Command parsing
- Error handling for unknown commands

---

# 🏗️ 10. Build System (Makefile)  
We include a Makefile that:

- Compiles all `.c` and `.s` files
- Produces `kernel.elf`
- Offers a `run` target to launch QEMU

This allows simple one-command builds.

---

# 🧠 11. How Everything Works Together  
Below is the flow from key press → terminal:

1. User presses a key  
2. Keyboard sends scan code → port `0x60`  
3. PIC signals IRQ1  
4. CPU jumps to IDT entry 33  
5. Assembly wrapper runs  
6. `interrupt_handler()` (C) processes input  
7. Scan code → ASCII conversion  
8. Character is:  
   - Displayed on screen  
   - Placed into input buffer  
9. Terminal uses `readline()` to capture commands  
10. Shell executes commands and prints output  

---

# 🧪 12. Testing Instructions

To test your OS in QEMU:

![alt text](<Screenshot 2025-12-05 193547.png>)

Everything should work through hardware interrupts.

---

# 🏁 13. Final Notes  
This project introduces you to **real OS internals**, such as:

- Hardware interrupt management  
- Low-level assembly interfaces  
- Device drivers  
- Interrupt-safe buffering  
- Command interpreter design  

These are fundamental building blocks used in Linux, Windows, and other real operating systems.

---
