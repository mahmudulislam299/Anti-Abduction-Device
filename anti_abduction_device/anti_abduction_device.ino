 /* Mahmudul Islam
 * EEE,Bangladesh University of Engineering and Technology (BUET)
 * Email: mahmudulislam299@gmail.com
 */
 
const int flexPin = A0; //pin A0 to read analog input
char phone_no[] = "+880*********";  //phone number to alert

//Variables:
int flexvalue, danger=0, th=140, danger_limit=20; 


void setup(){

  Serial.begin(9600);  //Open Serial connection at baud 9600
  delay(2000);
  Serial.println("AT+CMGF=1"); //set GSM to text mode
  delay(200);
}

void loop()
{
  flexsensor();
}

void flexsensor(){
  
  flexvalue= analogRead(flexPin);         //Read and save analog flexvaluefrom potentiometer
  Serial.println(flexvalue);               //Print value
  
  if(flexvalue<th){
    danger=danger+1;
    Serial.print("   danger==");
    Serial.println(danger);
    }

  if(danger>danger_limit) // danger cross the limit the alert message send
  {
    danger=0;
    Serial.println("alert");
    delay(2000);
    message();
//    delay(3000);
//    Serial.println("phone call ending and sms start to sending");
//    call();
      
  }
  delay(100);                          //Small delay
  
}

void message()
{
 Serial.print("AT+CMGS=\"");
Serial.print(phone_no);
Serial.println("\"");

delay(1000);  // delay is must it waits for > symbol

Serial.print("user in danger.");  //SMS body
Serial.write(0x1A);  // sends ctrl+z end of message
//Serial.write(0x0D);  // Carriage Return in Hex
//Serial.write(0x0A);  // Line feed in Hex

//The 0D0A pair of characters is the signal for the end of a line and beginning of another.
delay(1000); 
}


void call(){
  delay(500);
  Serial.print("ATD");; //Dial the phone number using ATD command
  Serial.print(phone_no);
  Serial.println(";"); // Semicolon is a must at the end
  delay(12000);
  Serial.println("ATH"); // After a delay of 5 secs Hang the call
  
}
