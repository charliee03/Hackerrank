// Global variables
let allSolutions = [];

// Load solutions from JSON file
async function loadSolutions() {
    try {
        const response = await fetch('solutions.json');
        
        if (!response.ok) {
            throw new Error(`HTTP error! Status: ${response.status}`);
        }
        
        allSolutions = await response.json();
        displaySolutions(allSolutions);
    } catch (err) {
        console.error('Error loading solutions:', err);
        document.getElementById('solutionsContainer').innerHTML = 
            `<div class="error">Error loading solutions. Please check the console for details.</div>`;
    }
}

// Display solutions in the container
function displaySolutions(solutions) {
    const container = document.getElementById('solutionsContainer');
    
    // Clear loading message
    container.innerHTML = '';
    
    if (solutions.length === 0) {
        container.innerHTML = '<div class="no-results">No matching solutions found</div>';
        return;
    }
    
    // Create and append solution cards
    solutions.forEach(solution => {
        container.appendChild(createSolutionCard(solution));
    });
    
    // Apply syntax highlighting
    document.querySelectorAll('pre code').forEach((block) => {
        hljs.highlightElement(block);
    });
}

// Create a card for a single solution
function createSolutionCard(solution) {
    const card = document.createElement('div');
    card.className = 'solution-card';

    const header = document.createElement('div');
    header.className = 'solution-header';

    const title = document.createElement('div');
    title.className = 'solution-title';
    title.textContent = solution.name;

    const copyBtn = document.createElement('button');
    copyBtn.className = 'copy-btn';
    copyBtn.textContent = 'Copy';

    const codeContainer = document.createElement('div');
    codeContainer.className = 'code-container';

    const pre = document.createElement('pre');
    const code = document.createElement('code');
    code.className = 'language-c';
    code.textContent = solution.code;
    pre.appendChild(code);

    codeContainer.appendChild(pre);
    header.appendChild(title);
    header.appendChild(copyBtn);
    card.appendChild(header);
    card.appendChild(codeContainer);

    // Toggle code visibility
    title.addEventListener('click', () => {
        codeContainer.classList.toggle('show');
    });

    // Copy code functionality
    copyBtn.addEventListener('click', async () => {
        try {
            await navigator.clipboard.writeText(solution.code);
            copyBtn.textContent = 'Copied!';
            setTimeout(() => {
                copyBtn.textContent = 'Copy';
            }, 2000);
        } catch (err) {
            console.error('Failed to copy:', err);
            alert('Failed to copy code. See console for details.');
        }
    });

    return card;
}

// Handle search functionality
function handleSearch() {
    const searchInput = document.getElementById('searchInput');
    
    searchInput.addEventListener('input', () => {
        const searchTerm = searchInput.value.toLowerCase();
        
        if (searchTerm === '') {
            displaySolutions(allSolutions);
            return;
        }
        
        // Filter solutions based on search term
        const filteredSolutions = allSolutions.filter(solution => 
            solution.name.toLowerCase().includes(searchTerm)
        );
        
        displaySolutions(filteredSolutions);
    });
}

// Initialize the application
document.addEventListener('DOMContentLoaded', () => {
    loadSolutions();
    handleSearch();
}); 