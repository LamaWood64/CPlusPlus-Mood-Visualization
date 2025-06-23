# MoodFrog – C++ Text Sentiment Visualizer 🐸

## About the Project
This is a C++ coursework project that analyzes the sentiment of a user-inputted text and visualizes the detected emotion using a cartoon frog drawn with OpenGL/GLUT.

Depending on whether the text is positive, neutral, or negative, the frog's facial expression changes — including a sad tear if the mood is negative.

## Technologies Used
- **C++**
- **OpenGL / GLUT**
- **TSV dictionary** for mood classification (500+ words)

## Project Logic

### 1. Dictionary Loading  
The program loads a `.tsv` file containing words labeled with emotional categories: **positive**, **neutral**, or **negative**.  
Each entry is mapped for quick lookup.

---

### 2. Text Preprocessing  
User input is normalized by:  
- converting all characters to lowercase  
- removing all punctuation marks  
This ensures accurate matching with the dictionary.

---

### 3. Mood Analysis  
- Each word in the input text is checked against the dictionary.  
- Counts are maintained for words in each mood category.  
- The dominant mood is determined based on these counts.

---

### 4. Visual Output with OpenGL  
Based on the detected mood, the program renders a cartoon frog with different expressions:  
- 😊 **Happy**: smiling frog  
- 😐 **Neutral**: straight face  
- 😢 **Sad**: frown with a tear  

---

