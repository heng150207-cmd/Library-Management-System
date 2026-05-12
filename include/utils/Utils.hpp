#pragma once
#include <string>

// ─────────────────────────────────────────────────────────────
//  Utils — small helpers used across the whole project
// ─────────────────────────────────────────────────────────────

// Clear console (Windows: cls)
void clearScreen();

// Pause and wait for Enter, then clear
void pauseScreen();

// Return today's date as "YYYY-MM-DD"
std::string currentDate();

// Discard remaining characters in cin buffer
void clearInput();

// Return lowercase copy of s
std::string toLower(std::string s);
