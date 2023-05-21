[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/eaoC82lc)
[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-718a45dd9cf7e7f842a935f5ebbe5719a5e09af4491e668f4dbf3b35d5cca122.svg)](https://classroom.github.com/online_ide?assignment_repo_id=10814426&assignment_repo_type=AssignmentRepo)
# PES Assignment - 7 : Waveforms
Student Name : Kiran Jojare

# Introduction
Using the KL25Z's direct memory access (DMA) subsystem, I'll be diving into digital-to-analog conversion (DAC) and analog-to-digital conversion (ADC). As I'm working with analog signals, I've learned that even the smallest mathematical details matter for achieving a high level of accuracy. My goal for this project is to produce precise results that demonstrate my understanding of these concepts. Just like in previous assignments, I'll be creating a GitHub project complete with code, documentation, and README. I may also need access to the 1B24 lab to use the oscilloscope. Let's get started and see what I can learn! 

# Background
For this assignment, I'll be using the KL25Z to generate four pure tones as analog signals. I will play these tones using the DAC and sample the resulting analog output using the ADC. Fortunately, I can configure the KL25Z so that the DAC output becomes an ADC input. The parameters for this project are a sampling rate of 48 kHz for the output and 96 kHz for the input, and 12 bits per sample for the output and 16 bits per sample for the input. I need to cycle through three waveforms: a 440 Hz sine wave (an A4), a 587 Hz sine wave (a D5), and an 880 Hz sinusoidal triangle waveform. Each waveform should be played for one second, and when it reaches the end of the list, it should start again from the beginning. For the triangle wave, the min and max points should match the sine tones. I should use linear interpolation for the triangle wave for x values between 0 and pi/2 with a step size governed by the number of samples per period. Once a note is playing, I should use the ADC to read 1024 samples and perform some relatively simple analysis, including reporting the minimum, maximum, and mean values, and integrating the autocorrelation function provided on Canvas to recover the fundamental period represented in the sampled audio.  

In order to complete this project, I need to develop several modules, including an extra credit function to accurately compute sin(x) using only integer math, a tone_to_samples() function that computes the samples representing a pure tone or the triangle waveform of a specified frequency, an audio output module that allows me to pass the computed buffer of audio samples into the module and use the KL25Z's DAC, TPM0, and DMA hardware to repeatedly play out the buffer without further intervention from my main loop, an audio input module that captures a number of input samples at the capture sampling frequency specified above, and an audio analysis module that analyzes the captured buffer and reports the minimum, maximum, and mean values. Finally, I need to use an oscilloscope to verify that there is no tearing at the transition point in my playout buffer. It's going to be a lot of work, but I'm excited to dive in and see what I can learn!

# Result 
The waveforms are generated as per the requirement of the assignment
### Sine Wave with 440 Hz 
![scope_18](https://user-images.githubusercontent.com/111842372/233912198-7120327e-c39d-4396-8c76-cc96360ec4b2.png).   

Observed frequency was 440.53Hz which is under +/- 8 Hz threshold frequency.   

### Sine Wave with 587 Hz
![scope_19](https://user-images.githubusercontent.com/111842372/233912288-8b6030a4-f154-4106-ba5b-177f5379d2b8.png).   

Observed frequency was 584.11Hz which is under +/- 8 Hz threshold frequency.   

### Sinusoidal Triangle with 880 Hz
![scope_23](https://user-images.githubusercontent.com/111842372/234000124-e577794a-2ee7-409c-a0a4-814c53572301.png)

Observed frequency was 873.33Hz which is under +/- 8 Hz threshold frequency.   

### Transition between Two Frequencies 440 Hz and 587 Hz
The following diagram shows the smooth tranistion between the above two mentioned frequencies
![scope_22](https://user-images.githubusercontent.com/111842372/233972262-76dbe4cf-3174-4508-b935-e5c0a48b9f0a.png)


# Serial Results
Check the following UART result as follows.    
![Screenshot 2023-04-24 at 9 58 27 AM](https://user-images.githubusercontent.com/111842372/234051956-6debbcf0-898a-4bb5-aa23-d1e153b43b98.png)

# Extra Credit
Implemented the ADC calibration routine specified in the KL25Z Reference Manual, §28.4.6.


# Code Organisation

| File Name           | Brief Description                                  |
|---------------------|----------------------------------------------------|
| Assignment-7-waveforms.c | File containing functions for generating and manipulating waveforms. |
| audio_input.c       | File containing functions for audio input processing.    |
| audio_input.h       | Header file for audio_input.c.                       |
| audio_output.c      | File containing functions for audio output processing.   |
| audio_output.h      | Header file for audio_output.c.                      |
| autocorollate.c     | File containing functions for autocorrelation calculations. |
| autocorollate.h     | Header file for autocorollate.c.                     |
| fp_trig.c           | File containing functions for fast and precise trigonometric calculations. |
| fp_trig.h           | Header file for fp_trig.c.                           |
| hardware_init.c     | File containing functions for initializing hardware components. |
| hardware_init.h     | Header file for hardware_init.c.                     |
| systick.c           | File containing functions for handling the SysTick timer. |
| systick.h           | Header file for systick.c.                           |
| test_sin.c          | File containing functions for testing sine wave generation. |
| test_sin.h          | Header file for test_sin.c.                          |
| tpm.c               | File containing functions for handling the TPM timer. |
| tpm.h               | Header file for tpm.c.                               |


# Extent Bugs

| Date | Description |
|------|-------------|
| April 9th 2023  | No bugs have been found in the repository code. |

