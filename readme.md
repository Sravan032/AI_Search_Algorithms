# 🧠 AI Graph Search Algorithms — C++ Implementations

This project is a collection of **15 search algorithms** frequently used in Artificial Intelligence, robotics navigation, and pathfinding problems.  
The focus is on showing **how different search strategies behave** rather than just producing an answer.

---

## 📌 Overview
Search algorithms can be divided into three major categories:

| Category | Description | Examples Implemented |
|----------|-------------|----------------------|
| **Uninformed Search** | No heuristic guidance; explores blindly. | BFS, DFS, British Museum Search |
| **Heuristic Search** | Uses estimated cost (heuristic) to guide search. | Hill Climbing, Beam Search, A* |
| **Cost + History Based Search** | Considers path cost and remembers visited states. | Branch & Bound variations, Hill Climbing with Memory |

---

## 🔍 Implemented Algorithms

### 1️⃣ Uninformed (Blind) Search
- **British Museum Search** – Tries every path until a solution is found. Guarantees a solution but highly inefficient.  
- **Depth-First Search (DFS)** – Goes as deep as possible before backtracking. Low memory use, but may find non-optimal paths.  
- **Breadth-First Search (BFS)** – Explores level by level. Guarantees shortest path in unweighted graphs.

---

### 2️⃣ Heuristic-Driven Search
- **Hill Climbing** – Always moves towards the neighbor that seems best according to a heuristic.  
- **Beam Search** – Keeps only a limited number of promising nodes at each level to save memory.  
- **A* Search** – Combines cost so far (g) with estimated cost to goal (h) for optimal and efficient results.

---

### 3️⃣ Memory-Augmented Search
- **DFS with History** – DFS that remembers visited nodes to prevent cycles.  
- **BFS with History** – BFS that avoids revisiting states.  
- **Hill Climbing with History** – Same as Hill Climbing, but avoids revisiting old states.  
- **Beam Search with History** – Beam Search with cycle avoidance.

---

### 4️⃣ Cost-Based Optimal Search
- **Branch and Bound** – Discards any path that already costs more than the best found so far.  
- **Branch and Bound with Cost + Heuristic** – Adds heuristic estimates to prune even faster.  
- **Branch and Bound + Cost + History** – Tracks visited states to reduce redundant work.

---

### 5️⃣ Theoretical / Benchmark Search
- **Oracle Search** – Assumes perfect knowledge of the solution path. Useful for comparison with real algorithms.

---

## ⚙️ Running the Code

```bash
# Compile (example: A* Search)
g++ astar.cpp -o astar

# Run
./astar
