/*
 * Course: COEN 2220 - Programming 2
 * Name: Keanel A. Martínez Aguilar
 * Lab: Lab 11 - Recursion and Merge Sort
 * Description: Practice - sort a temporary view without changing original tasks
 * Due date: November 2026
 */

#include <iostream>
#include <string>
using namespace std;

struct RepairTask
{
    string taskId;     // Preserve the identity of the original task.
    int daysUntilDue;  // Smaller values must appear first in the report.
    int minutesNeeded; // Break equal-deadline ties with smaller durations first.
};

bool comesBeforeOrEqual(const RepairTask *left, const RepairTask *right);
void mergeTaskView(RepairTask *view[], RepairTask *temporary[],
                   int first, int middle, int last);
void mergeSortView(RepairTask *view[], RepairTask *temporary[], int first, int last);
void displayOriginal(const RepairTask tasks[], int count);
void displayView(RepairTask *view[], int count);

int main()
{
    const int TASK_COUNT = 8;
    RepairTask tasks[TASK_COUNT] =
    {
        {"RT-101", 3, 30}, {"RT-102", 1, 20},
        {"RT-103", 2, 15}, {"RT-104", 1, 10},
        {"RT-105", 2, 15}, {"RT-106", 3, 10},
        {"RT-107", 1, 20}, {"RT-108", 2, 5}
    };
    RepairTask *view[TASK_COUNT];      // Borrow addresses of existing tasks.
    RepairTask *temporary[TASK_COUNT]; // Hold addresses while merging the view.
    for (int index = 0; index < TASK_COUNT; index++)
    {
        view[index] = &tasks[index]; // Preserve arrival order in the initial view.
    }

    cout << boolalpha;
    cout << "Original arrival order:" << endl;
    displayOriginal(tasks, TASK_COUNT);

    // ===== Resolve these TODOs now (Part C) =====
    // TODO (Part C): Activate the C test block after completing the comparator.
    
    cout << "Earlier deadline first: "
         << comesBeforeOrEqual(&tasks[1], &tasks[0]) << endl;
    cout << "Shorter duration within same deadline: "
         << comesBeforeOrEqual(&tasks[3], &tasks[1]) << endl;
    cout << "Exact tie keeps left: "
         << comesBeforeOrEqual(&tasks[2], &tasks[4]) << endl;
    cout << "Later deadline first: "
         << comesBeforeOrEqual(&tasks[0], &tasks[1]) << endl;
    

    // ===== Resolve these TODOs later (Part D) =====
    // TODO (Part D): Call mergeSortView for the complete logical range.
    mergeSortView(view, temporary, 0, TASK_COUNT - 1);
    // TODO (Part D): Display the sorted view with a descriptive heading.
    cout << "Sorted by deadline and duration:" << endl;
    displayView(view, TASK_COUNT);
    // TODO (Part D): Display tasks again to prove that arrival order did not change.
    cout << "Original arrival order (unchanged):" << endl;
    displayOriginal(tasks, TASK_COUNT);

    return 0;
}

bool comesBeforeOrEqual(const RepairTask *left, const RepairTask *right)
{
    // ===== Resolve this TODO now (Part C) =====
    // TODO (Part C): Implement the specified two-field order, including exact ties.
    if (left->daysUntilDue < right->daysUntilDue)
    {
        return true; // Left has an earlier deadline.
    }
    else if (left->daysUntilDue > right->daysUntilDue)
    {
        return false; // Right has an earlier deadline.
    }
    else
    {
        // Deadlines are equal, compare minutesNeeded.
        if (left->minutesNeeded < right->minutesNeeded)
        {
            return true; // Left has a shorter duration.
        }
        else if (left->minutesNeeded > right->minutesNeeded)
        {
            return false; // Right has a shorter duration.
        }
        else
        {
            return true; // Exact tie, preserve left's position.
        }
    }
    return false; // Temporary placeholder; replace this line in Part C.
}

// ===== Resolve these TODOs later (Part D) =====
void mergeSortView(RepairTask *view[], RepairTask *temporary[], int first, int last)
{
    // TODO (Part D): Implement recursive merge sort using inclusive indices.
    if (first < last)
    {
        int middle = first + (last - first) / 2; // Avoid potential overflow.
        mergeSortView(view, temporary, first, middle); // Sort left half.
        mergeSortView(view, temporary, middle + 1, last); // Sort right half.
        mergeTaskView(view, temporary, first, middle, last); // Merge sorted halves.
    }
}

void mergeTaskView(RepairTask *view[], RepairTask *temporary[],
                   int first, int middle, int last)
{
    // TODO (Part D): Merge two sorted segments using comesBeforeOrEqual.
    int leftIndex = first;      // Start of the left segment.
    int rightIndex = middle + 1; // Start of the right segment.
    // TODO (Part D): Preserve pending pointers and copy the merged segment back.
    int tempIndex = first; // Start of the temporary array.
    while (leftIndex <= middle && rightIndex <= last)
    {
        if (comesBeforeOrEqual(view[leftIndex], view[rightIndex]))
        {
            temporary[tempIndex++] = view[leftIndex++];
        }
        else
        {
            temporary[tempIndex++] = view[rightIndex++];
        }
    }
    // Copy any remaining elements from either segment.
    while (leftIndex <= middle)
    {
        temporary[tempIndex++] = view[leftIndex++];
    }
    while (rightIndex <= last)
    {
        temporary[tempIndex++] = view[rightIndex++];
    }
    // Copy the merged elements back to the original array.
    for (int i = first; i <= last; i++)
    {
        view[i] = temporary[i];
    }
}

void displayOriginal(const RepairTask tasks[], int count)
{
    for (int index = 0; index < count; index++)
    {
        cout << "Task: " << tasks[index].taskId
             << " | Days until due: " << tasks[index].daysUntilDue
             << " | Minutes: " << tasks[index].minutesNeeded << endl;
    }
}

void displayView(RepairTask *view[], int count)
{
    for (int index = 0; index < count; index++)
    {
        cout << "Task: " << view[index]->taskId
             << " | Days until due: " << view[index]->daysUntilDue
             << " | Minutes: " << view[index]->minutesNeeded << endl;
    }
}

/*
 * Analysis Answers
 *
 * C5 - Two-field decision
 * Explain the result for RT-103 compared with RT-108. Which field decides it?
 * Answer:
 * RT-103 has 2 days until due and 15 minutes needed, while RT-108 has 2 days until due and 5 minutes needed. 
 * Since both tasks tie on the primary field (daysUntilDue == 2), the secondary field (minutesNeeded) decides the outcome. 
 * RT-108 comes before RT-103 because 5 minutes is less than 15 minutes.
 *
 * D1 - Recursive ranges
 * Show first, last, middle, and the base-case evaluations along the first branch
 * starting at 0..7. Identify where execution resumes after the call for 0..0.
 * Answer:
 * - Root call: first = 0, last = 7, middle = 3 (left range: 0..3, right range: 4..7)
 * - Left child 1: first = 0, last = 3, middle = 1 (left range: 0..1, right range: 2..3)
 * - Left child 2: first = 0, last = 1, middle = 0 (left range: 0..0, right range: 1..1)
 * - Base case: first = 0, last = 0 (first >= last, returns immediately).
 * Execution then resumes back inside the active stack frame for range 0..1 to initiate the right recursive call (1..1).
 *
 * D2 - Stable ties
 * Identify both pairs of tasks that tie in the two sort fields. Explain how the
 * comparator and the merge preserve their arrival order.
 * Answer:
 * The pairs that tie completely across both fields are {RT-102, RT-107} (1 day, 20 minutes) and {RT-103, RT-105} (2 days, 15 minutes). 
 * When `comesBeforeOrEqual` compares two tasks with identical field values, it returns `true`. This causes the merge step to favor the left pointer, 
 * preserving their original relative arrival order in the view and ensuring stability.
 *
 * D3 - Time, space, and original data
 * Give the sorting time and auxiliary-space order of this pointer-array version.
 * Compare with the linked-list sort in Part B and explain why the original task
 * storage order is preserved here but the node order changes in Part B.
 * Answer:
 * - Time Complexity: O(n log n) due to the recursive splitting and linear merging across log n levels.
 * - Auxiliary Space Complexity: O(n) auxiliary storage space is required for the temporary pointer array (`temporary[]`), plus O(log n) call stack space. 
 * Compared to Part B (which rearranges pointers in-place within a linked list yielding O(log n) stack space and O(1) auxiliary data space), 
 * this version uses an external pointer array (`view`) so that reorganizing elements only modifies memory addresses without altering the original `tasks` array storage order.
 *
 * E1 - Pointer-array vs linked-list trade-offs
 * Compare the pointer-array merge sort on `view[]` with the linked-list merge sort
 * from Part B regarding memory allocation, cache locality, and pointer overhead.
 * Answer:
 * - Memory Allocation: The pointer-array approach uses a fixed external `view[]` and `temporary[]` array, avoiding any dynamic node allocation or deallocation during sorting. Part B operates on node pointers directly within a linked structure.
 * - Cache Locality: The original `tasks` array elements are stored in contiguous memory blocks, meaning the pointer array references enjoy better cache locality during traversal compared to scattered linked-list heap nodes.
 * - Pointer Overhead: Both approaches maintain pointers, but the pointer array adds an extra layer of indirection (`view[i]->...`), whereas the linked list relies entirely on node-to-node next pointers.
 *
 * E2 - Scalability and large reports
 * If `TASK_COUNT` grew to 100,000 items, how would the temporary pointer array and
 * recursive call stack impact performance and memory compared to in-place sorting?
 * Answer:
 * - Performance Impact: With 100,000 items, $n \log n$ scaling remains highly efficient (roughly $1.7 \times 10^6$ operations). However, allocating large temporary arrays (`temporary[100000]`) on the stack or heap can introduce memory overhead.
 * - Call Stack Impact: The recursion depth scales as $\log_2(100000) \approx 17$ levels, which consumes a negligible amount of stack space. 
 * - In-Place Comparison: True in-place sorting algorithms (like heap sort) avoid extra auxiliary arrays, making them more memory-efficient at massive scales, though merge sort on pointers remains faster for stable sorting and complex records.
 *
 * E3 - Practical application and design reflection
 * Why is sorting a separate view of pointers rather than the underlying data structures
 * preferred in real-world application architectures (such as UI tables or reports)?
 * Answer:
 * - Decoupling Data and Presentation: Sorting a separate view of pointers allows different parts of a program (or different user interface tabs/reports) to present the same underlying dataset sorted in multiple ways simultaneously (e.g., one sorted by deadline, another by duration, and another by arrival order) without duplicating memory-heavy data records.
 * - Efficiency with Large Objects: When records contain many large or complex fields copying or moving the actual struct/object instances during sorting is computationally expensive. Re-ordering lightweight memory pointers minimizes data movement, keeping re-sorting operations fast and responsive.
 */