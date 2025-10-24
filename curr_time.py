import datetime
def get_current_date():
    today = datetime.date.today()
    return today.strftime("%Y-%m-%d")
if __name__ == "__main__":
    print(get_current_date())