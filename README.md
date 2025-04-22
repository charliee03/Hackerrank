# HackerRank Solutions Website

This repository contains my solutions to various HackerRank problems in C, along with a website to display and share these solutions.

## Project Structure

- `/solutions` - Contains all the C solution files
- `/website` - Contains the website files to display solutions
  - HTML, CSS, and JavaScript files
  - Solutions are displayed with syntax highlighting
  - Copy button functionality
  - Search feature
- `generate_solutions.py` - Script to generate the solutions JSON file

## Local Development

1. Clone the repository:
   ```bash
   git clone [your-repo-url]
   cd hackerrank
   ```

2. Generate the solutions JSON:
   ```bash
   python generate_solutions.py
   ```

3. Run the local server:
   ```bash
   cd website
   python -m http.server 8000
   ```

4. Open http://localhost:8000 in your browser

## Deployment

This website is deployed on Vercel. Visit [your-vercel-url] to see it live.

## Features

- Clean, responsive UI
- Syntax highlighting for C code
- One-click code copy functionality
- Search functionality to find specific solutions
- Mobile-friendly design 