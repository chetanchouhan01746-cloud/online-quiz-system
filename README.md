# Online Quiz & Examination System

A lightweight **Online Quiz and Examination System** built in C and deployed as an interactive web application. It supports custom quiz creation, customizable exam timers, automatic score calculation, and an end-of-exam answer key review.

## Live Website Demo
[Click here to open the Live Quiz Portal](https://github.io)

## Project Files
* `quiz.c` - Core C language implementation using 2D character arrays, loops, conditional checks, and `<time.h>` for real-time exam tracking.
* `index.html` - Interactive web interface featuring a live countdown clock, automatic submission on timeout, and color-coded answer review.

## Key Features
1. **Custom Quiz & Timer Setup:** The quiz creator adds custom questions, four options (A, B, C, D), correct answers, and sets a custom time limit in minutes.
2. **Candidate Registration:** Records the student's full name and roll number before starting the exam timer.
3. **Time-Tracked Examination:** Enforces the allotted duration and calculates the exact minutes and seconds taken.
4. **Automatic Evaluation & Answer Key:** Computes total marks, percentage, PASS/FAIL status (40% passing criteria), and displays the full answer key only after the exam ends.
