# Spotify-Youtube Linker

This is a **work-in-progress** project that collects your Spotify music preferences and links them to corresponding YouTube videos. The goal is to allow users to automatically open the YouTube versions of their favorite Spotify tracks directly from their computer.

⚠️ **Disclaimer:** This project is **not yet complete**. Core functionality is still under development, and features may be missing or unstable.

---

## Features (Planned)

- Retrieve and store Spotify listening data locally.
- Search for matching YouTube videos for each track.
- Launch videos in your default browser automatically.
- User-controlled configuration for token and API setup.

---

## Requirements

Before building and running the project, make sure you have the following installed:

### 1. Clone the repository

```bash
git clone https://github.com/bobrob-chris/UniversalMusic
```

### 2. Create the CMake build files

In the root directory, run:

```bash
cmake -S . -B build
```

This will generate the necessary Visual Studio project files inside the `build/` folder.

### 3. Compile the project

You can build the project using CMake:

```bash
cmake --build build
```

Or open the `build` folder in Visual Studio Code and use the built-in CMake tools to compile and run the project.

---

### Configuration

The project relies on a `config.h` file to store sensitive API keys and user-specific settings.

The required information to populate secrets can be found by signing up for the Spotify and Youtube API

**✍️ Setup `config.h`**  
Below is a template section that you must fill in manually:
````config.h
#ifndef _SECRETS_H_
#define _SECRETS_H_

#pragma once


#define HIDDEN_SPOTIFY_CLIENT_ID "<insert yours here>"

#define HIDDEN_SPOTIFY_CLIENT_SECRET "<insert yours here>"

#define HIDDEN_SPOTIFY_USER_ID "<insert yours here>"

#define HIDDEN_YOUTUBE_API_KEY "<insert yours here>"


#endif
````