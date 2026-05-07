import csv
import mysql.connector
from mysql.connector import Error

# Database connection details
host = 'localhost'
user = 'root'
password = ''
database = 'creditCardFraud'

# Establishing a connection to the MySQL database
try:
    connection = mysql.connector.connect(
        host=host,
        user=user,
        password=password,
        database=database
    )

    if connection.is_connected():
        print("Connected to MySQL database")

        # Cursor to interact with the database
        cursor = connection.cursor()

        # Open the CSV file
        with open('/Users/abhisht/Downloads/fraudTest_updated.csv', 'r') as file:
            csv_reader = csv.reader(file)
            
            # Skip the header if your CSV has one (remove this line if no header)
            next(csv_reader)
            
            # SQL insert query
            insert_query = """
            INSERT INTO transactions (trans_date_trans_time, cc_num, merchant, category, amt, first_name, 
                                      last_name, street, city, state, zip, lat, `long`, job, trans_num, 
                                      merch_lat, merch_long, is_fraud)
            VALUES (%s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s)
            """
            
            # Read each row in the CSV and insert into the database
            for row in csv_reader:
                # Make sure to convert data types where necessary
                try:
                    trans_date_trans_time = row[0]
                    cc_num = int(row[1])
                    merchant = row[2]
                    category = row[3]
                    amt = float(row[4])
                    first_name = row[5]
                    last_name = row[6]
                    street = row[7]
                    city = row[8]
                    state = row[9]
                    zip_code = row[10]
                    lat = float(row[11])
                    long = float(row[12])
                    job = row[13]
                    trans_num = row[14]
                    merch_lat = float(row[15])
                    merch_long = float(row[16])
                    is_fraud = int(row[17])

                    # Insert the row into the database
                    cursor.execute(insert_query, (trans_date_trans_time, cc_num, merchant, category, amt, first_name, 
                                                  last_name, street, city, state, zip_code, lat, long, job, 
                                                  trans_num, merch_lat, merch_long, is_fraud))
                    # Commit the transaction
                    connection.commit()

                except Exception as e:
                    print(f"Error inserting row: {row} -> {e}")

        print("Data inserted successfully.")

except Error as e:
    print(f"Error connecting to MySQL: {e}")
finally:
    if connection.is_connected():
        cursor.close()
        connection.close()
        print("MySQL connection closed.")
