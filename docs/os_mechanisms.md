
# Technical Report: Operating System Mechanisms & Data Architecture

**Course Code:** BNF32303 (Operating Systems)  
**Project Component:** Smart Registration (RFID) & Google Form Finisher System  
**Group:** Team A  

---

## 1. Concurrency and Threading Architecture (Process Management)
Our registration system is designed to handle mass check-ins during the opening hours of the campus 4km Run event.

* **OS Mechanism:** The Python Flask backend environment operates as a multithreaded server. 
* **Handling Live Spikes:** When a massive crowd of runners scan their RFID tags sequentially at the entrance, the host Operating System allocates separate **POSIX/Worker Threads** from the system thread pool to handle each HTTP POST request.
* **CPU Scheduling:** These dynamic threads run concurrently under the OS kernel's pre-emptive CPU scheduling. This setup ensures that the server does not freeze or drop hardware connections when multiple requests hit the check-in route at the same moment.

---

## 2. Resource Locks and Process Synchronization (Protection)
Since all concurrent check-in threads are directed to read and update a single local database file (`runners.csv`), an OS **Race Condition** occurs if two threads attempt to modify the file stream simultaneously.

* **OS Mechanism (Mutex Lock):** To enforce strict Mutual Exclusion and protect data integrity, we instantiated a thread synchronization lock:
```python
  csv_lock = threading.Lock()
