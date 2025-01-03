//States
const int stSwitchedOff = 0;
const int stSwitchedOn = 1;
const int stOperating = 2;

//Event types
enum EventType {OnSwitchOn, OnSwitchOff, OnCardRead, OnPay, OnTimeElapsed, OnPauseClick, OnWaterClick, OnFoamClick, OnClick3};

//LEDs
enum OperatingLights : byte
{
  SWITCH_ON_LED = 1,
  SWITCH_OFF_LED = 2,
  PAUSE_LED = 3,
  WATERING_LED = 4,
  FOAMING_LED = 5,
  CLICK3_LED = 6
};

//function pointer type
typedef void (* pStateHandler)(EventType);

pStateHandler StateHandlers[3];

int currentState;
String cardId;
float balance;
int leftTime;

float prise;
int duraion;

EventType eventType;

float Getbalance(String cardId)
{
  return 0;
}

void TurnOnLEDs(int pattern)
{
  if(pattern & 1 > 0)
    digitalWrite(SWITCH_OFF_LED, HIGH);
  else
    digitalWrite(SWITCH_OFF_LED, LOW);

  if(pattern & 2 > 0)
    digitalWrite(SWITCH_ON_LED, HIGH);
  else
    digitalWrite(SWITCH_ON_LED, LOW);

  if(pattern & 4 > 0)
    digitalWrite(PAUSE_LED, HIGH);
  else
    digitalWrite(PAUSE_LED, LOW);

  if(pattern & 8 > 0)
    digitalWrite(WATERING_LED, HIGH);
  else
    digitalWrite(WATERING_LED, LOW);

  if(pattern & 16 > 0)
    digitalWrite(FOAMING_LED, HIGH);
  else
    digitalWrite(FOAMING_LED, LOW);

  if(pattern & 32 > 0)
    digitalWrite(CLICK3_LED, HIGH);
  else
    digitalWrite(CLICK3_LED, LOW);
}

void DoSwitchOff()
{
  cardId = "";
  balance = 0;
  leftTime = 0;

  TurnOnLEDs(1);
}

void DoSwitchOn()
{
  cardId = "";
  balance = 0;
  leftTime = 0;

  TurnOnLEDs(2);
}

void DoCardReading()
{
  cardId = "";
  balance + Getbalance(cardId);
}

void DoPaying()
{
  balance + prise;
}

void DoTimeElapsing()
{
  leftTime = 0;
}

void DoPause()
{
  TurnOnLEDs(4);
}

void DoWatering()
{
  balance = balance - prise;
  leftTime = duraion;

  TurnOnLEDs(8);
}

void DoFoaming()
{
  balance = balance - prise;
  leftTime = duraion;

  TurnOnLEDs(16);
}

void DoClicking3()
{
  balance = balance - prise;
  leftTime = duraion;

  TurnOnLEDs(32);
}

void DoError()
{

}

void setup() 
{
  pinMode(SWITCH_ON_LED, OUTPUT);
  pinMode(SWITCH_OFF_LED, OUTPUT);
  pinMode(PAUSE_LED, OUTPUT);
  pinMode(WATERING_LED, OUTPUT);
  pinMode(FOAMING_LED, OUTPUT);
  pinMode(CLICK3_LED, OUTPUT);

  StateHandlers[0] = SwitchedOff_StateHandler;
  StateHandlers[1] = SwitchedOn_StateHandler;
  StateHandlers[2] = Oprating_StateHandler;
  
  DoSwitchOff();
  currentState = stSwitchedOff;
}

void loop() 
{
  while(true)
  {
    StateHandlers[currentState](eventType);
  }
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------

void SwitchedOff_StateHandler(EventType eventType)
{
  switch(eventType)
  {
    case OnSwitchOn: 
        {
          DoSwitchOn();
          currentState = stSwitchedOn;
        }    
    break;
    
    default: DoError();
  } 
}

void SwitchedOn_StateHandler(EventType eventType)
{
  switch(eventType)
  {
    case OnCardRead: 
        {
          DoCardReading();
          //currentState = The Same;
        }    
    break;

    case OnPay: 
        {
          DoPaying();
          //currentState = The Same;
        }    
    break;
      
    case OnWaterClick: 
        {
          DoWatering();
          currentState = stOperating;
        }    
    break;
    
    case OnFoamClick: 
        {
          DoFoaming();
          currentState = stOperating;
        }    
    break;
    
    case OnClick3: 
        {
          DoClicking3();
          currentState = stOperating;
        }    
    break;

    case OnSwitchOff:
        {
          DoSwitchOff();
          currentState = stSwitchedOff;
        }    
    break;

    default: DoError();
  } 
}

void Oprating_StateHandler(EventType eventType)
{
  switch(eventType)
  {
    case OnCardRead: 
        {
          DoCardReading();
          //currentState = The Same;
        }    
    break;

    case OnPay: 
        {
          DoPaying();
          //currentState = The Same;
        }    
    break;

    case OnTimeElapsed: 
        {
          DoTimeElapsing();
          currentState = stSwitchedOn;
        }    
    break;
    
    case OnPauseClick: 
        {
          DoPause();
          currentState = stSwitchedOn;
        }    
    break;

    case OnSwitchOff:
        {
          DoSwitchOff();
          currentState = stSwitchedOff;
        }    
    break;

    default: DoError();
  }
}

