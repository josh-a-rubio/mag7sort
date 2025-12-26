# Magnificent Seven Market Snapshot (C + Python)

A lightweight terminal application that fetches **live market data** for the **Magnificent Seven** stocks, sorts them by daily percentage gain, and presents a clean, colorized market snapshot, powered by a C core with an external data-fetch executable.

---

## Overview

This application demonstrates a **systems-style architexture** where:

- **C** handles performance-critical logic, sorting, parsing, and presentation
- **Python** handles external data acquistion (Yahoo Finance)
- The Python layer is **compiled into a standalone executable** (via PyInstaller)
- The user interacts with **one binary only**

Every exection fecthes **fresh market data**, ensuring results are never stale.

---
