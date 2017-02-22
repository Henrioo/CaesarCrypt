# CaesarCrypt
A simple Caesar Cryptography Program which generates a key that is twice as long as the word/text itself.

When encrypting, the program reads the user input and generates a random 2 digit number from 00 to 94 for each entered character.
Then each character is beeing shifted by the respective generated number in the ASCII table.
The numbers are then beeing put together and act as the key which is needed to decrypt the text again.

When decrypting the program reads the encrypted text and the needed key from the user input and then goes through the key
2 digits at a time to shift the characters back again.
