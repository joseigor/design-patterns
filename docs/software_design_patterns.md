# Software Design Patterns

## 🎓 Module 1: Foundations – SOLID Principles for Robust Software Design

### How to measure software design quality?

![alt text](image.png)

### Symptoms of Poor Designed Software

<!-- TODO: Add poll for people to write what are the symptoms of poor designed software they have seen in their career -->

<!-- Introduce the book of Uncle Bob -->

- **Rigidity**: Rigidity is the tendency of software to be difficult to change. When a system is rigid, even small changes can require significant effort and lead to unintended consequences. In a rigid system the situations below is quite common:
  - A change in one part of the system requires changes in many other parts.
  - The system is tightly coupled, making it hard to isolate changes.
  - Developers avoid making necessary changes due to the fear of breaking existing functionality, often leading to "patching" instead of proper refactoring, increasing technical debt.
  - Estimating the effort for changes becomes unreliable, often resulting in delays and frustration.
  
```c++
// TODO: Example of rigid code or link
// TODO: create an AI image to represent rigidity
```

- **Fragility**: Fragility is the tendency of software to break in unexpected ways when changes are made. A fragile system is one where a change in one part of the codebase can lead to failures in other, seemingly unrelated parts. This often results in:
  - Unintended side effects when modifying code.
  - Difficulty in understanding how changes will impact the overall system.
  - Increased time spent on debugging and fixing issues that arise from changes.
  
```c++
// TODO: Example of fragile code or link
// TODO: create an AI image to represent fragility
```

- **Immobility**: Immobility refers to the difficulty of reusing code in different contexts or projects. When code is immobile, it is tightly coupled to a specific application or framework, making it hard to extract and reuse. This leads to:
  - Duplication of code across projects.
  - Increased maintenance effort as similar code exists in multiple places.
  - Challenges in adapting existing code for new requirements or technologies.
  
```c++
// TODO: Example of immobile code or link
// TODO: create an AI image to represent immobility
```

- **Viscosity**: Viscosity is the tendency of software to resist change, making it difficult to preserve the design of the system. In a viscous system, developers may find it easier to write new code than to modify existing code, leading to:
  - Accumulation of technical debt as quick fixes are preferred over proper refactoring.
  - Inconsistent design patterns and practices across the codebase.
  - Increased complexity as new code is added without addressing existing issues.
  - Two forms of viscosity:
    - **Software Viscosity**:  When the design-preserving changes are difficult to implement, such as when existing code is poorly structured or lacks clear abstractions. (e.g, you have a class that does too many things and you need to change it, but you don't want to break the existing functionality, so you write new code instead of modifying the existing class)
    - **Environment Viscosity**: The difficulty of using the development environment effectively, such as cumbersome build processes or complex deployment procedures. (e.g, in a monorepo you know that to keep the the system design you will need to modify other projects/libraries, testing, CI etc. and you just don't want to do it, so you write new code instead of modifying existing code)
  
```c++
// TODO: Example of viscous code or link
// TODO: create an AI image to represent viscosity
```

- **Needless Complexity**: This refers to the presence of unnecessary features or overly complicated designs that do not add value to the system as add unusable functionality hiden under the quote "we will need this in the future". This can lead to:
  - The system now carries extra code that is not used, making it harder to understand and maintain.
  
```c++
// TODO: Example of needless complexity or link
// TODO: create an AI image to represent needless complexity
```

- **Needless Repetition**: This is the duplication of code or logic that could be abstracted or reused. It often results in:
  - Increased maintenance effort as changes need to be made in multiple places.
  - Higher risk of bugs due to inconsistencies in duplicated code.
  - Difficulty in understanding the system as similar logic appears in multiple locations.
  
```c++
// TODO: Example of needless repetition or link
// TODO: create an AI image to represent needless repetition
```

- **Opacity**: Opacity refers to the lack of clarity in the codebase, making it difficult for developers to understand how the system works. This can result in:
  - Increased time spent on onboarding new developers.
  - Difficulty in debugging and maintaining the system.
  - A general sense of confusion about how different parts of the system interact.
  
```c++
// TODO: Example of opaque code or link
// TODO: create an AI image to represent opacity
```

### How a "well-designed" Software becomes "poorly-designed"

- **Poor Initial Design**: If the initial design does not follow best practices, it can lead to a host of issues, including opacity and needless complexity, making it difficult to evolve the software effectively.
- **Requirements Change**: As business needs evolve, the software must adapt. If the design is not flexible, it can lead to rigidity and fragility (Requirements are volatile, we as software developers need to be prepared for changes).
- **New Features**: Adding new features can introduce complexity and potential for bugs if the design does not accommodate growth.
- **Technical Debt**: Quick fixes and patches can accumulate, leading to immobility and viscosity as the codebase becomes harder to maintain.
- **Lack of Refactoring**: Over time, code can become cluttered with unnecessary complexity and repetition if not regularly refactored.
- **Company Culture**: A culture that does not prioritize good design practices can lead to poor coding habits, resulting in a codebase that is difficult to work with.
- **Team Turnover**: New team members may not understand the original design intent, leading to further issues with opacity and needless complexity as they make changes without a clear understanding of the system.

### The simple `Copy` example evolution

#### 1st Iteration

You manager asks to implement a simple `Copy` program that copies characters from the `keyboard` to the `printer`.

Requirements:

- The program should read characters from the keyboard until `EOF` (End of File) is reached and print them to the printer.

````c++
#include <iostream>
class Keyboard {
public:
    char readCharacter() {
        return std::cin.get();
    }
};

class Printer {
public:
    void printCharacter(char c) {
        std::cout << c;
    }
};

class Copy {
private:
    Keyboard keyboard_;
    Printer printer_;
public:
    void run() {
        char c;
        while ((c = keyboard_.readCharacter()) != EOF) {
            printer_.printCharacter(c);
        }
    }
};

int main() {
    Copy copy;
    copy.run();
    return 0;
}
````

- Does this code  satisfy the requirements?
  - Yes, it reads characters from the keyboard and prints them to the printer until EOF is reached.
- Is it a good design? Yes, if we consider the initial requirements, it is simple and straightforward.
  - It has separate classes for `Keyboard`, `Printer`, and `Copy`, which makes it easy to understand and maintain.

#### 2nd Iteration

Few months later, the client asks for a new feature: the program should also be able to read characters from a file and print them to the printer.

Requirements:

- The program should read characters from the keyboard until EOF is reached and print them to the printer.
- **The program should read characters from a file until EOF is reached and print them to the printer. (New)**

In the interval between the 1st and 2nd iteration, the system:

- Has evolved in size and complexity.
- Has been used in production, so we need to be careful with changes.
- The keyboard and printer classes are in used by other parts of the system, not only the `Copy` class.
- There are some critical bugs in the field that need to be fixed.
- Team members not familiar with the original design are now working on the project.
- The team is under pressure to deliver the new feature quickly.
- Some team members not familiar with good design practices are making changes to the codebase.

Is the situation familiar? Bugs, complex systems, requirement changes, time pressure ...

What would you do?

- Most of the time, the quickest solution is chosen instead of a good design solution.

Chosen Solution:

- Add a new class `FileReader` that reads characters from a file and modify the `Copy` class to use it.
- Make the default behavior to read from the keyboard, so we don't break the existing functionality.
- Add a flag to the `Copy` class to indicate whether to read from the keyboard or from a file.

```c++
// 2nd Iteration
#include <iostream>
#include <fstream>
class Keyboard {
public:
    char readCharacter() {
        return std::cin.get();
    }
};

class FileReader {
public:
    FileReader(const std::string& filename) : file(filename) {}
    char readCharacter() {
        return file.get();
    }
private:
    std::ifstream file;
};

class Printer {
public:
    void printCharacter(char c) {
        std::cout << c;
    }
};

class Copy {
private:
    Keyboard keyboard_;
    Printer printer_;
    FileReader *fileReader_ = nullptr; // Pointer to FileReader, initialized to nullptr
    bool readFromKeyboard_ = true; // New flag to indicate source
public:
    void setReadFromKeyboard(bool readFromKeyboard) {
        // Set the flag to indicate whether to read from keyboard or file
        readFromKeyboard_ = readFromKeyboard;
    }

    void setFileName(const std::string& filename) {
        fileReader_ =  new FileReader(filename);
    }

    void run() {
        char c;
        if (readFromKeyboard_) {
            while ((c = keyboard_.readCharacter()) != EOF) {
                printer_.printCharacter(c);
            }
        } else {
            if (fileReader_ == nullptr) {
                std::cerr << "FileReader not set. Please set a file name." << std::endl;
                return;
            }
            while ((c = fileReader_->readCharacter()) != EOF) {
                printer_.printCharacter(c);
            }
        }
    }
    ~Copy() {
        delete fileReader_; // Clean up FileReader if it was created
    }
};

int main() {
    Copy copy;
    copy.setReadFromKeyboard(false); // Change to read from file
    copy.setFileName("input.txt"); // Set the file name
    copy.run();
    // Now read from terminal
    copy.setReadFromKeyboard(true); // Change back to read from keyboard
    copy.run();
    return 0;
}

```

Consequences of the solution:

- The `Copy` class now has two responsibilities: reading from the keyboard and reading from a file.
- The `Copy` class is now more complex and harder to understand.
- The `Copy` class is now tightly coupled to the `Keyboard` and `FileReader` classes.
- The `Copy` class API has changed. Callers now need to set the source before calling `run()`.
- The `Copy` class is now harder to test, as it has dependencies on both `Keyboard` and `FileReader`.


#### 3rd Iteration

Few months later, the client asks for a new feature: the program should also be able to write characters to a socket.

Requirements:

- The program should be able to read characters from the keyboard  until EOF.
- The program should be able to read characters from a file until EOF.
- The program should be able to write the read characters to the printer.
- The program should be able to write the read characters to the printer.

Team Environment:

- The same as the previous iteration or even worse.

Chosen Solution:

- Add a new class `SocketWriter` that writes characters to a socket.
- Modify the `Copy` class to use it.
- Make the default behavior to write to the printer, so we don't break the existing functionality.
- Add a flag to the `Copy` class to indicate whether to write to the printer or to a socket.

```c++
// 3rd Iteration
#include <iostream>
#include <fstream>
class Keyboard {
public:
    char readCharacter() {
        return std::cin.get();
    }
};

class FileReader {
public:
    FileReader(const std::string& filename) : file(filename) {}
    char readCharacter() {
        return file.get();
    }
private:
    std::ifstream file;
};

class Printer {
public:
    void printCharacter(char c) {
        std::cout << c;
    }
};
class SocketWriter {
public:
    void writeCharacter(char c) {
        // Simulate writing to a socket
        std::cout << "Writing to socket: " << c;
    }
};

class Copy {
private:
    Keyboard keyboard_;
    Printer printer_;
    FileReader *fileReader_ = nullptr; // Pointer to FileReader, initialized to nullptr
    SocketWriter socketWriter_; // New SocketWriter instance
    bool readFromKeyboard_ = true; // New flag to indicate source
    bool writeToPrinter_ = true;
public:
    void setReadFromKeyboard(bool readFromKeyboard) {
        // Set the flag to indicate whether to read from keyboard or file
        readFromKeyboard_ = readFromKeyboard;
    }

    void setFileName(const std::string& filename) {
        fileReader_ = new FileReader(filename);
    }

    void setWriteToPrinter(bool writeToPrinter) {
        writeToPrinter_ = writeToPrinter;
    }

    void run() {
        char c;
        if (readFromKeyboard_) {
            while ((c = keyboard_.readCharacter()) != EOF) {
                if (writeToPrinter_) {
                    printer_.printCharacter(c);
                } else {
                    socketWriter_.writeCharacter(c);
                }
            }
        } else {
            if (fileReader_ == nullptr) {
                std::cerr << "FileReader not set. Please set a file name." << std::endl;
                return;
            }
            while ((c = fileReader_->readCharacter()) != EOF) {
                if (writeToPrinter_) {
                    printer_.printCharacter(c);
                } else {
                    socketWriter_.writeCharacter(c);
                }
            }
        }
    }

    ~Copy() {
        delete fileReader_; // Clean up FileReader if it was created
    }
};

int main() {
    Copy copy;
    copy.setReadFromKeyboard(false); // Change to read from file
    copy.setFileName("input.txt"); // Set the file name
    copy.setWriteToPrinter(false); // Change to write to socket
    copy.run();
    // Now read from terminal and write to printer
    copy.setReadFromKeyboard(true); // Change back to read from keyboard
    copy.setWriteToPrinter(true); // Change back to write to printer
    copy.run();
    return 0;
}
```

Do you think this is close to some real-world scenario?

- Siting now in a comfortable chair watching this presentation, you may think this unlikely to happen, but in reality, this is a common scenario in software development.

#### Code Smells

- The `Copy` class has too many responsibilities, goes against the `Single Responsibility Principle (SRP)`. It is responsible for:
  - Reading from the keyboard.
  - Reading from a file.
  - Writing to the printer.
  - Writing to a socket.

- The `Copy` class is tightly coupled to the `Keyboard`, `FileReader`, `Printer`, and `SocketWriter` classes, making it hard to change or extend the functionality without modifying the `Copy` class, violating the `Open/Closed Principle (OCP)`. If we want to add a new feature, we need to modify the `Copy` class.

- The `Copy` needs to know about the `Printer` and `SocketWriter`, FileReader, Keyboard, which violates the `Dependency Inversion Principle` (DIP). It should depend on abstractions, not concrete implementations.

- **Rigidity**: The `Copy` class is rigid, as it is difficult to change the behavior of reading or writing without modifying the class itself.
- **Fragility**: If the `Copy` class is modified, for example adding new API methods, it can break existing functionality, leading to unintended side effects.
- **Immobility**: The `Copy` class is immobile, as it is tightly coupled to the `Keyboard`, `FileReader`, `Printer`, and `SocketWriter` classes, making it hard to reuse the code in other contexts. For example, if in another project there a need to just read from a keyboard and write to a socket, to use the `Copy` class, you would need to copy the entire class along with its dependencies, which is not ideal.
- **Opacity**: Code start to become opaque, Copy.Run() started to do too many things.

### How basic understanding of SOLID principles can help


#### 1st Iteration

Requirements:

- The program should read characters from the keyboard until EOF (End of File) is reached and print them to the printer.

The same code used in the 1st iteration without SOLID principles in mind is already a good design, it satisfies the requirements and avoid complexity.

### 2nd Iteration

Requirements:

- The program should read characters from the keyboard until EOF is reached and print them to the printer.
- The program should read characters from a file until EOF is reached and print them to the printer.

Questions that start to arise:

- What if we need to read a character from more sources?
- What if we need to write a character to more destinations?
- What if we need to change the way we read or write characters?
- What if we need to test the code?

Ad good software developers, we know that just patching the current implementation wouldn't be a good solution. In our tool set we know about the `Single Responsibility Principle (SRP)` and `Open/Closed Principle (OCP)`. We need to refactor the code to make it more maintainable and extensible.

#### Refactored Code

```c++
#include <iostream>
#include <fstream>
#include <string>

class IReader {
public:
    virtual char read() = 0; // Pure virtual function for reading characters
    virtual ~IReader() = default; // Virtual destructor for proper cleanup
}

class IWriter {
public:
    virtual void write(char c) = 0; // Pure virtual function for writing characters
    virtual ~Writer() = default; // Virtual destructor for proper cleanup
};

class KeyboardReader : public IReader {
public:
    char read() override {
        return std::cin.get(); // Read character from standard input
    }
};

class FileReader : public IReader {
    public:
        FileReader(const std::string& filename) : file(filename) {}
        char read() override {
            return file.get(); // Read character from file
        }
    private:
        std::ifstream file; // File stream for reading characters
};

class Copy{
    public:
        void run(IReader& reader, IWriter& writer) {
            char c;
            while ((c = reader.read()) != EOF) {
                writer.write(c);
            }
        }
}

int main() {
    Copy copy;
    KeyboardReader keyboardReader;
    Printer printer;

    // Read from keyboard and write to printer
    copy.run(keyboardReader, printer);

    // Read from file and write to printer
    FileReader fileReader("input.txt");
    copy.run(fileReader, printer);

    return 0;
}
```

#### Benefits of the Refactored Code

- **Single Responsibility Principle (SRP)**: Each class has a single responsibility. `KeyboardReader` is responsible for reading from the keyboard, `FileReader` is responsible for reading from a file, and `Printer` is responsible for printing characters.
- **Open/Closed Principle (OCP)**: The `Copy` class is open for extension but closed for modification. We can add new readers or writers without modifying the `Copy` class.
- **Dependency Inversion Principle (DIP)**: The `Copy` class depends on abstractions (`IReader` and `IWriter`) rather than concrete implementations. This allows us to easily swap out implementations without changing the `Copy` class.
- **Testability**: The code is more testable, as we can easily mock the `IReader` and `IWriter` interfaces for unit testing. This allows us to test the `Copy` class without relying on actual input/output operations, making tests faster and more reliable.

### 3rd Iteration

Requirements:

- The program should be able to read characters from the keyboard until EOF.
- The program should be able to read characters from a file until EOF.
- The program should be able to write the read characters to the printer.
- **The program should be able to write the read characters to a socket.**

#### Refactored Code

```c++
#include <iostream>
#include <fstream>
#include <string>

// ... (same as previous code)
class SocketWriter : public IWriter {
public:
    void write(char c) override {
        // Simulate writing to a socket
        std::cout << "Writing to socket: " << c;
    }
};

// ... (same as previous code)

int main() {
    Copy copy;
    KeyboardReader keyboardReader;
    Printer printer;

    // Read from keyboard and write to printer
    copy.run(keyboardReader, printer);

    // Read from file and write to printer
    FileReader fileReader("input.txt");
    copy.run(fileReader, printer);

    // Read from keyboard and write to socket
    SocketWriter socketWriter;
    copy.run(keyboardReader, socketWriter);

    return 0;
}
```

### Final Thoughts

- Use the SOLID principles to detect possible problems in the design.
- Solve the problems by applying the appropriate design pattern.
- Keep the design as appropriate and clean as possible.
- The source code is the most important expression of the design, it must remain clean.
