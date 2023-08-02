#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_amex(char *card_number);
bool is_mastercard(char *card_number);
bool is_visa(char *card_number);
int get_checksum(char *card_number);
bool is_valid_card(char *card_number);

int main() {
    char card_number[20];
    printf("Enter your credit card number: ");
    scanf("%s", card_number);
    if (is_valid_card(card_number)) {
//        printf("Valid card\n");
    } else {
        printf("INVALID\n");
    }
    return 0;
}

bool is_amex(char *card_number) {
    int len = strlen(card_number);
    if (len != 15) {
        return false;
    }
    if (card_number[0] != '3') {
        return false;
    }
    if (card_number[1] != '4' && card_number[1] != '7') {
        return false;
    }
    return true;
}

bool is_mastercard(char *card_number) {
    int len = strlen(card_number);
    if (len != 16) {
        return false;
    }
    if (card_number[0] != '5') {
        return false;
    }
    char second_digit = card_number[1];
    if (second_digit < '1' || second_digit > '5') {
        return false;
    }
    return true;
}

bool is_visa(char *card_number) {
    int len = strlen(card_number);
    if (len != 13 && len != 16) {
        return false;
    }
    if (card_number[0] != '4') {
        return false;
    }
    return true;
}

int get_checksum(char *card_number) {
    int len = strlen(card_number);
    int sum = 0;
    bool multiply = false;
    for (int i = len - 1; i >= 0; i--) {
        int digit = card_number[i] - '0';
        if (multiply) {
            digit *= 2;
            if (digit > 9) {
                digit = digit / 10 + digit % 10;
            }
        }
        sum += digit;
        multiply = !multiply;
    }
    return sum;
}

bool is_valid_card(char *card_number) {
    int checksum = get_checksum(card_number);
    if (checksum % 10 != 0) {
        return false;
    }
    if (is_amex(card_number)) {
        printf("AMEX\n");
        return true;
    } else if (is_mastercard(card_number)) {
        printf("MASTERCARD\n");
        return true;
    } else if (is_visa(card_number)) {
        printf("VISA\n");
        return true;
    } else {
        return false;
    }
}