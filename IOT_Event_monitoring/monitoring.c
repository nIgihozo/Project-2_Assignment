#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define STUDENT_ID "54321"

// 1. Device Structure & Union
typedef struct {
    int id;
    char name[40];
    int type; // 1: Temperature, 2: Pressure, 3: Battery Voltage
    union {
        float temperature; // °C
        int pressure;      // PSI
        float voltage;     // Volts
    } readings;
    int status;           // 0: Normal, 1: Alert
    float prev_reading;   // Used for custom drift/change detection
} Device;

// Forward declarations of callbacks
void temperature_monitor(Device *device);
void pressure_monitor(Device *device);
void battery_monitor(Device *device);
void custom_drift_monitor(Device *device);

// Core processing dispatcher required by specs
void process_device(Device *device, void (*callback)(Device *)) {
    if (device && callback) {
        callback(device);
    }
}

// 4. Required Callbacks per Device Type
void temperature_monitor(Device *device) {
    // Normal range: 0.0°C to 50.0°C
    if (device->readings.temperature < 0.0f || device->readings.temperature > 50.0f) {
        device->status = 1;
    } else {
        device->status = 0;
    }
}

void pressure_monitor(Device *device) {
    // Normal range: 20 PSI to 100 PSI
    if (device->readings.pressure < 20 || device->readings.pressure > 100) {
        device->status = 1;
    } else {
        device->status = 0;
    }
}

void battery_monitor(Device *device) {
    // Normal range: >= 3.3V
    if (device->readings.voltage < 3.3f) {
        device->status = 1;
    } else {
        device->status = 0;
    }
}

// 6. Custom Callback Function: Sensor Drift & Rapid Change Detector
void custom_drift_monitor(Device *device) {
    float current_val = 0.0f;
    if (device->type == 1) current_val = device->readings.temperature;
    else if (device->type == 2) current_val = (float)device->readings.pressure;
    else if (device->type == 3) current_val = device->readings.voltage;

    float diff = fabsf(current_val - device->prev_reading);
    if (diff > 15.0f && device->prev_reading != 0.0f) {
        printf("  [CUSTOM ALERT] Rapid fluctuation detected on Device %d (%s)! Delta: %.2f\n", 
               device->id, device->name, diff);
        device->status = 1;
    }
    device->prev_reading = current_val;
}

// 2. Dynamic Device Management
void register_device(Device **devices, int *count, int *capacity) {
    int id, type;
    char name[40];

    printf("\nEnter Device ID (integer): ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input.\n");
        while(getchar() != '\n');
        return;
    }

    // Prevent duplicate device IDs
    for (int i = 0; i < *count; i++) {
        if ((*devices)[i].id == id) {
            printf("Error: Device ID %d already exists!\n", id);
            return;
        }
    }

    printf("Enter Device Name: ");
    scanf(" %39s", name);

    printf("Enter Device Type (1: Temperature, 2: Pressure, 3: Battery): ");
    if (scanf("%d", &type) != 1 || type < 1 || type > 3) {
        printf("Invalid device type. Must be 1, 2, or 3.\n");
        while(getchar() != '\n');
        return;
    }

    // Grow array dynamically if capacity reached
    if (*count >= *capacity) {
        *capacity *= 2;
        Device *temp = realloc(*devices, (*capacity) * sizeof(Device));
        if (!temp) {
            printf("Memory allocation failed during expansion!\n");
            return;
        }
        *devices = temp;
    }

    // Initialize new device
    (*devices)[*count].id = id;
    strcpy((*devices)[*count].name, name);
    (*devices)[*count].type = type;
    (*devices)[*count].status = 0;
    (*devices)[*count].prev_reading = 0.0f;

    // Set initial default union reading based on type
    if (type == 1) (*devices)[*count].readings.temperature = 25.0f;
    else if (type == 2) (*devices)[*count].readings.pressure = 50;
    else if (type == 3) (*devices)[*count].readings.voltage = 3.7f;

    (*count)++;
    printf("Device registered successfully!\n");
}

// 2. Display All Registered Devices
void display_devices(Device *devices, int count) {
    if (count == 0) {
        printf("\nNo devices currently registered.\n");
        return;
    }

    printf("\n--- REGISTERED DEVICES ---\n");
    printf("%-6s | %-15s | %-12s | %-12s | %-8s\n", "ID", "Name", "Type", "Value", "Status");
    printf("-------------------------------------------------------------------\n");
    
    Device *ptr = devices;
    for (int i = 0; i < count; i++, ptr++) {
        char type_str[20];
        char val_str[30];
        if (ptr->type == 1) {
            strcpy(type_str, "Temperature");
            sprintf(val_str, "%.1f °C", ptr->readings.temperature);
        } else if (ptr->type == 2) {
            strcpy(type_str, "Pressure");
            sprintf(val_str, "%d PSI", ptr->readings.pressure);
        } else {
            strcpy(type_str, "Battery");
            sprintf(val_str, "%.2f V", ptr->readings.voltage);
        }

        printf("%-6d | %-15s | %-12s | %-12s | %-8s\n",
               ptr->id, ptr->name, type_str, val_str, ptr->status ? "ALERT" : "Normal");
    }
}

// 2. Remove Device using ID 
void remove_device(Device **devices, int *count, int *capacity) {
    if (*count == 0) {
        printf("\nNo devices to remove.\n");
        return;
    }

    int id, found_idx = -1;
    printf("\nEnter Device ID to remove: ");
    if (scanf("%d", &id) != 1) {
        while(getchar() != '\n');
        return;
    }

    for (int i = 0; i < *count; i++) {
        if ((*devices)[i].id == id) {
            found_idx = i;
            break;
        }
    }

    if (found_idx == -1) {
        printf("Device ID %d not found.\n", id);
        return;
    }

    // Shift elements down
    for (int i = found_idx; i < *count - 1; i++) {
        (*devices)[i] = (*devices)[i + 1];
    }
    (*count)--;

    // Shrink array capacity if size drops significantly
    if (*count > 0 && *count < *capacity / 4 && *capacity > 2) {
        *capacity /= 2;
        Device *temp = realloc(*devices, (*capacity) * sizeof(Device));
        if (temp) *devices = temp;
    }

    printf("Device ID %d successfully removed.\n", id);
}

// 3. Simulated Device Readings & Callback Processing
void simulate_and_process(Device *devices, int count, int *total_processed, int *normal_count, int *abnormal_count, int *t_alerts, int *p_alerts, int *b_alerts) {
    if (count == 0) {
        printf("\nNo registered devices available for simulation. Please register devices first.\n");
        return;
    }

    printf("\n--- SIMULATING READINGS (10 Iterations) ---\n");
    // Array of standard callbacks indexed by type (Type 1, 2, 3 mapped to indices 0, 1, 2)
    void (*standard_callbacks[])(Device *) = { temperature_monitor, pressure_monitor, battery_monitor };

    for (int sim = 0; sim < 10; sim++) {
        int idx = rand() % count;
        Device *d = &devices[idx];

        // Generate random values within valid/abnormal ranges
        if (d->type == 1) {
            d->readings.temperature = -5.0f + (rand() % 650) / 10.0f; // -5.0 to 60.0 °C
        } else if (d->type == 2) {
            d->readings.pressure = 10 + (rand() % 110); // 10 to 120 PSI
        } else if (d->type == 3) {
            d->readings.voltage = 2.5f + (rand() % 18) / 10.0f; // 2.5 to 4.3 V
        }

        (*total_processed)++;

        // Process via standard callback function pointer dispatch
        process_device(d, standard_callbacks[d->type - 1]);
        
        // Also apply custom callback monitor
        custom_drift_monitor(d);

        if (d->status == 1) {
            (*abnormal_count)++;
            if (d->type == 1) (*t_alerts)++;
            else if (d->type == 2) (*p_alerts)++;
            else if (d->type == 3) (*b_alerts)++;
        } else {
            (*normal_count)++;
        }

        // Display individual reading result
        char val_str[30];
        if (d->type == 1) sprintf(val_str, "%.1f °C", d->readings.temperature);
        else if (d->type == 2) sprintf(val_str, "%d PSI", d->readings.pressure);
        else sprintf(val_str, "%.2f V", d->readings.voltage);

        printf("Reading #%d -> ID: %d | Name: %s | Value: %s | Result: %s\n",
               sim + 1, d->id, d->name, val_str, d->status ? "ALERT" : "Normal");
    }
}

// 6. Display Detected Alerts
void display_alerts(Device *devices, int count) {
    int alert_count = 0;
    printf("\n--- CURRENT ACTIVE ALERTS ---\n");
    Device *ptr = devices;
    for (int i = 0; i < count; i++, ptr++) {
        if (ptr->status == 1) {
            alert_count++;
            char type_str[20];
            char val_str[30];
            if (ptr->type == 1) {
                strcpy(type_str, "Temperature");
                sprintf(val_str, "%.1f °C", ptr->readings.temperature);
            } else if (ptr->type == 2) {
                strcpy(type_str, "Pressure");
                sprintf(val_str, "%d PSI", ptr->readings.pressure);
            } else {
                strcpy(type_str, "Battery");
                sprintf(val_str, "%.2f V", ptr->readings.voltage);
            }
            printf("Alert #%d: ID=%d, Name=%s, Type=%s, Value=%s\n",
                   alert_count, ptr->id, ptr->name, type_str, val_str);
        }
    }
    if (alert_count == 0) {
        printf("No active alerts detected.\n");
    }
}

// 8. Monitoring Summary Report
void generate_summary(int count, int total_processed, int normal_count, int abnormal_count, int t_alerts, int p_alerts, int b_alerts) {
    printf("\n=========================================\n");
    printf("Student ID: %s\n", STUDENT_ID);
    printf("Project: Dynamic IoT Event Monitoring Engine\n");
    printf("=========================================\n");
    printf("Total Registered Devices      : %d\n", count);
    printf("Total Readings Processed      : %d\n", total_processed);
    printf("Normal Readings Count         : %d\n", normal_count);
    printf("Abnormal Readings (Alerts)    : %d\n", abnormal_count);
    printf("Alerts Breakdown:\n");
    printf("  - Temperature Sensor Alerts : %d\n", t_alerts);
    printf("  - Pressure Sensor Alerts    : %d\n", p_alerts);
    printf("  - Battery Monitor Alerts    : %d\n", b_alerts);
    printf("Custom Callback Status        : Active (Sensor Drift & Rapid Change Detector)\n");
    printf("=========================================\n");
}

int main(void) {
    srand((unsigned int)time(NULL));

    int capacity = 2;
    int count = 0;
    Device *devices = malloc(capacity * sizeof(Device));
    if (!devices) {
        printf("Initial memory allocation failed.\n");
        return 1;
    }

    // Summary metrics tracking
    int total_processed = 0;
    int normal_count = 0;
    int abnormal_count = 0;
    int t_alerts = 0;
    int p_alerts = 0;
    int b_alerts = 0;

    int choice;
    do {
        printf("\n================ IOT MONITOR MENU ================\n");
        printf("1. Register a new device\n");
        printf("2. Display all registered devices\n");
        printf("3. Remove a device using its ID\n");
        printf("4. Generate simulated readings (10 readings)\n");
        printf("5. Display detected alerts\n");
        printf("6. Generate monitoring summary\n");
        printf("7. Exit program\n");
        printf("Enter your choice: ");
        

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number that are above.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                register_device(&devices, &count, &capacity);
                break;
            case 2:
                display_devices(devices, count);
                break;
            case 3:
                remove_device(&devices, &count, &capacity);
                break;
            case 4:
                simulate_and_process(devices, count, &total_processed, &normal_count, &abnormal_count, &t_alerts, &p_alerts, &b_alerts);
                break;
            case 5:
                display_alerts(devices, count);
                break;
            case 6:
                generate_summary(count, total_processed, normal_count, abnormal_count, t_alerts, p_alerts, b_alerts);
                break;
            case 7:
                printf("Exiting program and freeing dynamically allocated memory...\n");
                break;
            default:
                printf("Choice out of range. Please choose the options that are on the menu above.\n");
        }
    } while (choice != 7);

    // Free all allocated memory before termination
    free(devices);
    return 0;
}