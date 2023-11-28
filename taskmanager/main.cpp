//File: taskmanager.cpp
//Name: Chris Brown
//Date: 11/24/2023
//Course: CompSci 1
//Description: This is a program that you can create a task list in terminal, it will also store and retrieve these tasks
//Usage: Run the program, select and option, enter the task, due date and priority.

// https://discord.gg/Cm4V4f6Njz
// https://github.com/RangerNationXBL/Task-Manager
// https://twitter.com/fullyinvoled


#include <iostream> // Basic input and output
#include <fstream> // File stream for opening, writing, and closing files
#include <vector> // Data Structure
using namespace std; // I was going to do this a different way, but decided to use it last minute.

// The file will have several fields, maybe an addictional feature to eventually add it to a database.
// - Task Name
// - Task description
// - Task priority
// - Task Due Date
// -- Task Index Number.
// - Add times stamp to each entry

class Task {
public:
    // Constructor
    Task(const string& taskName, const string& description, int priority, const string& dueDate)
        : taskName(taskName), description(description), priority(priority), dueDate(dueDate), completed(false) {}


    void markAsComplete() {
        completed = true;
    }

    void displayTask() const {
        cout << "Task Name: " << taskName << "\n";
        cout << "Description: " << description << "\n";
        cout << "Priority: " << priority << "\n";
        cout << "Due Date: " << dueDate << "\n";
        cout << (completed ? "Status: Completed" : "Status: Incomplete") << "\n\n";
    }

    bool isCompleted() const{
        return completed;
    }

    const string& getDescription() const{
        return description;
    }

    const string& getDueDate() const{
        return dueDate;
    }

    const string& getTaskName() const{
        return taskName;
    }

private:
    string taskName, description, dueDate;
    int priority;
    bool completed;
};

void addTask(vector<Task>& taskList) {
    string taskName, description, dueDate;
    int priority;

    // Add time stamp for entry date and time.

    cout << "Enter the name of the task: ";
    cin.ignore();
    getline(cin, taskName);

    cout << "Please enter the details of the task: "; 
    cin.ignore();
    getline(cin, description);

    cout << "Enter a priority (1-5): ";
    cin >> priority;

    cout << "Enter a due date: ";
    cin >> dueDate;

    // An object is created to send to the vector
    Task newTask(taskName, description, priority, dueDate);
    taskList.push_back(newTask);

    cout << "Task added successfully!" << endl << endl;

}

void markAsComplete(vector<Task>& taskList) {
    if(taskList.empty()){
        cout << "No tasks to mark complete.\n\n";
        return;
    }

    cout << "Tasks:\n";
    for (size_t i = 0; i < taskList.size(); i++){
        cout << i+1 << ". " << taskList[i].getDescription() << " (" << (taskList[i].isCompleted() ? "Completed" : "incomplete") << ")\n";
    }

    int index;
    cout << "Enter the number of the task to mark as complete: ";
    cin >> index;

    if (index > 0 && static_cast<size_t>(index) <= taskList.size()){
        taskList[index - 1].markAsComplete();
        cout << "Task marked as complete!\n\n";
    }else{
        cout << "Invalid task number.\n\n";
    }
}

void displayTasks(const vector<Task>& taskList) {
    if (taskList.empty()){
        cout<< "No task to display. \n\n";
        return;
    }
    
    cout << "Tasks\n";
    for (const Task& task : taskList){
        task.displayTask();
    }
}

void loadTasksFromFile(vector<Task>& taskList) {
    ifstream file("tasks.txt");
    if (file.is_open()){
        string taskName, description, dueDate;
        int priority;
        bool completed;

        while (file >> taskName >> description >> priority >> dueDate >> completed){
            Task loadedTask(taskName, description, priority, dueDate);
            if (completed){
                loadedTask.markAsComplete();
            }
        taskList.push_back(loadedTask);
    }
    file.close();
    }else{
        cout << "No saved tasks found.\n";
    }
}

void saveTasksToFile(const vector<Task>& taskList) {
    
    // What I would like to add to this as a save,
    // - description
    // - due date
    // - priority
    // - completed

    ofstream file("tasks.txt");

    if (file.is_open()){
        for(const Task& task : taskList){
            file << task.getDescription() << " " << task.isCompleted() << " "<< task.isCompleted() << " " << task.getDueDate() <<  "\n";            
        }
    }else{
        cout << "This file is not open, and can not be saved! \n";
    }
}

int main() {
    vector<Task> taskList;

    loadTasksFromFile(taskList);

    int choice;
    do {
        cout << "Task Manager Menu:\n";
        cout << "1. Add Task\n";
        cout << "2. Mark Task as Complete\n";
        cout << "3. Display Tasks\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addTask(taskList);
                break;
            case 2:
                markAsComplete(taskList);
                break;
            case 3:
                displayTasks(taskList);
                break;
        }

    } while (choice != 0);

    saveTasksToFile(taskList);

    return 0;
}
