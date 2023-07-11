// Nima Mahanloo
// Posfix Evaluate
// CISP 430
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
// A structure as a node of stack
struct node
{
    double content = 0;
    node* next = nullptr;
    node* prev = nullptr;
};
// A module to add a node on stack's top
void addNode (node* (&top))
{
    top->next = new node;
    top->next->prev = top;
    top = top->next;
}
// A module to push data number on top as necessary
void pushStack (node* (&top), int (&stackPointer),  double pushData)
{
    if (top->content != '\0')
    {
        addNode(top);
        stackPointer++;
    }
    top->content = pushData;
}
// A module to pop top of stack as necessary
void popStack (node* (&top), int (&stackPointer))
{
    if (stackPointer > 0)
    {
        node* temp = top;
        top = top->prev;
        top->next = nullptr;
        delete temp;
        temp = nullptr;
        stackPointer--;
    }
    else if (stackPointer == 0)
    {
        top->content = 0;
    }
}
// A module to convert postfix expression to infix and evaluate that
void postfixEvaluate (node* (&top), int (&stackPointer), char readData)
{
    double tempResult = 0;
    if ((readData == '^') || (readData == '*') || (readData == '/') || (readData == '+') || (readData == '-'))
    {
        if (readData == '^')
        {
            tempResult = pow(top->prev->content, top->content);
            popStack(top, stackPointer);
            top->content = tempResult;
        }
        else if (readData == '*')
        {
            tempResult = top->prev->content * top->content;
            popStack(top, stackPointer);
            top->content = tempResult;
        }
        else if (readData == '/')
        {
            tempResult = top->prev->content / top->content;
            popStack(top, stackPointer);
            top->content = tempResult;
        }
        else if (readData == '+')
        {
            tempResult = top->prev->content + top->content;
            popStack(top, stackPointer);
            top->content = tempResult;
        }
        else if (readData == '-')
        {
            tempResult = top->prev->content - top->content;
            popStack(top, stackPointer);
            top->content = tempResult;
        }
    }
    else
    {
        double number = int(readData)-48;
        pushStack(top, stackPointer, number);
    }
}
// A module to read postfix expression from the input file and send it to infix evaluator module
void readFile (node* (&top), int (&stackPointer))
{
    char data;
    ifstream read("input.txt");
    if (read.is_open())
    {
        cout << "Postfix is : ";
        while (read.eof() == false)
        {
            read >> data;
            if (data != '\0')
            {
                postfixEvaluate (top, stackPointer, data);
                cout << data;
            }
            data = '\0';
        }
        cout << endl;
    }
    else
    {
        cout << "Error: Can not open file!" << endl;
    }
    read.close();
}
// A module to display infix evaluated number
printResult (node* top, int stackPointer)
{
    while (stackPointer > 0)
    {
        top = top->prev;
        stackPointer--;
    }
    cout << "Evaluated number is : ";
    while (top != nullptr)
    {
        cout << top->content << " ";
        top = top->next;
    }
    cout << endl;
}
// A module to clear stack
void cleanStack(node* (&top), int (&stackPointer))
{
    while (stackPointer > 0)
    {
        popStack(top, stackPointer);
    }
}

int main()
{
    // An integer variable as stack pointer
    int stackPointer = -1;
    // A character pointer as dynamic array to hold infix evaluated number
    char* outData = (char*)malloc(sizeof(char));
    // Initial character pointer array to null character
    outData = '\0';
    // An object from structure 'node' as stack
    node* stackSim = new node;
    // An object from node as stack's top
    node* stackTop = stackSim;
    // increase stack pointer by one
    stackPointer++;
    // Call a module to read postfix expression from file and send it to infix evaluator
    readFile(stackTop, stackPointer);
    // Call a module to display infix evaluated number to user
    printResult(stackTop, stackPointer);
    // Clear stack
    cleanStack (stackTop, stackPointer);
    // Clear heap and memory
    delete stackTop;
    stackTop = nullptr;
    delete stackSim;
    stackSim = nullptr;
    return 0;
}
