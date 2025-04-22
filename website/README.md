# HackerRank Solutions Website

This is a simple website to display and share your HackerRank C solutions. It features:

- A clean, responsive UI to display all your solutions
- Ability to click on a solution name to view its code
- Copy button to easily copy the code to clipboard
- Search functionality to find specific solutions

## How to Setup

1. Run the Python script to generate the JSON data file:
   ```
   python generate_solutions.py
   ```

2. Host the website using a local or production server:
   - For quick local testing, you can use Python's built-in server:
     ```
     cd hackerrank/website
     python -m http.server 8000
     ```
   - Then open `http://localhost:8000` in your browser

   - Alternatively, you can use any static file server or host it on GitHub Pages, Netlify, Vercel, etc.

## Project Structure

- `generate_solutions.py` - Scans your solutions folder and generates a JSON file
- `website/` - Contains the website files:
  - `index.html` - Main HTML structure
  - `styles.css` - Styling for the website
  - `script.js` - JavaScript for functionality
  - `solutions.json` - Generated JSON file with your solutions

## Customization

Feel free to customize the website to your liking:

- Edit the CSS in `styles.css` to change colors, fonts, layout, etc.
- Modify the header and footer in `index.html`
- Add more features to `script.js` such as filtering by difficulty, sorting options, etc.

## Adding New Solutions

When you add new C solutions to your solutions folder, simply run the Python script again to update the JSON file:

```
python generate_solutions.py
```

Then refresh your website to see the new solutions. 