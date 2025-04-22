import os
import json

def read_solutions(directory):
    solutions = []
    for filename in os.listdir(directory):
        if filename.endswith('.c'):
            file_path = os.path.join(directory, filename)
            with open(file_path, 'r', encoding='utf-8') as f:
                try:
                    code = f.read()
                    solutions.append({
                        'name': filename,
                        'code': code
                    })
                except Exception as e:
                    print(f"Error reading {filename}: {e}")
    
    # Sort solutions alphabetically by name
    solutions.sort(key=lambda x: x['name'])
    
    # Write to a JSON file
    with open('website/solutions.json', 'w', encoding='utf-8') as f:
        json.dump(solutions, f, indent=2)
    
    print(f"Generated JSON data with {len(solutions)} solutions")

if __name__ == "__main__":
    # Path to your hackerrank solutions folder
    solutions_path = "solutions"
    
    # Create website directory if it doesn't exist
    os.makedirs("website", exist_ok=True)
    
    read_solutions(solutions_path)
    print("Done! JSON file created at: website/solutions.json") 