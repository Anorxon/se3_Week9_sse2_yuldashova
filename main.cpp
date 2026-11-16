#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <random>
#include <iomanip>

using namespace std;

struct Job {
    string name;
    int priority;
};

class ArrayPriorityQueue {
private:
    vector<Job> jobs;

public:
    void enqueue(string name, int priority) {
        jobs.push_back({name, priority});
    }

    void dequeue() {
        if (jobs.empty()) {
            cout << "Queue is empty\n";
            return;
        }

        int best = 0;

        for (int i = 1; i < (int)jobs.size(); i++) {
            if (jobs[i].priority > jobs[best].priority) {
                best = i;
            }
        }

        cout << "Serving: " << jobs[best].name << "\n";
        jobs.erase(jobs.begin() + best);
    }

    Job peek() {
        if (jobs.empty()) {
            return {"", -1};
        }

        int best = 0;

        for (int i = 1; i < (int)jobs.size(); i++) {
            if (jobs[i].priority > jobs[best].priority) {
                best = i;
            }
        }

        return jobs[best];
    }

    bool empty() {
        return jobs.empty();
    }

    int size() {
        return (int)jobs.size();
    }
};

struct JobNode {
    string name;
    int priority;
    JobNode* next;
};

class LinkedPriorityQueue {
private:
    JobNode* head;

public:
    LinkedPriorityQueue() {
        head = nullptr;
    }

    void enqueue(string name, int priority) {
        JobNode* newNode = new JobNode{name, priority, nullptr};

        if (head == nullptr || priority > head->priority) {
            newNode->next = head;
            head = newNode;
            return;
        }

        JobNode* current = head;

        while (current->next != nullptr &&
               current->next->priority >= priority) {
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;
    }

    void dequeue() {
        if (head == nullptr) {
            cout << "Queue is empty\n";
            return;
        }

        JobNode* temp = head;

        cout << "Serving: " << temp->name << "\n";

        head = head->next;
        delete temp;
    }

    Job peek() {
        if (head == nullptr) {
            return {"", -1};
        }

        return {head->name, head->priority};
    }

    bool empty() {
        return head == nullptr;
    }

    ~LinkedPriorityQueue() {
        while (head != nullptr) {
            JobNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

bool isMaxHeap(vector<int> a) {
    int n = (int)a.size();

    for (int i = 0; i < n; i++) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && a[i] < a[left]) {
            return false;
        }

        if (right < n && a[i] < a[right]) {
            return false;
        }
    }

    return true;
}

class MaxHeap {
private:
    vector<int> a;

    void siftDown(int i, int n) {
        while (true) {
            int largest = i;
            int left = 2 * i + 1;
            int right = 2 * i + 2;

            if (left < n && a[left] > a[largest]) {
                largest = left;
            }

            if (right < n && a[right] > a[largest]) {
                largest = right;
            }

            if (largest == i) {
                break;
            }

            swap(a[i], a[largest]);
            i = largest;
        }
    }

public:
    void push(int value) {
        a.push_back(value);

        int i = (int)a.size() - 1;

        while (i > 0) {
            int parent = (i - 1) / 2;

            if (a[parent] >= a[i]) {
                break;
            }

            swap(a[parent], a[i]);
            i = parent;
        }
    }

    int peek() {
        if (a.empty()) {
            cout << "Heap is empty\n";
            return -1;
        }

        return a[0];
    }

    void popMax() {
        if (a.empty()) {
            cout << "Heap is empty\n";
            return;
        }

        a[0] = a.back();
        a.pop_back();

        if (!a.empty()) {
            siftDown(0, (int)a.size());
        }
    }

    void print() {
        for (int x : a) {
            cout << x << " ";
        }
        cout << "\n";
    }

    int size() {
        return (int)a.size();
    }
};

// Separate heap sort functions

void heapify(vector<int>& a, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && a[left] > a[largest]) {
        largest = left;
    }

    if (right < n && a[right] > a[largest]) {
        largest = right;
    }

    if (largest != i) {
        swap(a[i], a[largest]);
        heapify(a, n, largest);
    }
}

void heapSort(vector<int>& a) {
    int n = (int)a.size();

    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(a, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        swap(a[0], a[i]);
        heapify(a, i, 0);
    }
}

class MinHeap {
private:
    vector<int> a;

    void siftDown(int i) {
        int n = (int)a.size();

        while (true) {
            int smallest = i;
            int left = 2 * i + 1;
            int right = 2 * i + 2;

            if (left < n && a[left] < a[smallest]) {
                smallest = left;
            }

            if (right < n && a[right] < a[smallest]) {
                smallest = right;
            }

            if (smallest == i) {
                break;
            }

            swap(a[i], a[smallest]);
            i = smallest;
        }
    }

public:
    void push(int value) {
        a.push_back(value);

        int i = (int)a.size() - 1;

        while (i > 0) {
            int parent = (i - 1) / 2;

            if (a[parent] <= a[i]) {
                break;
            }

            swap(a[parent], a[i]);
            i = parent;
        }
    }

    int peekMin() {
        if (a.empty()) {
            cout << "Heap is empty\n";
            return -1;
        }

        return a[0];
    }

    void popMin() {
        if (a.empty()) {
            cout << "Heap is empty\n";
            return;
        }

        cout << "Removed: " << a[0] << "\n";

        a[0] = a.back();
        a.pop_back();

        if (!a.empty()) {
            siftDown(0);
        }
    }

    void print() {
        for (int x : a) {
            cout << x << " ";
        }
        cout << "\n";
    }
};

void siftDown(vector<int>& a, int n, int i) {
    while (true) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && a[left] > a[largest]) {
            largest = left;
        }

        if (right < n && a[right] > a[largest]) {
            largest = right;
        }

        if (largest == i) {
            break;
        }

        swap(a[i], a[largest]);
        i = largest;
    }
}

void buildMaxHeap(vector<int>& a) {
    int n = (int)a.size();

    for (int i = n / 2 - 1; i >= 0; i--) {
        siftDown(a, n, i);
    }
}

struct Task {
    string name;
    int priority;
    int arrival;
};

class TaskPriorityQueue {
private:
    vector<Task> a;

    bool higherPriority(Task x, Task y) {
        if (x.priority != y.priority) {
            return x.priority > y.priority;
        }

        return x.arrival < y.arrival;
    }

    void siftDown(int i) {
        int n = (int)a.size();

        while (true) {
            int best = i;
            int left = 2 * i + 1;
            int right = 2 * i + 2;

            if (left < n && higherPriority(a[left], a[best])) {
                best = left;
            }

            if (right < n && higherPriority(a[right], a[best])) {
                best = right;
            }

            if (best == i) {
                break;
            }

            swap(a[i], a[best]);
            i = best;
        }
    }

public:
    void addTask(string name, int priority, int arrival) {
        a.push_back({name, priority, arrival});

        int i = (int)a.size() - 1;

        while (i > 0) {
            int parent = (i - 1) / 2;

            if (!higherPriority(a[i], a[parent])) {
                break;
            }

            swap(a[i], a[parent]);
            i = parent;
        }
    }

    void serveNext() {
        if (a.empty()) {
            cout << "No tasks available\n";
            return;
        }

        cout << "Serving: " << a[0].name << "\n";

        a[0] = a.back();
        a.pop_back();

        if (!a.empty()) {
            siftDown(0);
        }
    }

    Task peek() {
        if (a.empty()) {
            return {"", -1, -1};
        }

        return a[0];
    }

    bool empty() {
        return a.empty();
    }
};

long long measureTime(int n, int method, const vector<int>& input) {
    using namespace chrono;

    auto start = steady_clock::now();

    if (method == 1) {
        MaxHeap heap;

        for (int x : input) {
            heap.push(x);
        }
    }
    else if (method == 2) {
        vector<int> a = input;
        buildMaxHeap(a);
    }
    else {
        vector<int> a = input;
        heapSort(a);
    }

    auto end = steady_clock::now();

    return duration_cast<microseconds>(end - start).count();
}

long long medianTime(int n, int method, const vector<int>& input) {
    vector<long long> times;

    for (int i = 0; i < 5; i++) {
        times.push_back(measureTime(n, method, input));
    }

    sort(times.begin(), times.end());

    return times[2];
}

void runBigOExperiment() {
    vector<int> sizes = {1000, 5000, 10000, 20000};

    mt19937 generator(42);
    uniform_int_distribution<int> distribution(1, 1000000);

    cout << left << setw(12) << "N"
         << setw(25) << "Heap Insert (us)"
         << setw(25) << "Build Heap (us)"
         << setw(20) << "Heap Sort (us)" << "\n";

    for (int n : sizes) {
        vector<int> input;

        for (int i = 0; i < n; i++) {
            input.push_back(distribution(generator));
        }

        long long insertTime = medianTime(n, 1, input);
        long long buildTime = medianTime(n, 2, input);
        long long sortTime = medianTime(n, 3, input);

        cout << left << setw(12) << n
             << setw(25) << insertTime
             << setw(25) << buildTime
             << setw(20) << sortTime << "\n";
    }
}

struct Patient {
    string name;
    int severity;
    int arrival;
};

class PatientQueue {
private:
    vector<Patient> a;

    bool higherPriority(Patient x, Patient y) {
        if (x.severity != y.severity) {
            return x.severity > y.severity;
        }

        return x.arrival < y.arrival;
    }

    void siftDown(int i) {
        int n = (int)a.size();

        while (true) {
            int best = i;
            int left = 2 * i + 1;
            int right = 2 * i + 2;

            if (left < n && higherPriority(a[left], a[best])) {
                best = left;
            }

            if (right < n && higherPriority(a[right], a[best])) {
                best = right;
            }

            if (best == i) {
                break;
            }

            swap(a[i], a[best]);
            i = best;
        }
    }

public:
    void addPatient(string name, int severity, int arrival) {
        a.push_back({name, severity, arrival});

        int i = (int)a.size() - 1;

        while (i > 0) {
            int parent = (i - 1) / 2;

            if (!higherPriority(a[i], a[parent])) {
                break;
            }

            swap(a[i], a[parent]);
            i = parent;
        }
    }

    void serveNext() {
        if (a.empty()) {
            cout << "No patients\n";
            return;
        }

        cout << "Patient: " << a[0].name
             << " | Severity: " << a[0].severity << "\n";

        a[0] = a.back();
        a.pop_back();

        if (!a.empty()) {
            siftDown(0);
        }
    }

    bool empty() {
        return a.empty();
    }
};

struct PrintJob {
    string document;
    int priority;
    int pages;
    int arrival;
};

class PrinterQueue {
private:
    vector<PrintJob> jobs;

public:
    void enqueue(string document, int priority, int pages, int arrival) {
        jobs.push_back({document, priority, pages, arrival});
    }

    void printNext() {
        if (jobs.empty()) {
            cout << "No print jobs\n";
            return;
        }

        int best = 0;

        for (int i = 1; i < (int)jobs.size(); i++) {
            if (jobs[i].priority > jobs[best].priority ||
                (jobs[i].priority == jobs[best].priority &&
                 jobs[i].arrival < jobs[best].arrival)) {
                best = i;
            }
        }

        cout << "Printing: " << jobs[best].document
             << " | Priority: " << jobs[best].priority
             << " | Pages: " << jobs[best].pages << "\n";

        jobs.erase(jobs.begin() + best);
    }

    bool empty() {
        return jobs.empty();
    }
};

struct TicketNode {
    int id;
    int urgency;
    int arrival;
    TicketNode* next;
};

class TicketQueue {
private:
    TicketNode* head;

public:
    TicketQueue() {
        head = nullptr;
    }

    void add(int id, int urgency, int arrival) {
        TicketNode* newNode =
            new TicketNode{id, urgency, arrival, nullptr};

        if (head == nullptr || urgency > head->urgency) {
            newNode->next = head;
            head = newNode;
            return;
        }

        TicketNode* current = head;

        while (current->next != nullptr &&
               current->next->urgency >= urgency) {
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;
    }

    void resolveNext() {
        if (head == nullptr) {
            cout << "No tickets\n";
            return;
        }

        TicketNode* temp = head;

        cout << "Resolved ticket: " << temp->id
             << " | Urgency: " << temp->urgency << "\n";

        head = head->next;
        delete temp;
    }

    void display() {
        TicketNode* current = head;

        while (current != nullptr) {
            cout << "[" << current->id
                 << ", " << current->urgency << "] -> ";

            current = current->next;
        }

        cout << "nullptr\n";
    }

    ~TicketQueue() {
        while (head != nullptr) {
            TicketNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

vector<int> topK(vector<int> scores, int k) {
    vector<int> heap;

    for (int score : scores) {
        if ((int)heap.size() < k) {
            heap.push_back(score);
            push_heap(heap.begin(), heap.end(), greater<int>());
        }
        else if (score > heap.front()) {
            pop_heap(heap.begin(), heap.end(), greater<int>());
            heap.back() = score;
            push_heap(heap.begin(), heap.end(), greater<int>());
        }
    }

    sort(heap.begin(), heap.end(), greater<int>());

    return heap;
}

struct DeliveryTask {
    int orderId;
    int urgency;
    int arrival;
};

class DeliveryQueue {
private:
    vector<DeliveryTask> a;

    bool higherPriority(DeliveryTask x, DeliveryTask y) {
        if (x.urgency != y.urgency) {
            return x.urgency > y.urgency;
        }

        return x.arrival < y.arrival;
    }

    void siftDown(int i) {
        int n = (int)a.size();

        while (true) {
            int best = i;
            int left = 2 * i + 1;
            int right = 2 * i + 2;

            if (left < n && higherPriority(a[left], a[best])) {
                best = left;
            }

            if (right < n && higherPriority(a[right], a[best])) {
                best = right;
            }

            if (best == i) {
                break;
            }

            swap(a[i], a[best]);
            i = best;
        }
    }

public:
    void addDelivery(int orderId, int urgency, int arrival) {
        a.push_back({orderId, urgency, arrival});

        int i = (int)a.size() - 1;

        while (i > 0) {
            int parent = (i - 1) / 2;

            if (!higherPriority(a[i], a[parent])) {
                break;
            }

            swap(a[i], a[parent]);
            i = parent;
        }
    }

    void serveNext() {
        if (a.empty()) {
            cout << "No deliveries\n";
            return;
        }

        cout << "Delivering order: " << a[0].orderId
             << " | Urgency: " << a[0].urgency << "\n";

        a[0] = a.back();
        a.pop_back();

        if (!a.empty()) {
            siftDown(0);
        }
    }

    bool empty() {
        return a.empty();
    }
};



int main() {

    ArrayPriorityQueue q1;

    q1.enqueue("A", 2);
    q1.enqueue("B", 8);
    q1.enqueue("C", 5);
    q1.enqueue("D", 8);

    while (!q1.empty()) {
        q1.dequeue();
    }



    LinkedPriorityQueue q2;

    q2.enqueue("A", 2);
    q2.enqueue("B", 8);
    q2.enqueue("C", 5);
    q2.enqueue("D", 8);

    while (!q2.empty()) {
        q2.dequeue();
    }



    vector<int> validHeap = {90, 70, 80, 20, 50, 60};
    vector<int> invalidHeap = {90, 70, 95, 20, 50, 60};

    cout << "Valid heap: "
         << (isMaxHeap(validHeap) ? "Yes" : "No") << "\n";

    cout << "Invalid heap: "
         << (isMaxHeap(invalidHeap) ? "Yes" : "No") << "\n";

    cout << "Tree representation:\n";

    for (int i = 0; i < (int)validHeap.size(); i++) {
        cout << "Index " << i
             << " | Value: " << validHeap[i];

        if (i > 0) {
            cout << " | Parent index: " << (i - 1) / 2;
        }

        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < (int)validHeap.size()) {
            cout << " | Left index: " << left;
        }

        if (right < (int)validHeap.size()) {
            cout << " | Right index: " << right;
        }

        cout << "\n";
    }



    MaxHeap maxHeap;

    vector<int> numbers = {90, 70, 80, 20, 50, 60, 85};

    for (int x : numbers) {
        maxHeap.push(x);
        cout << "After inserting " << x << ": ";
        maxHeap.print();
    }

    cout << "Maximum: " << maxHeap.peek() << "\n";
    cout << "Heap size: " << maxHeap.size() << "\n";



    cout << "Before removing maximum: ";
    maxHeap.print();

    maxHeap.popMax();

    cout << "After removing maximum: ";
    maxHeap.print();

    vector<int> sortNumbers = {4, 10, 3, 5, 1};

    heapSort(sortNumbers);

    cout << "Sorted array: ";

    for (int x : sortNumbers) {
        cout << x << " ";
    }

    cout << "\n";



    MinHeap minHeap;

    vector<int> minNumbers = {12, 7, 25, 3, 18, 1};

    for (int x : minNumbers) {
        minHeap.push(x);
    }

    cout << "Min heap: ";
    minHeap.print();

    minHeap.popMin();
    minHeap.popMin();

    cout << "After removing two minimum values: ";
    minHeap.print();




    vector<int> buildNumbers = {4, 10, 3, 5, 1};

    buildMaxHeap(buildNumbers);

    cout << "Bottom-up heap: ";

    for (int x : buildNumbers) {
        cout << x << " ";
    }

    cout << "\n";

    MaxHeap repeatedHeap;

    vector<int> repeatedNumbers = {4, 10, 3, 5, 1};

    for (int x : repeatedNumbers) {
        repeatedHeap.push(x);
    }

    cout << "Repeated insertion heap: ";
    repeatedHeap.print();

    cout << "Bottom-up heap valid: "
         << (isMaxHeap(buildNumbers) ? "Yes" : "No") << "\n";

    cout << "Repeated insertion heap valid: "
         << (isMaxHeap(repeatedNumbers) ? "Yes" : "No") << "\n";



    TaskPriorityQueue taskQueue;

    taskQueue.addTask("A", 3, 0);
    taskQueue.addTask("B", 8, 1);
    taskQueue.addTask("C", 8, 2);
    taskQueue.addTask("D", 5, 3);

    while (!taskQueue.empty()) {
        taskQueue.serveNext();
    }


    runBigOExperiment();

    cout << "\nExpected complexities:\n";
    cout << "Repeated heap insertion: O(n log n)\n";
    cout << "Bottom-up build: O(n)\n";
    cout << "Heap sort: O(n log n)\n";



    PatientQueue patients;

    patients.addPatient("Patient A", 2, 0);
    patients.addPatient("Patient B", 5, 1);
    patients.addPatient("Patient C", 9, 2);
    patients.addPatient("Patient D", 5, 3);
    patients.addPatient("Patient E", 7, 4);
    patients.addPatient("Patient F", 3, 5);

    while (!patients.empty()) {
        patients.serveNext();
    }



    PrinterQueue printer;

    printer.enqueue("Document A", 2, 5, 0);
    printer.enqueue("Document B", 8, 10, 1);
    printer.enqueue("Document C", 5, 3, 2);
    printer.enqueue("Document D", 8, 7, 3);

    while (!printer.empty()) {
        printer.printNext();
    }



    TicketQueue tickets;

    tickets.add(101, 3, 0);
    tickets.add(102, 8, 1);
    tickets.add(103, 5, 2);

    cout << "After head, middle and tail insertion:\n";
    tickets.display();

    tickets.add(104, 8, 3);

    cout << "After adding another ticket:\n";
    tickets.display();

    while (true) {
        tickets.resolveNext();
        tickets.display();
        break;
    }

    tickets.resolveNext();
    tickets.resolveNext();
    tickets.resolveNext();
    tickets.resolveNext();



    vector<int> scores = {10, 40, 25, 90, 70, 30, 60};

    int k = 3;

    vector<int> bestScores = topK(scores, k);

    cout << "Top " << k << " scores: ";

    for (int x : bestScores) {
        cout << x << " ";
    }

    cout << "\n";



    DeliveryQueue deliveries;

    deliveries.addDelivery(1001, 3, 0);
    deliveries.addDelivery(1002, 8, 1);
    deliveries.addDelivery(1003, 5, 2);
    deliveries.addDelivery(1004, 8, 3);

    cout << "Delivery order:\n";

    while (!deliveries.empty()) {
        deliveries.serveNext();
    }

    vector<int> durations = {35, 10, 50, 20, 15};

    heapSort(durations);

    cout << "Sorted delivery durations: ";

    for (int x : durations) {
        cout << x << " ";
    }

    cout << "\n";

    return 0;
}
