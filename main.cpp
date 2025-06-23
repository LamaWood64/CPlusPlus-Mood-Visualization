#define GL_SILENCE_DEPRECATION
// to ignore the messages from Xcode sine the GLUT is no longer supported
#include <GLUT/glut.h>
// import it to make visualisation
#include <iostream>
// to enter the imput and see the output
#include <fstream>
// to read our file with emotions dictionary
#include <sstream>
// to wparse lines from file
#include <unordered_map>
// to be able to fast word-to-mood lookup
#include <string>
// to work with text
#include <cctype>
// to make letters lowercase



const std::string mood_file = "/Users/anastasia/Desktop/C++ Test/C++ Course/C++ Course/cplus/Mood detection/Mood detection/500 Words for mood detection.tsv";
// mood file contains 500 words with clusters for happy, sad, and neutral


std::string final_sentiment = "neutral";
// neutral is a default value and then will be changed

struct EmotionEntry {
    std::string emotion;
    int value;
};
// here we organizing data for each of emotions to work with it

std::unordered_map<std::string, EmotionEntry> load_mood(const std::string& filename) {
    // takes a filename and returns dict with key of str and meaning is emotion and number for it
    std::unordered_map<std::string, EmotionEntry> mood;
    std::ifstream file(filename);
    // oper the file in reading mode
    std::string line, word, emotion;
    // creates the empty dict, where we will write data from file
    int value;

    if (!file.is_open()) {
        std::cerr << "ERROR: cant open this file." << filename << std::endl;
        exit(1);
    }
    // checking if file is open and show an error if not
    
    while (getline(file, line)) {
        std::istringstream string(line);
        // read each line
        if (string >> word >> emotion >> value) {
        // create a stream from str to devide it into parts
            mood[word] = {emotion, value};
        // take the word, emotion and value
        // to put the element in the dictionary
        }
    }
    return mood;
}



std::string to_lower(const std::string& input) {
    std::string result;
    for (char c : input) result += std::tolower(c);
    return result;
}
// convert all words to lower case

std::string remove_punctuation(const std::string& input) {
    std::string result;
    for (char c : input) {
        if (std::isalpha(c) || std::isspace(c)) result += c;
    }
    return result;
}
// remove all of the punctuation marks


void analyze_sentiment(const std::string& text, const std::unordered_map<std::string, EmotionEntry>& lexicon) {
    int positive_score = 0;
    int negative_score = 0;

    std::istringstream ss(remove_punctuation(to_lower(text)));
    std::string word;

    while (ss >> word) {
        auto it = lexicon.find(word);
        if (it != lexicon.end()) {
            std::string emotion = it->second.emotion;
            int value = it->second.value;
            std::cout << "Found word in the dict: \"" << word << "\" with emotion of: " << emotion << std::endl;

            if (emotion == "positive") positive_score += value;
            else if (emotion == "negative") negative_score += value;
        }
    }

    std::cout << "Final calculation: positive = " << positive_score << ", negative = " << negative_score << std::endl;

    if (positive_score > negative_score) final_sentiment = "positive";
    else if (negative_score > positive_score) final_sentiment = "negative";
    else final_sentiment = "neutral";

    std::cout << "The final emotion of this text is " << final_sentiment << std::endl;
}

void draw_frog_face() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    // black background
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.3f, 0.8f, 0.3f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float rad = i * 3.14159f / 180.0f;
        glVertex2f(cos(rad) * 0.6f, sin(rad) * 0.6f);
    }
    glEnd();
    // face is a green circle

    glColor3f(1.0f, 1.0f, 1.0f);
    for (float offset : {-0.4f, 0.4f}) {
        glBegin(GL_POLYGON);
        for (int i = 0; i < 360; i++) {
            float rad = i * 3.14159f / 180.0f;
            glVertex2f(offset + cos(rad) * 0.18f, 0.4f + sin(rad) * 0.18f);
        }
        glEnd();
    // white eyes
    }

    glColor3f(0.0f, 0.0f, 0.0f);
    for (float offset : {-0.4f, 0.4f}) {
        glBegin(GL_POLYGON);
        for (int i = 0; i < 360; i++) {
            float rad = i * 3.14159f / 180.0f;
            glVertex2f(offset + cos(rad) * 0.08f, 0.4f + sin(rad) * 0.08f);
        }
        glEnd();
    // black puplis
    }

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float rad = i * 3.14159f / 180.0f;
        glVertex2f(-0.37f + cos(rad) * 0.03f, 0.44f + sin(rad) * 0.03f);
    }
    glEnd();
    // white glare in eye
    
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float rad = i * 3.14159f / 180.0f;
        glVertex2f(0.43f + cos(rad) * 0.03f, 0.44f + sin(rad) * 0.03f);
    }
    glEnd();
    // same white glare in second the eye


    glColor3f(0, 0, 0);
    if (final_sentiment == "positive") {
        glBegin(GL_LINE_STRIP);
        for (int i = 0; i <= 180; i++) {
            float rad = i * 3.14159f / 180.0f;
            glVertex2f(cos(rad) * 0.3f, -0.2f - sin(rad) * 0.1f);
        }
        glEnd();
        // positive mouth and emotions
        
    } else if (final_sentiment == "negative") {
        glBegin(GL_LINE_STRIP);
        for (int i = 0; i <= 180; i++) {
            float rad = i * 3.14159f / 180.0f;
            glVertex2f(cos(rad) * 0.3f, -0.2f + sin(rad) * 0.1f);
        }
        glEnd();
        // negative mouth and emotions

        glColor3f(0.5f, 0.7f, 1.0f);
        glBegin(GL_POLYGON);
        for (int i = 0; i < 360; i++) {
            float rad = i * 3.14159f / 180.0f;
            glVertex2f(-0.4f + cos(rad) * 0.03f, 0.3f + sin(rad) * 0.05f);
        }
        glEnd();
        // tear if emotion is sad

    } else {
        glBegin(GL_LINES);
        glVertex2f(-0.3f, -0.2f);
        glVertex2f(0.3f, -0.2f);
        glEnd();
    }
        // mouth for neutral emotion
    glFlush();
}

int main(int argc, char** argv) {
    auto lexicon = load_mood(mood_file);

    std::cout << "Please, enter your text (put empty string to exit):\n";
    std::string input, line;
    while (getline(std::cin, line)) {
        if (line.empty()) break;
        input += line + " ";
    }

    analyze_sentiment(input, lexicon);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Emotional frog");
    gluOrtho2D(-1, 1, -1, 1);
    glutDisplayFunc(draw_frog_face);
    glutMainLoop();

    return 0;
}
