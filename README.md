# Magnificent Seven Market Snapshot (C + Python)

A lightweight terminal application that fetches **live market data** for the **Magnificent Seven** stocks, sorts them by daily percentage gain, and presents a clean, colorized market snapshot, powered by a C core with an external data-fetch executable.

---

## Demo / Screenshots

> <img width="409" height="355" alt="Screenshot 2025-12-26 at 7 08 51 PM" src="https://github.com/user-attachments/assets/2350449e-3055-46c5-95e9-2c5ee09897bf" />

> Example output includes:
> - Live prices
> - Percent gains and losses
> - Market caps
> - Winner and loser of the day
> - Colorized sorting  

## Overview

### Problem
Most market dashboards are bloated, web-based, and overkill for quick daily insight. They require browsers, logins, or paid APIs, and obscure the core signal with noise.

### Solution

This project provides a **fast, minimal, terminal-first market snapshot** for the Magnificent Seven stocks. It pulls live data, computes daily percent changes, sorts results fairly, and renders a readable, colorized summary using a performant C backend.

This application demonstrates a **systems-style architecture** where:

- **C** handles performance-critical logic, sorting, parsing, and presentation
- **Python** handles external data acquisition (Yahoo Finance)
- The Python layer is **compiled into a standalone executable** (via PyInstaller)
- The user interacts with **one binary only**

Every exection fetches **fresh market data**, ensuring results are never stale.

---

## Key Features

- Live market data fetched at runtime
- Sorts stocks by daily percentage gain (not price)
- Highlights winner and loser of the day
- Color-coded gains and losses (green/red)
- Aggregates total market capitalization
- No user input required
- Deterministic, repeatable output
- Clean separation between data fetching and core logic

---

## Tech Stack

- **C (C99)**

  Core application, sorting algorithm, parsing, rendering
- **Python (bundled executable)**

  External data fetcher built with PyInstaller
- **Yahoo Finance (yfinance)**

  Free, live market data source
- **POSIX / Unix environment**

  Standard system calls and execution model

---

## Architecture / System Design

```
┌────────────┐
│  mag7sort  │  (C executable)
└─────┬──────┘
      │ system()
      ▼
┌───────────────┐
│ fetch-mag7    │  (standalone executable)
│  - pulls data │
│  - writes CSV │
└─────┬─────────┘
      ▼
┌──────────────────┐
│ mag7_data.csv    │
│  ticker, price,  │
│  % gain, cap     │
└──────────────────┘
```

- The C program **always fetches fresh data on each run**
- The Python logic is compiled into a standalone executable
- Data is exchanged via a simple CSV contract
- Sorting and presentation are handled entirely in C

---

## Getting Started

### Prerequisites

- Unix-like OS (macOS or Linux)
- C compiler (clang or gcc)

> Python is **not required at runtime**

> The data fetcher is bundled as an executable.

### Clone & Prepare

```bash
git clone https://github.com/josh-a-rubio/mag7sort
cd mag7sort/src
chmod +x fetch-mag7
```

### Build

```bash
gcc -o mag7sort main.c
```

Make sure the following files are in the same directory:
- `mag7sort`
- `fetch-mag7` (executable)

### Run

```bash
./mag7sort
```

---

## Usage / Application Flow

1. User runs `./mag7sort`
2. Program disables stdin to prevent user input
3. External fetch executable runs silently
4. Live market data is written to `mag7_data.csv`
5. C program parses the CSV
6. Stocks are sorted by daily percent gain with merge sort
7. Market snapshot is rendered to the terminal

---

## Security Considerations & Limitations

- No user input is accepted or parsed
- stdin is explicitly disabled
- No network access occurs in the C binary
- External execution is tightly scoped
- CSV format is validated before use

Limitations:

- Depends on Yahoo Finance availability
- Market cap values may reflect intraday estimates
- Not intended for trading or financial advice

---

## Design Decisions

- **Percent gain over price**

  Percentage change provides a fair comparison across stocks.
- **C for core logic**

  Deterministic performance, memory control, and low overhead.
- **External fetch executable**

  Avoid forcing users to install Python packages or manage dependencies.
- **CSV over JSON**

  Simpler parsing, fewer failure modes, and better fit for C.

---

## Roadmap / Future Work

- Historical trend comparison
- Configurable ticker sets
- Optional JSON export
- C-native HTTP fetcher
- Windows compatibility
- Automated daily snapshots

---

## License

MIT License

---

## Author

Josh A. Rubio


