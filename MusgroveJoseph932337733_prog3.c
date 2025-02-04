import os
import random
import glob
import csv

def find_csv_files():
    """Find all CSV files starting with 'movies_' in the current directory."""
    return glob.glob("movies_*.csv")

def get_largest_csv():
    """Find the largest CSV file based on size."""
    csv_files = find_csv_files()
    return max(csv_files, key=os.path.getsize) if csv_files else None

def get_smallest_csv():
    """Find the smallest CSV file based on size."""
    csv_files = find_csv_files()
    return min(csv_files, key=os.path.getsize) if csv_files else None

def process_csv_file(file_name, onid):
    """Process the selected CSV file and organize movies by year."""
    if not os.path.exists(file_name):
        print("File not found.")
        return
    
    dir_name = f"{onid}.movies.{random.randint(10000, 99999)}"
    os.makedirs(dir_name, mode=0o750, exist_ok=True)
    
    movies_by_year = {}
    with open(file_name, 'r', encoding='utf-8') as file:
        reader = csv.reader(file)
        next(reader)  # Skip header
        for row in reader:
            if len(row) < 4:
                continue  # Skip malformed lines
            title, year, languages, rating = row
            year = year.strip()
            if year not in movies_by_year:
                movies_by_year[year] = []
            movies_by_year[year].append(title.strip())
    
    for year, titles in movies_by_year.items():
        year_file = os.path.join(dir_name, f"{year}.txt")
        with open(year_file, 'w', encoding='utf-8') as yf:
            for title in titles:
                yf.write(title + '\n')
        os.chmod(year_file, 0o640)
    
    print(f"Processed '{file_name}'. Files created in '{dir_name}'")

def main_menu():
    """Display the main menu and handle user choices."""
    onid = input("Enter your ONID: ")
    while True:
        print("\nMain Menu:")
        print("1. Select a file to process")
        print("2. Exit")
        choice = input("Enter your choice: ")
        
        if choice == '1':
            csv_files = find_csv_files()
            if not csv_files:
                print("No CSV files found.")
                continue
            
            print("\nSelect a file:")
            print("1. Largest file")
            print("2. Smallest file")
            print("3. Enter filename manually")
            file_choice = input("Choose an option: ")
            
            if file_choice == '1':
                file_name = get_largest_csv()
            elif file_choice == '2':
                file_name = get_smallest_csv()
            elif file_choice == '3':
                file_name = input("Enter the file name: ")
            else:
                print("Invalid choice.")
                continue
            
            if file_name and os.path.exists(file_name):
                process_csv_file(file_name, onid)
            else:
                print("File not found.")
        elif choice == '2':
            print("Exiting.")
            break
        else:
            print("Invalid choice. Try again.")

if __name__ == "__main__":
    main_menu()
