#pragma once
#include "main.h"
#include "Console.h"
#include "Telnet.h"
#include "T2Input.h"

void console_char_in(char ch);
void console_str_in(const char* str);
void console_str_with_length_in(const char* str, int length);

void console_char_out(char ch);
void console_str_out(const char* str);
void console_str_with_length_out(const char* str, int length);