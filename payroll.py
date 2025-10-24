def calc_payroll(employee, hours):
    base = 50000
    hours_rate = 200
    threshold = 40
    if hours < 0:
        return "Invalid hours"
    total = 0
    pay_base = "N"
    pay_hourly = "N"
    overtime = "N"
    absence_report = "N"
    if employee.upper() == "S":
        pay_base = "Y"
        total = base
        if hours == 0:
            absence_report = "Y"

    elif employee.upper() == "H":
        pay_hourly = "Y"
        if hours <= threshold:
            total = hours * hours_rate
        else:
            reguler = threshold * hours_rate
            overtime = hours - threshold
            overtime_pay = overtime * hours_rate * 1.5
            total = reguler + overtime_pay
            overtime = "Y"
    else:
        return "Invalid employee type"
    total = round(total, 2)
    return{
        "total_pay": total,
        "base_pay": pay_base,
        "hourly_pay": pay_hourly,
        "overtime": overtime,
        "absence_report": absence_report
    }