# Telecom System Propagation Simulator and Optimizer

This C++ project models, simulates, and optimizes electromagnetic signal propagation in a telecom environment containing **Software Defined Metasurfaces (SDMs)**, **transmitters**, **receivers**, and **obstacles**.

## 🧠 Overview

The system is represented as a graph where:
- **Nodes** are system elements: SDMs, users (receivers), and transmitters.
- **Edges** represent potential propagation paths.

The simulator includes modules for:
- Signal **propagation modeling**
- Signal **estimation at receivers**
- **Swarm intelligence optimization** (custom and genetic algorithms)
- **Pareto-based multi-objective optimization** for power and delay spread

---

## 🚀 Features

### 1. Graph-Based Environment Modeling
- Represents a 3D telecom space with obstacles
- Uses a graph abstraction to model SDMs, users, and transmission paths

### 2. Propagation Simulation
- Simulates ray propagation through the environment
- Uses a `RayHandler` class to estimate received signals

### 3. Optimization Algorithms
- Includes a **custom swarm-based algorithm** and a **genetic algorithm**
- Optimizes SDM modes to improve:
  - **Signal power**
  - **Delay spread** (Pareto front optimization)

### 4. Mode Distribution Management
- `ModeHandler` class manages mode distributions
- Uses the **Alias Method** for efficient sampling

### 5. Final System State Capture
- `SystemState` class encapsulates:
  - Chosen EM function (mode) for each SDM
  - Final signal characteristics at each receiver

---
