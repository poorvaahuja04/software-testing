#include <stdio.h>
struct PayrollResult {
    double total_pay;
    char pay_base;
    char pay_hourly;
    char overtime;
    char absence_report; 
};
struct PayrollResult calculate_payroll(char employee_type, double hours) {
    const double base_salary = 50000.0;
    const double hourly_rate = 200.0;
    const int threshold = 40;
    struct PayrollResult result;
    result.total_pay = 0.0;
    result.pay_base = 'N';
    result.pay_hourly = 'N';
    result.overtime = 'N';
    result.absence_report = 'N';
    if (hours < 0) {
        printf("Invalid hours\n");
        return result;
    }
    if (employee_type == 'S' || employee_type == 's') {
        result.pay_base = 'Y';
        result.total_pay = base_salary;
    } else if (employee_type == 'H' || employee_type == 'h') {
        result.pay_hourly = 'Y';
        if (hours < threshold) {
            result.total_pay = hours * hourly_rate;
            result.absence_report = 'Y';
        } 
        else if (hours == threshold) {
            result.total_pay = hours * hourly_rate;
        }
        else {
            double regular_pay = threshold * hourly_rate;
            double overtime_hours = hours - threshold;
            double overtime_pay = overtime_hours * hourly_rate * 1.5;
            result.total_pay = regular_pay + overtime_pay;
            result.overtime = 'Y';
        }
    } else {
        printf("Invalid employee type. Only 'S' or 'H'.\n");
    }
    return result;
}
int main() {
    char employee_type;
    double hours;
    printf("Enter employee type (S = Salaried, H = Hourly): ");
    scanf(" %c", &employee_type);

    printf("Enter number of hours worked: ");
    scanf("%lf", &hours);
    struct PayrollResult result = calculate_payroll(employee_type, hours);
    printf("\nPayroll Summary:\n");
    printf("Total Pay: Rs. %.2f\n", result.total_pay);
    printf("Pay Base Salary: %c\n", result.pay_base);
    printf("Pay Hourly: %c\n", result.pay_hourly);
    printf("Overtime: %c\n", result.overtime);
    printf("Absence Report: %c\n", result.absence_report);
    return 0;
}
