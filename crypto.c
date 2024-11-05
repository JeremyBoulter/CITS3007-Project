#include "crypto.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#define INT_MIN 0
#define INT_MAX 300

void caesar_encrypt(char range_low, char range_high, int key, const char * plain_text, char * cipher_text) {
    // Determine the size of the range
    int range_size = range_high - range_low + 1;

    // Iterate over each character in the plaintext
    for (int i = 0; plain_text[i] != '\0'; i++) {
        // If the character is within the range, encrypt it
        if (plain_text[i] >= range_low && plain_text[i] <= range_high) {
            // Shift the character by the key, wrapping around if necessary
            cipher_text[i] = ((plain_text[i] - range_low + key) % range_size) + range_low;
        } else {
            // If the character is outside the range, copy it over unchanged
            cipher_text[i] = plain_text[i];
        }
    }

    // Add the null terminator to the end of the ciphertext
    cipher_text[strlen(plain_text)] = '\0';
}

void caesar_decrypt(char range_low, char range_high, int key, const char * cipher_text, char * plain_text) {
    // If the key is equal to the size of the alphabet, return the original message
    if (key == range_high - range_low + 1) {
        strcpy(plain_text, cipher_text);
        return;
    }

    // Perform the decryption
    int i;
    for (i = 0; cipher_text[i] != '\0'; i++) {
        char c = cipher_text[i];
        if (c >= range_low && c <= range_high) {
            c = ((c - range_low - key) % (range_high - range_low + 1) + (range_high - range_low + 1)) % (range_high - range_low + 1) + range_low;
        }
        plain_text[i] = c;
    }
    plain_text[i] = '\0';  // Null-terminate the string
}

void vigenere_encrypt(char range_low, char range_high, const char *key, const char *plain_text, char *cipher_text) {
    int key_length = strlen(key);
    int key_index = 0;

    for (int i = 0; plain_text[i] != '\0'; i++) {
        char c = plain_text[i];

        if (c >= range_low && c <= range_high) {
            // Calculate the shift for the current character using the current key character
            int shift = key[key_index % key_length] - range_low;

            // Encrypt the character using the Vigenere cipher
            c = ((c - range_low + shift) % (range_high - range_low + 1)) + range_low;

            // Increment the key index
            key_index++;
        }

        // Write the (possibly encrypted) character to the cipher text
        cipher_text[i] = c;
    }

    // Null-terminate the cipher text
    cipher_text[strlen(plain_text)] = '\0';
}

void vigenere_decrypt(char range_low, char range_high, const char *key, const char *cipher_text, char *plain_text) {
    int key_length = strlen(key);
    int key_index = 0;

    for (int i = 0; cipher_text[i] != '\0'; i++) {
        char c = cipher_text[i];

        if (c >= range_low && c <= range_high) {
            // Calculate the shift for the current character using the current key character
            int shift = key[key_index % key_length] - range_low;

            // Decrypt the character using the Vigenere cipher
            c = ((c - range_low - shift + (range_high - range_low + 1)) % (range_high - range_low + 1)) + range_low;

            // Increment the key index
            key_index++;
        }

        // Write the (possibly decrypted) character to the plain text
        plain_text[i] = c;
    }

    // Null-terminate the plain text
    plain_text[strlen(cipher_text)] = '\0';
}



int cli(int argc, char ** argv) {
    // Check the number of arguments
    if (argc != 4) {
        fprintf(stderr, "Error: Invalid number of arguments\n");
        return 1;
    }

    // Parse the operation, key, and message from the arguments
    char *operation = argv[1];
    char *key = argv[2];
    char *message = argv[3];

    if (strlen(key) == 0) {
        fprintf(stderr, "Error: Key cannot be empty\n");
        return 1;
    }
    if (strlen(message) == 0) {
        fprintf(stderr, "Error: Message cannot be empty\n");
        return 1;
    }

    // Allocate memory for the result
    size_t message_length = strlen(message);
    char *result = malloc(message_length + 1);  // +1 for the null terminator
    if (result == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory\n");
        return 1;
    }

    // Perform the appropriate operation
    if (strcmp(operation, "caesar-encrypt") == 0) {
        // Validate the key
        char *endptr;
        long key_value = strtol(key, &endptr, 10);
        if (*endptr != '\0' || key_value < INT_MIN || key_value > INT_MAX) {
            fprintf(stderr, "Error: Invalid key for Caesar cipher, must be positive integer\n");
            free(result);  // Free the memory
            return 1;
        }
        // Perform the operation
        caesar_encrypt('A', 'Z', (int)key_value, message, result);
    } 
    
    else if (strcmp(operation, "caesar-decrypt") == 0) {
        // Validate the key
        char *endptr;
        long key_value = strtol(key, &endptr, 10);
        if (*endptr != '\0' || key_value < INT_MIN || key_value > INT_MAX) {
            fprintf(stderr, "Error: Invalid key for Caesar cipher, must be positive integer\n");
            free(result);  // Free the memory
            return 1;
        }
        // Perform the operation
        caesar_decrypt('A', 'Z', (int)key_value, message, result);
    } 
    
    else if (strcmp(operation, "vigenere-encrypt") == 0) {
        // Perform the operation
        vigenere_encrypt('A', 'Z', key, message, result);
    } 
    
    else if (strcmp(operation, "vigenere-decrypt") == 0) {
        // Perform the operation
        vigenere_decrypt('A', 'Z', key, message, result);
    } 
    
    else {
        fprintf(stderr, "Error: Invalid operation\n");
        free(result);  // Free the memory
        return 1;
    }

    // Print the result
    printf("%s\n", result);

    // Free the memory
    free(result);

    return 0;
}

int main() {
    // Test arguments
    char *argv1[] = {"program", "vigenere-encrypt", "KEY", "HELLO"};
    char *argv2[] = {"program", "vigenere-decrypt", "KEY", "RIJVS"};
    char *argv3[] = {"program", "vigenere-encrypt", "ABC", "HELLO"};
    char *argv4[] = {"program", "vigenere-decrypt", "ABC", "HFNLP"};

    // Test cases
    printf("Test 1: Vigenere encryption with key 'KEY'\n");
    cli(4, argv1);
    printf("\nTest 2: Vigenere decryption with key 'KEY'\n");
    cli(4, argv2);
    printf("\nTest 3: Vigenere encryption with key 'ABC'\n");
    cli(4, argv3);
    printf("\nTest 4: Vigenere decryption with key 'ABC'\n");
    cli(4, argv4);

    return 0;
}