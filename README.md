# Word Ladder Puzzle Game

A command-line puzzle game implemented in modern C++. It challenges players to transform one word into another by changing a single letter at each step — with each intermediate step also being a valid word. The game uses efficient data structures and graph algorithms to provide intelligent hints and analyze user gameplay.

---

## 🔍 Example

Transform `SAME` to `COST` by changing one letter at a time:
- SAME  → **C**AME  → CA**S**E  → CAS**T**  → C**O**ST

Each step is a valid English word, and only one letter changes at a time.

---

## 🧠 Core Features

- **Graph-based word transitions** using adjacency lists
- **Template-based graph class** for flexibility
- **Optimized graph construction** via wildcard pattern matching
- **Shortest path search** using Breadth-First Search (BFS)
- **Two gameplay modes**:  
  - 🚀 **Auto-solve mode** for instant solutions  
  - 🎮 **Interactive play mode** with smart hinting system
- **Gameplay analytics and logging**
- **Cross-session data tracking** in `.csv` format
- **Custom user hints** with color-coded terminal output

---

## 🛠 Technologies & Libraries

- **C++17**
- STL containers:
  - `vector` – for graph adjacency lists
  - `map` – for wildcard indexing and word lookup
  - `set` – for uniqueness in analytics
  - `queue` – for BFS traversal
  - `stack` – for path reconstruction
  - `fstream` – for file I/O
  - `chrono` – for date & time tracking
  - ASCII color codes for terminal feedback

---

## 🧩 Game Logic

### Word Graph Construction

- Each word is a **node** in the graph.
- Two nodes are connected if the words differ by **exactly one letter**.
- **Wildcard patterns** are used to find neighboring words efficiently.
  
Example wildcard patterns:
- AME → **S**AME, **N**AME, **L**AME, **C**AME
- SME → S**A**ME, S**O**ME
- SA*E → SA**L**E, SA**G**E, SA**N**E, SA**S**E, SA**M**E


Words matching the same pattern are connected in the graph.

### Pathfinding Algorithm

- The shortest transformation is computed using **BFS**, ensuring minimal steps.
- Each valid transformation is tracked and reconstructed via a **parent map**.

---

## 🎮 Gameplay Modes

### 🔹 Auto Mode

- User provides start and target words.
- The game computes and displays the optimal transformation sequence.

### 🔸 Interactive Mode

- User enters their name.
- A random start/target pair is selected from a dictionary filtered by word length.
- The user plays the game step by step:
  - The app verifies valid transitions (1-letter difference, must be in dictionary).
  - User can request **hints** — suggested letters are **color-highlighted**.
  - All moves, hints, and timestamps are recorded.

---

## 📁 Output Format

Results are logged in a user-specific `.csv` file:
--- 
- Data is **appended** for each new session.
- Can be processed for statistics or visualizations.

---

## 📊 Analytics Module

Run personalized stats by typing the user's name:

- Displays:
  - Total games played
  - Unique words used (via `std::set`)
  - Average number of steps vs. optimal
  - Hints usage frequency
  - Most frequently used words (optional)

---

## 🎨 Hint System with Color

Hints are printed with color codes using ANSI escape sequences:


🔄 Future Enhancements
- Difficulty levels based on word length
- Time-based challenges
- Support for larger dictionaries and themes
