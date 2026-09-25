## File Overview

### 1. `NasaLaunchAnalysis.cpp`
* **Purpose:** Reads historical space launch records from `Space_Corrected.csv` to extract time-of-day information and compute the overall average launch time.
* **Key Implementation Details:**
  * **File I/O:** Utilizes `std::ifstream` to read launch data row-by-row while skipping the CSV header line.
  * **Pattern Matching & Substring Parsing:** Locates timestamps by detecting the `" UTC"` string marker, safely extracting two-digit hour and minute values using `.substr()`.
  * **Data Filtering:** Automatically filters out records with missing or incomplete time fields, storing exactly **4,198 valid records** into a `std::vector<TimeCode>`.
  * **Time Arithmetic:** Uses overloaded `+` and `/` operators on `TimeCode` instances to sum total launch hours/minutes and calculate the overall average time.
* **Results:**
  * **Valid Data Points Extracted:** 4,198
  * **Average Launch Time:** 12:07:56

---

### 2. `PaintDryTimer.cpp`
* **Purpose:** Tracks remaining paint drying times based on physical surface area calculations and system clock timestamps.
* **Key Implementation Details:**
  * **`DryingSnapShot` Struct:** Stores item metadata, a start time timestamp (`time_t`), and a heap-allocated pointer to a `TimeCode` object (`TimeCode* timeToDry`).
  * **Surface Area Geometry (`get_sphere_sa`):** Calculates sphere surface area using $4 \pi r^2$.
  * **Dynamic Allocation (`compute_time_code`):** Allocates new `TimeCode` objects on the heap using the `new` keyword and ensures memory cleanup using `delete`.
  * **Real-time Remaining Duration (`get_time_remaining`):** Measures total initial duration against elapsed system time (`time(0)`).
  * **Automated Unit Testing (`tests()`):** Verifies correct mathematical outputs, memory allocation, and time calculations using standard assertions (`cassert`).

---