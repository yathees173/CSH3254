# 🚀 MPI Parallel Computing Practicals

This repository contains practical programs written in **C using MPI** for distributed-memory parallel computing.

The programs were created and tested using **Visual Studio Code**.

## 📚 Topics Covered

* MPI process creation
* Process rank and process size
* Sending and receiving data
* Point-to-point communication
* Broadcast
* Scatter and gather
* Reduction operations
* Parallel calculations

## 🛠️ Technologies Used

* C
* MPI
* Visual Studio Code

## ✅ Requirements

* C compiler
* Microsoft MPI
* Visual Studio Code

## ▶️ Compile the Program

Open the `.c` file in Visual Studio Code and press:

```text
Ctrl + Shift + B
```

This runs the configured build task and creates the executable file.

You can also compile using:

```bash
mpicc program.c -o program
```

## ▶️ Run the Program

Open the terminal and run:

```bash
mpiexec -n 6 program.exe
```

Here:

* `mpiexec` starts the MPI program
* `-n 6` runs the program using 6 processes
* `program.exe` is the compiled executable file

The number of processes may change depending on the program.

## 📁 File Type

MPI programs in this repository are saved using the `.c` extension because they are written in the C programming language.

Example:

```text
mpi_sum.c
```

## 🎯 Purpose

The purpose of this repository is to practise MPI communication and understand how multiple processes work together in a distributed-memory system.
