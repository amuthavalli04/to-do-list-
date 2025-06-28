#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100
#define MAX_TITLE_LEN 100

struct Task {
    char title[MAX_TITLE_LEN];
    int completed; 
};

struct Task tasks[MAX_TASKS];
int taskCount = 0;

void loadTasks() {
    FILE *file = fopen("tasks.txt", "r");
    if (file == NULL) return;

    while (fscanf(file, " %[^\t]\t%d\n", tasks[taskCount].title, &tasks[taskCount].completed) != EOF) {
        taskCount++;
    }
    fclose(file);
}

void saveTasks() {
    FILE *file = fopen("tasks.txt", "w");
    for (int i = 0; i < taskCount; i++) {
        fprintf(file, "%s\t%d\n", tasks[i].title, tasks[i].completed);
    }
    fclose(file);
}

void addTask() {
    if (taskCount >= MAX_TASKS) {
        printf("Task list is full!\n");
        return;
    }

    printf("Enter task title: ");
    getchar(); 
    fgets(tasks[taskCount].title, MAX_TITLE_LEN, stdin);
    tasks[taskCount].title[strcspn(tasks[taskCount].title, "\n")] = '\0'; 
    tasks[taskCount].completed = 0;
    taskCount++;
    saveTasks();
    printf("Task added successfully!\n");
}

void viewTasks() {
    if (taskCount == 0) {
        printf("No tasks available.\n");
        return;
    }
    printf("\nTo-Do List:\n");
    for (int i = 0; i < taskCount; i++) {
        printf("%d. [%c] %s\n", i + 1, tasks[i].completed ? 'X' : ' ', tasks[i].title);
    }
}

void markCompleted() {
    int index;
    printf("Enter task number to mark as completed: ");
    scanf("%d", &index);
    if (index < 1 || index > taskCount) {
        printf("Invalid task number.\n");
        return;
    }
    tasks[index - 1].completed = 1;
    saveTasks();
    printf("Task marked as completed.\n");
}

void deleteTask() {
    int index;
    printf("Enter task number to delete: ");
    scanf("%d", &index);
    if (index < 1 || index > taskCount) {
        printf("Invalid task number.\n");
        return;
    }

    for (int i = index - 1; i < taskCount - 1; i++) {
        tasks[i] = tasks[i + 1];
    }
    taskCount--;
    saveTasks();
    printf("Task deleted.\n");
}

int main() {
    int choice;
    loadTasks();
    do {
        printf("\n=== TO-DO LIST MENU ===\n");
        printf("1. View Tasks\n");
        printf("2. Add Task\n");
        printf("3. Mark Task as Completed\n");
        printf("4. Delete Task\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: viewTasks(); break;
            case 2: addTask(); break;
            case 3: markCompleted(); break;
            case 4: deleteTask(); break;
            case 5: printf("Goodbye!\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 5);

    return 0;
}
