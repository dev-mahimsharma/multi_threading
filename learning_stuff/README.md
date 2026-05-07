# Windows Multithreading Function List

## Core Types

| Function / Type | Description |
|---|---|
| `HANDLE` | A Windows reference to an object like a thread, file, mutex, or event. |
| `DWORD` | A 32-bit unsigned integer type used often in Windows API. |
| `LPVOID` | A generic pointer type, basically `void *`, used for passing data to threads. |
| `WINAPI` | Calling convention required for Windows thread functions. |

---

## Thread Functions

| Function | Description |
|---|---|
| `CreateThread` | Creates a new thread and starts running a function in that thread. |
| `WaitForSingleObject` | Waits for one thread or object to finish/signaled before continuing. |
| `WaitForMultipleObjects` | Waits for multiple threads or objects to finish/signaled before continuing. |
| `CloseHandle` | Closes a Windows handle after you are done using it. |
| `Sleep` | Pauses the current thread for a given number of milliseconds. |
| `GetLastError` | Returns the last Windows error code after an API call fails. |

---

## Locking Functions

| Function / Type | Description |
|---|---|
| `CRITICAL_SECTION` | A lightweight lock used to protect shared data inside one process. |
| `InitializeCriticalSection` | Initializes a `CRITICAL_SECTION` before it is used. |
| `EnterCriticalSection` | Locks the critical section so only one thread can access protected data. |
| `LeaveCriticalSection` | Unlocks the critical section so other threads can access protected data. |
| `DeleteCriticalSection` | Cleans up a `CRITICAL_SECTION` when it is no longer needed. |

---

## Condition Variable Functions

| Function / Type | Description |
|---|---|
| `CONDITION_VARIABLE` | Lets threads sleep until another thread wakes them when a condition changes. |
| `InitializeConditionVariable` | Initializes a condition variable before it is used. |
| `SleepConditionVariableCS` | Puts a thread to sleep and temporarily unlocks a `CRITICAL_SECTION`; when woken, it locks again. |
| `WakeConditionVariable` | Wakes one sleeping thread waiting on a condition variable. |
| `WakeAllConditionVariable` | Wakes all sleeping threads waiting on a condition variable. |

---
