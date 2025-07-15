# Minitalk

![C](https://img.shields.io/badge/Language-C-blue.svg)![OS](https://img.shields.io/badge/OS-Linux%20%7C%20macOS-lightgrey.svg)!(https://img.shields.io/badge/42%20Project-Minitalk-black.svg)

**Minitalk is a project from the 42 coding school that showcases a fundamental aspect of Unix programming: Inter-Process Communication (IPC). The challenge is to create a client-server program that communicates a string of text using only two custom signals: `SIGUSR1` and `SIGUSR2`.**

This project demonstrates how simple signals, traditionally used for basic process management, can be harnessed to transmit complex data, bit by bit.

---

## 🚀 How it Works: The Core Concept

The fundamental idea behind Minitalk is to represent data in its most basic form: binary. Since we have two distinct signals, `SIGUSR1` and `SIGUSR2`, we can assign a binary value to each:

*   `SIGUSR1` = **0**
*   `SIGUSR2` = **1**

By sending a sequence of these signals from a client process to a server process, we can transmit any character, and by extension, any string of text.

### The Journey of a Character

1.  **Client-Side (Deconstruction):** The client takes a character (e.g., `'A'`).
2.  The ASCII value of `'A'` is `65`. In binary, this is `01000001`.
3.  The client sends a sequence of 8 signals to the server, one for each bit. For `'A'`, this sequence would be:
    `SIGUSR1` (0) `SIGUSR2` (1) `SIGUSR1` (0) `SIGUSR1` (0) `SIGUSR1` (0) `SIGUSR1` (0) `SIGUSR1` (0) `SIGUSR2` (1)

4.  **Server-Side (Reconstruction):** The server listens for these signals.
5.  Upon receiving a signal, it reconstructs the bits back into a byte. It uses bit-shifting operations to place the incoming `0` or `1` into an `unsigned char` variable.
6.  After 8 signals have been received, the server has a complete byte, which it can then print as a character.

This process is repeated for every character in the message, followed by a null terminator (`\0`) to signify the end of the transmission.

---

## 🛠️ Implementation Details

The project is divided into two main components: the `server` and the `client`. Both have a mandatory and a bonus version.

### The Server

The server's primary role is to listen for and interpret signals sent by the client.

*   **PID Display**: Upon launch, the server immediately prints its Process ID (PID). This PID is essential, as it's the "address" the client needs to send signals to.
    ```bash
    $ ./server
    PID: 12345
    ```
*   **Signal Handling with `sigaction`**: The server uses the `sigaction` function to establish a sophisticated handler for `SIGUSR1` and `SIGUSR2`. Unlike the simpler `signal` function, `sigaction` allows us to get more information about the incoming signal, most importantly, the PID of the sender (the client). This is achieved by setting the `SA_SIGINFO` flag.

*   **Reconstructing Bytes**: The handler uses `static` variables to preserve data across multiple signal calls. A `static unsigned char` is used to build the character bit by bit, and a `static int` counts the number of bits received.

    ```c
    // Server-side logic snippet
    void sigusr_handler(int sig, siginfo_t *info, void *ucontext)
    {
        static unsigned char  byte;
        static unsigned int   bit_num;

        // ... identify client PID from info->si_pid ...

        byte = byte << 1; // Shift the byte to the left to make room for the new bit
        if (sig == SIGUSR2)
            byte |= 1; // Set the last bit to 1 if the signal is SIGUSR2

        bit_num++;
        if (bit_num == 8)
        {
            // ... print the character and reset for the next byte ...
        }
    }
    ```

### The Client

The client is responsible for taking a message and translating it into a series of signals directed at the server.

*   **Sending Signals**: The client iterates through each character of the input string. For each character, it uses bitwise operations to check each of the 8 bits.
*   **Bitwise Logic**: The `>>` (right shift) and `&` (bitwise AND) operators are used to isolate each bit of a character.

    ```c
    // Client-side logic snippet
    void ft_send_byte(unsigned char byte, int pid)
    {
        int i = 8;
        while (i--)
        {
            if ((byte >> i) & 1) // Check if the i-th bit is 1
                kill(pid, SIGUSR2);
            else
                kill(pid, SIGUSR1);
            // ... wait for server acknowledgment (in bonus version) ...
        }
    }
    ```
*   **Transmission End**: After sending all characters in the string, the client sends one final character: the null terminator (`\0`). This signals to the server that the message is complete.

---

## ✨ Bonus Features: A Robust Communication Protocol

The bonus part of the project introduces a crucial feature: **server-to-client acknowledgment**.

### The Problem of Speed

Without any feedback mechanism, the client could send signals much faster than the server can process them. This can lead to signals being missed, resulting in corrupted data.

### The Solution: Acknowledgment

To solve this, the bonus server sends a signal back to the client (`SIGUSR2` in this implementation) after successfully receiving each bit.

*   **Client Waits**: The bonus client, after sending a bit, pauses and waits for this acknowledgment signal. It only sends the next bit after the acknowledgment is received.
*   **Synchronization**: This creates a synchronized, one-to-one exchange of signals, guaranteeing that no data is lost. The `volatile sig_atomic_t` type is used for the acknowledgment flag to ensure it behaves correctly within the signal handler context.

The bonus client also counts the number of acknowledgment signals received and, at the end of the transmission, prints a confirmation message, verifying that the entire message was received by the server.

```bash
$ ./client_bonus 12345 "Hello, World!"
Received 104 signals from server corresponding to 13 bytes.
```
This confirms that all 13 characters (including the null terminator) were successfully transmitted and acknowledged.

---

## 📋 How to Use

1.  **Compile the project:**
    ```bash
    make
    ```    This will create the `server`, `client`, `server_bonus`, and `client_bonus` executables.

2.  **Run the server:**
    ```bash
    ./server_bonus
    # The server will print its PID
    # PID: [SERVER_PID]
    ```

3.  **In a new terminal, run the client:**
    Replace `[SERVER_PID]` with the PID from the previous step and provide a message in quotes.
    ```bash
    ./client_bonus [SERVER_PID] "Your message here! This also supports 🐘 and other UTF-8 characters."
    ```

4.  **Observe the Output:**
    *   The server terminal will print your message character by character.
    *   The client terminal will confirm the number of bytes successfully sent and acknowledged.

---

## 🧠 Key Concepts Learned

*   **UNIX Signals**: Deep understanding of `SIGUSR1`, `SIGUSR2`, and the signal handling mechanism.
*   **Inter-Process Communication (IPC)**: A practical, low-level implementation of IPC on Unix-like systems.
*   **`sigaction`**: Using `sigaction` for reliable and informative signal handling, including retrieving the sender's PID.
*   **Bit Manipulation**: Extensive use of bitwise operators (`<<`, `>>`, `&`, `|`) to encode and decode data.
*   **Process Management**: Working with Process IDs (`PID`) and the `kill()` system call.
*   **Synchronization**: Implementing a client-server acknowledgment system to prevent data loss.
