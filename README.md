# CS253, Assignment-1, Car Rental System

Welcome to the Car Rental System. The program is written in C++ and links 4 databases:
1. Car Database: contains the following headers
   -Car model
   -Minimum Customer Record (if the customer record is less than the minimum customer record of the model then the car can not be rented)
   -Price for renting the car when the car is in full 100% condition and no discount levied.
   -Has the model been rented or not
   -Name of the owner who has rented the model (If the model is not rented then it is stored as "0")
   -ID of the owner who has rented the model (If the model is not rented then it is stored as "0")
   -Type of owner ( "c" for customer, "e" for employee, and "n" for none)
   -Due date
   -Condition of the car ( stored between 0 and 100, with 0 when the car can not be used and 100 when the car is in perfect condition)
2. Customer and Employee Database (separate databases with the same format)
   -Stores the name of the customer/employee
   -Stores the ID of the customer/employee
   -Password of the customer/employee
   -Customer/Employee record (when the customer/employee is registered, the customer/employee record=15 is stored)
3. Manager Database
   -Stores the name of the manager
   -Stores the ID of the manager
   -Stores the password of the manager
