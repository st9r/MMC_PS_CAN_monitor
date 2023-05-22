#include <SPI.h>
#include <mcp2515.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 32 

#define OLED_RESET     -1 
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

float temp_at;
float temp_engine1;
float temp_engine2;
struct can_frame canMsg;
MCP2515 mcp2515(10);


int buttonPin = 3; // Change this to the pin number that you used to connect the TTP223 sensor
int buttonState = LOW;
int currentPage = 1; // The current display page

void setup() {
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); 
  }

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(8, 0);
  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);
  mcp2515.setListenOnlyMode(); //set MCP2515 to listen only mode //
  display.println("Mitsubishi");
  display.setTextSize(1);
  display.setCursor(28, 20);
  display.println("Loading....");
  display.display();
  delay(2000); 
  display.clearDisplay();
  Serial.println("------- CAN Read ----------");
  Serial.println("ID  DLC   DATA");
  
  pinMode(buttonPin, INPUT); // Set the button pin as an input
}


void displayPage1() {
  display.clearDisplay();
  display.setCursor(0, 5);
  display.setTextSize(1);
  display.println("Transmission");
  display.setTextSize(1);
  display.println("temperature");
  display.setTextSize(2.5);
  display.setCursor(79, 5);
  display.println(temp_at, 0);
   display.setTextSize(1);
  display.setCursor(79, 20);
  display.println("deg. C");
  display.display();
}

void displayPage2() {
  display.clearDisplay();
  display.setCursor(0, 5);
  display.setTextSize(2);
  display.println("ENGINE");
  display.setTextSize(1);
  display.println("from ECU");
  display.setTextSize(2.5);
  display.setCursor(79, 5);
  display.println(temp_engine1, 0);
  display.setTextSize(1);
  display.setCursor(79, 20);
  display.println("deg. C");
  display.display();
}

void displayPage3() {
  display.clearDisplay();
  display.setCursor(0, 5);
  display.setTextSize(2);
  display.println("ENGINE");
  display.setTextSize(1);
  display.println("from meter");
  display.setTextSize(2.5);
  display.setCursor(79, 5);
  display.println(temp_engine2, 0);
  display.setTextSize(1);
  display.setCursor(79, 20);
  display.println("deg. C");
  display.display();
}
  
void displayPage4() {

display.clearDisplay();
display.setTextSize(1);
display.setTextColor(WHITE);
display.setCursor(0, 1);
display.println("AT");
display.setCursor(83, 1);
display.println(temp_at, 0);
display.setCursor(0, 13);
display.println("ENGINE 0x14D");
display.setCursor(83, 13);
display.println(temp_engine1, 0);
display.setCursor(0, 25);
display.println("ENGINE 0x152");
display.setCursor(83, 25);
display.println(temp_engine2, 0);
display.display();
}

void loop() {
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
    Serial.print(canMsg.can_id, HEX); // print ID
    Serial.print(" ");
    Serial.print(canMsg.can_dlc, HEX); // print DLC
    Serial.print(" ");
    
    for (int i = 0; i<canMsg.can_dlc; i++)
      Serial.print(canMsg.data[i],HEX);
      Serial.print(" ");
    }

    if (canMsg.can_id == 0x14D)
    {
      temp_engine1 = (canMsg.data[5]);
      temp_engine1 = temp_engine1 - 40;
    }
    if (canMsg.can_id == 0x152)
    {
      temp_engine2 = (canMsg.data[5]);
      temp_engine2 = temp_engine2 - 40;
    }
    if (canMsg.can_id == 0x1B1)
    {
      temp_at = (canMsg.data[4]);
      temp_at = temp_at - 40;
    }
    

    int newButtonState = digitalRead(buttonPin);


  if (newButtonState != buttonState) {
    // Update the button state variable
    buttonState = newButtonState;

    if (buttonState == HIGH) {
      currentPage++;
      if (currentPage > 6) {
        currentPage = 1;
      }
    }
  }

  // Display the current page
  switch (currentPage) {
    case 2:
      displayPage1();
      break;
    case 1:
      displayPage2();
      break;
    case 3:
      displayPage3();
      break;
    case 4:
      displayPage4();
      break;
    case 5:
      display.clearDisplay();
      display.setTextSize(1.5);
      display.setTextColor(WHITE);
      display.setCursor(10, 15);
      display.println("Display OFF");
      display.display();
      delay(2000); 
      display.clearDisplay();
      display.display();
      currentPage = 6;
      break;
    case 6:
      display.clearDisplay();
      display.display();
      break;
  }
    Serial.println();      
  } 