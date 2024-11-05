# CITS3007-Project
Secure Coding Project for 2024

The Vigenere cipher is a polyalphabetic substitution cipher that uses a repeating keyword to determine shifts for each letter in the plaintext. Each letter of the plaintext is shifted by an amount defined by the corresponding letter in the repeating keyword. For example, using the keyword "KEY" and the plaintext "HELLOWORLD":

| Plaintext    | H | E | L | L | O | W | O | R | L | D |
|--------------|---|---|---|---|---|---|---|---|---|---|
| Keystream    | K | E | Y | K | E | Y | K | E | Y | K |
| Ciphertext   | R | I | J | V | S | U | Y | V | J | N |

Each letter of the plaintext is encrypted with a Caesar cipher shifted by the alphabetical position of the corresponding keystream letter (e.g., "K" is a shift of 10, "E" is a shift of 4).

## Project Requirements

- Implement encryption and decryption functions for both Caesar and Vigenere ciphers.
- Provide a command-line interface (CLI) for running these functions.
- Ensure code quality and adherence to C11 s
