##AUTO SMS GSM MODEM VEHICLE SECURITY
This Project is about Realizing a Automatic Vehicle Lock System.I have used ATMega8 IC and the code is written in Embedded C.For dumping the Hex File I have used the eXtreme Burner AVR.The circuit diagram and the Flowchart for the project is given below.

You can get the Circuit diagram,flowchart, Output Srceens and relevant documents in this [link](https://goo.gl/kAao1w).

#Building the Code
I have used the Atmel Studio IDE for writing and building the code.To create the project follow these steps.
1. Open Atmel studio and go to **File -> New -> Project**
2. Select **GCC C Executable Project** and Give a suitable name and solution Name in the Space given below.Suppose Engine as I have used
3. Select OK
4. You will be asked to Select a Device.Search **ATMega8** and Click OK
5. Then Copy The Contents of **Engine.c** in my project to your Generated c file
6. Copy paste other Files into your Application directory.
7. Then Right Click on the Project file in the Solution Explorer that is shown with a dropdown menu.Select **Add -> Existing Item**
8. Select all the header files and c files and Click OK

Now you are ready to get started.For building and generating the hex file follow these steps
1. Go to Menu bar and Select **Build -> Build Solution** or **Press F7**
2. The Output below will show Build successfully if there are no syntactical errors.

You will find the hex file in the Debug folder of your Application folder.
