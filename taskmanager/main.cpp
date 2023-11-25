/*
Decided to not use "using namespace std;" after reading several reason why I should not use it.
In the future when I start doing larger it might create extra work for the compiler. It might
have been old info but it seems legit enough to used std::stuff.
*/
#include <iostream>
#include <fstream>
#include <vector>

// Task class definition
class Task {
public:
    // Constructor
    Task(const std::string& description, int priority, const std::string& dueDate)
        : description(description), priority(priority), dueDate(dueDate), completed(false) {}

    // Member functions
    void markAsComplete() {
        completed = true;
    }

    void displayTask() const {
        using std::cout;
        std::cout << "Description: " << description << "\n";
        std::cout << "Priority: " << priority << "\n";
        std::cout << "Due Date: " << dueDate << "\n";
        std::cout << (completed ? "Status: Completed" : "Status: Incomplete") << "\n\n";
    }

    bool isCompleted() const{
        return completed;
    }

    const std::string& getDescription() const{
        return description;
    }

private:
    std::string description;
    int priority;
    std::string dueDate;
    bool completed;
};

// Function to add a task to the task list
void addTask(std::vector<Task>& taskList) {
    // Get task details from the user
    // Create a Task object and add it to the task list
    // Save the updated task list to a file

    std::string description;
    int priority;
    std::string dueDate;

    std::cout << "Please enter the details of the task: ";
    std::cin.ignore();
    std::getline(std::cin, description);

    std::cout << "Enter a priority (1-5): ";
    std::cin >> priority;

    std::cout << "Enter a due date: ";
    std::cin >> dueDate;

    Task newTask(description, priority, dueDate);
    taskList.push_back(newTask);

    std::cout << "Task added successfully!" << std::endl << std::endl;

}

// Function to mark a task as complete
void markAsComplete(std::vector<Task>& taskList) {
    // Display the list of tasks with their indices
    // Get the index of the task to mark as complete from the user
    // Mark the selected task as complete
    // Save the updated task list to a file
    if(taskList.empty()){
        std::cout << "No tasks to mark complete.\n\n";
        return;
    }

    std::cout << "Tasks:\n";
    for (size_t i = 0; i < taskList.size(); i++){
        std::cout << i+1 << ". " << taskList[i].getDescription() << " (" << (taskList[i].isCompleted() ? "Completed" : "incomplete") << ")\n";
    }

    int index;
    std::cout << "Enter the number of the task to mark as complete: ";
    std::cin >> index;

    if (index > 0 && static_cast<size_t>(index) <= taskList.size()){
        taskList[index - 1].markAsComplete();
        std::cout << "Task marked as complete!\n\n";
    }else{
        std::cout << "Invalid task number.\n\n";
    }
}

// Function to display the list of tasks
void displayTasks(const std::vector<Task>& taskList) {
    // Display each task in the task list
    if (taskList.empty()){
        std::cout<< "No task to display. \n\n";
        return;
    }
    
    std::cout << "Tasks\n";
    for (const Task& task : taskList){
        task.displayTask();
    }
}

// Function to load tasks from a file
void loadTasksFromFile(std::vector<Task>& taskList) {
    // Read tasks from a file and populate the task list
    std::ifstream file("tasks.txt");
    if (file.is_open()){
        std::string description;
        int priority;
        std::string dueDate;
        bool completed;

        while (file >> description >> priority >> dueDate >> completed){
            Task loadedTask(description, priority, dueDate);
            if (completed){
                loadedTask.markAsComplete();
            }
        taskList.push_back(loadedTask);
    }
    file.close();
    }else{
        std::cout << "No saved tasks found.\n";
    }
}

// Function to save tasks to a file
void saveTasksToFile(const std::vector<Task>& taskList) {
    // Write tasks to a file
    std::ofstream file("tasks.txt");

    if (file.is_open()){
        for(const Task& task : taskList){
            file << task.getDescription() << " " << task.isCompleted() << " "<< task.isCompleted() << "\n";            
        }
    }
}

int main() {
    std::vector<Task> taskList;

    // Load tasks from a file
    loadTasksFromFile(taskList);

    // Main menu loop
    int choice;
    do {
        std::cout << "Task Manager Menu:\n";
        std::cout << "1. Add Task\n";
        std::cout << "2. Mark Task as Complete\n";
        std::cout << "3. Display Tasks\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

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
            // Additional cases for more menu options
        }

    } while (choice != 0);

    // Save tasks to a file before exiting
    saveTasksToFile(taskList);

    return 0;
}
