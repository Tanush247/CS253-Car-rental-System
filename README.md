# CS253, Assignment-1, Car Rental System

Welcome to the Car Rental System. The program is written in C++ and links 4 databases:
1. **Car Database**: contains the following headers
   1. Car model
   2. Minimum Customer Record (if the customer record is less than the minimum customer record of the model then the car can not be rented)
   3. Price for renting the car when the car is in full 100% condition and no discount levied.
   4. Has the model been rented or not
   5. Name of the owner who has rented the model (If the model is not rented then it is stored as "0")
   6. ID of the owner who has rented the model (If the model is not rented then it is stored as "0")
   7. Type of owner ( "c" for customer, "e" for employee, and "n" for none)
   8. Due date
   9. Condition of the car ( stored between 0 and 100, with 0 when the car can not be used and 100 when the car is in perfect condition)
3. **Customer and Employee Database** (separate databases with the same format)
   1. Stores the name of the customer/employee
   2. Stores the ID of the customer/employee
   3. Password of the customer/employee
   4. Customer/Employee record (when the customer/employee is registered, the customer/employee record=15 is stored)
4. **Manager Database**
   1. Stores the name of the manager
   2. Stores the ID of the manager
   3. Stores the password of the manager
  
**Functionalities of Customer/Employee** (similar functions of customer and employee)
1. *Login/Register*-> requires name, ID, and password. For registering database is updated and we move to the login menu. While login if any of the parameters are wrong the output thrown is "Invalid Credentials". Different employees cannot have same ID. The code is able to handle same ID both for customer and employee 
2. Upon successful login we move to the login menu:
   1. *Seeing All Available Cars*: One can see all the available cars that can be rented by the user. A car with a higher minimum customer record or already rented is not shown. Price for employees is cut down by 15%. The price is also affected by the current condition of the car. I have taken the price and condition to be linearly related. That is for condition level to be 70 the price would be 0.7*original price.
   2. *Seeing Your Rented Cars*: Displays the list of all user's rented cars.
   3. *Renting A Car*: Prompts the user to enter the model of the car and today's date. Based on today's date the database stores a date 7 day ahead of the input date. The date is stored in form of a string in
      DDMMYYYY format. Using the <regex> library the code is able to output invalid date if the user enters any other format of date. Based on the availibility of the car and the customer record the car is either rented or not rented. Upon renting the car the car database is automically updated.
   4. *Check Current Dues*: The feature requires user to enter the current date and correspondingly outputs a fine in the cases when the customer date is later than the due date. Fine per extra day is taken to $5 and a 15% discount is given for the employees.
   5. *Clear dues*: The feature is used to clear all dues for the customer. The final output of the function shows the due that has been paid by the customer to complete the transaction. The Car that had been earlier rented by the customer/employee is freed and based on the condition and fine the customer record is updated.
   6. *Checking Customer/Employee Record*: The feature outputs the current employee/customer record.
   7. *Logout*: To Logout the user and to return back to the main home screen.


**Functionalities of Manager**
1. *Login/Register*: This feature is similar to login/register the manager in the car rental system based on name, ID and password. Manager of same name and password are possible. However ID's should be differnet.
2. Upon succesful login the following functions can be performed by the manager:
   1. *For seeing the current status of all the cars*: This outputs the current status of all cars-> Model, Price,Condition, If not rented outputs Car Not Rented else outputs the details of the user and the due date of the car.
   2. *For adding customers/employee/car*. Pushes the corresponding entity in it's database.
   3. *For removing customer/employee/car*: On removing customer/employee the code also checks if the deleted user had rented a car. In that case the car is freed and it's condition remains the same.
   4. *For updating customer/employee/car*.
      1. *Updating customer/employee*: asks for ID and updates the name, password and customer/employee record. On updating the name the corresponding changes are also reflected in the car database in case the user owned the car.
      2. *Updating car*: Takes in the car model and updates the minimum customer record, rent, condition of the car if the car model exists.
   5. *Logout*: To logout the manager and return back to the main home screen.



Classes:
1. **User class**:
   1. *attributes*: string name, string ID and string password
2. **Customer And Employee Class**: Both children class of User class
   1. *functions*: clear_dues, check_current_dues, rent_a_car, check_mine_rented, check_available.
4. **Manager class**: Children class of User class
   1. *functions*: check_current_status, remove_user, remove_car, user_removed_car, user_update_cars, user_update, car_update
5. **Car class**:
   1. *attributes*: string model, int condition, int minimum_requirement, int rent, isRented, renter
   2. *functions*: Check_if_car_exists, Push_New_Car
