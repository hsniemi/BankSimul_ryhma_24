# BankSimul_ryhma_24
This project was a part of a school course software Development application project. 
Memebers of the project group were: Tuomas Lammassaari, Henna Niemi, Tomi Lakkakorpi.
The project goal was to make a demo program of an Automated Teller Machine (ATM). 

### Objectives
The baseline goal for the project was to create a demo version of an ATM with all 
the functions that a normal ATM has. This includes ability to check your balance, 
check previous transactions, withdraw cash and the ability to transfer money to another person.
For the demo project the team was given an RFID reader and cards to simulate a bank card reader and bank cards. 
A secondary goal for the team with the project was to expand their knowledge on creating 
software using the evolutionary development method (EVO) and also to learn how to work as a team on a project and 
learning how to communicate with others to prevent confusion and misunderstandings.


<figure>
  <img src="readme_images/banksimul_rfid_reader.jpg" alt="" width="300">
  <figcaption> FIGURE 2. RFID reader and cards </figcaption>
</figure>


<figure>
    <img src="readme_images/banksimul_activity_diagram.jpg" alt="" style="width:100%">
    <figcaption align = "start"><b>FIGURE 3. Activity Diagram</b></figcaption>
</figure>

### Results
The system worked as intended and it fully meets the goals of the customer.  When a customer 
goes to the ATM the system first asks for the customer's bank card. If the system recognizes the card 
from the database, it will proceed to ask the PIN code for the card. If the customer 
types the code incorrectly three times, the system will tell the customer the PIN code is incorrect 
and it will return to the log in screen. The customers bank account and bank card will also get locked if
the PIN code is typed wrong three times. If the customer gets the PIN correctly, the system will proceed 
into the main window of the ATM, where the customer can proceed to withdraw cash, transfer money, 
check previous transactions or check their balance. After the customer has finished using the ATM the customer 
will press the log out button which will make the system return to the main screen for the next customer to use the system.

### Conclusions
Currently the system is operating correctly and is fully functional, although it could use some visual improvements 
for the user interface. The project provided a good understanding on how a banking system operates, 
and we think we succeeded in our project quite well.