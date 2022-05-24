// Initialising each component with a pin
const int FSR = A0; 
int buzzer = 10;
int button = 2;
int flag = 0; // to reset the system
int FSR_value; // to store the FSR value
int buttonState;
String password = "12345678";
String pwd;

void setup () {
  pinMode (buzzer, OUTPUT); // buzzer is an output device
  pinMode (button, INPUT); // button is an input device
  Serial.begin(9600);
}

void loop () {
  if( flag==0 ){ // when the button is not pressed yet
    buttonState = digitalRead(button);
    if(buttonState == HIGH){
      Serial.print ("Button - High");
    }
    FSR_value = analogRead(FSR); //reading value from sensor
    if (FSR_value == 0) // there is an object present above the sensor
    {
      analogWrite (buzzer, LOW);
      delay (100);
      analogWrite (buzzer, LOW);
      delay (100); 
    } 
    else //object has been taken away, buzzer starts to ring
    {
      analogWrite (buzzer, HIGH);
    }
    //Serial.print ("\nFSR value: ");
    Serial.print ("\n");
    Serial.print (FSR_value);
    delay(100);
  }
  if(buttonState == HIGH){ // wants to stop the system
    // enter the correct password into the serial monitor
    Serial.println("\t\tARTEFACT SECURITY SYSTEM");
    Serial.println("\n\nUser is trying to stop the system...");
    Serial.println("\n\nEnter password: ");
    while(Serial.available()==0){}
    pwd = Serial.readString(); //gets input in serial monitor
    if(password==pwd){ // if password matches, stop the system
      FSR_value = 0;
      flag = 1;    //stop occurs by setting up the flag
      analogWrite (buzzer, LOW);
      delay (100);
      analogWrite (buzzer, LOW);
      delay (100);
    }
    else{ //password mismatch condition
      Serial.println("\nPassword inputted mismatch!");
      Serial.println("\nPress the stop button again to retry...");      
    }  
  }
}
