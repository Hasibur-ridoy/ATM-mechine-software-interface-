#include <Wire.h>
#include <LiquidCrystal.h>
#include <Keypad.h>

const byte ROWS = 4;          //four rows for the keypad
const byte COLS = 3;          //four columns for the keypad
char PIN_DB[2][4] = {"1234"}; //database for the PINs
char PIN[4];                  //stores the input PIN
char key;                     //stores the last pressed key
int i = 0;                    //PIN digit count
int balance = 82854;

char keys[ROWS][COLS] =
    {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'},
        {'*', '0', '#'}};

byte rowPins[ROWS] = {4, 5, 6, 7}; //assigns Arduino pins to the row pinouts of the keypad
byte colPins[COLS] = {1, 2, 3};    //assigns Arduino pins to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS); //instantiates a Keypad object

const int rs = 8, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13; //assigns Arduino pins to the pinouts of the LCD

LiquidCrystal lcd(rs, en, d4, d5, d6, d7); //creates a variable of type LiquidCrystal

void setup() //Arduio function to initialize variables, pin modes, start using libraries, etc. Runs only once, after each powerup or reset
{
    lcd.begin(20, 4);                 //initializes the interface to the LCD screen, and specifies the dimensions (col, row)
    lcd.setCursor(0, 0);              //positions the LCD cursor
    lcd.print("Welcome to RSi Bank"); //prints the message on the LCD screen
    delay(1000);
    lcd.setCursor(0, 0);

    for (int j = 0; j < 20; j++)
    {
        lcd.scrollDisplayLeft(); //scrolls the contents of the display one space to the left.
        delay(100);
    }

    lcd.clear();
}

void loop() //this is the main function of the Arduino; loops consecutively, allowing the program to change and respond
{
    while (true)
    {
    inputPIN:
        lcd.setCursor(0, 0);
        lcd.print("Enter your PIN: ");
        delay(50);

        char key = keypad.getKey();

        if (key)
        {
            lcd.setCursor(i, 1);
            delay(100);

            PIN[i] = key;
            lcd.print(PIN[i]);
            i++;

            if (i == 4)
            {
                delay(1000);
                lcd.clear();
                delay(1000);

                //PIN validation
                if ((PIN[0] == PIN_DB[0][0]) && (PIN[1] == PIN_DB[0][1]) && (PIN[2] == PIN_DB[0][2]) && (PIN[3] == PIN_DB[0][3]))
                {
                    lcd.print("Welcome, Mr. Hasib");
                    delay(1000);

                    while (true)
                    {
                        lcd.clear();
                        delay(500);
                        lcd.print("1 - Withdrawal");
                        lcd.setCursor(0, 1);
                        lcd.print("2 - Deposit");
                        lcd.setCursor(0, 2);
                        lcd.print("3 - Balance Inquiry");
                        lcd.setCursor(0, 3);
                        lcd.print("4 - Log Out");
                        delay(500);

                        lcd.setCursor(0, 0);

                        while (true)
                        {
                            char key = keypad.getKey();
                            if (key)
                            {
                                if (key != NO_KEY)
                                {
                                    if (key == '1') //code for withdrawal operation
                                    {
                                        lcd.clear();
                                        lcd.print("Select the amount: ");
                                        delay(500);
                                        lcd.setCursor(0, 1);
                                        lcd.print("1- $100");
                                        lcd.setCursor(0, 2);
                                        lcd.print("2- $200");
                                        lcd.setCursor(0, 3);
                                        lcd.print("3- $3000");
                                        lcd.setCursor(11, 1);
                                        lcd.print("4- $400");
                                        lcd.setCursor(11, 2);
                                        lcd.print("5- $500");
                                        lcd.setCursor(11, 3);
                                        lcd.print("6- Other");
                                        //delay(5000);
                                        while (true)
                                        {
                                            char key = keypad.getKey();
                                            if (key)
                                            {
                                                if (key != NO_KEY)
                                                {
                                                    String s = "";
                                                    if (key > '0' && key <= '5')
                                                    {
                                                        s += key;
                                                        int a = s.toInt();
                                                        balance -= (a * 100);
                                                        lcd.clear();
                                                        lcd.print("Processing...");
                                                        delay(2000);
                                                        lcd.clear();
                                                    }
                                                    else
                                                    {
                                                        lcd.clear();
                                                        lcd.print("Enter the amount: ");
                                                        lcd.setCursor(0, 3);
                                                        lcd.print("Enter '#' when done.");
                                                        int j = 0;
                                                        while (true)
                                                        {
                                                            char key = keypad.getKey();
                                                            if (key)
                                                            {
                                                                lcd.setCursor(j, 1);
                                                                lcd.print(key);
                                                                s += key;
                                                                j++;

                                                                if (key == '#')
                                                                {
                                                                    int a = s.toInt();
                                                                    balance -= a;
                                                                    lcd.clear();
                                                                    lcd.print("Processing...");
                                                                    delay(2000);
                                                                    lcd.clear();

                                                                    break;
                                                                }
                                                            }
                                                        }
                                                    }
                                                    break;
                                                }
                                            }
                                        }
                                        break;
                                    }

                                    if (key != NO_KEY)
                                    {
                                        if (key == '2') //code for deposit operation
                                        {
                                            lcd.clear();
                                            lcd.print("Enter the amount: ");
                                            lcd.setCursor(0, 3);
                                            lcd.print("Enter '#' when done.");
                                            String s = "";
                                            int j = 0;
                                            while (true)
                                            {
                                                char key = keypad.getKey();
                                                if (key)
                                                {
                                                    lcd.setCursor(j, 1);
                                                    lcd.print(key);
                                                    s += key;
                                                    j++;

                                                    if (key == '#')
                                                    {
                                                        int a = s.toInt();
                                                        balance += a;
                                                        lcd.clear();
                                                        lcd.print("Processing...");
                                                        delay(2000);
                                                        lcd.clear();

                                                        break;
                                                    }
                                                }
                                            }
                                            break;
                                        }

                                        if (key != NO_KEY)
                                        {
                                            if (key == '3') //code for balance check operation
                                            {
                                                String s = "";
                                                s += balance;

                                                lcd.clear();
                                                lcd.print("Please wait...");
                                                delay(2000);
                                                lcd.clear();
                                                lcd.print("Balance:");
                                                delay(500);
                                                lcd.setCursor(9, 0);
                                                lcd.print(s);
                                                delay(2000);
                                                lcd.clear();

                                                break;
                                            }

                                            if (key != NO_KEY)
                                            {
                                                if (key == '4') //code for logging out operation
                                                {
                                                    lcd.clear();
                                                    delay(500);
                                                    lcd.print("Please take out your");
                                                    lcd.setCursor(0, 1);
                                                    lcd.print(" card.");
                                                    delay(2000);
                                                    lcd.clear();
                                                    delay(500);
                                                    lcd.setCursor(5, 1);
                                                    lcd.print("Thank you");
                                                    lcd.setCursor(1, 2);
                                                    lcd.print("for being with us.");
                                                    delay(1000);
                                                    lcd.clear();
                                                    delay(2000);

                                                    i = 0; //resets the counter for the current session
                                                    goto inputPIN;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                else //following code executes when the input PIN is incorrect
                {
                    lcd.print("Incorrect PIN.");
                    delay(2000);
                    lcd.clear();
                    delay(1000);
                }

                i = 0; //resets the counter for the current session
                break;
            }
        }
    }
}
